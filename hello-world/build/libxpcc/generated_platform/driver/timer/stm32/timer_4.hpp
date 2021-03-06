// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_TIMER_4_HPP
#define XPCC_STM32_TIMER_4_HPP

#include "../../../type_ids.hpp"
#include "general_purpose_base.hpp"

namespace xpcc
{
namespace stm32
{
/**
 * General Purpose Timer 4
 *
 * Interrupt handler:
 * @code
 * extern "C" void
 * TIM4_IRQHandler(void)
 * {
 *     Timer4::resetInterruptFlags(Timer4::...);
 *
 *     ...
 * }
 * @endcode
 *
 * @warning	The Timer has much more possibilities than presented by this
 * 			interface (e.g. Input Capture, Trigger for other Timers, DMA).
 * 			It might be expanded in the future.
 *
 * @author		Fabian Greif
 * @ingroup		stm32f407vg_timer
 */
class Timer4 : public GeneralPurposeTimer
{
public:
	/// TypeId used to connect GPIO pins to this peripheral's Channel1.
	static const TypeId::Timer4Channel1 Channel1;
	/// TypeId used to connect GPIO pins to this peripheral's Channel2.
	static const TypeId::Timer4Channel2 Channel2;
	/// TypeId used to connect GPIO pins to this peripheral's Channel3.
	static const TypeId::Timer4Channel3 Channel3;
	/// TypeId used to connect GPIO pins to this peripheral's Channel4.
	static const TypeId::Timer4Channel4 Channel4;
	/// TypeId used to connect GPIO pins to this peripheral's ExternalTrigger.
	static const TypeId::Timer4ExternalTrigger ExternalTrigger;
public:
	enum class MasterMode : uint32_t
	{
		Reset 			= 0,							// 0b000
		Enable 			= TIM_CR2_MMS_0,				// 0b001
		Update 			= TIM_CR2_MMS_1,				// 0b010
		Pulse 			= TIM_CR2_MMS_1 | TIM_CR2_MMS_0,// 0b011
		CompareOc1Ref 	= TIM_CR2_MMS_2,				// 0b100
		CompareOc2Ref 	= TIM_CR2_MMS_2 | TIM_CR2_MMS_0,// 0b101
		// Only available on TIM2/3/4
		CompareOc3Ref 	= TIM_CR2_MMS_2 | TIM_CR2_MMS_1,// 0b110
		CompareOc4Ref 	= TIM_CR2_MMS_2 | TIM_CR2_MMS_1	// 0b111
										| TIM_CR2_MMS_0,
	};

	enum class SlaveModeTrigger : uint32_t
	{
		Internal1 = TIM_SMCR_TS_0,
		Internal2 = TIM_SMCR_TS_1,
		TimerInput1EdgeDetector = TIM_SMCR_TS_2,
		TimerInput1Filtered = TIM_SMCR_TS_2 | TIM_SMCR_TS_0,
		TimerInput2Filtered = TIM_SMCR_TS_2 | TIM_SMCR_TS_1,
		External = TIM_SMCR_TS_2 | TIM_SMCR_TS_1 | TIM_SMCR_TS_0,
	};

	enum class SlaveMode : uint32_t
	{
		/// Slave mode disabled - if CEN = '1' then the prescaler is clocked directly by the internal clock.
		Disabled	= 0,
		/// Counter counts up/down on TI2FP2 edge depending on TI1FP1 level.
		Encoder1	= TIM_SMCR_SMS_0,
		/// Counter counts up/down on TI1FP1 edge depending on TI2FP2 level.
		Encoder2	= TIM_SMCR_SMS_1,
		/// Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input.
		Encoder3	= TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0,
		/// Rising edge of the selected trigger input (TRGI) reinitializes the counter and generates an update of the registers.
		Reset		= TIM_SMCR_SMS_2,
		/// The counter clock is enabled when the trigger input (TRGI) is high. The counter stops (but is not reset) as soon as the trigger becomes low. Both start and stop of the counter are controlled.
		Gated		= TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0,
		/// The counter starts at a rising edge of the trigger TRGI (but it is not reset). Only the start of the counter is controlled.
		Trigger	= TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1,
		/// Rising edges of the selected trigger (TRGI) clock the counter.
		ExternalClock = TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0,
	};

