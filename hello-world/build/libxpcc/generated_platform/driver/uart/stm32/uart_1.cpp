// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#include "../../../device.hpp"
#include "uart_hal_1.hpp"
#include "uart_1.hpp"

#include <xpcc/architecture/driver/atomic.hpp>

namespace
{
	static xpcc::atomic::Queue<uint8_t, 16> rxBuffer;
	static xpcc::atomic::Queue<uint8_t, 250> txBuffer;
}
void
xpcc::stm32::Usart1::initializeBuffered(uint32_t interruptPriority)
{
	UsartHal1::enableInterruptVector(true, interruptPriority);
	UsartHal1::enableInterrupt(Interrupt::RxNotEmpty);
}
void
xpcc::stm32::Usart1::writeBlocking(uint8_t data)
{
	while(!UsartHal1::isTransmitRegisterEmpty());
	UsartHal1::write(data);
}

void
xpcc::stm32::Usart1::writeBlocking(const uint8_t *data, std::size_t length)
{
	while (length-- != 0) {
		writeBlocking(*data++);
	}
}

void
xpcc::stm32::Usart1::flushWriteBuffer()
{
	while(!isWriteFinished());
}

bool
xpcc::stm32::Usart1::write(uint8_t data)
{
	if(txBuffer.isEmpty() && UsartHal1::isTransmitRegisterEmpty()) {
		UsartHal1::write(data);
	} else {
		if (!txBuffer.push(data))
			return false;
		// Disable interrupts while enabling the transmit interrupt
		atomic::Lock lock;
		// Transmit Data Register Empty Interrupt Enable
		UsartHal1::enableInterrupt(Interrupt::TxEmpty);
	}
	return true;
}

std::size_t
xpcc::stm32::Usart1::write(const uint8_t *data, std::size_t length)
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
xpcc::stm32::Usart1::isWriteFinished()
{
	return txBuffer.isEmpty() && UsartHal1::isTransmitRegisterEmpty();
}

std::size_t
xpcc::stm32::Usart1::discardTransmitBuffer()
{
	std::size_t count = 0;
	// disable interrupt since buffer will be cleared
	UsartHal1::disableInterrupt(UsartHal1::Interrupt::TxEmpty);
	while(!txBuffer.isEmpty()) {
		++count;
		txBuffer.pop();
	}
	return count;
}

bool
xpcc::stm32::Usart1::read(uint8_t &data)
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
xpcc::stm32::Usart1::read(uint8_t *data, std::size_t length)
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
xpcc::stm32::Usart1::discardReceiveBuffer()
{
	std::size_t count = 0;
	while(!rxBuffer.isEmpty()) {
		++count;
		rxBuffer.pop();
	}
	return count;
}


extern "C" void
USART1_IRQHandler()
{
	if (xpcc::stm32::UsartHal1::isReceiveRegisterNotEmpty()) {
		// TODO: save the errors
		uint8_t data;
		xpcc::stm32::UsartHal1::read(data);
		rxBuffer.push(data);
	}
	if (xpcc::stm32::UsartHal1::isTransmitRegisterEmpty()) {
		if (txBuffer.isEmpty()) {
			// transmission finished, disable TxEmpty interrupt
			xpcc::stm32::UsartHal1::disableInterrupt(xpcc::stm32::UsartHal1::Interrupt::TxEmpty);
		}
		else {
			xpcc::stm32::UsartHal1::write(txBuffer.get());
			txBuffer.pop();
		}
	}
}
