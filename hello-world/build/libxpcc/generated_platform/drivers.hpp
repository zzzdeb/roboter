// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2013, Roboterclub Aachen e.V.
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

#ifndef XPCC__DRIVERS_HPP
#define XPCC__DRIVERS_HPP

// Include driver header files
// gpio/generic
#include "driver/gpio/generic/gpio.hpp"
// core/generic
// one_wire/generic
#include "driver/one_wire/generic/one_wire_master.hpp"
// i2c/generic
#include "driver/i2c/generic/i2c_master.hpp"
#include "driver/i2c/generic/type_ids.hpp"
// clock/generic
#include "driver/clock/generic/common_clock.hpp"
// can/generic
#include "driver/can/generic/can_bit_timings.hpp"
// spi/generic
#include "driver/spi/generic/spi_master.hpp"
#include "driver/spi/generic/type_ids.hpp"
// core/cortex
#include "driver/core/cortex/cycle_counter.hpp"
#include "driver/core/cortex/systick/systick_timer.hpp"
// adc/stm32
#include "driver/adc/stm32/adc_1.hpp"
#include "driver/adc/stm32/adc_interrupt_1.hpp"
#include "driver/adc/stm32/type_ids.hpp"
#include "driver/adc/stm32/adc_2.hpp"
#include "driver/adc/stm32/adc_interrupt_2.hpp"
#include "driver/adc/stm32/adc_3.hpp"
#include "driver/adc/stm32/adc_interrupt_3.hpp"
// can/stm32
#include "driver/can/stm32/can_1.hpp"
#include "driver/can/stm32/can_filter.hpp"
#include "driver/can/stm32/error_code.hpp"
#include "driver/can/stm32/type_ids.hpp"
#include "driver/can/stm32/can_2.hpp"
// clock/stm32
#include "driver/clock/stm32/clock.hpp"
#include "driver/clock/stm32/type_ids.hpp"
#include "driver/clock/stm32/static.hpp"
#include "driver/clock/stm32/pll_calculator.hpp"
// dma/stm32
#include "driver/dma/stm32/dma_base.hpp"
#include "driver/dma/stm32/dma_1.hpp"
#include "driver/dma/stm32/type_ids.hpp"
#include "driver/dma/stm32/dma_2.hpp"
// fsmc/stm32
#include "driver/fsmc/stm32/fsmc.hpp"
#include "driver/fsmc/stm32/type_ids.hpp"
// i2c/stm32
#include "driver/i2c/stm32/i2c_master_1.hpp"
#include "driver/i2c/stm32/type_ids.hpp"
#include "driver/i2c/stm32/i2c_master_2.hpp"
#include "driver/i2c/stm32/i2c_master_3.hpp"
// id/stm32
#include "driver/id/stm32/id.hpp"
// random/stm32
#include "driver/random/stm32/random_number_generator.hpp"
// spi/stm32
#include "driver/spi/stm32/spi_base.hpp"
#include "driver/spi/stm32/spi_hal_1.hpp"
#include "driver/spi/stm32/spi_master_1.hpp"
#include "driver/spi/stm32/type_ids.hpp"
#include "driver/spi/stm32/spi_hal_2.hpp"
#include "driver/spi/stm32/spi_master_2.hpp"
#include "driver/spi/stm32/spi_hal_3.hpp"
#include "driver/spi/stm32/spi_master_3.hpp"
// spi/stm32_uart
#include "driver/spi/stm32_uart/uart_spi_master_1.hpp"
#include "driver/spi/stm32_uart/type_ids.hpp"
#include "driver/spi/stm32_uart/uart_spi_master_2.hpp"
#include "driver/spi/stm32_uart/uart_spi_master_3.hpp"
#include "driver/spi/stm32_uart/uart_spi_master_6.hpp"
// timer/stm32
#include "driver/timer/stm32/timer_1.hpp"
#include "driver/timer/stm32/type_ids.hpp"
#include "driver/timer/stm32/advanced_base.hpp"
#include "driver/timer/stm32/basic_base.hpp"
#include "driver/timer/stm32/general_purpose_base.hpp"
#include "driver/timer/stm32/timer_2.hpp"
#include "driver/timer/stm32/timer_3.hpp"
#include "driver/timer/stm32/timer_4.hpp"
#include "driver/timer/stm32/timer_5.hpp"
#include "driver/timer/stm32/timer_6.hpp"
#include "driver/timer/stm32/timer_7.hpp"
#include "driver/timer/stm32/timer_8.hpp"
#include "driver/timer/stm32/timer_9.hpp"
#include "driver/timer/stm32/timer_10.hpp"
#include "driver/timer/stm32/timer_11.hpp"
#include "driver/timer/stm32/timer_12.hpp"
#include "driver/timer/stm32/timer_13.hpp"
#include "driver/timer/stm32/timer_14.hpp"
// uart/stm32
#include "driver/uart/stm32/uart_hal_1.hpp"
#include "driver/uart/stm32/uart_1.hpp"
#include "driver/uart/stm32/uart_base.hpp"
#include "driver/uart/stm32/type_ids.hpp"
#include "driver/uart/stm32/uart_baudrate.hpp"
#include "driver/uart/stm32/uart_hal_2.hpp"
#include "driver/uart/stm32/uart_2.hpp"
#include "driver/uart/stm32/uart_hal_3.hpp"
#include "driver/uart/stm32/uart_3.hpp"
#include "driver/uart/stm32/uart_hal_4.hpp"
#include "driver/uart/stm32/uart_4.hpp"
#include "driver/uart/stm32/uart_hal_5.hpp"
#include "driver/uart/stm32/uart_5.hpp"
#include "driver/uart/stm32/uart_hal_6.hpp"
#include "driver/uart/stm32/uart_6.hpp"
// usb/stm32_fs
#include "driver/usb/stm32_fs/type_ids.hpp"
// gpio/stm32
#include "driver/gpio/stm32/gpio.hpp"
#endif	// XPCC__DRIVERS_HPP
