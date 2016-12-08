// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#include <xpcc_config.hpp>
#include "timer_5.hpp"

// ----------------------------------------------------------------------------
void
xpcc::stm32::Timer5::clockEnable()
{
	// enable clock
	RCC->APB1ENR  |=  RCC_APB1ENR_TIM5EN;
}

void
xpcc::stm32::Timer5::enable()
{
	// enable clock
	RCC->APB1ENR  |=  RCC_APB1ENR_TIM5EN;

	// reset timer
	RCC->APB1RSTR |=  RCC_APB1RSTR_TIM5RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM5RST;
}

void
xpcc::stm32::Timer5::disable()
{
	// disable clock
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM5EN;

	TIM5->CR1 = 0;
	TIM5->DIER = 0;
	TIM5->CCER = 0;
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Timer5::setMode(Mode mode, SlaveMode slaveMode,
		SlaveModeTrigger slaveModeTrigger, MasterMode masterMode,
		bool enableOnePulseMode)
{
	// disable timer
	TIM5->CR1 = 0;
	TIM5->CR2 = 0;

	if (slaveMode == SlaveMode::Encoder1 || \
		slaveMode == SlaveMode::Encoder2 || \
		slaveMode == SlaveMode::Encoder3)
	{
		// Prescaler has to be 1 when using the quadrature decoder
		setPrescaler(1);
	}
	// ARR Register is buffered, only Under/Overflow generates update interrupt
	if (enableOnePulseMode) {
		TIM5->CR1 = TIM_CR1_ARPE | TIM_CR1_URS | TIM_CR1_OPM
										| static_cast<uint32_t>(mode);
	} else {
		TIM5->CR1 = TIM_CR1_ARPE | TIM_CR1_URS
										| static_cast<uint32_t>(mode);
	}
	TIM5->CR2 = static_cast<uint32_t>(masterMode);
	TIM5->SMCR = static_cast<uint32_t>(slaveMode)
						| static_cast<uint32_t>(slaveModeTrigger);
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Timer5::configureInputChannel(uint32_t channel,
		InputCaptureMapping input, InputCapturePrescaler prescaler,
		InputCapturePolarity polarity, uint8_t filter,
		bool xor_ch1_3)
{
	channel -= 1;	// 1..4 -> 0..3

	// disable channel
	TIM5->CCER &= ~((TIM_CCER_CC1NP | TIM_CCER_CC1P | TIM_CCER_CC1E) << (channel * 4));

	uint32_t flags = static_cast<uint32_t>(input);
	flags |= static_cast<uint32_t>(prescaler) << 2;
	flags |= (static_cast<uint32_t>(filter) & 0xf) << 4;
	
	if (channel <= 1)
	{
		uint32_t offset = 8 * channel;

		flags <<= offset;
		flags |= TIM5->CCMR1 & ~(0xff << offset);

		TIM5->CCMR1 = flags;

		if(channel == 0) {
			if(xor_ch1_3)
				TIM5->CR2 |= TIM_CR2_TI1S;
			else
				TIM5->CR2 &= ~TIM_CR2_TI1S;
		}
	}
	else {
		uint32_t offset = 8 * (channel - 2);

		flags <<= offset;
		flags |= TIM5->CCMR2 & ~(0xff << offset);

		TIM5->CCMR2 = flags; 
	}

	TIM5->CCER |=
		(TIM_CCER_CC1E | static_cast<uint32_t>(polarity)) << (channel * 4);
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Timer5::configureOutputChannel(uint32_t channel,
		OutputCompareMode_t mode, Value compareValue, PinState out)
{
	channel -= 1;	// 1..4 -> 0..3
	
	// disable channel
	TIM5->CCER &= ~((TIM_CCER_CC1NP | TIM_CCER_CC1P | TIM_CCER_CC1E) << (channel * 4));
	
	setCompareValue(channel + 1, compareValue);
	
	// enable preload (the compare value is loaded at each update event)
	uint32_t flags = mode.value | TIM_CCMR1_OC1PE;
	
	if (channel <= 1)
	{
		uint32_t offset = 8 * channel;
		
		flags <<= offset;
		flags |= TIM5->CCMR1 & ~(0xff << offset);
		
		TIM5->CCMR1 = flags;
	}
	else {
		uint32_t offset = 8 * (channel - 2);
		
		flags <<= offset;
		flags |= TIM5->CCMR2 & ~(0xff << offset);
		
		TIM5->CCMR2 = flags; 
	}
	
	if (mode != OutputCompareMode::Inactive && out == PinState::Enable) {
		TIM5->CCER |= (TIM_CCER_CC1E) << (channel * 4);
	}
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Timer5::enableInterruptVector(bool enable, uint32_t priority)
{
	if (enable) {
		// Set priority for the interrupt vector
		NVIC_SetPriority(TIM5_IRQn, priority);
		
		// register IRQ at the NVIC
		NVIC_EnableIRQ(TIM5_IRQn);
	}
	else {
		NVIC_DisableIRQ(TIM5_IRQn);
	}
}