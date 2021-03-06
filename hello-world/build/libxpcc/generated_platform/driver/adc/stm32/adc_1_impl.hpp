// coding: utf-8
/* Copyright (c) 2012, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------


#ifndef XPCC_STM32_ADC1_HPP
#	error 	"Don't include this file directly, use 'adc_1.hpp' instead!"
#endif

template< class SystemClock, uint32_t frequency, uint16_t tolerance >
void
xpcc::stm32::Adc1::initialize()
{
	constexpr float desired = float(SystemClock::Adc) / (frequency > 36000000 ? 36000000 : frequency);

	// respect the prescaler range of 2, 4, 6, 8
	constexpr uint8_t pre_ceil = (
			std::ceil(desired) > 6 ? 8 : (
			std::ceil(desired) > 4 ? 6 : (
			std::ceil(desired) > 2 ? 4 :
									 2
			)));
	constexpr uint8_t pre_floor = (
			std::floor(desired) < 4 ? 2 : (
			std::floor(desired) < 6 ? 4 : (
			std::floor(desired) < 8 ? 6 :
									  8
			)));

	// calculate the possible baudrates above and below the requested baudrate
	constexpr uint32_t baud_lower = SystemClock::Adc / pre_ceil;
	constexpr uint32_t baud_upper = SystemClock::Adc / pre_floor;

	// calculate the half-point between the upper and lower baudrate
	constexpr uint32_t baud_middle = (baud_upper + baud_lower) / 2;
	// decide which divisor is closer to a possible baudrate
	// lower baudrate means higher divisor!
	constexpr uint8_t pre = (frequency < baud_middle) ? pre_ceil : pre_floor;

	// check if within baudrate tolerance
	assertBaudrateInTolerance<
			SystemClock::Adc / pre,
			frequency,
			tolerance >();

	// translate the prescaler into the bitmapping
	constexpr Prescaler prescaler = (
			(pre >= 8) ? Prescaler::Div8 : (
			(pre >= 6) ? Prescaler::Div6 : (
			(pre >= 4) ? Prescaler::Div4 :
						 Prescaler::Div2
			)));

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;	// start ADC Clock
	ADC1->CR2 |= ADC_CR2_ADON;			// switch on ADC

	setPrescaler(prescaler);
}

void
xpcc::stm32::Adc1::setPrescaler(const Prescaler prescaler)
{
	ADC->CCR = (ADC->CCR & ~(0b11 << 17)) | (uint32_t(prescaler) << 17);
}

void
xpcc::stm32::Adc1::enableTemperatureRefVMeasurement()
{
	ADC->CCR |= ADC_CCR_TSVREFE;
}

void
xpcc::stm32::Adc1::disableTemperatureRefVMeasurement()
{
	ADC->CCR &= ~ADC_CCR_TSVREFE;
}
void
xpcc::stm32::Adc1::setLeftAdjustResult()
{
	ADC1->CR2 |= ADC_CR2_ALIGN;
}

void
xpcc::stm32::Adc1::setRightAdjustResult()
{
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
}

bool
xpcc::stm32::Adc1::setChannel(const Channel channel,
									 const SampleTime sampleTime)
{
	if (uint32_t(channel) >= 18) return false;
	// clear number of conversions in the sequence
	// and set number of conversions to 1
	ADC1->SQR1 = 0;
	ADC1->SQR2 = 0;
	ADC1->SQR3 = uint32_t(channel) & 0x1f;

	setSampleTime(channel, sampleTime);
	return true;
}

xpcc::stm32::Adc1::Channel
xpcc::stm32::Adc1::getChannel()
{
	return Channel(ADC1->SQR3 & 0x1f);
}

bool
xpcc::stm32::Adc1::addChannel(const Channel channel,
									const SampleTime sampleTime)
{
	// read channel count
	uint8_t channel_count = (ADC1->SQR1 & ADC_SQR1_L) >> 20;
	++channel_count;
	if(channel_count > 0x0f) return false; // emergency exit
	// write channel number
	if(channel_count < 6) {
		ADC1->SQR3 |=
			(uint32_t(channel) & 0x1f) << (channel_count*5);
	} else 	if(channel_count < 12) {
		ADC1->SQR2 |=
			(uint32_t(channel) & 0x1f) << ((channel_count-6)*5);
	} else {
		ADC1->SQR1 |=
			(uint32_t(channel) & 0x1f) << ((channel_count-12)*5);
	}
	// update channel count
	ADC1->SQR1 = (ADC1->SQR1 & ~ADC_SQR1_L) | (channel_count << 20);

	setSampleTime(channel, sampleTime);
	return true;
}

void
xpcc::stm32::Adc1::setSampleTime(const Channel channel,
										const SampleTime sampleTime)
{
	if (uint32_t(channel) < 10) {
		ADC1->SMPR2 |= uint32_t(sampleTime)
								<< (uint32_t(channel) * 3);
	}
	else {
		ADC1->SMPR1 |= uint32_t(sampleTime)
								<< ((uint32_t(channel)-10) * 3);
	}
}

void
xpcc::stm32::Adc1::enableFreeRunningMode()
{
	ADC1->CR2 |= ADC_CR2_CONT;	// set to continuous mode
}

void
xpcc::stm32::Adc1::disableFreeRunningMode()
{
	ADC1->CR2 &= ~ADC_CR2_CONT;		// set to single mode
}

void
xpcc::stm32::Adc1::disable()
{
	ADC1->CR2 &= ~(ADC_CR2_ADON);		// switch off ADC
	RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN; // stop ADC Clock
}

void
xpcc::stm32::Adc1::startConversion()
{
	acknowledgeInterruptFlags(InterruptFlag::All);
	// starts single conversion for the regular group
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

bool
xpcc::stm32::Adc1::isConversionFinished()
{
	return (ADC1->SR & ADC_SR_EOC);
}

uint16_t
xpcc::stm32::Adc1::getValue()
{
	return ADC1->DR;
}


uint16_t
xpcc::stm32::Adc1::readChannel(Channel channel)
{
	if (!setChannel(channel)) return 0;

	startConversion();
	// wait until the conversion is finished
	while (!isConversionFinished())
		;

	return getValue();
}

// ----------------------------------------------------------------------------
// TODO: move this to some shared header for all cortex m3 platforms
// Re-implemented here to save some code space. As all arguments in the calls
// below are constant the compiler is able to calculate everything at
// compile time.

#ifndef XPCC_CUSTOM_NVIC_FUNCTIONS
#define XPCC_CUSTOM_NVIC_FUNCTIONS

static xpcc_always_inline void
nvicEnableInterrupt(const IRQn_Type IRQn)
{
	NVIC->ISER[(uint32_t(IRQn) >> 5)] = (1 << (uint32_t(IRQn) & 0x1F));
}

static xpcc_always_inline void
nvicDisableInterrupt(IRQn_Type IRQn)
{
	NVIC_DisableIRQ(IRQn);
}

#endif // XPCC_CUSTOM_NVIC_FUNCTIONS

void
xpcc::stm32::Adc1::enableInterruptVector(const uint32_t priority,
												const bool enable)
{
	const IRQn_Type InterruptVector = ADC_IRQn;
	if (enable) {
		NVIC_SetPriority(InterruptVector, priority);
		nvicEnableInterrupt(InterruptVector);
	} else {
		NVIC_DisableIRQ(InterruptVector);
	}
}

void
xpcc::stm32::Adc1::enableInterrupt(const Interrupt_t interrupt)
{
	ADC1->CR1 |= interrupt.value;
}

void
xpcc::stm32::Adc1::disableInterrupt(const Interrupt_t interrupt)
{
	ADC1->CR1 &= ~interrupt.value;
}

xpcc::stm32::Adc1::InterruptFlag_t
xpcc::stm32::Adc1::getInterruptFlags()
{
	return InterruptFlag_t(ADC1->SR);
}

void
xpcc::stm32::Adc1::acknowledgeInterruptFlags(const InterruptFlag_t flags)
{
	// Flags are cleared by writing a one to the flag position.
	// Writing a zero is ignored.
	ADC1->SR = flags.value;
}