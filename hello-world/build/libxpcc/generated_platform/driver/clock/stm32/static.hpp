// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2011, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32__STATIC_HPP
#define XPCC_STM32__STATIC_HPP

#include <stdint.h>		// uint32_t
#include "../../../device.hpp"
#include "../../../type_ids.hpp"
#include "../generic/common_clock.hpp"
#include "pll_calculator.hpp"
#include "clock.hpp"

using namespace xpcc::clock;


namespace xpcc
{
	namespace stm32
	{

		/*
		 * Used to setup pll with constants
		 */
		template<int InputFrequency, int OutputFrequency, int UsbFrequency, ClockControl::PllSource Source>
		class PllSetup
		{
		private:
			typedef Stm32F2F4PllSettings<MHz192, InputFrequency, OutputFrequency, UsbFrequency> p;
		public:
			static StartupError
			enable()
			{
				ClockControl::enablePll(Source, p::PllM, p::PllN, p::PllP, p::PllQ);

				xpcc::clock::fcpu     = OutputFrequency;
				xpcc::clock::fcpu_kHz = OutputFrequency / 1000;
				xpcc::clock::fcpu_MHz = OutputFrequency / 1000000;
				xpcc::clock::ns_per_loop = ::round(1000000000.f / OutputFrequency * 3.f);
				return StartupError::None;
			}
		};



