// coding: utf-8
/* Copyright (c) 2011-2013, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

#include <xpcc/debug/error_report.hpp>
#include <xpcc/architecture/driver/atomic/queue.hpp>
#include <xpcc/utils.hpp>

#include "can_2.hpp"
#include <xpcc_config.hpp>

// ----------------------------------------------------------------------------
// CAN bit timing register (CAN_BTR)
#define CAN_BTR_SJW_POS		24
#define CAN_BTR_TS2_POS		20
#define CAN_BTR_TS1_POS		16

// ----------------------------------------------------------------------------
static xpcc::atomic::Queue<xpcc::can::Message, 32> txQueue;
static xpcc::atomic::Queue<xpcc::can::Message, 32> rxQueue;
// ----------------------------------------------------------------------------
// Re-implemented here to save some code space. As all arguments in the calls
// below are constant the compiler is able to calculate everything at
// compile time.
static xpcc_always_inline void
nvicEnableInterrupt(IRQn_Type IRQn)
{
	NVIC->ISER[((uint32_t)(IRQn) >> 5)] = (1UL << ((uint32_t)(IRQn) & 0x1F));
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Can2::initializeWithPrescaler(
		uint16_t prescaler, uint8_t bs1, uint8_t bs2,
		uint32_t interruptPriority, Mode startupMode, bool overwriteOnOverrun)
{
	// enable clock
	RCC->APB1ENR  |=  RCC_APB1ENR_CAN2EN;

	// reset controller
	RCC->APB1RSTR |=  RCC_APB1RSTR_CAN2RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_CAN2RST;

	// CAN Master Reset
	// FMP bits and CAN_MCR register are initialized to the reset values
	CAN2->MCR |= CAN_MCR_RESET;
	while (CAN2->MCR & CAN_MCR_RESET)
		;

	// Exit from sleep mode
	CAN2->MCR &= (~(uint32_t)CAN_MCR_SLEEP);

	// Bus off is left automatically by the hardware after 128 occurrences
	// of 11 recessive bits, TX Order depends on the order of request and
	// not on the CAN priority.
	if (overwriteOnOverrun) {
		CAN2->MCR |= CAN_MCR_ABOM | CAN_MCR_TXFP;
	}
	else {
		// No overwrite at RX FIFO: Once a receive FIFO is full the next
		// incoming message will be discarded
		CAN2->MCR |= CAN_MCR_ABOM | CAN_MCR_RFLM | CAN_MCR_TXFP;
	}

	// Request initialization
	CAN2->MCR |= CAN_MCR_INRQ;
	while ((CAN2->MSR & CAN_MSR_INAK) == 0) {
		// Wait until the initialization mode is entered.
		// The CAN hardware waits until the current CAN activity (transmission
		// or reception) is completed before entering the initialization mode.
	}

	// Enable Interrupts:
	// FIFO1 Overrun, FIFO0 Overrun
	CAN2->IER = CAN_IER_FOVIE1 | CAN_IER_FOVIE0;

	CAN2->IER |= CAN_IER_TMEIE;
	// Set vector priority
	NVIC_SetPriority(CAN2_RX0_IRQn, interruptPriority);
	NVIC_SetPriority(CAN2_RX1_IRQn, interruptPriority);

	// Register Interrupts at the NVIC
	nvicEnableInterrupt(CAN2_RX0_IRQn);
	nvicEnableInterrupt(CAN2_RX1_IRQn);

	nvicEnableInterrupt(CAN2_TX_IRQn);
	NVIC_SetPriority(CAN2_TX_IRQn, interruptPriority);
	CAN2->IER |= CAN_IER_FMPIE1 | CAN_IER_FMPIE0;
	CAN2->BTR =
			  ((1 - 1) << CAN_BTR_SJW_POS) |		// SJW (1 to 4 possible)
			((bs2 - 1) << CAN_BTR_TS2_POS) |		// BS2 Samplepoint
			((bs1 - 1) << CAN_BTR_TS1_POS) |		// BS1 Samplepoint
			static_cast<uint32_t>(startupMode) |
			(prescaler - 1);

	// Request leave initialization
	CAN2->MCR &= ~(uint32_t)CAN_MCR_INRQ;
	while ((CAN2->MSR & CAN_MSR_INAK) == CAN_MSR_INAK) {
		// wait for the normal mode
	}

	return;
}

// ----------------------------------------------------------------------------
// Configure the mailbox to send a CAN message.
// Low level function called by sendMessage and by Tx Interrupt.
static void
sendMailbox(const xpcc::can::Message& message, uint32_t mailboxId)
{
	CAN_TxMailBox_TypeDef* mailbox = &CAN2->sTxMailBox[mailboxId];
	
	if (message.isExtended()) {
		mailbox->TIR = message.identifier << 3 | CAN_TI0R_IDE;
	}
	else {
		mailbox->TIR = message.identifier << 21;
	}
	
	if (message.isRemoteTransmitRequest()) {
		mailbox->TIR |= CAN_TI0R_RTR;
	}
	
	// Set up the DLC
	mailbox->TDTR = message.getLength();
	
	// Set up the data field (copy the 8x8-bits into two 32-bit registers)
	const uint8_t * xpcc_may_alias data = message.data;
	mailbox->TDLR = reinterpret_cast<const uint32_t *>(data)[0];
	mailbox->TDHR = reinterpret_cast<const uint32_t *>(data)[1];
	
	// Request transmission
	mailbox->TIR |= CAN_TI0R_TXRQ;
}

// ----------------------------------------------------------------------------
// Low level function to receive a message from mailbox.
// Called by Rx Interrupt or by getMessage.
static void
readMailbox(xpcc::can::Message& message, uint32_t mailboxId)
{
	CAN_FIFOMailBox_TypeDef* mailbox = &CAN2->sFIFOMailBox[mailboxId];
	
	uint32_t rir = mailbox->RIR;
	if (rir & CAN_RI0R_IDE) {
		message.identifier = rir >> 3;
		message.setExtended();
	}
	else {
		message.identifier = rir >> 21;
		message.setExtended(false);
	}
	message.setRemoteTransmitRequest(rir & CAN_RI0R_RTR);
	
	message.length = mailbox->RDTR & CAN_TDT1R_DLC;
	
	uint8_t * xpcc_may_alias data = message.data;
	reinterpret_cast<uint32_t *>(data)[0] = mailbox->RDLR;
	reinterpret_cast<uint32_t *>(data)[1] = mailbox->RDHR;
}

// ----------------------------------------------------------------------------
/* Transmit Interrupt
 *
 * Generated when Transmit Mailbox 0..2 becomes empty.
 */