	// This type is the internal size of the counter.
	// Timer 2 and 5 are the only one which have the size of 32 bit and
	// only on stm32f2, stm32f4 and stm32f7
	typedef uint16_t Value;

	// Just enable the clock of the peripheral
	static void
	clockEnable();

	// Enables the clock and resets the timer
	static void
	enable();

	static void
	disable();

	static inline void
	pause()
	{
		TIM4->CR1 &= ~TIM_CR1_CEN;
	}

	static inline void
	start()
	{
		TIM4->CR1 |= TIM_CR1_CEN;
	}

	static void
	setMode(Mode mode,
			SlaveMode slaveMode = SlaveMode::Disabled,
			SlaveModeTrigger slaveModeTrigger = static_cast<SlaveModeTrigger>(0),
			MasterMode masterMode = MasterMode::Reset,
			bool enableOnePulseMode = false);

	static inline void
	setPrescaler(uint16_t prescaler)
	{
		// Because a prescaler of zero is not possible the actual
		// prescaler value is \p prescaler - 1 (see Datasheet)
		TIM4->PSC = prescaler - 1;
	}

	static inline void
	setOverflow(Value overflow)
	{
		TIM4->ARR = overflow;
	}

	template<class SystemClock>
	static Value
	setPeriod(uint32_t microseconds, bool autoApply = true)
	{
		// This will be inaccurate for non-smooth frequencies (last six digits
		// unequal to zero)
		uint32_t cycles = microseconds * (SystemClock::Timer4 / 1000000UL);
		uint16_t prescaler = (cycles + 65535) / 65536;	// always round up
		Value overflow = cycles / prescaler;

		overflow = overflow - 1;	// e.g. 36000 cycles are from 0 to 35999

		setPrescaler(prescaler);
		setOverflow(overflow);

		if (autoApply) {
			// Generate Update Event to apply the new settings for ARR
			TIM4->EGR |= TIM_EGR_UG;
		}

		return overflow;
	}

	static inline void
	applyAndReset()
	{
		// Generate Update Event to apply the new settings for ARR
		TIM4->EGR |= TIM_EGR_UG;
	}

	static inline Value
	getValue()
	{
		return TIM4->CNT;
	}

	static inline void
	setValue(Value value)
	{
		TIM4->CNT = value;
	}

public:
	static void
	configureInputChannel(uint32_t channel, InputCaptureMapping input,
			InputCapturePrescaler prescaler,
			InputCapturePolarity polarity, uint8_t filter,
			bool xor_ch1_3=false);

	static void
	configureOutputChannel(uint32_t channel, OutputCompareMode_t mode,
			Value compareValue, PinState out = PinState::Enable);

	/// Switch to Pwm Mode 2
	///
	/// While upcounting channel will be active as long as the time value is
	/// smaller than the compare value, else inactive.
	/// Timer will not be disabled while switching modes.
	static void
	setInvertedPwm(uint32_t channel)
	{
		channel -= 1;	// 1..2 -> 0..1

		{
			uint32_t flags = static_cast<uint32_t>(OutputCompareMode::Pwm2);

			if (channel <= 1)
			{
				uint32_t offset = 8 * channel;

				flags <<= offset;
				flags |= TIM4->CCMR1 & ~(TIM_CCMR1_OC1M << offset);
				TIM4->CCMR1 = flags;
			}
			else {
				uint32_t offset = 8 * (channel - 2);

				flags <<= offset;
				flags |= TIM4->CCMR2 & ~(TIM_CCMR1_OC1M << offset);

				TIM4->CCMR2 = flags;
			}
		}
	}

