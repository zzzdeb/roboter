// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#include <xpcc_config.hpp>
#include "timer_7.hpp"

void
xpcc::stm32::Timer7::enable()
{
	// enable clock
	RCC->APB1ENR  |=  RCC_APB1ENR_TIM7EN;
	// reset timer
	RCC->APB1RSTR |=  RCC_APB1RSTR_TIM7RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM7RST;
}

void
xpcc::stm32::Timer7::disable()
{
	// disable clock
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM7EN;

	TIM7->CR1 = 0;
	TIM7->DIER = 0;
}

void
xpcc::stm32::Timer7::setMode(Mode mode)
{
	// ARR Register is buffered, only Under/Overflow generates update interrupt
	TIM7->CR1 = TIM_CR1_ARPE | TIM_CR1_URS | static_cast<uint32_t>(mode);
	TIM7->CR2 = 0;
}

void
xpcc::stm32::Timer7::enableInterruptVector(bool enable, uint32_t priority)
{
	if (enable) {
		// Set vector priority
		NVIC_SetPriority(TIM7_IRQn, priority);
		// register IRQ at the NVIC
		NVIC_EnableIRQ(TIM7_IRQn);
	}
	else {
		NVIC_DisableIRQ(TIM7_IRQn);
	}
}