extern "C" void
CAN2_TX_IRQHandler()
{
	uint32_t mailbox;
	uint32_t tsr = CAN2->TSR;
	
	if (tsr & CAN_TSR_RQCP2) {
		mailbox = 2;
		CAN2->TSR = CAN_TSR_RQCP2;
	}
	else if (tsr & CAN_TSR_RQCP1) {
		mailbox = 1;
		CAN2->TSR = CAN_TSR_RQCP1;
	}
	else {
		mailbox = 0;
		CAN2->TSR = CAN_TSR_RQCP0;
	}
	
	if (!txQueue.isEmpty())
	{
		sendMailbox(txQueue.get(), mailbox);
		txQueue.pop();
	}
}

// ----------------------------------------------------------------------------
/* FIFO0 Interrupt
 *
 * Generated on a new received message, FIFO0 full condition and Overrun
 * Condition.
 */
extern "C" void
CAN2_RX0_IRQHandler()
{
	if (CAN2->RF0R & CAN_RF0R_FOVR0) {
		xpcc::ErrorReport::report(xpcc::stm32::CAN2_FIFO0_OVERFLOW);
		
		// release overrun flag & access the next message
		CAN2->RF0R = CAN_RF0R_FOVR0 | CAN_RF0R_RFOM0;
	}
	
	xpcc::can::Message message;
	readMailbox(message, 0);
	
	// Release FIFO (access the next message)
	CAN2->RF0R = CAN_RF0R_RFOM0;
	
	if (!rxQueue.push(message)) {
		xpcc::ErrorReport::report(xpcc::stm32::CAN2_FIFO0_OVERFLOW);
	}
}

// ----------------------------------------------------------------------------
/* FIFO1 Interrupt
 *
 * See FIFO0 Interrupt
 */
