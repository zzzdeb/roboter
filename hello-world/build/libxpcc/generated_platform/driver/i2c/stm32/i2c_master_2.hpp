// coding: utf-8
/* Copyright (c) 2011, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------
/*
 * WARNING: This file is generated automatically, do not edit!
 * Please modify the corresponding *.in file instead and rebuild this file.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_I2C_2_HPP
#define XPCC_STM32_I2C_2_HPP

#include "../../../device.hpp"
#include "type_ids.hpp"
#include <xpcc/architecture/interface/i2c_master.hpp>

/**
 * @ingroup 	stm32f407vg
 * @defgroup	stm32f407vg_i2c I2C
 */

namespace xpcc
{

namespace stm32
{

/**
 * I2cMaster implementation of I2C2 module.
 *
 * Interrupts must be enabled.
 *
 * @author		Georgi Grinshpun
 * @author		Niklas Hauser
 * @ingroup		stm32f407vg_i2c
 */
class I2cMaster2 : public ::xpcc::I2cMaster
{
public:
	static const TypeId::I2cMaster2Sda Sda;
	static const TypeId::I2cMaster2Scl Scl;

public:
	/**
	 * Set up the I2C module for master operation.
	 *
	 * @param	rate
	 *		`Standard` or `Fast`, `High` datarate is not supported
	 */
	template<class SystemClock, uint32_t baudrate=Baudrate::Standard,
			uint16_t tolerance = xpcc::Tolerance::FivePercent >
	static xpcc_always_inline void
	initialize()
	{
		// calculate the expected clock ratio
		constexpr uint8_t scalar = (baudrate <= 100000) ? 2 : ((baudrate <= 300000) ? 3 : 25);

		// calculate the fractional prescaler value
		constexpr float pre_raw  = float(SystemClock::I2c2) / (scalar * baudrate);
		// respect the prescaler range of 1 or 4 to 4095
		constexpr uint32_t pre_ceil = std::ceil(pre_raw) > 4095 ? 4095 : std::ceil(pre_raw);
		constexpr uint32_t pre_floor = std::floor(pre_raw) < ((scalar < 3) ? 4 : 1) ?
				((scalar < 3) ? 4 : 1) : std::floor(pre_raw);

		// calculate the possible baudrates above and below the requested baudrate
		constexpr uint32_t baud_lower = SystemClock::I2c2 / ( scalar * pre_ceil  );
		constexpr uint32_t baud_upper = SystemClock::I2c2 / ( scalar * pre_floor );

		// calculate the fractional prescaler value corresponding to the baudrate exactly
		// between the upper and lower baudrate
		constexpr uint32_t baud_middle = (baud_upper + baud_lower) / 2;
		// decide which prescaler value is closer to a possible baudrate
		constexpr uint32_t pre = (baudrate < baud_middle) ? pre_ceil : pre_floor;

		// check if within baudrate tolerance
		constexpr uint32_t generated_baudrate = SystemClock::I2c2 / ( scalar * pre );
		assertBaudrateInTolerance<
				/* clostest available baudrate */ generated_baudrate,
				/* desired baudrate */ baudrate,
				tolerance >();

		// the final prescaler value is augmented with the F/S and DUTY bit.
		constexpr uint32_t prescaler = pre |
				((scalar >= 3) ? (1 << 15) : 0) |
				((scalar == 25) ? (1 << 14) : 0);

		// peripheral frequency clock
		constexpr uint8_t freq = SystemClock::I2c2 / 1000000;

		// maximum rise time: assuming its linear:
		// 1000ns @ 100kHz and 300ns @ 400kHz
		//   => y = x * m + b, with m = -2.3333ns/kHz, b = 1233.3333ns
		constexpr float max_rise_time = -2.333333f * (float(baudrate) / 1000.f) + 1233.333333f;
		// calculate trise
		constexpr float trise_raw = max_rise_time < 0 ? 0 : std::floor(max_rise_time / (1000.f / freq));
		constexpr uint8_t trise = trise_raw > 62 ? 63 : (trise_raw + 1);

		initializeWithPrescaler(freq, trise, prescaler);
	}

	// start documentation inherited
	static bool
	start(I2cTransaction *transaction, ConfigurationHandler handler = nullptr);

	static Error
	getErrorState();

	static void
	reset();
	// end documentation inherited

private:
	static void
	initializeWithPrescaler(uint8_t peripheralFrequency, uint8_t riseTime, uint16_t prescaler);
};

} // namespace stm32

} // namespace xpcc

#endif // XPCC_STM32_I2C_2_HPP