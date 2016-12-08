// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------


#ifndef XPCC_STM32_UARTHAL_5_HPP
#	error 	"Don't include this file directly, use" \
#			"'uart_hal_5.hpp' instead!"
#endif

// ----------------------------------------------------------------------------
void
xpcc::stm32::UartHal5::setParity(const Parity parity)
{
	uint32_t flags = UART5->CR1;
	flags &= ~(USART_CR1_PCE | USART_CR1_PS | USART_CR1_M);
	flags |= static_cast<uint32_t>(parity);
	if (parity != Parity::Disabled) {
		// Parity Bit counts as 9th bit -> enable 9 data bits
		flags |= USART_CR1_M;
	}
	UART5->CR1 = flags;
}

void
xpcc::stm32::UartHal5::enable()
{
	// FIXME: there seems to be a bug in the stm32f3xxlib which does not provide
	//        the necessary RCC_APB1ENR_UART5EN define and probably defines
	//        RCC_APB1ENR_UART4EN incorrectly (0x00100000 instead of 0x00080000)
	// enable clock
	RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
	// reset uart
	RCC->APB1RSTR |=  RCC_APB1RSTR_UART5RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_UART5RST;
	UART5->CR1 |= USART_CR1_UE;		// Uart Enable
}

void
xpcc::stm32::UartHal5::disable()
{
	// TX, RX, Uart, etc. Disable
	UART5->CR1 = 0;
	// FIXME: there seems to be a bug in the stm32f3xxlib which does not provide
	//        the necessary RCC_APB1ENR_UART5EN define and probably defines
	//        RCC_APB1ENR_UART4EN incorrectly (0x00100000 instead of 0x00080000)
	// disable clock
	RCC->APB1ENR &= ~RCC_APB1ENR_UART5EN;
}
template<class SystemClock, uint32_t baudrate,
		xpcc::stm32::UartHal5::OversamplingMode oversample>
void xpcc_always_inline
xpcc::stm32::UartHal5::initialize(Parity parity)
{
	initializeWithBrr(UartBaudrate::getBrr<SystemClock::Uart5, baudrate>(),
			parity,
			oversample);
}
template<class SystemClock, uint32_t baudrate>
void xpcc_always_inline
xpcc::stm32::UartHal5::initialize(Parity parity)
{
	initializeWithBrr(UartBaudrate::getBrr<SystemClock::Uart5, baudrate>(), parity,
					  UartBaudrate::getOversamplingMode(SystemClock::Uart5, baudrate));
}


void inline
xpcc::stm32::UartHal5::initializeWithBrr(uint16_t brr, Parity parity, OversamplingMode oversample)
{
	enable();
	// DIRTY HACK: disable and reenable uart to be able to set
	//             baud rate as well as parity
	UART5->CR1 &= ~USART_CR1_UE;	// Uart Disable
	// set baudrate
	UART5->BRR = brr;
	setParity(parity);
	setOversamplingMode(oversample);
	UART5->CR1 |=  USART_CR1_UE;	// Uart Reenable
}

void
xpcc::stm32::UartHal5::setOversamplingMode(OversamplingMode mode)
{
	if(mode == OversamplingMode::By16) {
		UART5->CR1 &= ~static_cast<uint32_t>(OversamplingMode::By8);
	} else {
		UART5->CR1 |=  static_cast<uint32_t>(OversamplingMode::By8);
	}
}
void
xpcc::stm32::UartHal5::write(uint8_t data)
{
	UART5->DR = data;
}

void
xpcc::stm32::UartHal5::read(uint8_t &data)
{
	data = UART5->DR;
}

void
xpcc::stm32::UartHal5::setTransmitterEnable(const bool enable)
{
	if (enable) {
		UART5->CR1 |=  USART_CR1_TE;
	} else {
		UART5->CR1 &= ~USART_CR1_TE;
	}
}

void
xpcc::stm32::UartHal5::setReceiverEnable(bool enable)
{
	if (enable) {
		UART5->CR1 |=  USART_CR1_RE;
	} else {
		UART5->CR1 &= ~USART_CR1_RE;
	}
}

bool
xpcc::stm32::UartHal5::isReceiveRegisterNotEmpty()
{
	return UART5->SR & USART_SR_RXNE;
}

bool
xpcc::stm32::UartHal5::isTransmitRegisterEmpty()
{
	return UART5->SR & USART_SR_TXE;
}

void
xpcc::stm32::UartHal5::enableInterruptVector(bool enable, uint32_t priority)
{
	if (enable) {
		// Set priority for the interrupt vector
		NVIC_SetPriority(UART5_IRQn, priority);

		// register IRQ at the NVIC
		NVIC_EnableIRQ(UART5_IRQn);
	}
	else {
		NVIC_DisableIRQ(UART5_IRQn);
	}
}

void
xpcc::stm32::UartHal5::enableInterrupt(Interrupt_t interrupt)
{
	UART5->CR1 |= interrupt.value;
}

void
xpcc::stm32::UartHal5::disableInterrupt(Interrupt_t interrupt)
{
	UART5->CR1 &= ~interrupt.value;
}

xpcc::stm32::UartHal5::InterruptFlag_t
xpcc::stm32::UartHal5::getInterruptFlags()
{
	return InterruptFlag_t( UART5->SR );
}

void
xpcc::stm32::UartHal5::acknowledgeInterruptFlags(InterruptFlag_t flags)
{
	/* Interrupts must be cleared manually by accessing SR and DR.
	 * Overrun Interrupt, Noise flag detected, Framing Error, Parity Error
	 * p779: "It is cleared by a software sequence (an read to the
	 * USART_SR register followed by a read to the USART_DR register"
	 */
	if (flags & InterruptFlag::OverrunError) {
		uint32_t tmp;
		tmp = UART5->SR;
		tmp = UART5->DR;
		(void) tmp;
	}
	(void) flags;	// avoid compiler warning
}