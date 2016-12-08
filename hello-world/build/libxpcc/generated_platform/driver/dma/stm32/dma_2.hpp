// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_DMA2_HPP
#define XPCC_STM32_DMA2_HPP

#include <stdint.h>
#include "../../../type_ids.hpp"
#include "../../../device.hpp"

/**
 * @ingroup 	stm32f407vg
 * @defgroup	stm32f407vg_dma DMA
 */

namespace xpcc
{

namespace stm32
{

/**
 * DMA
 *
 * Does not support - among other things - double buffering or FIFO usage
 *
 * @author	Kevin Laeufer
 * @ingroup	stm32f407vg_dma
 */
class Dma2
{
public:
	static inline void
	enable();

	static inline void
	disable();


public:
	class Stream0 : public DmaBase
	{
	public:
		/// will disable the stream
		static inline void
		setMemorySource(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		static inline void
		stop();

		/// will disable the stream
		static inline void
		configure(
			Channel channel,
			uint16_t sample_length,
			Priority priority = Priority::Medium,
			CircularMode circular = CircularMode::Disabled
			, FlowControl flow = FlowControl::Dma);
		static inline void
		start();

		static inline bool
		isFinished();

		static inline DataTransferDirection
		getDataTransferDirection();
	};
	class Stream1 : public DmaBase
	{
	public:
		/// will disable the stream
		static inline void
		setMemorySource(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		static inline void
		stop();

		/// will disable the stream
		static inline void
		configure(
			Channel channel,
			uint16_t sample_length,
			Priority priority = Priority::Medium,
			CircularMode circular = CircularMode::Disabled
			, FlowControl flow = FlowControl::Dma);
		static inline void
		start();

		static inline bool
		isFinished();

		static inline DataTransferDirection
		getDataTransferDirection();
	};
	class Stream2 : public DmaBase
	{
	public:
		/// will disable the stream
		static inline void
		setMemorySource(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		static inline void
		stop();

		/// will disable the stream
		static inline void
		configure(
			Channel channel,
			uint16_t sample_length,
			Priority priority = Priority::Medium,
			CircularMode circular = CircularMode::Disabled
			, FlowControl flow = FlowControl::Dma);
		static inline void
		start();

		static inline bool
		isFinished();

		static inline DataTransferDirection
		getDataTransferDirection();
	};
	class Stream3 : public DmaBase
	{
	public:
		/// will disable the stream
		static inline void
		setMemorySource(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		static inline void
		stop();

		/// will disable the stream
		static inline void
		configure(
			Channel channel,
			uint16_t sample_length,
			Priority priority = Priority::Medium,
			CircularMode circular = CircularMode::Disabled
			, FlowControl flow = FlowControl::Dma);
		static inline void
		start();

		static inline bool
		isFinished();

		static inline DataTransferDirection
		getDataTransferDirection();
	};
	class Stream4 : public DmaBase
	{
	public:
		/// will disable the stream
		static inline void
		setMemorySource(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		static inline void
		stop();

		/// will disable the stream
		static inline void
		configure(
			Channel channel,
			uint16_t sample_length,
			Priority priority = Priority::Medium,
			CircularMode circular = CircularMode::Disabled
			, FlowControl flow = FlowControl::Dma);
		static inline void
		start();

		static inline bool
		isFinished();

		static inline DataTransferDirection
		getDataTransferDirection();
	};
	class Stream5 : public DmaBase
	{
	public:
		/// will disable the stream
		static inline void
		setMemorySource(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		static inline void
		stop();

		/// will disable the stream
		static inline void
		configure(
			Channel channel,
			uint16_t sample_length,
			Priority priority = Priority::Medium,
			CircularMode circular = CircularMode::Disabled
			, FlowControl flow = FlowControl::Dma);
		static inline void
		start();

		static inline bool
		isFinished();

		static inline DataTransferDirection
		getDataTransferDirection();
	};
	class Stream6 : public DmaBase
	{
	public:
		/// will disable the stream
		static inline void
		setMemorySource(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		static inline void
		stop();

		/// will disable the stream
		static inline void
		configure(
			Channel channel,
			uint16_t sample_length,
			Priority priority = Priority::Medium,
			CircularMode circular = CircularMode::Disabled
			, FlowControl flow = FlowControl::Dma);
		static inline void
		start();

		static inline bool
		isFinished();

		static inline DataTransferDirection
		getDataTransferDirection();
	};
	class Stream7 : public DmaBase
	{
	public:
		/// will disable the stream
		static inline void
		setMemorySource(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemorySource(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralSource(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint8_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint8_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint16_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint16_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setMemoryDestination(uint32_t* address,
			MemoryIncrementMode inc = MemoryIncrementMode::Increment
			, MemoryBurstTransfer transfer = MemoryBurstTransfer::Single);
		/// will disable the stream
		static inline void
		setPeripheralDestination(uint32_t* address,
			PeripheralIncrementMode inc = PeripheralIncrementMode::Fixed
			, PeripheralBurstTransfer transfer = PeripheralBurstTransfer::Single);
		static inline void
		stop();

		/// will disable the stream
		static inline void
		configure(
			Channel channel,
			uint16_t sample_length,
			Priority priority = Priority::Medium,
			CircularMode circular = CircularMode::Disabled
			, FlowControl flow = FlowControl::Dma);
		static inline void
		start();

		static inline bool
		isFinished();

		static inline DataTransferDirection
		getDataTransferDirection();
	};
};

}	// namespace stm32

}	// namespace xpcc

#include "dma_2_impl.hpp"

#endif	// XPCC_STM32_DMA2_HPP
