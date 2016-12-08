// coding: utf-8
/* Copyright (c) 2012, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------






#ifndef XPCC_STM32_ADC1_HPP
#define XPCC_STM32_ADC1_HPP

#include <stdint.h>
#include "../../../type_ids.hpp"
#include "../../../device.hpp"
#include <xpcc/architecture/interface/adc.hpp>
#include <xpcc/architecture/interface/register.hpp>

/**
 * @ingroup 	stm32f407vg
 * @defgroup	stm32f407vg_adc ADC
 */

namespace xpcc
{

namespace stm32
{

/**
 * Analog/Digital-Converter module (ADC1).
 *
 * The 12-bit ADC is a successive approximation analog-to-digital
 * converter. It has up to 18 multiplexed channels allowing it to measure
 * signals from 16 external and two internal sources.
 * The result of the ADC is stored in a left-aligned or right-aligned
 * 16-bit data register.
 *
 * @author	Stephan Kugelmann
 * @author	David Hebbeker
 * @author	ekiwi
 * @ingroup	stm32f407vg_adc
 */
class Adc1 : public xpcc::Adc
{
public:
	/// TypeId used to connect GPIO pins to this adc's Channel0.
	static const TypeId::Adc1Channel0 Channel0;
	/// TypeId used to connect GPIO pins to this adc's Channel1.
	static const TypeId::Adc1Channel1 Channel1;
	/// TypeId used to connect GPIO pins to this adc's Channel2.
	static const TypeId::Adc1Channel2 Channel2;
	/// TypeId used to connect GPIO pins to this adc's Channel3.
	static const TypeId::Adc1Channel3 Channel3;
	/// TypeId used to connect GPIO pins to this adc's Channel4.
	static const TypeId::Adc1Channel4 Channel4;
	/// TypeId used to connect GPIO pins to this adc's Channel5.
	static const TypeId::Adc1Channel5 Channel5;
	/// TypeId used to connect GPIO pins to this adc's Channel6.
	static const TypeId::Adc1Channel6 Channel6;
	/// TypeId used to connect GPIO pins to this adc's Channel7.
	static const TypeId::Adc1Channel7 Channel7;
	/// TypeId used to connect GPIO pins to this adc's Channel8.
	static const TypeId::Adc1Channel8 Channel8;
	/// TypeId used to connect GPIO pins to this adc's Channel9.
	static const TypeId::Adc1Channel9 Channel9;
	/// TypeId used to connect GPIO pins to this adc's Channel10.
	static const TypeId::Adc1Channel10 Channel10;
	/// TypeId used to connect GPIO pins to this adc's Channel11.
	static const TypeId::Adc1Channel11 Channel11;
	/// TypeId used to connect GPIO pins to this adc's Channel12.
	static const TypeId::Adc1Channel12 Channel12;
	/// TypeId used to connect GPIO pins to this adc's Channel13.
	static const TypeId::Adc1Channel13 Channel13;
	/// TypeId used to connect GPIO pins to this adc's Channel14.
	static const TypeId::Adc1Channel14 Channel14;
	/// TypeId used to connect GPIO pins to this adc's Channel15.
	static const TypeId::Adc1Channel15 Channel15;
	/// TypeId used to connect GPIO pins to this adc's Channel16.
	static const TypeId::Adc1Channel16 Channel16;
	/// TypeId used to connect GPIO pins to this adc's Channel17.
	static const TypeId::Adc1Channel17 Channel17;
	/// TypeId used to connect GPIO pins to this adc's Channel18.
	static const TypeId::Adc1Channel18 Channel18;
	static constexpr uint8_t Resolution = 12;

public:
	/**
	 * Channels, which can be used with this ADC.
	 *
	 * You can specify the channel by using a pin-name, like PIN_C0, an
	 * internal sensor, like TEMPERATURE_SENSOR or just the plain
	 * channel number, like CHANNEL_0.
	 */
	enum class
	Channel : uint8_t	// TODO: What is the best type?
	{
		Channel0 = 0,
		Channel1 = 1,
		Channel2 = 2,
		Channel3 = 3,
		Channel4 = 4,
		Channel5 = 5,
		Channel6 = 6,
		Channel7 = 7,
		Channel8 = 8,
		Channel9 = 9,
		Channel10 = 10,
		Channel11 = 11,
		Channel12 = 12,
		Channel13 = 13,
		Channel14 = 14,
		Channel15 = 15,
		Channel16 = 16,
		Channel17 = 17,
		Channel18 = 18,

		BatDiv2 = 18, /// Half the V_BAT voltage.

		/** Measure the ambient temperature of the device.
		 *
		 * @li Supported temperature range: -40 to 125 C
		 * @li Precision: +-1.5 C
		 *
		 * @see Reference manual (i.e. RM0090) for the formula for the
		 * 	calculation of the actual temperature.
		 * @note The TSVREFE bit must be set to enable the conversion of
		 * 	this internal channel.
		 */
		TemperatureSensor = 16,

		/** Internal reference voltage.
		 *
		 * @note The TSVREFE bit must be set to enable the conversion of
		 * 	this internal channel.
		 */
		InternalReference = 17,
	};

private:
	/**
	 * Programmable prescaler to divide the APB2 clock frequency, which
	 * is used for the analog circuitry (not the digital interface which
	 * is used for registers).
	 */
	enum class
	Prescaler : uint8_t
	{
		Div2 = 0b00,	///< PCLK2 divided by 2
		Div4 = 0b01,	///< PCLK2 divided by 4
		Div6 = 0b10,	///< PCLK2 divided by 6
		Div8 = 0b11		///< PCLK2 divided by 8
	};

public:
	/**
	 * Sampling time of the input voltage.
	 *
	 * Total conversion time is T_con = Sampling time + 12 cycles
	 */
	enum class
	SampleTime : uint8_t
	{
		Cycles3 	= 0b000,	///< 3 ADCCLK cycles
		Cycles15 	= 0b001,	///< 15 ADCCLK cycles
		Cycles28 	= 0b010,	///< 28 ADCCLK cycles
		Cycles56 	= 0b011,	///< 56 ADCCLK cycles
		Cycles84 	= 0b100,	///< 84 ADCCLK cycles
		Cycles112 	= 0b101,	///< 112 ADCCLK cycles
		Cycles144 	= 0b110,	///< 144 ADCCLK cycles
		Cycles480 	= 0b111		///< 480 ADCCLK cycles
	};

