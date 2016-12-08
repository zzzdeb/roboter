// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_SPI_HAL3_HPP
#	error 	"Don't include this file directly, use 'spi_hal3.hpp' instead!"
#endif

void inline
xpcc::stm32::SpiHal3::enable()
{
	// enable clock
	RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
	// reset spi
	RCC->APB1RSTR |=  RCC_APB1RSTR_SPI3RST;
	RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI3RST;
	SPI3->CR1 |= SPI_CR1_SPE;		// SPI Enable
}

void inline
xpcc::stm32::SpiHal3::disable()
{
	// disable clock
	RCC->APB1ENR &= ~RCC_APB1ENR_SPI3EN;
}

void inline
xpcc::stm32::SpiHal3::initialize(Prescaler prescaler,
		MasterSelection masterSelection, DataMode dataMode,
		DataOrder dataOrder, DataSize dataSize)
{
	enable();
	// disable peripheral
	SPI3->CR1 &= ~SPI_CR1_SPE;
	// set parameters
	SPI3->CR1 = 	  static_cast<uint32_t>(dataMode)
						| static_cast<uint32_t>(dataOrder)
						| static_cast<uint32_t>(masterSelection)
						| static_cast<uint32_t>(prescaler)
						| static_cast<uint32_t>(dataSize);
	if(masterSelection == MasterSelection::Master) {
		SPI3->CR2 |=  SPI_CR2_SSOE; // for master mode
	}
	// reenable peripheral
	SPI3->CR1 |= SPI_CR1_SPE;
}

void inline
xpcc::stm32::SpiHal3::setDataMode(DataMode dataMode)
{
	SPI3->CR1 = (SPI3->CR1 & ~static_cast<uint32_t>(DataMode::All))
										 | static_cast<uint32_t>(dataMode);
}

void inline
xpcc::stm32::SpiHal3::setDataOrder(DataOrder dataOrder)
{
	SPI3->CR1 = (SPI3->CR1 & ~static_cast<uint32_t>(DataOrder::All))
										 | static_cast<uint32_t>(dataOrder);
}

void inline
xpcc::stm32::SpiHal3::setDataSize(DataSize dataSize)
{
	// TODO: implement as set/reset bit
	SPI3->CR1 = (SPI3->CR1 & ~static_cast<uint32_t>(DataSize::All))
										 | static_cast<uint32_t>(dataSize);
}

void inline
xpcc::stm32::SpiHal3::setMasterSelection(MasterSelection masterSelection)
{
	// TODO: implement as set/reset bit
	SPI3->CR1 = (SPI3->CR1 & ~static_cast<uint32_t>(MasterSelection::All))
										 | static_cast<uint32_t>(masterSelection);
}

inline bool
xpcc::stm32::SpiHal3::isReceiveRegisterNotEmpty()
{
	return getInterruptFlags() & InterruptFlag::RxBufferNotEmpty;
}

inline bool
xpcc::stm32::SpiHal3::isTransmitRegisterEmpty()
{
	return getInterruptFlags() & InterruptFlag::TxBufferEmpty;
}

void inline
xpcc::stm32::SpiHal3::write(uint16_t data)
{
	SPI3->DR = data;
}

void inline
xpcc::stm32::SpiHal3::write(uint8_t data)
{
	write(static_cast<uint16_t>(data));
}

void inline
xpcc::stm32::SpiHal3::read(uint8_t &data)
{
	data = static_cast<uint8_t>(SPI3->DR);
}

void inline
xpcc::stm32::SpiHal3::read(uint16_t &data)
{
	data = static_cast<uint16_t>(SPI3->DR);
}

void inline
xpcc::stm32::SpiHal3::enableInterruptVector(bool enable, uint32_t priority)
{
	if (enable) {
		// Set priority for the interrupt vector
		NVIC_SetPriority(SPI3_IRQn, priority);
		// register IRQ at the NVIC
		NVIC_EnableIRQ(SPI3_IRQn);
	}
	else {
		NVIC_DisableIRQ(SPI3_IRQn);
	}
}

void inline
xpcc::stm32::SpiHal3::enableInterrupt(Interrupt_t interrupt)
{
	SPI3->CR2 |= interrupt.value;
}

void inline
xpcc::stm32::SpiHal3::disableInterrupt(Interrupt_t interrupt)
{
	SPI3->CR2 &= ~interrupt.value;
}

xpcc::stm32::SpiHal3::InterruptFlag_t inline
xpcc::stm32::SpiHal3::getInterruptFlags()
{
	return InterruptFlag_t(SPI3->SR);
}

void inline
xpcc::stm32::SpiHal3::acknowledgeInterruptFlag(InterruptFlag_t /*flags*/)
{
	// TODO: implement; see STM32F3 reference manual p. 736
	// SPI3->SR = flags.value;
}