extern "C" void
CAN2_RX1_IRQHandler()
{
	if (CAN2->RF1R & CAN_RF1R_FOVR1) {
		xpcc::ErrorReport::report(xpcc::stm32::CAN2_FIFO1_OVERFLOW);
		
		// release overrun flag & access the next message
		CAN2->RF1R = CAN_RF1R_FOVR1 | CAN_RF1R_RFOM1;
	}
	
	xpcc::can::Message message;
	readMailbox(message, 1);
	
	// Release FIFO (access the next message)
	CAN2->RF1R = CAN_RF1R_RFOM1;
	
	if (!rxQueue.push(message)) {
		xpcc::ErrorReport::report(xpcc::stm32::CAN2_FIFO1_OVERFLOW);
	}
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Can2::setMode(Mode mode)
{
	// Request initialization
	CAN2->MCR |= CAN_MCR_INRQ;
	while ((CAN2->MSR & CAN_MSR_INAK) == 0) {
		// Wait until the initialization mode is entered.
		// The CAN hardware waits until the current CAN activity (transmission
		// or reception) is completed before entering the initialization mode.
	}

	CAN2->BTR = (CAN2->BTR & ~(CAN_BTR_SILM | CAN_BTR_LBKM))
						| static_cast<uint32_t>(mode);

	// Leave initialization mode
	CAN2->MCR &= ~CAN_MCR_INRQ;
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Can2::setAutomaticRetransmission(bool retransmission)
{
	if (retransmission) {
		// Enable retransmission
		CAN2->MCR = (CAN2->MCR & ~CAN_MCR_NART);
	} else {
		// Disable retransmission
		CAN2->MCR = (CAN2->MCR | CAN_MCR_NART);
	}
}

// ----------------------------------------------------------------------------
bool
xpcc::stm32::Can2::isMessageAvailable()
{
	return !rxQueue.isEmpty();
}

// ----------------------------------------------------------------------------
bool
xpcc::stm32::Can2::getMessage(can::Message& message)
{
	if (rxQueue.isEmpty())
	{
		// no message in the receive buffer
		return false;
	}
	else {
		memcpy(&message, &rxQueue.get(), sizeof(message));
		rxQueue.pop();
		return true;
	}
}

// ----------------------------------------------------------------------------
bool
xpcc::stm32::Can2::isReadyToSend()
{
	return txQueue.isNotFull();
}

// ----------------------------------------------------------------------------
bool
xpcc::stm32::Can2::sendMessage(const can::Message& message)
{
	// This function is not reentrant. If one of the mailboxes is empty it
	// means that the software buffer is empty too. Therefore the mailbox
	// will stay empty and won't be taken by an interrupt.
	if ((CAN2->TSR & (CAN_TSR_TME0 | CAN_TSR_TME1 | CAN_TSR_TME2)) == 0)
	{
		// All mailboxes used at the moment
		if (!txQueue.push(message)) {
			xpcc::ErrorReport::report(xpcc::stm32::CAN2_TX_OVERFLOW);
			return false;
		}
		return true;
	}
	else {
		// Get number of the first free mailbox
		uint32_t mailbox = (CAN2->TSR & CAN_TSR_CODE) >> 24;
		
		sendMailbox(message, mailbox);
		return true;
	}
}

// ----------------------------------------------------------------------------
xpcc::stm32::Can2::BusState
xpcc::stm32::Can2::getBusState()
{
	if (CAN2->ESR & CAN_ESR_BOFF) {
		return BusState::Off;
	}
	else if (CAN2->ESR & CAN_ESR_BOFF) {
		return BusState::ErrorPassive;
	}
	else if (CAN2->ESR & CAN_ESR_EWGF) {
		return BusState::ErrorWarning;
	}
	else {
		return BusState::Connected;
	}
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Can2::enableStatusChangeInterrupt(
		uint32_t interruptEnable,
		uint32_t interruptPriority)
{
	NVIC_SetPriority(CAN2_SCE_IRQn, interruptPriority);
	nvicEnableInterrupt(CAN2_SCE_IRQn);

	CAN2->IER = interruptEnable | (CAN2->IER & 0x000000ff);
}