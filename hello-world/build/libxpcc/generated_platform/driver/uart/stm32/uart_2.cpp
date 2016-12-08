// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#include "../../../device.hpp"
#include "uart_hal_2.hpp"
#include "uart_2.hpp"

#include <xpcc/architecture/driver/atomic.hpp>

namespace
{
	static xpcc::atomic::Queue<uint8_t, 16> rxBuffer;
	static xpcc::atomic::Queue<uint8_t, 250> txBuffer;
}
void
xpcc::stm32::Usart2::initializeBuffered(uint32_t interruptPriority)
{
	UsartHal2::enableInterruptVector(true, interruptPriority);
	UsartHal2::enableInterrupt(Interrupt::RxNotEmpty);
}
void
xpcc::stm32::Usart2::writeBlocking(uint8_t data)
{
	while(!UsartHal2::isTransmitRegisterEmpty());
	UsartHal2::write(data);
}

void
xpcc::stm32::Usart2::writeBlocking(const uint8_t *data, std::size_t length)
{
	while (length-- != 0) {
		writeBlocking(*data++);
	}
}

void
xpcc::stm32::Usart2::flushWriteBuffer()
{
	while(!isWriteFinished());
}

bool
xpcc::stm32::Usart2::write(uint8_t data)
{
	if(txBuffer.isEmpty() && UsartHal2::isTransmitRegisterEmpty()) {
		UsartHal2::write(data);
	} else {
		if (!txBuffer.push(data))
			return false;
		// Disable interrupts while enabling the transmit interrupt
		atomic::Lock lock;
		// Transmit Data Register Empty Interrupt Enable
		UsartHal2::enableInterrupt(Interrupt::TxEmpty);
	}
	return true;
}

std::size_t
xpcc::stm32::Usart2::write(const uint8_t *data, std::size_t length)
{
	uint32_t i = 0;
	for (; i < length; ++i)
	{
		if (!write(*data++)) {
			return i;
		}
	}
	return i;
}

bool
xpcc::stm32::Usart2::isWriteFinished()
{
	return txBuffer.isEmpty() && UsartHal2::isTransmitRegisterEmpty();
}

std::size_t
xpcc::stm32::Usart2::discardTransmitBuffer()
{
	std::size_t count = 0;
	// disable interrupt since buffer will be cleared
	UsartHal2::disableInterrupt(UsartHal2::Interrupt::TxEmpty);
	while(!txBuffer.isEmpty()) {
		++count;
		txBuffer.pop();
	}
	return count;
}

bool
xpcc::stm32::Usart2::read(uint8_t &data)
{
	if (rxBuffer.isEmpty()) {
		return false;
	} else {
		data = rxBuffer.get();
		rxBuffer.pop();
		return true;
	}
}

std::size_t
xpcc::stm32::Usart2::read(uint8_t *data, std::size_t length)
{
	uint32_t i = 0;
	for (; i < length; ++i)
	{
		if (rxBuffer.isEmpty()) {
			return i;
		} else {
			*data++ = rxBuffer.get();
			rxBuffer.pop();
		}
	}
	return i;
}

std::size_t
xpcc::stm32::Usart2::discardReceiveBuffer()
{
	std::size_t count = 0;
	while(!rxBuffer.isEmpty()) {
		++count;
		rxBuffer.pop();
	}
	return count;
}


extern "C" void
USART2_IRQHandler()
{
	if (xpcc::stm32::UsartHal2::isReceiveRegisterNotEmpty()) {
		// TODO: save the errors
		uint8_t data;
		xpcc::stm32::UsartHal2::read(data);
		rxBuffer.push(data);
	}
	if (xpcc::stm32::UsartHal2::isTransmitRegisterEmpty()) {
		if (txBuffer.isEmpty()) {
			// transmission finished, disable TxEmpty interrupt
			xpcc::stm32::UsartHal2::disableInterrupt(xpcc::stm32::UsartHal2::Interrupt::TxEmpty);
		}
		else {
			xpcc::stm32::UsartHal2::write(txBuffer.get());
			txBuffer.pop();
		}
	}
}
