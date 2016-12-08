// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#include "uart_spi_master_2.hpp"
#include <xpcc/math/utils/bit_operation.hpp>
#include <xpcc/architecture/interface/register.hpp>

xpcc::stm32::UartSpiMaster2::DataOrder
	xpcc::stm32::UartSpiMaster2::dataOrder =
	xpcc::stm32::UartSpiMaster2::DataOrder::MsbFirst;

// Bit0: single transfer state
// Bit1: block transfer state
uint8_t
xpcc::stm32::UartSpiMaster2::state(0);

uint8_t
xpcc::stm32::UartSpiMaster2::count(0);

void *
xpcc::stm32::UartSpiMaster2::context(nullptr);

xpcc::Spi::ConfigurationHandler
xpcc::stm32::UartSpiMaster2::configuration(nullptr);
// ----------------------------------------------------------------------------

uint8_t
xpcc::stm32::UartSpiMaster2::acquire(void *ctx, ConfigurationHandler handler)
{
	if (context == nullptr)
	{
		context = ctx;
		count = 1;
		// if handler is not nullptr and is different from previous configuration
		if (handler and configuration != handler) {
			configuration = handler;
			configuration();
		}
		return 1;
	}

	if (ctx == context)
		return ++count;

	return 0;
}

uint8_t
xpcc::stm32::UartSpiMaster2::release(void *ctx)
{
	if (ctx == context)
	{
		if (--count == 0)
			context = nullptr;
	}
	return count;
}
// ----------------------------------------------------------------------------

xpcc::ResumableResult<uint8_t>
xpcc::stm32::UartSpiMaster2::transfer(uint8_t data)
{
	// this is a manually implemented "fast resumable function"
	// there is no context or nesting protection, since we don't need it.
	// there are only two states encoded into 1 bit (LSB of state):
	//   1. waiting to start, and
	//   2. waiting to finish.

	// LSB == Bit0 ?
	if ( !(state & Bit0) )
	{
		// wait for previous transfer to finish
		if (!UsartHal2::isTransmitRegisterEmpty())
			return {xpcc::rf::Running};

		// start transfer by copying data into register
		if(dataOrder == DataOrder::MsbFirst) {
			data = ::xpcc::bitReverse(data);
		}
		UsartHal2::write(data);

		// set LSB = 1
		state |= Bit0;
	}

	if (!UsartHal2::isReceiveRegisterNotEmpty())
		return {xpcc::rf::Running};

	UsartHal2::read(data);

	if(dataOrder == DataOrder::MsbFirst) {
		data = ::xpcc::bitReverse(data);
	}

	// transfer finished
	state &= ~Bit0;
	return {xpcc::rf::Stop, data};
}

xpcc::ResumableResult<void>
xpcc::stm32::UartSpiMaster2::transfer(
		uint8_t * tx, uint8_t * rx, std::size_t length)
{
	// this is a manually implemented "fast resumable function"
	// there is no context or nesting protection, since we don't need it.
	// there are only two states encoded into 1 bit (0x02 of state):
	//   1. initialize index, and
	//   2. wait for 1-byte transfer to finish.

	// we need to globally remember which byte we are currently transferring
	static std::size_t index = 0;

	// we are only interested in Bit1
	switch(state & Bit1)
	{
		case 0:
			// we will only visit this state once
			state |= Bit1;

			// initialize index and check range
			index = 0;
			while (index < length)
			{
		default:
		{
				// call the resumable function
				xpcc::ResumableResult<uint8_t> result = transfer(tx ? tx[index] : 0);

				// if the resumable function is still running, so are we
				if (result.getState() > xpcc::rf::NestingError)
					return {xpcc::rf::Running};

				// if rx != 0, we copy the result into the array
				if (rx) rx[index] = result.getResult();
		}
				index++;
			}

			// clear the state
			state &= ~Bit1;
			return {xpcc::rf::Stop};
	}
}