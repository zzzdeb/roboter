// coding: utf-8
/* Copyright (c) 2011-2016, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#include "clock.hpp"

namespace xpcc
{
namespace clock
{

uint32_t xpcc_fastdata fcpu(16000000);
uint32_t xpcc_fastdata fcpu_kHz(16000);
uint16_t xpcc_fastdata fcpu_MHz(16);
uint16_t xpcc_fastdata ns_per_loop(187.5);

}
}

// ----------------------------------------------------------------------------
bool
xpcc::stm32::ClockControl::enableInternalClock(uint32_t waitCycles)
{
	bool retval;
	RCC->CR |= RCC_CR_HSION;
	while (not (retval = (RCC->CR & RCC_CR_HSIRDY)) and --waitCycles)
		;
	return retval;
}

bool
xpcc::stm32::ClockControl::enableExternalClock(uint32_t waitCycles)
{
	bool retval;
	RCC->CR |= RCC_CR_HSEBYP | RCC_CR_HSEON;
	while (not (retval = (RCC->CR & RCC_CR_HSERDY)) and --waitCycles)
		;
	return retval;
}

bool
xpcc::stm32::ClockControl::enableExternalCrystal(uint32_t waitCycles)
{
	bool retval;
	RCC->CR = (RCC->CR & ~RCC_CR_HSEBYP) | RCC_CR_HSEON;
	while (not (retval = (RCC->CR & RCC_CR_HSERDY)) and --waitCycles)
		;
	return retval;
}

bool
xpcc::stm32::ClockControl::enableLowSpeedInternalClock(uint32_t waitCycles)
{
	bool retval;
	RCC->CSR |= RCC_CSR_LSION;
	while (not (retval = (RCC->CSR & RCC_CSR_LSIRDY)) and --waitCycles)
		;
	return retval;
}

bool
xpcc::stm32::ClockControl::enableLowSpeedExternalClock(uint32_t waitCycles)
{
	bool retval;
	RCC->BDCR |= RCC_BDCR_LSEBYP | RCC_BDCR_LSEON;
	while (not (retval = (RCC->BDCR & RCC_BDCR_LSERDY)) and --waitCycles)
		;
	return retval;
}

bool
xpcc::stm32::ClockControl::enableLowSpeedExternalCrystal(uint32_t waitCycles)
{
	bool retval;
	RCC->BDCR = (RCC->BDCR & ~RCC_BDCR_LSEBYP) | RCC_BDCR_LSEON;
	while (not (retval = (RCC->BDCR & RCC_BDCR_LSERDY)) and --waitCycles)
		;
	return retval;
}

// ----------------------------------------------------------------------------
bool
xpcc::stm32::ClockControl::enablePll(PllSource source, uint8_t pllM,
	uint16_t pllN, uint8_t pllP, uint8_t pllQ, uint32_t waitCycles)
{
	uint32_t tmp = 0;


	// Read reserved values and clear all other values
	tmp = RCC->PLLCFGR & ~(RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLM
			| RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ);

	// PLLSRC source for pll and for plli2s
	tmp |= static_cast<uint32_t>(source);

	// PLLM (0) = factor is user defined VCO input frequency must be configured to 2MHz
	tmp |= ((uint32_t) pllM) & RCC_PLLCFGR_PLLM;

	// PLLN (6) = factor is user defined
	tmp |= (((uint32_t) pllN) << 6) & RCC_PLLCFGR_PLLN;

	// PLLP (16) divider for CPU frequency; (00: PLLP = 2, 01: PLLP = 4, etc.)
	tmp |= (((uint32_t) (pllP / 2) - 1) << 16) & RCC_PLLCFGR_PLLP;

	// PLLQ (24) divider for USB frequency; (0-15)
	tmp |= (((uint32_t) pllQ) << 24) & RCC_PLLCFGR_PLLQ;

	RCC->PLLCFGR = tmp;

	// enable pll
	RCC->CR |= RCC_CR_PLLON;

	while (not (tmp = (RCC->CR & RCC_CR_PLLRDY)) and --waitCycles)
		;

	return tmp;
}
// ----------------------------------------------------------------------------
bool
xpcc::stm32::ClockControl::enableSystemClock(SystemClockSource src, uint32_t waitCycles)
{
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | uint32_t(src);

	// Wait till the main PLL is used as system clock source
	src = SystemClockSource(uint32_t(src) << 2);
	while ((RCC->CFGR & RCC_CFGR_SWS) != uint32_t(src))
	{
		if (not --waitCycles)
			return false;
	}

	return true;
}