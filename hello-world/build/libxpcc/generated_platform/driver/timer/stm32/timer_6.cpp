// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#include <xpcc_config.hpp>
#include "timer_6.hpp"

void
xpcc::stm32::Timer6::enable()
{
	// enable clock
	RCC->APB1ENR  |=  RCC_APB1ENR_TIM6EN;
	// reset timer
	RCC->APB1RSTR |=  RCC_APB1RSTR_TIM6RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM6RST;
}

void
xpcc::stm32::Timer6::disable()
{
	// disable clock
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN;

	TIM6->CR1 = 0;
	TIM6->DIER = 0;
}

void
xpcc::stm32::Timer6::setMode(Mode mode)
{
	// ARR Register is buffered, only Under/Overflow generates update interrupt
	TIM6->CR1 = TIM_CR1_ARPE | TIM_CR1_URS | static_cast<uint32_t>(mode);
	TIM6->CR2 = 0;
}

void
xpcc::stm32::Timer6::enableInterruptVector(bool enable, uint32_t priority)
{
	if (enable) {
		// Set vector priority
		NVIC_SetPriority(TIM6_DAC_IRQn, priority);
		// register IRQ at the NVIC
		NVIC_EnableIRQ(TIM6_DAC_IRQn);
	}
	else {
		NVIC_DisableIRQ(TIM6_DAC_IRQn);
	}
}