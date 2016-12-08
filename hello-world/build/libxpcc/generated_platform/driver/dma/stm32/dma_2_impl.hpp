// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_DMA2_HPP
#	error 	"Don't include this file directly, use 'dma_2.hpp' instead!"
#endif

void
xpcc::stm32::Dma2::enable()
{
	RCC->AHB1ENR  |= RCC_AHB1ENR_DMA2EN;
	RCC->AHB1RSTR |=  RCC_AHB1RSTR_DMA2RST;
	RCC->AHB1RSTR &= ~RCC_AHB1RSTR_DMA2RST;
}

void
xpcc::stm32::Dma2::disable()
{
	RCC->AHB1ENR &= ~RCC_AHB1ENR_DMA2EN;
}


void
xpcc::stm32::Dma2::Stream0::setMemorySource(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream0->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream0->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream0::setPeripheralSource(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream0->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream0::setMemorySource(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream0->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream0->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream0::setPeripheralSource(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream0->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream0::setMemorySource(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream0->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream0->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream0::setPeripheralSource(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream0->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream0::setMemoryDestination(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream0->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream0->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream0::setPeripheralDestination(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream0->M0AR = DMA2_Stream0->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream0->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream0::setMemoryDestination(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream0->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream0->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream0::setPeripheralDestination(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream0->M0AR = DMA2_Stream0->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream0->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream0::setMemoryDestination(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream0->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream0->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream0::setPeripheralDestination(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream0->M0AR = DMA2_Stream0->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream0->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream0::stop()
{
	DMA2_Stream0->CR &= ~DMA_SxCR_EN;
	while(DMA2_Stream0->CR & DMA_SxCR_EN); // wait for stream to be stopped
}

void
xpcc::stm32::Dma2::Stream0::configure(
	Channel channel,
	uint16_t sample_length, Priority priority, CircularMode circular
	, FlowControl flow)
{
	//stop();
	DMA2_Stream0->CR = (DMA2_Stream0->CR & ~configmask) | static_cast<uint32_t>(priority)
										  | static_cast<uint32_t>(circular)
		| static_cast<uint32_t>(channel) | static_cast<uint32_t>(flow);
	DMA2_Stream0->NDTR = sample_length;
}

void
xpcc::stm32::Dma2::Stream0::start()
{
	DMA2_Stream0->CR |= DMA_SxCR_EN;
}

bool
xpcc::stm32::Dma2::Stream0::isFinished()
{
	return !(DMA2_Stream0->CR & DMA_SxCR_EN);
}

xpcc::stm32::Dma2::Stream0::DataTransferDirection
xpcc::stm32::Dma2::Stream0::getDataTransferDirection()
{
	return static_cast<DataTransferDirection>(
		DMA2_Stream0->CR & (DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1));
}

void
xpcc::stm32::Dma2::Stream1::setMemorySource(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream1->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream1->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream1::setPeripheralSource(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream1->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream1::setMemorySource(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream1->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream1->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream1::setPeripheralSource(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream1->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream1::setMemorySource(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream1->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream1->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream1::setPeripheralSource(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream1->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream1::setMemoryDestination(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream1->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream1->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream1::setPeripheralDestination(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream1->M0AR = DMA2_Stream1->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream1->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream1::setMemoryDestination(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream1->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream1->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream1::setPeripheralDestination(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream1->M0AR = DMA2_Stream1->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream1->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream1::setMemoryDestination(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream1->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream1->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream1::setPeripheralDestination(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream1->M0AR = DMA2_Stream1->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream1->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream1::stop()
{
	DMA2_Stream1->CR &= ~DMA_SxCR_EN;
	while(DMA2_Stream1->CR & DMA_SxCR_EN); // wait for stream to be stopped
}

void
xpcc::stm32::Dma2::Stream1::configure(
	Channel channel,
	uint16_t sample_length, Priority priority, CircularMode circular
	, FlowControl flow)
{
	//stop();
	DMA2_Stream1->CR = (DMA2_Stream1->CR & ~configmask) | static_cast<uint32_t>(priority)
										  | static_cast<uint32_t>(circular)
		| static_cast<uint32_t>(channel) | static_cast<uint32_t>(flow);
	DMA2_Stream1->NDTR = sample_length;
}

void
xpcc::stm32::Dma2::Stream1::start()
{
	DMA2_Stream1->CR |= DMA_SxCR_EN;
}

bool
xpcc::stm32::Dma2::Stream1::isFinished()
{
	return !(DMA2_Stream1->CR & DMA_SxCR_EN);
}

xpcc::stm32::Dma2::Stream1::DataTransferDirection
xpcc::stm32::Dma2::Stream1::getDataTransferDirection()
{
	return static_cast<DataTransferDirection>(
		DMA2_Stream1->CR & (DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1));
}

void
xpcc::stm32::Dma2::Stream2::setMemorySource(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream2->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream2->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream2::setPeripheralSource(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream2->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream2::setMemorySource(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream2->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream2->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream2::setPeripheralSource(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream2->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream2::setMemorySource(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream2->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream2->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream2::setPeripheralSource(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream2->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream2::setMemoryDestination(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream2->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream2->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream2::setPeripheralDestination(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream2->M0AR = DMA2_Stream2->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream2->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream2::setMemoryDestination(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream2->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream2->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream2::setPeripheralDestination(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream2->M0AR = DMA2_Stream2->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream2->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream2::setMemoryDestination(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream2->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream2->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream2::setPeripheralDestination(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream2->M0AR = DMA2_Stream2->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream2->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream2::stop()
{
	DMA2_Stream2->CR &= ~DMA_SxCR_EN;
	while(DMA2_Stream2->CR & DMA_SxCR_EN); // wait for stream to be stopped
}

void
xpcc::stm32::Dma2::Stream2::configure(
	Channel channel,
	uint16_t sample_length, Priority priority, CircularMode circular
	, FlowControl flow)
{
	//stop();
	DMA2_Stream2->CR = (DMA2_Stream2->CR & ~configmask) | static_cast<uint32_t>(priority)
										  | static_cast<uint32_t>(circular)
		| static_cast<uint32_t>(channel) | static_cast<uint32_t>(flow);
	DMA2_Stream2->NDTR = sample_length;
}

void
xpcc::stm32::Dma2::Stream2::start()
{
	DMA2_Stream2->CR |= DMA_SxCR_EN;
}

bool
xpcc::stm32::Dma2::Stream2::isFinished()
{
	return !(DMA2_Stream2->CR & DMA_SxCR_EN);
}

xpcc::stm32::Dma2::Stream2::DataTransferDirection
xpcc::stm32::Dma2::Stream2::getDataTransferDirection()
{
	return static_cast<DataTransferDirection>(
		DMA2_Stream2->CR & (DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1));
}

void
xpcc::stm32::Dma2::Stream3::setMemorySource(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream3->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream3->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream3::setPeripheralSource(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream3->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream3::setMemorySource(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream3->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream3->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream3::setPeripheralSource(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream3->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream3::setMemorySource(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream3->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream3->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream3::setPeripheralSource(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream3->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream3::setMemoryDestination(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream3->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream3->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream3::setPeripheralDestination(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream3->M0AR = DMA2_Stream3->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream3->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream3::setMemoryDestination(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream3->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream3->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream3::setPeripheralDestination(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream3->M0AR = DMA2_Stream3->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream3->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream3::setMemoryDestination(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream3->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream3->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream3::setPeripheralDestination(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream3->M0AR = DMA2_Stream3->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream3->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream3::stop()
{
	DMA2_Stream3->CR &= ~DMA_SxCR_EN;
	while(DMA2_Stream3->CR & DMA_SxCR_EN); // wait for stream to be stopped
}

void
xpcc::stm32::Dma2::Stream3::configure(
	Channel channel,
	uint16_t sample_length, Priority priority, CircularMode circular
	, FlowControl flow)
{
	//stop();
	DMA2_Stream3->CR = (DMA2_Stream3->CR & ~configmask) | static_cast<uint32_t>(priority)
										  | static_cast<uint32_t>(circular)
		| static_cast<uint32_t>(channel) | static_cast<uint32_t>(flow);
	DMA2_Stream3->NDTR = sample_length;
}

void
xpcc::stm32::Dma2::Stream3::start()
{
	DMA2_Stream3->CR |= DMA_SxCR_EN;
}

bool
xpcc::stm32::Dma2::Stream3::isFinished()
{
	return !(DMA2_Stream3->CR & DMA_SxCR_EN);
}

xpcc::stm32::Dma2::Stream3::DataTransferDirection
xpcc::stm32::Dma2::Stream3::getDataTransferDirection()
{
	return static_cast<DataTransferDirection>(
		DMA2_Stream3->CR & (DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1));
}

void
xpcc::stm32::Dma2::Stream4::setMemorySource(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream4->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream4->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream4::setPeripheralSource(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream4->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream4::setMemorySource(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream4->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream4->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream4::setPeripheralSource(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream4->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream4::setMemorySource(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream4->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream4->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream4::setPeripheralSource(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream4->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream4::setMemoryDestination(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream4->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream4->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream4::setPeripheralDestination(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream4->M0AR = DMA2_Stream4->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream4->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream4::setMemoryDestination(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream4->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream4->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream4::setPeripheralDestination(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream4->M0AR = DMA2_Stream4->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream4->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream4::setMemoryDestination(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream4->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream4->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream4::setPeripheralDestination(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream4->M0AR = DMA2_Stream4->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream4->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream4::stop()
{
	DMA2_Stream4->CR &= ~DMA_SxCR_EN;
	while(DMA2_Stream4->CR & DMA_SxCR_EN); // wait for stream to be stopped
}

void
xpcc::stm32::Dma2::Stream4::configure(
	Channel channel,
	uint16_t sample_length, Priority priority, CircularMode circular
	, FlowControl flow)
{
	//stop();
	DMA2_Stream4->CR = (DMA2_Stream4->CR & ~configmask) | static_cast<uint32_t>(priority)
										  | static_cast<uint32_t>(circular)
		| static_cast<uint32_t>(channel) | static_cast<uint32_t>(flow);
	DMA2_Stream4->NDTR = sample_length;
}

void
xpcc::stm32::Dma2::Stream4::start()
{
	DMA2_Stream4->CR |= DMA_SxCR_EN;
}

bool
xpcc::stm32::Dma2::Stream4::isFinished()
{
	return !(DMA2_Stream4->CR & DMA_SxCR_EN);
}

xpcc::stm32::Dma2::Stream4::DataTransferDirection
xpcc::stm32::Dma2::Stream4::getDataTransferDirection()
{
	return static_cast<DataTransferDirection>(
		DMA2_Stream4->CR & (DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1));
}

void
xpcc::stm32::Dma2::Stream5::setMemorySource(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream5->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream5->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream5::setPeripheralSource(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream5->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream5::setMemorySource(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream5->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream5->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream5::setPeripheralSource(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream5->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream5::setMemorySource(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream5->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream5->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream5::setPeripheralSource(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream5->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream5::setMemoryDestination(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream5->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream5->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream5::setPeripheralDestination(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream5->M0AR = DMA2_Stream5->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream5->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream5::setMemoryDestination(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream5->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream5->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream5::setPeripheralDestination(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream5->M0AR = DMA2_Stream5->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream5->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream5::setMemoryDestination(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream5->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream5->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream5::setPeripheralDestination(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream5->M0AR = DMA2_Stream5->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream5->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream5::stop()
{
	DMA2_Stream5->CR &= ~DMA_SxCR_EN;
	while(DMA2_Stream5->CR & DMA_SxCR_EN); // wait for stream to be stopped
}

void
xpcc::stm32::Dma2::Stream5::configure(
	Channel channel,
	uint16_t sample_length, Priority priority, CircularMode circular
	, FlowControl flow)
{
	//stop();
	DMA2_Stream5->CR = (DMA2_Stream5->CR & ~configmask) | static_cast<uint32_t>(priority)
										  | static_cast<uint32_t>(circular)
		| static_cast<uint32_t>(channel) | static_cast<uint32_t>(flow);
	DMA2_Stream5->NDTR = sample_length;
}

void
xpcc::stm32::Dma2::Stream5::start()
{
	DMA2_Stream5->CR |= DMA_SxCR_EN;
}

bool
xpcc::stm32::Dma2::Stream5::isFinished()
{
	return !(DMA2_Stream5->CR & DMA_SxCR_EN);
}

xpcc::stm32::Dma2::Stream5::DataTransferDirection
xpcc::stm32::Dma2::Stream5::getDataTransferDirection()
{
	return static_cast<DataTransferDirection>(
		DMA2_Stream5->CR & (DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1));
}

void
xpcc::stm32::Dma2::Stream6::setMemorySource(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream6->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream6->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream6::setPeripheralSource(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream6->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream6::setMemorySource(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream6->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream6->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream6::setPeripheralSource(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream6->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream6::setMemorySource(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream6->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream6->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream6::setPeripheralSource(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream6->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream6::setMemoryDestination(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream6->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream6->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream6::setPeripheralDestination(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream6->M0AR = DMA2_Stream6->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream6->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream6::setMemoryDestination(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream6->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream6->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream6::setPeripheralDestination(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream6->M0AR = DMA2_Stream6->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream6->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream6::setMemoryDestination(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream6->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream6->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream6::setPeripheralDestination(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream6->M0AR = DMA2_Stream6->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream6->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream6::stop()
{
	DMA2_Stream6->CR &= ~DMA_SxCR_EN;
	while(DMA2_Stream6->CR & DMA_SxCR_EN); // wait for stream to be stopped
}

void
xpcc::stm32::Dma2::Stream6::configure(
	Channel channel,
	uint16_t sample_length, Priority priority, CircularMode circular
	, FlowControl flow)
{
	//stop();
	DMA2_Stream6->CR = (DMA2_Stream6->CR & ~configmask) | static_cast<uint32_t>(priority)
										  | static_cast<uint32_t>(circular)
		| static_cast<uint32_t>(channel) | static_cast<uint32_t>(flow);
	DMA2_Stream6->NDTR = sample_length;
}

void
xpcc::stm32::Dma2::Stream6::start()
{
	DMA2_Stream6->CR |= DMA_SxCR_EN;
}

bool
xpcc::stm32::Dma2::Stream6::isFinished()
{
	return !(DMA2_Stream6->CR & DMA_SxCR_EN);
}

xpcc::stm32::Dma2::Stream6::DataTransferDirection
xpcc::stm32::Dma2::Stream6::getDataTransferDirection()
{
	return static_cast<DataTransferDirection>(
		DMA2_Stream6->CR & (DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1));
}

void
xpcc::stm32::Dma2::Stream7::setMemorySource(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream7->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream7->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream7::setPeripheralSource(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream7->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream7::setMemorySource(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream7->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream7->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream7::setPeripheralSource(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream7->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream7::setMemorySource(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::MemoryToPeripheral) {
		dir = DataTransferDirection::MemoryToPeripheral;
		DMA2_Stream7->M0AR = reinterpret_cast<uint32_t>(address);

	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream7->PAR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}

void
xpcc::stm32::Dma2::Stream7::setPeripheralSource(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	static constexpr DataTransferDirection dir = DataTransferDirection::PeripheralToMemory;
	DMA2_Stream7->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream7::setMemoryDestination(uint8_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit8;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream7->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream7->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream7::setPeripheralDestination(uint8_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit8;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream7->M0AR = DMA2_Stream7->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream7->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream7::setMemoryDestination(uint16_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit16;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream7->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream7->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream7::setPeripheralDestination(uint16_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit16;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream7->M0AR = DMA2_Stream7->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream7->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream7::setMemoryDestination(uint32_t* address,
	MemoryIncrementMode inc
, MemoryBurstTransfer transfer)
{
	//stop();
	static constexpr MemoryDataSize size = MemoryDataSize::Bit32;
	// a memory source could mean that either a memory-to-peripheral or a
	// memory-to-memory transfer is intended
	// we'll use the current transfer mode to determine what to do
	DataTransferDirection dir;
	if(getDataTransferDirection() == DataTransferDirection::PeripheralToMemory) {
		dir = DataTransferDirection::PeripheralToMemory;
		DMA2_Stream7->M0AR = reinterpret_cast<uint32_t>(address);
	} else {
		dir = DataTransferDirection::MemoryToMemory;
		DMA2_Stream7->M0AR = reinterpret_cast<uint32_t>(address);
	}
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~memoryMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)      | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}


void
xpcc::stm32::Dma2::Stream7::setPeripheralDestination(uint32_t* address,
	PeripheralIncrementMode inc
, PeripheralBurstTransfer transfer)
{
	//stop();
	static constexpr PeripheralDataSize size = PeripheralDataSize::Bit32;
	// if memory-to-memory mode was selected, the memory source
	// will have been saved in the Peripheral Register
	// in memory-to-peripheral mode, the memory source will
	// need to be saved in the Memory Register
	if(getDataTransferDirection() == DataTransferDirection::MemoryToMemory) {
		DMA2_Stream7->M0AR = DMA2_Stream7->PAR;
	}
	static constexpr DataTransferDirection dir = DataTransferDirection::MemoryToPeripheral;
	DMA2_Stream7->PAR = reinterpret_cast<uint32_t>(address);
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~peripheralMask) | static_cast<uint32_t>(size)
		| static_cast<uint32_t>(inc)          | static_cast<uint32_t>(dir)
		| static_cast<uint32_t>(transfer);
}
void
xpcc::stm32::Dma2::Stream7::stop()
{
	DMA2_Stream7->CR &= ~DMA_SxCR_EN;
	while(DMA2_Stream7->CR & DMA_SxCR_EN); // wait for stream to be stopped
}

void
xpcc::stm32::Dma2::Stream7::configure(
	Channel channel,
	uint16_t sample_length, Priority priority, CircularMode circular
	, FlowControl flow)
{
	//stop();
	DMA2_Stream7->CR = (DMA2_Stream7->CR & ~configmask) | static_cast<uint32_t>(priority)
										  | static_cast<uint32_t>(circular)
		| static_cast<uint32_t>(channel) | static_cast<uint32_t>(flow);
	DMA2_Stream7->NDTR = sample_length;
}

void
xpcc::stm32::Dma2::Stream7::start()
{
	DMA2_Stream7->CR |= DMA_SxCR_EN;
}

bool
xpcc::stm32::Dma2::Stream7::isFinished()
{
	return !(DMA2_Stream7->CR & DMA_SxCR_EN);
}

xpcc::stm32::Dma2::Stream7::DataTransferDirection
xpcc::stm32::Dma2::Stream7::getDataTransferDirection()
{
	return static_cast<DataTransferDirection>(
		DMA2_Stream7->CR & (DMA_SxCR_DIR_0 | DMA_SxCR_DIR_1));
}