	// Static Clocks/Plls/Osciallators
template<int InputFrequency> class InternalClock;

template<>
class
InternalClock<MHz16>
{
private:


public:
	static const ::xpcc::stm32::TypeId::InternalClock Id;

	static StartupError
	enable(const uint32_t waitCycles = 1500)
	{
		if (!ClockControl::enableInternalClock(waitCycles))
			return StartupError::InternalClock;


		ClockControl::setApb1Prescaler(ClockControl::Apb1Prescaler::Div4);
		ClockControl::setApb2Prescaler(ClockControl::Apb2Prescaler::Div2);
		return StartupError::None;
	}

	static constexpr int
	outputFrequency = MHz16;
};


template<int InputFrequency>
class
ExternalClock
{
private:


public:
	static const ::xpcc::stm32::TypeId::ExternalClock Id;

	static StartupError
	enable(const uint32_t waitCycles = 1500)
	{
		if (!ClockControl::enableExternalClock(waitCycles))
			return StartupError::ExternalClock;


		ClockControl::setApb1Prescaler(ClockControl::Apb1Prescaler::Div4);
		ClockControl::setApb2Prescaler(ClockControl::Apb2Prescaler::Div2);
		return StartupError::None;
	}

	static constexpr int
	outputFrequency = InputFrequency;
};


template<int InputFrequency>
class
ExternalCrystal
{
private:


public:
	static const ::xpcc::stm32::TypeId::ExternalCrystal Id;

	static StartupError
	enable(const uint32_t waitCycles = 1500)
	{
		if (!ClockControl::enableExternalCrystal(waitCycles))
			return StartupError::ExternalCrystal;


		ClockControl::setApb1Prescaler(ClockControl::Apb1Prescaler::Div4);
		ClockControl::setApb2Prescaler(ClockControl::Apb2Prescaler::Div2);
		return StartupError::None;
	}

	static constexpr int
	outputFrequency = InputFrequency;
};


template<class Input, int OutputFrequency, int UsbFrequency> class Pll;

template<int InputFrequency, int OutputFrequency, int UsbFrequency>
class
Pll<InternalClock<InputFrequency>, OutputFrequency, UsbFrequency>
{
public:
	static const ::xpcc::stm32::TypeId::Pll Id;

	static StartupError
	enable(const uint32_t waitCycles = 1500)
	{
		StartupError err = StartupError::None;
		err = InternalClock<InputFrequency>::enable(waitCycles);
		if (err != StartupError::None) return err;
		return PllSetup<InputFrequency,
				OutputFrequency, UsbFrequency,
				ClockControl::PllSource::InternalClock>::enable();
	}
	static constexpr int
	outputFrequency = OutputFrequency;
};
template<int InputFrequency, int OutputFrequency, int UsbFrequency>
class
Pll<ExternalClock<InputFrequency>, OutputFrequency, UsbFrequency>
{
public:
	static const ::xpcc::stm32::TypeId::Pll Id;

	static StartupError
	enable(const uint32_t waitCycles = 1500)
	{
		StartupError err = StartupError::None;
		err = ExternalClock<InputFrequency>::enable(waitCycles);
		if (err != StartupError::None) return err;
		return PllSetup<InputFrequency,
				OutputFrequency, UsbFrequency,
				ClockControl::PllSource::ExternalClock>::enable();
	}
	static constexpr int
	outputFrequency = OutputFrequency;
};
template<int InputFrequency, int OutputFrequency, int UsbFrequency>
class
Pll<ExternalCrystal<InputFrequency>, OutputFrequency, UsbFrequency>
{
public:
	static const ::xpcc::stm32::TypeId::Pll Id;

	static StartupError
	enable(const uint32_t waitCycles = 1500)
	{
		StartupError err = StartupError::None;
		err = ExternalCrystal<InputFrequency>::enable(waitCycles);
		if (err != StartupError::None) return err;
		return PllSetup<InputFrequency,
				OutputFrequency, UsbFrequency,
				ClockControl::PllSource::ExternalCrystal>::enable();
	}
	static constexpr int
	outputFrequency = OutputFrequency;
};


template<class Input> class SystemClock;


template<int OutputFrequency>
class
SystemClock<InternalClock<OutputFrequency> >
{
private:
	static_assert(OutputFrequency >= MHz8,
		"OutputFrequency of SystemClock needs to be higher or equal to MHz8");

	static_assert(OutputFrequency <= MHz168,
		"OutputFrequency of SystemClock needs to be lower or equal to MHz168");

public:
	/// TypeId to connect an Output to SystemClock
	static const ::xpcc::stm32::TypeId::SystemClock Id;

	// Frequencies
	static constexpr int Frequency = OutputFrequency;
	static constexpr int AHB = Frequency * 1;
	static constexpr int SystemTimer = AHB * 1/8;

	static constexpr int APB1 = AHB * 1/4;
	static constexpr int APB1Timers = APB1 * 2;
	static constexpr int Timer2 = APB1Timers;

	static constexpr int Timer3 = APB1Timers;

	static constexpr int Timer4 = APB1Timers;

	static constexpr int Timer5 = APB1Timers;

	static constexpr int Timer6 = APB1Timers;

	static constexpr int Timer7 = APB1Timers;

	static constexpr int Timer12 = APB1Timers;

	static constexpr int Timer13 = APB1Timers;

	static constexpr int Timer14 = APB1Timers;


	static constexpr int Dac = APB1;

	static constexpr int Can1 = APB1;

	static constexpr int Can2 = APB1;

	static constexpr int I2c1 = APB1;

	static constexpr int I2c2 = APB1;

	static constexpr int I2c3 = APB1;

	static constexpr int Spi2 = APB1;

	static constexpr int Spi3 = APB1;

	static constexpr int Usart2 = APB1;

	static constexpr int Usart3 = APB1;

	static constexpr int Uart4 = APB1;

	static constexpr int Uart5 = APB1;

	static constexpr int Uart7 = APB1;

	static constexpr int Uart8 = APB1;


	static constexpr int APB2 = AHB * 1/2;
	static constexpr int APB2Timers = APB2 * 2;
	static constexpr int Timer1 = APB2Timers;

	static constexpr int Timer8 = APB2Timers;

	static constexpr int Timer9 = APB2Timers;

	static constexpr int Timer10 = APB2Timers;

	static constexpr int Timer11 = APB2Timers;


	static constexpr int Spi1 = APB2;

	static constexpr int Spi4 = APB2;

	static constexpr int Spi5 = APB2;

	static constexpr int Spi6 = APB2;

	static constexpr int Sdio = APB2;

	static constexpr int Adc = APB2;

	static constexpr int Usart1 = APB2;

	static constexpr int Usart6 = APB2;


	static constexpr int Dma = AHB;

	static constexpr int Gpio = AHB;


	static constexpr int AHB3 = Frequency * 1;
	static constexpr int Fsmc = AHB3;


	static StartupError
	enable(const uint32_t waitCycles = 1500)
	{
		StartupError err =  InternalClock<OutputFrequency>::enable(waitCycles);
		if (err != StartupError::None) return err;
		ClockControl::setFlashLatency(OutputFrequency);
		if(ClockControl::enableSystemClock(
				ClockControl::SystemClockSource::InternalClock, waitCycles))
			return StartupError::None;
		return StartupError::InternalClock;
	}
};

template<int OutputFrequency>
class
SystemClock<ExternalClock<OutputFrequency> >
{
private:
	static_assert(OutputFrequency >= MHz8,
		"OutputFrequency of SystemClock needs to be higher or equal to MHz8");

	static_assert(OutputFrequency <= MHz168,
		"OutputFrequency of SystemClock needs to be lower or equal to MHz168");

public:
	/// TypeId to connect an Output to SystemClock
	static const ::xpcc::stm32::TypeId::SystemClock Id;

	// Frequencies
	static constexpr int Frequency = OutputFrequency;
	static constexpr int AHB = Frequency * 1;
	static constexpr int SystemTimer = AHB * 1/8;

	static constexpr int APB1 = AHB * 1/4;
	static constexpr int APB1Timers = APB1 * 2;
	static constexpr int Timer2 = APB1Timers;

	static constexpr int Timer3 = APB1Timers;

	static constexpr int Timer4 = APB1Timers;

	static constexpr int Timer5 = APB1Timers;

	static constexpr int Timer6 = APB1Timers;

	static constexpr int Timer7 = APB1Timers;

	static constexpr int Timer12 = APB1Timers;

	static constexpr int Timer13 = APB1Timers;

	static constexpr int Timer14 = APB1Timers;


	static constexpr int Dac = APB1;

	static constexpr int Can1 = APB1;

	static constexpr int Can2 = APB1;

	static constexpr int I2c1 = APB1;

	static constexpr int I2c2 = APB1;

	static constexpr int I2c3 = APB1;

	static constexpr int Spi2 = APB1;

	static constexpr int Spi3 = APB1;

	static constexpr int Usart2 = APB1;

	static constexpr int Usart3 = APB1;

	static constexpr int Uart4 = APB1;

	static constexpr int Uart5 = APB1;

	static constexpr int Uart7 = APB1;

	static constexpr int Uart8 = APB1;


	static constexpr int APB2 = AHB * 1/2;
	static constexpr int APB2Timers = APB2 * 2;
	static constexpr int Timer1 = APB2Timers;

	static constexpr int Timer8 = APB2Timers;

	static constexpr int Timer9 = APB2Timers;

	static constexpr int Timer10 = APB2Timers;

	static constexpr int Timer11 = APB2Timers;


	static constexpr int Spi1 = APB2;

	static constexpr int Spi4 = APB2;

	static constexpr int Spi5 = APB2;

	static constexpr int Spi6 = APB2;

	static constexpr int Sdio = APB2;

	static constexpr int Adc = APB2;

	static constexpr int Usart1 = APB2;

	static constexpr int Usart6 = APB2;


	static constexpr int Dma = AHB;

	static constexpr int Gpio = AHB;


	static constexpr int AHB3 = Frequency * 1;
	static constexpr int Fsmc = AHB3;


	static StartupError
	enable(const uint32_t waitCycles = 1500)
	{
		StartupError err =  ExternalClock<OutputFrequency>::enable(waitCycles);
		if (err != StartupError::None) return err;
		ClockControl::setFlashLatency(OutputFrequency);
		if(ClockControl::enableSystemClock(
				ClockControl::SystemClockSource::ExternalClock, waitCycles))
			return StartupError::None;
		return StartupError::ExternalClock;
	}
};

template<int OutputFrequency>
class
SystemClock<ExternalCrystal<OutputFrequency> >
{
private:
	static_assert(OutputFrequency >= MHz8,
		"OutputFrequency of SystemClock needs to be higher or equal to MHz8");

	static_assert(OutputFrequency <= MHz168,
		"OutputFrequency of SystemClock needs to be lower or equal to MHz168");

public:
	/// TypeId to connect an Output to SystemClock
	static const ::xpcc::stm32::TypeId::SystemClock Id;

	// Frequencies
	static constexpr int Frequency = OutputFrequency;
	static constexpr int AHB = Frequency * 1;
	static constexpr int SystemTimer = AHB * 1/8;

	static constexpr int APB1 = AHB * 1/4;
	static constexpr int APB1Timers = APB1 * 2;
	static constexpr int Timer2 = APB1Timers;

	static constexpr int Timer3 = APB1Timers;

	static constexpr int Timer4 = APB1Timers;

	static constexpr int Timer5 = APB1Timers;

	static constexpr int Timer6 = APB1Timers;

	static constexpr int Timer7 = APB1Timers;

	static constexpr int Timer12 = APB1Timers;

	static constexpr int Timer13 = APB1Timers;

	static constexpr int Timer14 = APB1Timers;


	static constexpr int Dac = APB1;

	static constexpr int Can1 = APB1;

	static constexpr int Can2 = APB1;

	static constexpr int I2c1 = APB1;

	static constexpr int I2c2 = APB1;

	static constexpr int I2c3 = APB1;

	static constexpr int Spi2 = APB1;

	static constexpr int Spi3 = APB1;

	static constexpr int Usart2 = APB1;

	static constexpr int Usart3 = APB1;

	static constexpr int Uart4 = APB1;

	static constexpr int Uart5 = APB1;

	static constexpr int Uart7 = APB1;

	static constexpr int Uart8 = APB1;


	static constexpr int APB2 = AHB * 1/2;
	static constexpr int APB2Timers = APB2 * 2;
	static constexpr int Timer1 = APB2Timers;

	static constexpr int Timer8 = APB2Timers;

	static constexpr int Timer9 = APB2Timers;

	static constexpr int Timer10 = APB2Timers;

	static constexpr int Timer11 = APB2Timers;


	static constexpr int Spi1 = APB2;

	static constexpr int Spi4 = APB2;

	static constexpr int Spi5 = APB2;

	static constexpr int Spi6 = APB2;

	static constexpr int Sdio = APB2;

	static constexpr int Adc = APB2;

	static constexpr int Usart1 = APB2;

	static constexpr int Usart6 = APB2;


	static constexpr int Dma = AHB;

	static constexpr int Gpio = AHB;


	static constexpr int AHB3 = Frequency * 1;
	static constexpr int Fsmc = AHB3;


	static StartupError
	enable(const uint32_t waitCycles = 1500)
	{
		StartupError err =  ExternalCrystal<OutputFrequency>::enable(waitCycles);
		if (err != StartupError::None) return err;
		ClockControl::setFlashLatency(OutputFrequency);
		if(ClockControl::enableSystemClock(
				ClockControl::SystemClockSource::ExternalCrystal, waitCycles))
			return StartupError::None;
		return StartupError::ExternalCrystal;
	}
};

template<class Input, int OutputFrequency, int UsbFrequency>
class
SystemClock<Pll<Input, OutputFrequency, UsbFrequency> >
{
private:
	static_assert(OutputFrequency >= MHz8,
		"OutputFrequency of SystemClock needs to be higher or equal to MHz8");

	static_assert(OutputFrequency <= MHz168,
		"OutputFrequency of SystemClock needs to be lower or equal to MHz168");

public:
	/// TypeId to connect an Output to SystemClock
	static const ::xpcc::stm32::TypeId::SystemClock Id;

	// Frequencies
	static constexpr int Frequency = OutputFrequency;
	static constexpr int AHB = Frequency * 1;
	static constexpr int SystemTimer = AHB * 1/8;

	static constexpr int APB1 = AHB * 1/4;
	static constexpr int APB1Timers = APB1 * 2;
	static constexpr int Timer2 = APB1Timers;

	static constexpr int Timer3 = APB1Timers;

	static constexpr int Timer4 = APB1Timers;

	static constexpr int Timer5 = APB1Timers;

	static constexpr int Timer6 = APB1Timers;

	static constexpr int Timer7 = APB1Timers;

	static constexpr int Timer12 = APB1Timers;

	static constexpr int Timer13 = APB1Timers;

	static constexpr int Timer14 = APB1Timers;


	static constexpr int Dac = APB1;

	static constexpr int Can1 = APB1;

	static constexpr int Can2 = APB1;

	static constexpr int I2c1 = APB1;

	static constexpr int I2c2 = APB1;

	static constexpr int I2c3 = APB1;

	static constexpr int Spi2 = APB1;

	static constexpr int Spi3 = APB1;

	static constexpr int Usart2 = APB1;

	static constexpr int Usart3 = APB1;

	static constexpr int Uart4 = APB1;

	static constexpr int Uart5 = APB1;

	static constexpr int Uart7 = APB1;

	static constexpr int Uart8 = APB1;


	static constexpr int APB2 = AHB * 1/2;
	static constexpr int APB2Timers = APB2 * 2;
	static constexpr int Timer1 = APB2Timers;

	static constexpr int Timer8 = APB2Timers;

	static constexpr int Timer9 = APB2Timers;

	static constexpr int Timer10 = APB2Timers;

	static constexpr int Timer11 = APB2Timers;


	static constexpr int Spi1 = APB2;

	static constexpr int Spi4 = APB2;

	static constexpr int Spi5 = APB2;

	static constexpr int Spi6 = APB2;

	static constexpr int Sdio = APB2;

	static constexpr int Adc = APB2;

	static constexpr int Usart1 = APB2;

	static constexpr int Usart6 = APB2;


	static constexpr int Dma = AHB;

	static constexpr int Gpio = AHB;


	static constexpr int AHB3 = Frequency * 1;
	static constexpr int Fsmc = AHB3;


	static StartupError
	enable(const uint32_t waitCycles = 1500)
	{
		StartupError err =  Pll<Input, OutputFrequency, UsbFrequency>::enable(waitCycles);
		if (err != StartupError::None) return err;
		ClockControl::setFlashLatency(OutputFrequency);
		if(ClockControl::enableSystemClock(
				ClockControl::SystemClockSource::Pll, waitCycles))
			return StartupError::None;
		return StartupError::Pll;
	}
};


class ClockOutput1
{
public:
	static const ::xpcc::stm32::TypeId::ClockOutput1 Id;

