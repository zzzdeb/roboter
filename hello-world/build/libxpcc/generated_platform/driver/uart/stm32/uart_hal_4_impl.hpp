// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------


#ifndef XPCC_STM32_UARTHAL_4_HPP
#	error 	"Don't include this file directly, use" \
#			"'uart_hal_4.hpp' instead!"
#endif

// ----------------------------------------------------------------------------
void
xpcc::stm32::UartHal4::setParity(const Parity parity)
{
	uint32_t flags = UART4->CR1;
	flags &= ~(USART_CR1_PCE | USART_CR1_PS | USART_CR1_M);
	flags |= static_cast<uint32_t>(parity);
	if (parity != Parity::Disabled) {
		// Parity Bit counts as 9th bit -> enable 9 data bits
		flags |= USART_CR1_M;
	}
	UART4->CR1 = flags;
}

void
xpcc::stm32::UartHal4::enable()
{
	// FIXME: there seems to be a bug in the stm32f3xxlib which does not provide
	//        the necessary RCC_APB1ENR_UART5EN define and probably defines
	//        RCC_APB1ENR_UART4EN incorrectly (0x00100000 instead of 0x00080000)
	// enable clock
	RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
	// reset uart
	RCC->APB1RSTR |=  RCC_APB1RSTR_UART4RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_UART4RST;
	UART4->CR1 |= USART_CR1_UE;		// Uart Enable
}

void
xpcc::stm32::UartHal4::disable()
{
	// TX, RX, Uart, etc. Disable
	UART4->CR1 = 0;
	// FIXME: there seems to be a bug in the stm32f3xxlib which does not provide
	//        the necessary RCC_APB1ENR_UART5EN define and probably defines
	//        RCC_APB1ENR_UART4EN incorrectly (0x00100000 instead of 0x00080000)
	// disable clock
	RCC->APB1ENR &= ~RCC_APB1ENR_UART4EN;
}
template<class SystemClock, uint32_t baudrate,
		xpcc::stm32::UartHal4::OversamplingMode oversample>
void xpcc_always_inline
xpcc::stm32::UartHal4::initialize(Parity parity)
{
	initializeWithBrr(UartBaudrate::getBrr<SystemClock::Uart4, baudrate>(),
			parity,
			oversample);
}
template<class SystemClock, uint32_t baudrate>
void xpcc_always_inline
xpcc::stm32::UartHal4::initialize(Parity parity)
{
	initializeWithBrr(UartBaudrate::getBrr<SystemClock::Uart4, baudrate>(), parity,
					  UartBaudrate::getOversamplingMode(SystemClock::Uart4, baudrate));
}


void inline
xpcc::stm32::UartHal4::initializeWithBrr(uint16_t brr, Parity parity, OversamplingMode oversample)
{
	enable();
	// DIRTY HACK: disable and reenable uart to be able to set
	//             baud rate as well as parity
	UART4->CR1 &= ~USART_CR1_UE;	// Uart Disable
	// set baudrate
	UART4->BRR = brr;
	setParity(parity);
	setOversamplingMode(oversample);
	UART4->CR1 |=  USART_CR1_UE;	// Uart Reenable
}

void
xpcc::stm32::UartHal4::setOversamplingMode(OversamplingMode mode)
{
	if(mode == OversamplingMode::By16) {
		UART4->CR1 &= ~static_cast<uint32_t>(OversamplingMode::By8);
	} else {
		UART4->CR1 |=  static_cast<uint32_t>(OversamplingMode::By8);
	}
}
void
xpcc::stm32::UartHal4::write(uint8_t data)
{
	UART4->DR = data;
}

void
xpcc::stm32::UartHal4::read(uint8_t &data)
{
	data = UART4->DR;
}

void
xpcc::stm32::UartHal4::setTransmitterEnable(const bool enable)
{
	if (enable) {
		UART4->CR1 |=  USART_CR1_TE;
	} else {
		UART4->CR1 &= ~USART_CR1_TE;
	}
}

void
xpcc::stm32::UartHal4::setReceiverEnable(bool enable)
{
	if (enable) {
		UART4->CR1 |=  USART_CR1_RE;
	} else {
		UART4->CR1 &= ~USART_CR1_RE;
	}
}

bool
xpcc::stm32::UartHal4::isReceiveRegisterNotEmpty()
{
	return UART4->SR & USART_SR_RXNE;
}

bool
xpcc::stm32::UartHal4::isTransmitRegisterEmpty()
{
	return UART4->SR & USART_SR_TXE;
}

void
xpcc::stm32::UartHal4::enableInterruptVector(bool enable, uint32_t priority)
{
	if (enable) {
		// Set priority for the interrupt vector
		NVIC_SetPriority(UART4_IRQn, priority);

		// register IRQ at the NVIC
		NVIC_EnableIRQ(UART4_IRQn);
	}
	else {
		NVIC_DisableIRQ(UART4_IRQn);
	}
}

void
xpcc::stm32::UartHal4::enableInterrupt(Interrupt_t interrupt)
{
	UART4->CR1 |= interrupt.value;
}

void
xpcc::stm32::UartHal4::disableInterrupt(Interrupt_t interrupt)
{
	UART4->CR1 &= ~interrupt.value;
}

xpcc::stm32::UartHal4::InterruptFlag_t
xpcc::stm32::UartHal4::getInterruptFlags()
{
	return InterruptFlag_t( UART4->SR );
}

void
xpcc::stm32::UartHal4::acknowledgeInterruptFlags(InterruptFlag_t flags)
{
	/* Interrupts must be cleared manually by accessing SR and DR.
	 * Overrun Interrupt, Noise flag detected, Framing Error, Parity Error
	 * p779: "It is cleared by a software sequence (an read to the
	 * USART_SR register followed by a read to the USART_DR register"
	 */
	if (flags & InterruptFlag::OverrunError) {
		uint32_t tmp;
		tmp = UART4->SR;
		tmp = UART4->DR;
		(void) tmp;
	}
	(void) flags;	// avoid compiler warning
}