	/**
	 * Possible interrupts.
	 *
	 * An interrupt can be produced on the end of conversion for regular
	 * and injected groups, when the analog watchdog status bit is set
	 * and when the overrun status bit is set.
	 */
	enum class
	Interrupt : uint32_t
	{
		/// Analog watchdog status bit is set
		AnalogWatchdog			= ADC_CR1_AWDIE,
		/// End of conversion of a regular group
		EndOfRegularConversion	= ADC_CR1_EOCIE,
		/// End of conversion of an injected group
		EndOfInjectedConversion	= ADC_CR1_JEOCIE,
		/// Overrun (if data are lost)
		Overrun					= ADC_CR1_OVRIE,
	};
	XPCC_FLAGS32(Interrupt);

	enum class
	InterruptFlag : uint32_t
	{
		/// Analog watchdog status bit is set
		AnalogWatchdog			= ADC_SR_AWD,
		/// End of conversion of a regular group
		EndOfRegularConversion	= ADC_SR_EOC,
		/// End of conversion of an injected group
		EndOfInjectedConversion	= ADC_SR_JEOC,
		/// Overrun (if data are lost)
		Overrun					= ADC_SR_OVR,
		/// All InterruptFlags
		All				= ADC_SR_AWD | ADC_SR_EOC | ADC_SR_JEOC | ADC_SR_OVR,
	};
	XPCC_FLAGS32(InterruptFlag);

public:
	// start documentation inherited
	/**
	 * Initialize and enable the A/D converter.
	 *
	 * Enables the ADC clock and switches on the ADC. The ADC clock
	 * prescaler will be set as well.
	 *
	 * The ADC clock must not exceed 36 MHz for Vdd > 2.4V, or 18MHz for Vdd < 2.4V.
	 */
	template< class SystemClock, uint32_t frequency=10000000,
			uint16_t tolerance = xpcc::Tolerance::TenPercent >
	static void
	initialize();

	static inline void
	disable();

