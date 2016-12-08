// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------


#ifndef XPCC_STM32_UARTHAL_3_HPP
#	error 	"Don't include this file directly, use" \
#			"'usart_hal_3.hpp' instead!"
#endif

// ----------------------------------------------------------------------------
void
xpcc::stm32::UsartHal3::setParity(const Parity parity)
{
	uint32_t flags = USART3->CR1;
	flags &= ~(USART_CR1_PCE | USART_CR1_PS | USART_CR1_M);
	flags |= static_cast<uint32_t>(parity);
	if (parity != Parity::Disabled) {
		// Parity Bit counts as 9th bit -> enable 9 data bits
		flags |= USART_CR1_M;
	}
	USART3->CR1 = flags;
}

void
xpcc::stm32::UsartHal3::enable()
{
	// FIXME: there seems to be a bug in the stm32f3xxlib which does not provide
	//        the necessary RCC_APB1ENR_UART5EN define and probably defines
	//        RCC_APB1ENR_UART4EN incorrectly (0x00100000 instead of 0x00080000)
	// enable clock
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	// reset uart
	RCC->APB1RSTR |=  RCC_APB1RSTR_USART3RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_USART3RST;
	USART3->CR1 |= USART_CR1_UE;		// Uart Enable
}

void
xpcc::stm32::UsartHal3::disable()
{
	// TX, RX, Uart, etc. Disable
	USART3->CR1 = 0;
	// FIXME: there seems to be a bug in the stm32f3xxlib which does not provide
	//        the necessary RCC_APB1ENR_UART5EN define and probably defines
	//        RCC_APB1ENR_UART4EN incorrectly (0x00100000 instead of 0x00080000)
	// disable clock
	RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN;
}
template<class SystemClock, uint32_t baudrate,
		xpcc::stm32::UsartHal3::OversamplingMode oversample>
void xpcc_always_inline
xpcc::stm32::UsartHal3::initialize(Parity parity)
{
	initializeWithBrr(UartBaudrate::getBrr<SystemClock::Usart3, baudrate>(),
			parity,
			oversample);
}
template<class SystemClock, uint32_t baudrate>
void xpcc_always_inline
xpcc::stm32::UsartHal3::initialize(Parity parity)
{
	initializeWithBrr(UartBaudrate::getBrr<SystemClock::Usart3, baudrate>(), parity,
					  UartBaudrate::getOversamplingMode(SystemClock::Usart3, baudrate));
}


void inline
xpcc::stm32::UsartHal3::initializeWithBrr(uint16_t brr, Parity parity, OversamplingMode oversample)
{
	enable();
	// DIRTY HACK: disable and reenable uart to be able to set
	//             baud rate as well as parity
	USART3->CR1 &= ~USART_CR1_UE;	// Uart Disable
	// set baudrate
	USART3->BRR = brr;
	setParity(parity);
	setOversamplingMode(oversample);
	USART3->CR1 |=  USART_CR1_UE;	// Uart Reenable
}

void
xpcc::stm32::UsartHal3::setOversamplingMode(OversamplingMode mode)
{
	if(mode == OversamplingMode::By16) {
		USART3->CR1 &= ~static_cast<uint32_t>(OversamplingMode::By8);
	} else {
		USART3->CR1 |=  static_cast<uint32_t>(OversamplingMode::By8);
	}
}
void
xpcc::stm32::UsartHal3::setSpiClock(SpiClock clk)
{
	if(clk == SpiClock::Disabled) {
		USART3->CR2 &= ~static_cast<uint32_t>(SpiClock::Enabled);
	} else {
		USART3->CR2 |=  static_cast<uint32_t>(SpiClock::Enabled);
	}
}

void
xpcc::stm32::UsartHal3::setSpiDataMode(SpiDataMode mode)
{
	USART3->CR2 =
		(USART3->CR2 & ~static_cast<uint32_t>(SpiDataMode::Mode3))
		| static_cast<uint32_t>(mode);
}

void
xpcc::stm32::UsartHal3::setLastBitClockPulse(LastBitClockPulse pulse)
{
	if(pulse == LastBitClockPulse::DoNotOutput) {
		USART3->CR2 &= ~static_cast<uint32_t>(LastBitClockPulse::Output);
	} else {
		USART3->CR2 |=  static_cast<uint32_t>(LastBitClockPulse::Output);
	}
}
void
xpcc::stm32::UsartHal3::write(uint8_t data)
{
	USART3->DR = data;
}

void
xpcc::stm32::UsartHal3::read(uint8_t &data)
{
	data = USART3->DR;
}

void
xpcc::stm32::UsartHal3::setTransmitterEnable(const bool enable)
{
	if (enable) {
		USART3->CR1 |=  USART_CR1_TE;
	} else {
		USART3->CR1 &= ~USART_CR1_TE;
	}
}

void
xpcc::stm32::UsartHal3::setReceiverEnable(bool enable)
{
	if (enable) {
		USART3->CR1 |=  USART_CR1_RE;
	} else {
		USART3->CR1 &= ~USART_CR1_RE;
	}
}

bool
xpcc::stm32::UsartHal3::isReceiveRegisterNotEmpty()
{
	return USART3->SR & USART_SR_RXNE;
}

bool
xpcc::stm32::UsartHal3::isTransmitRegisterEmpty()
{
	return USART3->SR & USART_SR_TXE;
}

void
xpcc::stm32::UsartHal3::enableInterruptVector(bool enable, uint32_t priority)
{
	if (enable) {
		// Set priority for the interrupt vector
		NVIC_SetPriority(USART3_IRQn, priority);

		// register IRQ at the NVIC
		NVIC_EnableIRQ(USART3_IRQn);
	}
	else {
		NVIC_DisableIRQ(USART3_IRQn);
	}
}

void
xpcc::stm32::UsartHal3::enableInterrupt(Interrupt_t interrupt)
{
	USART3->CR1 |= interrupt.value;
}

void
xpcc::stm32::UsartHal3::disableInterrupt(Interrupt_t interrupt)
{
	USART3->CR1 &= ~interrupt.value;
}

xpcc::stm32::UsartHal3::InterruptFlag_t
xpcc::stm32::UsartHal3::getInterruptFlags()
{
	return InterruptFlag_t( USART3->SR );
}

void
xpcc::stm32::UsartHal3::acknowledgeInterruptFlags(InterruptFlag_t flags)
{
	/* Interrupts must be cleared manually by accessing SR and DR.
	 * Overrun Interrupt, Noise flag detected, Framing Error, Parity Error
	 * p779: "It is cleared by a software sequence (an read to the
	 * USART_SR register followed by a read to the USART_DR register"
	 */
	if (flags & InterruptFlag::OverrunError) {
		uint32_t tmp;
		tmp = USART3->SR;
		tmp = USART3->DR;
		(void) tmp;
	}
	(void) flags;	// avoid compiler warning
}