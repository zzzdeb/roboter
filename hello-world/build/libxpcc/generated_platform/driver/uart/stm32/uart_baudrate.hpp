// coding: utf-8
/* Copyright (c) 2014, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_UART_BAUDRATE_HPP
#define XPCC_STM32_UART_BAUDRATE_HPP

#include "uart_base.hpp"
#include <xpcc/architecture/interface.hpp>

namespace xpcc
{

namespace stm32
{

/**
 * This class provides several helper functions to calculate the values for
 * the fractional baudrate generator.
 *
 * All of these functions are `constexpr` functions which allow compile time
 * evaluation.
 * If you really need to change the baudrate at runtime, consider calculating
 * the register values at compile time, storing them in your program, then
 * switching them at runtime.
 * This will save you a *lot* of flash and execution time.
 *
 * @author	Kevin Laeufer
 * @author	Niklas Hauser
 * @ingroup	stm32f407vg_uart
 */
class UartBaudrate : /** @cond */protected xpcc::Peripheral /** @endcond */
{
public:
	/**
	 * Returns the highest Oversampling Mode that is possible for this configuration.
	 */
	static constexpr UartBase::OversamplingMode
	getOversamplingMode(uint32_t clockrate, uint32_t baudrate)
	{
		return (baudrate <= clockrate / 16) ? UartBase::OversamplingMode::By16 : UartBase::OversamplingMode::By8;
	}
	/**
	 * Get the best BRR for chosen baudrate and tolerance.
	 *
	 * @tparam	clockrate
	 * 		the modules clock frequency in Hz
	 * @tparam	baudrate
	 * 		the desired baudrate in Hz
	 * @tparam	tolerance
	 * 		the allowed absolute tolerance for the resulting baudrate
	 */
	template< uint32_t clockrate, uint32_t baudrate, uint16_t tolerance = 1000 >
	static uint16_t xpcc_always_inline
	getBrr()
	{
		constexpr uint32_t scalar = (baudrate * 16l > clockrate) ? 8 : 16;
		constexpr uint32_t max = (scalar == 16) ? 65536 : 32768;

		// calculate the fractional prescaler value
		constexpr float pre_raw = static_cast<float>(clockrate) / (baudrate);
		// respect the prescaler range of 1 to 4096
		constexpr uint32_t pre_ceil = std::ceil(pre_raw) > max ? max : std::ceil(pre_raw);
		constexpr uint32_t pre_floor = std::floor(pre_raw) < 1 ? 1 : std::floor(pre_raw);

		// calculate the possible baudrates above and below the requested baudrate
		constexpr uint32_t baud_lower = clockrate / ( pre_ceil );
		constexpr uint32_t baud_upper = clockrate / ( pre_floor );

		// calculate the half-point between the upper and lower baudrate
		constexpr uint32_t baud_middle = (baud_upper + baud_lower) / 2;
		// decide which prescaler value is closer to a possible baudrate
		constexpr uint32_t prescaler = (baudrate < baud_middle) ? pre_ceil : pre_floor;

		// brr needs to be formatted right for scalar == 8
		constexpr uint16_t brr = (scalar == 16) ? prescaler :
				(((prescaler & ~0b111) << 1) | (prescaler & 0b111));

		// check if within baudrate tolerance
		constexpr uint32_t generated_baudrate = clockrate / ( prescaler );
		assertBaudrateInTolerance<
				/* nearest possible value */ generated_baudrate,
				/* desired = */ baudrate,
				tolerance >();

		return brr;
	}

};

}	// namespace stm32

}	// namespace xpcc

#endif // XPCC_STM32_UART_BAUDRATE_HPP
