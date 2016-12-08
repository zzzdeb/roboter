// coding: utf-8
/*
* Copyright (c) 2013, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part for the xpcc library and is released under the
* 3-clause BSD license. See the file `LICENSE` for the full license
* governing this code.
*/
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_UART_BASE_HPP
#define XPCC_STM32_UART_BASE_HPP

#include <stdint.h>
#include "../../../device.hpp"
#include <xpcc/architecture/interface/register.hpp>

// STM has some weird ideas about continuity
#define	USART_BRR_DIV_MANTISSA	USART_BRR_DIV_Mantissa
#define	USART_BRR_DIV_FRACTION	USART_BRR_DIV_Fraction
/**
* @ingroup 	stm32f407vg
* @defgroup	stm32f407vg_uart UART
*/

namespace xpcc
{
namespace stm32
{
/**
 * Base class for the UART classes
 *
 * Provides some common enum that do not depend on the specific UART.
 *
 * @author Kevin Laeufer
 * @internal
 * @ingroup		stm32f407vg_uart
 */
class UartBase
{

public:
	enum class Interrupt : uint32_t
	{
		/// Call interrupt when a parity error occurred.
		ParityError	= USART_CR1_PEIE,
		/// Call interrupt when transmit register is empty (i.e. the byte has been transfered to the shift out register
		TxEmpty		= USART_CR1_TXEIE,
		/// Called when the byte was completely transmitted
		TxComplete	= USART_CR1_TCIE,
		/// Call interrupt when char received (RXNE) or overrun occurred (ORE)
		RxNotEmpty	= USART_CR1_RXNEIE,
	};
	XPCC_FLAGS32(Interrupt);

	enum class InterruptFlag : uint32_t
	{
		/// Set if the transmit data register is empty.
		TxEmpty			= USART_SR_TXE,
		/// Set if the transmission is complete.
		TxComplete		= USART_SR_TC,
		/// Set if the receive data register is not empty.
		RxNotEmpty		= USART_SR_RXNE,
		/// Set if receive register was not cleared.
		OverrunError	= USART_SR_ORE,
		/// Set if a de-synchronization, excessive noise or a break character is detected
		FramingError 	= USART_SR_FE,
		/// Set if a parity error was detected.
		ParityError		= USART_SR_PE,
	};
	XPCC_FLAGS32(InterruptFlag);

	enum class Parity : uint32_t
	{
		Disabled 	= 0,
		Even 		= USART_CR1_PCE,
		Odd  		= USART_CR1_PCE | USART_CR1_PS,
	};

	/// Spi Data Mode, Mode0 is the most common mode
	enum class
	SpiDataMode : uint32_t
	{
		Mode0 = 0b00,			///< clock normal,   sample on rising  edge
		Mode1 = USART_CR2_CPHA,	///< clock normal,   sample on falling edge
		Mode2 = USART_CR2_CPOL,	///< clock inverted, sample on falling  edge
		Mode3 = USART_CR2_CPOL | USART_CR2_CPHA
		///< clock inverted, sample on rising edge
	};

	enum class
	OversamplingMode : uint32_t
	{
		By16 = 0b0,
		By8  = USART_CR1_OVER8,
	};
	enum class
	LastBitClockPulse : uint32_t
	{
		DoNotOutput = 0b0,
		Output = USART_CR2_LBCL,
	};

	enum class
	SpiClock : uint32_t
	{
		Disabled = 0b0,
		Enabled  = USART_CR2_CLKEN,
	};

};

}	// namespace stm32

}	// namespace xpcc

#endif // XPCC_STM32_UART_BASE_HPP