	/// Switch to Pwm Mode 1
	///
	/// While upcounting channel will be inactive as long as the time value is
	/// smaller than the compare value, else active.
	/// **Please note**: Timer will not be disabled while switching modes.
	static void
	setNormalPwm(uint32_t channel)
	{
		channel -= 1;	// 1..2 -> 0..1

		{
			uint32_t flags = static_cast<uint32_t>(OutputCompareMode::Pwm);

			if (channel <= 1)
			{
				uint32_t offset = 8 * channel;

				flags <<= offset;
				flags |= TIM4->CCMR1 & ~(TIM_CCMR1_OC1M << offset);
				TIM4->CCMR1 = flags;
			}
			else {
				uint32_t offset = 8 * (channel - 2);

				flags <<= offset;
				flags |= TIM4->CCMR2 & ~(TIM_CCMR1_OC1M << offset);

				TIM4->CCMR2 = flags;
			}
		}
	}

	/// Switch to Inactive Mode
	///
	/// The channel output will be forced to the inactive level.
	/// **Please note**: Timer will not be disabled while switching modes.
	static void
	forceInactive(uint32_t channel)
	{
		channel -= 1;	// 1..2 -> 0..1

		{
			uint32_t flags = static_cast<uint32_t>(OutputCompareMode::ForceLow);

			if (channel <= 1)
			{
				uint32_t offset = 8 * channel;

				flags <<= offset;
				flags |= TIM4->CCMR1 & ~(TIM_CCMR1_OC1M << offset);
				TIM4->CCMR1 = flags;
			}
			else {
				uint32_t offset = 8 * (channel - 2);

				flags <<= offset;
				flags |= TIM4->CCMR2 & ~(TIM_CCMR1_OC1M << offset);

				TIM4->CCMR2 = flags;
			}
		}
	}

	/// Switch to Active Mode
	///
	/// The channel output will be forced to the active level.
	/// **Please note**: Timer will not be disabled while switching modes.
	static void
	forceActive(uint32_t channel)
	{
		channel -= 1;	// 1..2 -> 0..1

		{
			uint32_t flags = static_cast<uint32_t>(OutputCompareMode::ForceHigh);

			if (channel <= 1)
			{
				uint32_t offset = 8 * channel;

				flags <<= offset;
				flags |= TIM4->CCMR1 & ~(TIM_CCMR1_OC1M << offset);
				TIM4->CCMR1 = flags;
			}
			else {
				uint32_t offset = 8 * (channel - 2);

				flags <<= offset;
				flags |= TIM4->CCMR2 & ~(TIM_CCMR1_OC1M << offset);

				TIM4->CCMR2 = flags;
			}
		}
	}


	static inline void
	setCompareValue(uint32_t channel, Value value)
	{
		*(&TIM4->CCR1 + (channel - 1)) = value;
	}

	static inline Value
	getCompareValue(uint32_t channel)
	{
		return *(&TIM4->CCR1 + (channel - 1));
	}

public:
	static void
	enableInterruptVector(bool enable, uint32_t priority);

	static inline void
	enableInterrupt(Interrupt_t interrupt)
	{
		TIM4->DIER |= interrupt.value;
	}

	static inline void
	disableInterrupt(Interrupt_t interrupt)
	{
		TIM4->DIER &= ~interrupt.value;
	}

	static inline void
	enableDmaRequest(DmaRequestEnable dmaRequests)
	{
		TIM4->DIER |= static_cast<uint32_t>(dmaRequests);
	}

	static inline void
	disableDmaRequest(DmaRequestEnable dmaRequests)
	{
		TIM4->DIER &= ~static_cast<uint32_t>(dmaRequests);
	}

	static inline InterruptFlag_t
	getInterruptFlags()
	{
		return InterruptFlag_t(TIM4->SR);
	}

	static inline void
	acknowledgeInterruptFlags(InterruptFlag_t flags)
	{
		// Flags are cleared by writing a zero to the flag position.
		// Writing a one is ignored.
		TIM4->SR = ~flags.value;
	}
};

}	// namespace stm32

}	// namespace xpcc

#endif // XPCC_STM32_TIMER_4_HPP