// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------
#ifndef XPCC_STM32_UART_1_HPP
#define XPCC_STM32_UART_1_HPP

#include <xpcc/architecture/interface/uart.hpp>
#include "../../../type_ids.hpp"
#include "uart_base.hpp"
#include "uart_baudrate.hpp"
#include "uart_hal_1.hpp"

namespace xpcc
{

namespace stm32
{

/**
 * Universal asynchronous receiver transmitter (USART1)
 *
 * @author		Kevin Laeufer
 * @author		Niklas Hauser
 * @ingroup		stm32f407vg_uart
 */
class Usart1 : public UartBase, public ::xpcc::Uart
{
public:
	/// TypeId used to connect GPIO pins to this peripheral's rx.
	static const TypeId::Uart1Rx Rx;
	/// TypeId used to connect GPIO pins to this peripheral's tx.
	static const TypeId::Uart1Tx Tx;

private:
	/// Second stage initialize for buffered uart
	// that need to be implemented in the .cpp
	static void
	initializeBuffered(uint32_t interruptPriority);
public:
template< 	class SystemClock, uint32_t baudrate,
		uint16_t tolerance = xpcc::Tolerance::OnePercent >
	static void xpcc_always_inline
	initialize(uint32_t interruptPriority, Parity parity = Parity::Disabled)
	{
		constexpr UartBase::OversamplingMode oversample =
				UartBaudrate::getOversamplingMode(SystemClock::Usart1, baudrate);
		UsartHal1::initializeWithBrr(
				UartBaudrate::getBrr<SystemClock::Usart1, baudrate, tolerance>(),
				parity,
				oversample);
		initializeBuffered(interruptPriority);
		UsartHal1::setTransmitterEnable(true);
		UsartHal1::setReceiverEnable(true);
	}

	static void
	writeBlocking(uint8_t data);

	static void
	writeBlocking(const uint8_t *data, std::size_t length);

	static void
	flushWriteBuffer();

	static bool
	write(uint8_t data);

	static std::size_t
	write(const uint8_t *data, std::size_t length);

	static bool
	isWriteFinished();

	static std::size_t
	discardTransmitBuffer();

	static bool
	read(uint8_t &data);

	static std::size_t
	read(uint8_t *buffer, std::size_t length);

	static std::size_t
	discardReceiveBuffer();
};

}	// namespace stm32

}	// namespace xpcc

#endif // XPCC_STM32_UART_1_HPP