	/**
	 * Start a new conversion or continuous conversions.
	 *
	 * @pre A ADC channel must be selected with setChannel(). When using
	 * 	a STM32F10x a delay of at least t_STAB after initialize() must
	 * 	be waited!
	 *
	 * @post The result can be fetched with getValue()
	 * @attention When using a STM32F10x, the application should allow a delay of t_STAB between
	 * 	power up and start of conversion. Refer to Reference Manual
	 * 	(RM0008) ADC_CR2_ADON.
	 */
	static inline void
	startConversion();

	static inline bool
	isConversionFinished();

	static inline uint16_t
	getValue();


	static inline uint16_t
	readChannel(Channel channel);


	/**
	 * Analog channel selection.
	 *
	 * This not for scan mode. The number of channels will be set to 1,
	 * the channel selected and the corresponding pin will be set to
	 * analog input.
	 * If the the channel is modified during a conversion, the current
	 * conversion is reset and a new start pulse is sent to the ADC to
	 * convert the new chosen channnel / group of channels.
	 *
	 *
	 * @param channel		The channel which shall be read.
	 * @param sampleTime	The sample time to sample the input voltage.
	 *
	 * @pre The ADC clock must be started and the ADC switched on with
	 * 		initialize()
	 */
	static inline bool
	setChannel(const Channel channel,
			   const SampleTime sampleTime = static_cast<SampleTime>(0b000));

	static inline Channel
	getChannel();


	static inline void
	enableFreeRunningMode();

	static inline void
	disableFreeRunningMode();


	static inline void
	setLeftAdjustResult();

	static inline void
	setRightAdjustResult();
	// stop documentation inherited

	// TODO
	//static void
	//calibrate();


	/// Switch on temperature- and V_REF measurement.
	static inline void
	enableTemperatureRefVMeasurement();

	/// Switch on temperature- and V_REF measurement.
	static inline void
	disableTemperatureRefVMeasurement();
	/// Add a channel to conversion group.
	static inline bool
	addChannel(const Channel channel,
		const SampleTime sampleTime = static_cast<SampleTime>(0b000));

	/// change sample time of ADC channel
	static inline void
	setSampleTime(const Channel channel,
		const SampleTime sampleTime = static_cast<SampleTime>(0b000));


	static inline void
	enableInterruptVector(const uint32_t priority, const bool enable = true);

	/**
	 * Enables the ADC Conversion Complete Interrupt.
	 *
	 * You could catch the interrupt using this example function:
	 * @li for STM32F4XX: `extern "C" void ADC_IRQHandler()`
	 * @li for STM32F10X: `extern "C" void ADC1_2_IRQHandler()`
	 *
	 * @pre The ADC clock must be started and the ADC switched on with
	 * 	initialize(). Also the Interrupt Vector needs to be enabled first.
	 *
	 * @param priority Priority to set
	 * @param interrupt The interrupt, which shall be enabled. See
	 * 	Interrupt for available interrupts.
	 *
	 * @note ADC1 and ADC2 interrupts are mapped onto the same interrupt
	 * 	vector. ADC3 interrupts are mapped onto a separate interrupt
	 * 	vector.
	 */
	static inline void
	enableInterrupt(const Interrupt_t interrupt);

	/**
	 * Disables the ADC Conversion Complete Interrupt.
	 */
	static inline void
	disableInterrupt(const Interrupt_t interrupt);


	/**
	 * Returns if the th interrupt flags set.
	 *
	 * @pre The ADC clock must be started and the ADC switched on with
	 * 	initialize()
	 */
	static inline InterruptFlag_t
	getInterruptFlags();

	/**
	 * Clears the specified interrupt flag.
	 *
	 * @param flag
	 * 		The interrupt flag, which shall be cleared.
	 *
	 * @pre The ADC clock must be started and the ADC switched on with
	 * 		initialize().
	 */
	static inline void
	acknowledgeInterruptFlags(const InterruptFlag_t flags);

private:
	/**
	 * Select the frequency of the clock to the ADC. The clock is common
	 * for all the ADCs (ADC1, ADC2, ADC3) and all channels.
	 *
	 * @pre The ADC clock must be started and the ADC switched on with
	 * 	initialize()
	 *
	 * @param prescaler
	 * 		The prescaler specifies by which factor the system clock
	 * 		will be divided.
	 */
	static inline void
	setPrescaler(const Prescaler prescaler = Prescaler::Div8);
};

} // namespace stm32

} // namespace xpcc

#include "adc_1_impl.hpp"

#endif	// XPCC_STM32_ADC1_HPP
