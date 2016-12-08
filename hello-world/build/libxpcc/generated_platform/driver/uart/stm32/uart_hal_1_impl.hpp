// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------


#ifndef XPCC_STM32_UARTHAL_1_HPP
#	error 	"Don't include this file directly, use" \
#			"'usart_hal_1.hpp' instead!"
#endif

// ----------------------------------------------------------------------------
void
xpcc::stm32::UsartHal1::setParity(const Parity parity)
{
	uint32_t flags = USART1->CR1;
	flags &= ~(USART_CR1_PCE | USART_CR1_PS | USART_CR1_M);
	flags |= static_cast<uint32_t>(parity);
	if (parity != Parity::Disabled) {
		// Parity Bit counts as 9th bit -> enable 9 data bits
		flags |= USART_CR1_M;
	}
	USART1->CR1 = flags;
}

void
xpcc::stm32::UsartHal1::enable()
{
	// enable clock
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	// reset timer
	RCC->APB2RSTR |=  RCC_APB2RSTR_USART1RST;
	RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;
	USART1->CR1 |= USART_CR1_UE;		// Uart Enable
}

void
xpcc::stm32::UsartHal1::disable()
{
	// TX, RX, Uart, etc. Disable
	USART1->CR1 = 0;
	// disable clock
	RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
}
template<class SystemClock, uint32_t baudrate,
		xpcc::stm32::UsartHal1::OversamplingMode oversample>
void xpcc_always_inline
xpcc::stm32::UsartHal1::initialize(Parity parity)
{
	initializeWithBrr(UartBaudrate::getBrr<SystemClock::Usart1, baudrate>(),
			parity,
			oversample);
}
template<class SystemClock, uint32_t baudrate>
void xpcc_always_inline
xpcc::stm32::UsartHal1::initialize(Parity parity)
{
	initializeWithBrr(UartBaudrate::getBrr<SystemClock::Usart1, baudrate>(), parity,
					  UartBaudrate::getOversamplingMode(SystemClock::Usart1, baudrate));
}


void inline
xpcc::stm32::UsartHal1::initializeWithBrr(uint16_t brr, Parity parity, OversamplingMode oversample)
{
	enable();
	// DIRTY HACK: disable and reenable uart to be able to set
	//             baud rate as well as parity
	USART1->CR1 &= ~USART_CR1_UE;	// Uart Disable
	// set baudrate
	USART1->BRR = brr;
	setParity(parity);
	setOversamplingMode(oversample);
	USART1->CR1 |=  USART_CR1_UE;	// Uart Reenable
}

void
xpcc::stm32::UsartHal1::setOversamplingMode(OversamplingMode mode)
{
	if(mode == OversamplingMode::By16) {
		USART1->CR1 &= ~static_cast<uint32_t>(OversamplingMode::By8);
	} else {
		USART1->CR1 |=  static_cast<uint32_t>(OversamplingMode::By8);
	}
}
void
xpcc::stm32::UsartHal1::setSpiClock(SpiClock clk)
{
	if(clk == SpiClock::Disabled) {
		USART1->CR2 &= ~static_cast<uint32_t>(SpiClock::Enabled);
	} else {
		USART1->CR2 |=  static_cast<uint32_t>(SpiClock::Enabled);
	}
}

void
xpcc::stm32::UsartHal1::setSpiDataMode(SpiDataMode mode)
{
	USART1->CR2 =
		(USART1->CR2 & ~static_cast<uint32_t>(SpiDataMode::Mode3))
		| static_cast<uint32_t>(mode);
}

void
xpcc::stm32::UsartHal1::setLastBitClockPulse(LastBitClockPulse pulse)
{
	if(pulse == LastBitClockPulse::DoNotOutput) {
		USART1->CR2 &= ~static_cast<uint32_t>(LastBitClockPulse::Output);
	} else {
		USART1->CR2 |=  static_cast<uint32_t>(LastBitClockPulse::Output);
	}
}
void
xpcc::stm32::UsartHal1::write(uint8_t data)
{
	USART1->DR = data;
}

void
xpcc::stm32::UsartHal1::read(uint8_t &data)
{
	data = USART1->DR;
}

void
xpcc::stm32::UsartHal1::setTransmitterEnable(const bool enable)
{
	if (enable) {
		USART1->CR1 |=  USART_CR1_TE;
	} else {
		USART1->CR1 &= ~USART_CR1_TE;
	}
}

void
xpcc::stm32::UsartHal1::setReceiverEnable(bool enable)
{
	if (enable) {
		USART1->CR1 |=  USART_CR1_RE;
	} else {
		USART1->CR1 &= ~USART_CR1_RE;
	}
}

bool
xpcc::stm32::UsartHal1::isReceiveRegisterNotEmpty()
{
	return USART1->SR & USART_SR_RXNE;
}

bool
xpcc::stm32::UsartHal1::isTransmitRegisterEmpty()
{
	return USART1->SR & USART_SR_TXE;
}

void
xpcc::stm32::UsartHal1::enableInterruptVector(bool enable, uint32_t priority)
{
	if (enable) {
		// Set priority for the interrupt vector
		NVIC_SetPriority(USART1_IRQn, priority);

		// register IRQ at the NVIC
		NVIC_EnableIRQ(USART1_IRQn);
	}
	else {
		NVIC_DisableIRQ(USART1_IRQn);
	}
}

void
xpcc::stm32::UsartHal1::enableInterrupt(Interrupt_t interrupt)
{
	USART1->CR1 |= interrupt.value;
}

void
xpcc::stm32::UsartHal1::disableInterrupt(Interrupt_t interrupt)
{
	USART1->CR1 &= ~interrupt.value;
}

xpcc::stm32::UsartHal1::InterruptFlag_t
xpcc::stm32::UsartHal1::getInterruptFlags()
{
	return InterruptFlag_t( USART1->SR );
}

void
xpcc::stm32::UsartHal1::acknowledgeInterruptFlags(InterruptFlag_t flags)
{
	/* Interrupts must be cleared manually by accessing SR and DR.
	 * Overrun Interrupt, Noise flag detected, Framing Error, Parity Error
	 * p779: "It is cleared by a software sequence (an read to the
	 * USART_SR register followed by a read to the USART_DR register"
	 */
	if (flags & InterruptFlag::OverrunError) {
		uint32_t tmp;
		tmp = USART1->SR;
		tmp = USART1->DR;
		(void) tmp;
	}
	(void) flags;	// avoid compiler warning
}