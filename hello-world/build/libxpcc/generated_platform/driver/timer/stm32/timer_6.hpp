// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_TIMER_6_HPP
#define XPCC_STM32_TIMER_6_HPP

#include "../../../type_ids.hpp"
#include "basic_base.hpp"

namespace xpcc
{

namespace stm32
{

/**
 * @brief		Basic Timer 6
 *
 * Interrupt handler:
 * \code
 * extern "C" void
 * TIM6_IRQHandler(void)
 * {
 *     Timer6::resetInterruptFlags(Timer6::FLAG_UPDATE);
 *
 *     ...
 * }
 * \endcode
 *
 * For the STM32F2xx and STM32F4xx:
 * \code
 * extern "C" void
 * TIM6_DAC_IRQHandler(void)
 * {
 *     Timer6::resetInterruptFlags(Timer6::FLAG_UPDATE);
 *
 *     ...
 * }
 * \endcode
 *
 * @author		Fabian Greif
 * @ingroup		stm32f407vg_timer
 */
class Timer6 : public BasicTimer
{
public:

public:
	static void
	enable();

	static void
	disable();

	static inline void
	pause()
	{
		TIM6->CR1 &= ~TIM_CR1_CEN;
	}

	static inline void
	start()
	{
		TIM6->CR1 |= TIM_CR1_CEN;
	}

	static void
	setMode(Mode mode);

	static inline void
	setPrescaler(uint16_t prescaler)
	{
		// Because a prescaler of zero is not possible the actual
		// prescaler value is \p prescaler - 1 (see Datasheet)
		TIM6->PSC = prescaler - 1;
	}

	static inline void
	setOverflow(uint16_t overflow)
	{
		TIM6->ARR = overflow;
	}

	template<class SystemClock>
	static uint16_t
	setPeriod(uint32_t microseconds, bool autoApply = true)
	{
		// This will be inaccurate for non-smooth frequencies (last six digits
		// unequal to zero)
		uint32_t cycles = microseconds * (SystemClock::Timer6 / 1000000UL);

		uint16_t prescaler = (cycles + 65535) / 65536;	// always round up
		uint16_t overflow = cycles / prescaler;

		overflow = overflow - 1;	// e.g. 36000 cycles are from 0 to 35999
		setPrescaler(prescaler);
		setOverflow(overflow);

		if (autoApply) {
			// Generate Update Event to apply the new settings for ARR
			TIM6->EGR |= TIM_EGR_UG;
		}

		return overflow;
	}

	static inline void
	applyAndReset()
	{
		// Generate Update Event to apply the new settings for ARR
		TIM6->EGR |= TIM_EGR_UG;
	}

	static inline uint16_t
	getValue()
	{
		return TIM6->CNT;
	}

	static inline void
	setValue(uint16_t value)
	{
		TIM6->CNT = value;
	}

	static void
	enableInterruptVector(bool enable, uint32_t priority);

	static inline void
	enableInterrupt(Interrupt_t interrupt)
	{
		TIM6->DIER |= interrupt.value;
	}

	static inline void
	disableInterrupt(Interrupt_t interrupt)
	{
		TIM6->DIER &= ~interrupt.value;
	}

	static inline InterruptFlag_t
	getInterruptFlags()
	{
		return InterruptFlag_t(TIM6->SR);
	}

	static void
	acknowledgeInterruptFlags(InterruptFlag_t interrupt)
	{
		// Flags are cleared by writing a zero to the flag position.
		// Writing a one is ignored.
		TIM6->SR = ~interrupt.value;
	}
};

}	// namespace stm32

}	// namespace xpcc

#endif // XPCC_STM32_TIMER_6_HPP