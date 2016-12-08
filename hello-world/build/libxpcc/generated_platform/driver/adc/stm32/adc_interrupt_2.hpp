// coding: utf-8
/* Copyright (c) 2011, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------


#ifndef XPCC_STM32_ADC_INTERRUPT_2_HPP
#define XPCC_STM32_ADC_INTERRUPT_2_HPP

#include <xpcc/utils/dummy.hpp>
#include "adc_2.hpp"
#include <xpcc/architecture/interface/adc_interrupt.hpp>


namespace xpcc
{

namespace stm32
{

/**
 * ADC Interrupt module
 *
 * This class allows you to attach functions to the ADC Conversion
 * Complete Interrupt via function pointers.
 * Be aware however, that this implementation is slower and requires
 * more resources than writing the function code directly into
 * the interrupt service routines.
 *
 * @see AnalogSensors uses this implemenation.
 *
 * @ingroup		stm32f407vg_adc
 * @author		Niklas Hauser
 */
class AdcInterrupt2 : public Adc2, public xpcc::AdcInterrupt
{
public:
	static inline void
	attachInterruptHandler(Handler handler=xpcc::dummy)
	{
		AdcInterrupt2::handler = handler;
	}

public:
	static Handler handler;
};

}	// namespace f4

}	// namespace xpcc

#endif // XPCC_F4_ADC_INTERRUPT_HPP