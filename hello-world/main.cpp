/* Copyright (c) 2016, Roboterclub Aachen e.V.
 *
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 * ------------------------------------------------------------------------- */
#include <xpcc/architecture/platform.hpp>
#include <xpcc/debug/logger.hpp>
#define XPCC_BOARD_HAS_LOGGER

xpcc::IODeviceWrapper< Usart2, xpcc::IOBuffer::BlockIfFull > loggerDevice;

xpcc::log::Logger xpcc::log::debug(loggerDevice);
xpcc::log::Logger xpcc::log::info(loggerDevice);
xpcc::log::Logger xpcc::log::warning(loggerDevice);
xpcc::log::Logger xpcc::log::error(loggerDevice);

int main()
{
	Board::initialize();
	Board::Leds::setOutput();

    GpioOutputA2::connect(Usart2::Tx);
    Usart2::initialize <Board::systemClock, 115200>(12);

	while (1)
	{
		Board::Leds::toggle();
		xpcc::delayMilliseconds(Board::Button::read() ? 250 : 500);
#ifdef XPCC_BOARD_HAS_LOGGER
		static uint32_t counter(0);
		XPCC_LOG_INFO << "Loop counter: " << (counter++) << xpcc::endl;
#endif
	}
	return 0;
}
