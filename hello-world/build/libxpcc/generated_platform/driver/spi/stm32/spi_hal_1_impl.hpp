// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_SPI_HAL1_HPP
#	error 	"Don't include this file directly, use 'spi_hal1.hpp' instead!"
#endif

void inline
xpcc::stm32::SpiHal1::enable()
{
	// enable clock
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	// reset spi
	RCC->APB2RSTR |=  RCC_APB2RSTR_SPI1RST;
	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
	SPI1->CR1 |= SPI_CR1_SPE;		// SPI Enable
}

void inline
xpcc::stm32::SpiHal1::disable()
{
	// disable clock
	RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
}

void inline
xpcc::stm32::SpiHal1::initialize(Prescaler prescaler,
		MasterSelection masterSelection, DataMode dataMode,
		DataOrder dataOrder, DataSize dataSize)
{
	enable();
	// disable peripheral
	SPI1->CR1 &= ~SPI_CR1_SPE;
	// set parameters
	SPI1->CR1 = 	  static_cast<uint32_t>(dataMode)
						| static_cast<uint32_t>(dataOrder)
						| static_cast<uint32_t>(masterSelection)
						| static_cast<uint32_t>(prescaler)
						| static_cast<uint32_t>(dataSize);
	if(masterSelection == MasterSelection::Master) {
		SPI1->CR2 |=  SPI_CR2_SSOE; // for master mode
	}
	// reenable peripheral
	SPI1->CR1 |= SPI_CR1_SPE;
}

void inline
xpcc::stm32::SpiHal1::setDataMode(DataMode dataMode)
{
	SPI1->CR1 = (SPI1->CR1 & ~static_cast<uint32_t>(DataMode::All))
										 | static_cast<uint32_t>(dataMode);
}

void inline
xpcc::stm32::SpiHal1::setDataOrder(DataOrder dataOrder)
{
	SPI1->CR1 = (SPI1->CR1 & ~static_cast<uint32_t>(DataOrder::All))
										 | static_cast<uint32_t>(dataOrder);
}

void inline
xpcc::stm32::SpiHal1::setDataSize(DataSize dataSize)
{
	// TODO: implement as set/reset bit
	SPI1->CR1 = (SPI1->CR1 & ~static_cast<uint32_t>(DataSize::All))
										 | static_cast<uint32_t>(dataSize);
}

void inline
xpcc::stm32::SpiHal1::setMasterSelection(MasterSelection masterSelection)
{
	// TODO: implement as set/reset bit
	SPI1->CR1 = (SPI1->CR1 & ~static_cast<uint32_t>(MasterSelection::All))
										 | static_cast<uint32_t>(masterSelection);
}

inline bool
xpcc::stm32::SpiHal1::isReceiveRegisterNotEmpty()
{
	return getInterruptFlags() & InterruptFlag::RxBufferNotEmpty;
}

inline bool
xpcc::stm32::SpiHal1::isTransmitRegisterEmpty()
{
	return getInterruptFlags() & InterruptFlag::TxBufferEmpty;
}

void inline
xpcc::stm32::SpiHal1::write(uint16_t data)
{
	SPI1->DR = data;
}

void inline
xpcc::stm32::SpiHal1::write(uint8_t data)
{
	write(static_cast<uint16_t>(data));
}

void inline
xpcc::stm32::SpiHal1::read(uint8_t &data)
{
	data = static_cast<uint8_t>(SPI1->DR);
}

void inline
xpcc::stm32::SpiHal1::read(uint16_t &data)
{
	data = static_cast<uint16_t>(SPI1->DR);
}

void inline
xpcc::stm32::SpiHal1::enableInterruptVector(bool enable, uint32_t priority)
{
	if (enable) {
		// Set priority for the interrupt vector
		NVIC_SetPriority(SPI1_IRQn, priority);
		// register IRQ at the NVIC
		NVIC_EnableIRQ(SPI1_IRQn);
	}
	else {
		NVIC_DisableIRQ(SPI1_IRQn);
	}
}

void inline
xpcc::stm32::SpiHal1::enableInterrupt(Interrupt_t interrupt)
{
	SPI1->CR2 |= interrupt.value;
}

void inline
xpcc::stm32::SpiHal1::disableInterrupt(Interrupt_t interrupt)
{
	SPI1->CR2 &= ~interrupt.value;
}

xpcc::stm32::SpiHal1::InterruptFlag_t inline
xpcc::stm32::SpiHal1::getInterruptFlags()
{
	return InterruptFlag_t(SPI1->SR);
}

void inline
xpcc::stm32::SpiHal1::acknowledgeInterruptFlag(InterruptFlag_t /*flags*/)
{
	// TODO: implement; see STM32F3 reference manual p. 736
	// SPI1->SR = flags.value;
}