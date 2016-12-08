// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#include "../../../device.hpp"

extern "C"
void
xpcc_gpio_enable(void)
{
	// FIXME: add possibility to switch individual clocks on and off
	// Enable GPIO clock
	RCC->AHB1ENR  |=
		RCC_AHB1ENR_GPIOAEN |
		RCC_AHB1ENR_GPIOBEN |
		RCC_AHB1ENR_GPIOCEN |
		RCC_AHB1ENR_GPIODEN |
		RCC_AHB1ENR_GPIOEEN |
		RCC_AHB1ENR_GPIOHEN;
	// Reset GPIO peripheral
	RCC->AHB1RSTR |=
		RCC_AHB1RSTR_GPIOARST |
		RCC_AHB1RSTR_GPIOBRST |
		RCC_AHB1RSTR_GPIOCRST |
		RCC_AHB1RSTR_GPIODRST |
		RCC_AHB1RSTR_GPIOERST |
		RCC_AHB1RSTR_GPIOHRST;
	RCC->AHB1RSTR &= ~(
		RCC_AHB1RSTR_GPIOARST |
		RCC_AHB1RSTR_GPIOBRST |
		RCC_AHB1RSTR_GPIOCRST |
		RCC_AHB1RSTR_GPIODRST |
		RCC_AHB1RSTR_GPIOERST |
		RCC_AHB1RSTR_GPIOHRST);
}