	enum class Division
	{
		By1 = 1,
		By2 = 2,
		By3 = 3,
		By4 = 4,
		By5 = 5,
	};

	static xpcc_always_inline void
	setDivision(Division)
	{
		//ClockControl::enableClockOutput1(static_cast<int>(d));
	}
	// Connect Functions
	static xpcc_always_inline void
	connect(::xpcc::stm32::TypeId::InternalClock /* t */, uint8_t div = 1)
	{
		ClockControl::enableClockOutput1(ClockControl::ClockOutput1Source::InternalClock, div);
	}
	static xpcc_always_inline void
	connect(::xpcc::stm32::TypeId::ExternalClock /* t */, uint8_t div = 1)
	{
		ClockControl::enableClockOutput1(ClockControl::ClockOutput1Source::ExternalClock, div);
	}
	static xpcc_always_inline void
	connect(::xpcc::stm32::TypeId::ExternalCrystal /* t */, uint8_t div = 1)
	{
		ClockControl::enableClockOutput1(ClockControl::ClockOutput1Source::ExternalCrystal, div);
	}
	static xpcc_always_inline void
	connect(::xpcc::stm32::TypeId::Pll /* t */, uint8_t div = 1)
	{
		ClockControl::enableClockOutput1(ClockControl::ClockOutput1Source::Pll, div);
	}
};


class ClockOutput2
{
public:
	static const ::xpcc::stm32::TypeId::ClockOutput2 Id;

