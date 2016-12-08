// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

#include "spi_master_3.hpp"
#include <xpcc/architecture/interface/register.hpp>

// Bit0: single transfer state
// Bit1: block transfer state
uint8_t
xpcc::stm32::SpiMaster3::state(0);

uint8_t
xpcc::stm32::SpiMaster3::count(0);

void *
xpcc::stm32::SpiMaster3::context(nullptr);

xpcc::Spi::ConfigurationHandler
xpcc::stm32::SpiMaster3::configuration(nullptr);
// ----------------------------------------------------------------------------

uint8_t
xpcc::stm32::SpiMaster3::acquire(void *ctx, ConfigurationHandler handler)
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
xpcc::stm32::SpiMaster3::release(void *ctx)
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
xpcc::stm32::SpiMaster3::transfer(uint8_t data)
{
	// this is a manually implemented "fast resumable function"
	// there is no context or nesting protection, since we don't need it.
	// there are only two states encoded into 1 bit (LSB of state):
	//   1. waiting to start, and
	//   2. waiting to finish.

	// LSB != Bit0 ?
	if ( !(state & Bit0) )
	{
		// wait for previous transfer to finish
		if (!SpiHal3::isTransmitRegisterEmpty())
			return {xpcc::rf::Running};

		// start transfer by copying data into register
		SpiHal3::write(data);

		// set LSB = Bit0
		state |= Bit0;
	}

	if (!SpiHal3::isReceiveRegisterNotEmpty())
		return {xpcc::rf::Running};

	SpiHal3::read(data);

	// transfer finished
	state &= ~Bit0;
	return {xpcc::rf::Stop, data};
}

xpcc::ResumableResult<void>
xpcc::stm32::SpiMaster3::transfer(
		uint8_t * tx, uint8_t * rx, std::size_t length)
{
	// this is a manually implemented "fast resumable function"
	// there is no context or nesting protection, since we don't need it.
	// there are only two states encoded into 1 bit (Bit1 of state):
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
				// if tx == 0, we use a dummy byte 0x00
				// else we copy it from the array
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