// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_UART_SPI_MASTER2_HPP
#define XPCC_STM32_UART_SPI_MASTER2_HPP

#include <xpcc/architecture/interface/spi_master.hpp>
#include "../../uart/stm32/uart_hal_2.hpp"
#include "type_ids.hpp"

namespace xpcc
{

namespace stm32
{

/**
 * Serial Peripheral Interface of the Uart module.
 *
 * @warnind	Be aware, that the uart module can send bytes only LSB first.
 *			Therefore the data is bit reversed in software for DataOrder::MsbFirst.
 *
 * @author		Niklas Hauser
 * @ingroup		stm32f407vg_spi
 */
class UartSpiMaster2 : public xpcc::SpiMaster, public UartBase
{
	static DataOrder dataOrder;
	static uint8_t state;
	static uint8_t count;
	static void *context;
	static ConfigurationHandler configuration;
public:
	static const TypeId::UartSpiMaster2Sck  Sck;
	static const TypeId::UartSpiMaster2Miso Miso;
	static const TypeId::UartSpiMaster2Mosi Mosi;

public:
	enum class
	DataMode : uint32_t
	{
		Mode0 = 0b00,			///< clock normal,   sample on rising  edge
		Mode1 = USART_CR2_CPHA,	///< clock normal,   sample on falling edge
		Mode2 = USART_CR2_CPOL,	///< clock inverted, sample on falling  edge
		Mode3 = USART_CR2_CPOL | USART_CR2_CPHA
		///< clock inverted, sample on rising edge
	};

public:
	template< 	class SystemClock, uint32_t baudrate,
				uint16_t tolerance = xpcc::Tolerance::FivePercent >
	static void
	initialize()
	{
		constexpr UartBase::OversamplingMode oversample =
				UartBaudrate::getOversamplingMode(SystemClock::Usart2, baudrate);
		UsartHal2::initializeWithBrr(
				UartBaudrate::getBrr<SystemClock::Usart2, baudrate, tolerance>(),
				UsartHal2::Parity::Disabled,
				oversample);
		UsartHal2::setLastBitClockPulse(UsartHal2::LastBitClockPulse::Output);
		UsartHal2::setSpiClock(UsartHal2::SpiClock::Enabled);
		UsartHal2::setTransmitterEnable(true);
		UsartHal2::setReceiverEnable(true);
		dataOrder = DataOrder::MsbFirst;
		state = 0;
	}


	static void
	setDataMode(DataMode mode)
	{
		UsartHal2::setSpiDataMode(static_cast<UartBase::SpiDataMode>(mode));
	}

	/// @warning 	On this target, only `DataOrder::LsbFirst` is natively
	///				supported!
	///				`DataOrder::MsbFirst` is reimplemented in software using
	///				xpcc::bitReverse(), which adds some overhead.
	/// @see	xpcc::bitReverse()
	static void
	setDataOrder(DataOrder order)
	{
		dataOrder = order;
	}


	static uint8_t
	acquire(void *ctx, ConfigurationHandler handler = nullptr);

	static uint8_t
	release(void *ctx);


	static uint8_t
	transferBlocking(uint8_t data)
	{
		return RF_CALL_BLOCKING(transfer(data));
	}

	static void
	transferBlocking(uint8_t *tx, uint8_t *rx, std::size_t length)
	{
		RF_CALL_BLOCKING(transfer(tx, rx, length));
	}


	static xpcc::ResumableResult<uint8_t>
	transfer(uint8_t data);

	static xpcc::ResumableResult<void>
	transfer(uint8_t *tx, uint8_t *rx, std::size_t length);
};

} // namespace stm32

} // namespace xpcc

#endif // XPCC_STM32_UART_SPI_MASTER2_HPP