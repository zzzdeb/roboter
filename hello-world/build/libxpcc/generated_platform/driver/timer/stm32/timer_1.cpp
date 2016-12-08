// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

#include <xpcc_config.hpp>
#include "timer_1.hpp"

// ----------------------------------------------------------------------------
void
xpcc::stm32::Timer1::enable()
{
	// enable clock
	RCC->APB2ENR  |=  RCC_APB2ENR_TIM1EN;
	
	// reset timer
	RCC->APB2RSTR |=  RCC_APB2RSTR_TIM1RST;
	RCC->APB2RSTR &= ~RCC_APB2RSTR_TIM1RST;
}

void
xpcc::stm32::Timer1::disable()
{
	// disable clock
	RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
	
	TIM1->CR1 = 0;
	TIM1->DIER = 0;
	TIM1->CCER = 0;
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Timer1::setMode(Mode mode, SlaveMode slaveMode,
		SlaveModeTrigger slaveModeTrigger, MasterMode masterMode
		)
{
	// disable timer
	TIM1->CR1 = 0;
	TIM1->CR2 = 0;
	
	if (slaveMode == SlaveMode::Encoder1 ||
		slaveMode == SlaveMode::Encoder2 ||
		slaveMode == SlaveMode::Encoder3)
	{
		setPrescaler(1);
	}

	// ARR Register is buffered, only Under/Overflow generates update interrupt
	TIM1->CR1 = TIM_CR1_ARPE | TIM_CR1_URS | static_cast<uint32_t>(mode);
	TIM1->CR2 = static_cast<uint32_t>(masterMode);
	TIM1->SMCR = static_cast<uint32_t>(slaveMode) |
						static_cast<uint32_t>(slaveModeTrigger);
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Timer1::configureInputChannel(uint32_t channel,
		InputCaptureMapping input, InputCapturePrescaler prescaler,
		InputCapturePolarity polarity, uint8_t filter,
		bool xor_ch1_3)
{
	channel -= 1;	// 1..4 -> 0..3
	
	// disable channel
	TIM1->CCER &= ~((TIM_CCER_CC1NP | TIM_CCER_CC1P | TIM_CCER_CC1E) << (channel * 4));
	
	uint32_t flags = static_cast<uint32_t>(input);
	flags |= static_cast<uint32_t>(prescaler) << 2;
	flags |= static_cast<uint32_t>(filter&0xf) << 4;
	
	if (channel <= 1)
	{
		uint32_t offset = 8 * channel;

		flags <<= offset;
		flags |= TIM1->CCMR1 & ~(0xff << offset);

		TIM1->CCMR1 = flags;

		if(channel == 0) {
			if(xor_ch1_3)
				TIM1->CR2 |= TIM_CR2_TI1S;
			else
				TIM1->CR2 &= ~TIM_CR2_TI1S;
		}
	}
	else {
		uint32_t offset = 8 * (channel - 2);
		
		flags <<= offset;
		flags |= TIM1->CCMR2 & ~(0xff << offset);
		
		TIM1->CCMR2 = flags; 
	}
	
	TIM1->CCER |= (TIM_CCER_CC1E | static_cast<uint32_t>(polarity)) << (channel * 4);
}

// ----------------------------------------------------------------------------
void
xpcc::stm32::Timer1::configureOutputChannel(uint32_t channel,
		OutputCompareMode mode, uint16_t compareValue)
{
	channel -= 1;	// 1..4 -> 0..3
	
	// disable output
	TIM1->CCER &= ~(0xf << (channel * 4));
	
	setCompareValue(channel + 1, compareValue);
	
	// enable preload (the compare value is loaded at each update event)
	uint32_t flags = static_cast<uint32_t>(mode) | TIM_CCMR1_OC1PE;
		
	if (channel <= 1)
	{
		uint32_t offset = 8 * channel;
		
		flags <<= offset;
		flags |= TIM1->CCMR1 & ~(0xff << offset);
		
		TIM1->CCMR1 = flags;
	}
	else {
		uint32_t offset = 8 * (channel - 2);
		
		flags <<= offset;
		flags |= TIM1->CCMR2 & ~(0xff << offset);
		
		TIM1->CCMR2 = flags; 
	}
	
	// Disable Repetition Counter (FIXME has to be done here for some unknown reason)
	TIM1->RCR = 0;
	
	if (mode != OutputCompareMode::Inactive) {
		TIM1->CCER |= (TIM_CCER_CC1E) << (channel * 4);
	}
}

void
xpcc::stm32::Timer1::configureOutputChannel(uint32_t channel,
OutputCompareMode mode,
PinState out, OutputComparePolarity polarity,
PinState out_n, OutputComparePolarity polarity_n,
OutputComparePreload preload)
{
	channel -= 1;	// 1..4 -> 0..3

	// disable output
	TIM1->CCER &= ~(0xf << (channel * 4));

	uint32_t flags = static_cast<uint32_t>(mode) | static_cast<uint32_t>(preload);

	if (channel <= 1)
	{
		uint32_t offset = 8 * channel;

		flags <<= offset;
		flags |= TIM1->CCMR1 & ~(0xff << offset);

		TIM1->CCMR1 = flags;
	}
	else {
		uint32_t offset = 8 * (channel - 2);

		flags <<= offset;
		flags |= TIM1->CCMR2 & ~(0xff << offset);

		TIM1->CCMR2 = flags; 
	}

	// Disable Repetition Counter (FIXME has to be done here for some unknown reason)
	TIM1->RCR = 0;

	// CCER Flags (Enable/Polarity)
	flags = (static_cast<uint32_t>(polarity_n) << 2) |
			(static_cast<uint32_t>(out_n)      << 2) |
			 static_cast<uint32_t>(polarity) | static_cast<uint32_t>(out);

	TIM1->CCER |= flags << (channel * 4);
}

void
xpcc::stm32::Timer1::configureOutputChannel(uint32_t channel,
uint32_t modeOutputPorts)
{
	channel -= 1;	// 1..4 -> 0..3

	{
		uint32_t flags = modeOutputPorts & (0x70);

		if (channel <= 1)
		{
			uint32_t offset = 8 * channel;

			flags <<= offset;
			flags |= TIM1->CCMR1 & ~(TIM_CCMR1_OC1M << offset);
			TIM1->CCMR1 = flags;
		}
		else {
			uint32_t offset = 8 * (channel - 2);

			flags <<= offset;
			flags |= TIM1->CCMR2 & ~(TIM_CCMR1_OC1M << offset);

			TIM1->CCMR2 = flags;
		}
	}

	// Disable Repetition Counter (FIXME has to be done here for some unknown reason)
	TIM1->RCR = 0;

	uint32_t flags = (modeOutputPorts & (0xf)) << (channel * 4);
	flags |= TIM1->CCER & ~(0xf << (channel * 4));
	TIM1->CCER = flags;
}

// ----------------------------------------------------------------------------
// Re-implemented here to save some code space. As all arguments in the calls
// below are constant the compiler is able to calculate everything at
// compile time.
static xpcc_always_inline void
nvicEnableInterrupt(IRQn_Type IRQn)
{
	NVIC->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

static xpcc_always_inline void
nvicDisableInterrupt(IRQn_Type IRQn)
{
	NVIC_DisableIRQ(IRQn);
}
#	define TIM1_BRK_IRQn		TIM1_BRK_TIM9_IRQn
#	define TIM1_UP_IRQn			TIM1_UP_TIM10_IRQn
#	define TIM1_TRG_COM_IRQn	TIM1_TRG_COM_TIM11_IRQn
// ----------------------------------------------------------------------------
void
xpcc::stm32::Timer1::enableInterruptVector(Interrupt interrupt, bool enable, uint32_t priority)
{
	if (enable)
	{
		if (interrupt & Interrupt::Update) {
			NVIC_SetPriority(TIM1_UP_IRQn, priority);
			nvicEnableInterrupt(TIM1_UP_IRQn);
		}
		
		if (interrupt & Interrupt::Break) {
			NVIC_SetPriority(TIM1_BRK_IRQn, priority);
			nvicEnableInterrupt(TIM1_BRK_IRQn);
		}
		
		if (interrupt & (Interrupt::COM | Interrupt::Trigger)) {
			NVIC_SetPriority(TIM1_TRG_COM_IRQn, priority);
			nvicEnableInterrupt(TIM1_TRG_COM_IRQn);
		}	
		if (interrupt & 
				(Interrupt::CaptureCompare1 | Interrupt::CaptureCompare2 |
				 Interrupt::CaptureCompare3 | Interrupt::CaptureCompare4)) {
			NVIC_SetPriority(TIM1_CC_IRQn, priority);
			nvicEnableInterrupt(TIM1_CC_IRQn);
		}
	}
	else
	{
		if (interrupt & Interrupt::Update) {
			nvicDisableInterrupt(TIM1_UP_IRQn);
		}
		
		if (interrupt & Interrupt::Break) {
			nvicDisableInterrupt(TIM1_BRK_IRQn);
		}
		
		if (interrupt & (Interrupt::COM | Interrupt::Trigger)) {
			nvicDisableInterrupt(TIM1_TRG_COM_IRQn);
		}
		if (interrupt & 
				(Interrupt::CaptureCompare1 | Interrupt::CaptureCompare2 |
				 Interrupt::CaptureCompare3 | Interrupt::CaptureCompare4)) {
			nvicDisableInterrupt(TIM1_CC_IRQn);
		}
	}
}