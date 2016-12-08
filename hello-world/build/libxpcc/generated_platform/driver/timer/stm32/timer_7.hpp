// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_TIMER_7_HPP
#define XPCC_STM32_TIMER_7_HPP

#include "../../../type_ids.hpp"
#include "basic_base.hpp"

namespace xpcc
{

namespace stm32
{

/**
 * @brief		Basic Timer 7
 *
 * Interrupt handler:
 * \code
 * extern "C" void
 * TIM7_IRQHandler(void)
 * {
 *     Timer7::resetInterruptFlags(Timer7::FLAG_UPDATE);
 *
 *     ...
 * }
 * \endcode
 *
 
 *
 * @author		Fabian Greif
 * @ingroup		stm32f407vg_timer
 */
class Timer7 : public BasicTimer
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
		TIM7->CR1 &= ~TIM_CR1_CEN;
	}

	static inline void
	start()
	{
		TIM7->CR1 |= TIM_CR1_CEN;
	}

	static void
	setMode(Mode mode);

	static inline void
	setPrescaler(uint16_t prescaler)
	{
		// Because a prescaler of zero is not possible the actual
		// prescaler value is \p prescaler - 1 (see Datasheet)
		TIM7->PSC = prescaler - 1;
	}

	static inline void
	setOverflow(uint16_t overflow)
	{
		TIM7->ARR = overflow;
	}

	template<class SystemClock>
	static uint16_t
	setPeriod(uint32_t microseconds, bool autoApply = true)
	{
		// This will be inaccurate for non-smooth frequencies (last six digits
		// unequal to zero)
		uint32_t cycles = microseconds * (SystemClock::Timer7 / 1000000UL);

		uint16_t prescaler = (cycles + 65535) / 65536;	// always round up
		uint16_t overflow = cycles / prescaler;

		overflow = overflow - 1;	// e.g. 36000 cycles are from 0 to 35999
		setPrescaler(prescaler);
		setOverflow(overflow);

		if (autoApply) {
			// Generate Update Event to apply the new settings for ARR
			TIM7->EGR |= TIM_EGR_UG;
		}

		return overflow;
	}

	static inline void
	applyAndReset()
	{
		// Generate Update Event to apply the new settings for ARR
		TIM7->EGR |= TIM_EGR_UG;
	}

	static inline uint16_t
	getValue()
	{
		return TIM7->CNT;
	}

	static inline void
	setValue(uint16_t value)
	{
		TIM7->CNT = value;
	}

	static void
	enableInterruptVector(bool enable, uint32_t priority);

	static inline void
	enableInterrupt(Interrupt_t interrupt)
	{
		TIM7->DIER |= interrupt.value;
	}

	static inline void
	disableInterrupt(Interrupt_t interrupt)
	{
		TIM7->DIER &= ~interrupt.value;
	}

	static inline InterruptFlag_t
	getInterruptFlags()
	{
		return InterruptFlag_t(TIM7->SR);
	}

	static void
	acknowledgeInterruptFlags(InterruptFlag_t interrupt)
	{
		// Flags are cleared by writing a zero to the flag position.
		// Writing a one is ignored.
		TIM7->SR = ~interrupt.value;
	}
};

}	// namespace stm32

}	// namespace xpcc

#endif // XPCC_STM32_TIMER_7_HPP