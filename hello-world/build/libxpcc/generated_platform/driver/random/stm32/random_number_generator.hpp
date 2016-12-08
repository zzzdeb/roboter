// coding: utf-8
/* Copyright (c) 2012, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_RANDOM_NUMBER_GENERATOR_HPP
#define XPCC_STM32_RANDOM_NUMBER_GENERATOR_HPP

#include <stdint.h>
#include "../../../device.hpp"

/**
 * @ingroup 	stm32f407vg
 * @defgroup	stm32f407vg_random Random
 */

namespace xpcc
{

namespace stm32
{

/**
 * Random Number Generator
 *
 * @todo check error status
 *
 * @author	Fabian Greif
 * @ingroup	stm32f407vg_random
 */
class RandomNumberGenerator
{
public:
	static inline void
	enable()
	{
		RNG->CR = RNG_CR_RNGEN;
	}

	/**
	 * Check if a new random number is ready
	 *
	 * @return	 `true` if a new random number has been generated
	 * 			and can be read via getValue()
	 */
	static inline bool
	isReady()
	{
		return (RNG->SR & RNG_SR_DRDY);
	}

	/**
	 * Read the generated 32-bit random number
	 *
	 * Once read isReady() will return `false` until a new number
	 * has be generated.
	 */
	static inline uint32_t
	getValue()
	{
		return RNG->DR;
	}
};

}

}

#endif	// XPCC_STM32_RANDOM_NUMBER_GENERATOR_HPP