	enum class Division
	{
		By1 = 1,
		By2 = 2,
		By3 = 3,
		By4 = 4,
		By5 = 5,
	};

	static xpcc_always_inline void
	setDivision(Division)
	{
		//ClockControl::enableClockOutput2(static_cast<int>(d));
	}
	// Connect Functions
	static xpcc_always_inline void
	connect(::xpcc::stm32::TypeId::SystemClock /* t */, uint8_t div = 1)
	{
		ClockControl::enableClockOutput2(ClockControl::ClockOutput2Source::SystemClock, div);
	}
	static xpcc_always_inline void
	connect(::xpcc::stm32::TypeId::ExternalClock /* t */, uint8_t div = 1)
	{
		ClockControl::enableClockOutput2(ClockControl::ClockOutput2Source::ExternalClock, div);
	}
	static xpcc_always_inline void
	connect(::xpcc::stm32::TypeId::ExternalCrystal /* t */, uint8_t div = 1)
	{
		ClockControl::enableClockOutput2(ClockControl::ClockOutput2Source::ExternalCrystal, div);
	}
	static xpcc_always_inline void
	connect(::xpcc::stm32::TypeId::Pll /* t */, uint8_t div = 1)
	{
		ClockControl::enableClockOutput2(ClockControl::ClockOutput2Source::Pll, div);
	}
};

	}
}

#endif	//  XPCC_STM32__STATIC_HPP