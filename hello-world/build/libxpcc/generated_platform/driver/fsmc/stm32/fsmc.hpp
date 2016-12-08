// coding: utf-8
/* Copyright (c) 2012-2013, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32_FSMC_HPP
#define XPCC_STM32_FSMC_HPP

#include <stdint.h>
#include "../../../device.hpp"
#include "../../../type_ids.hpp"

/**
 * @ingroup 	stm32f407vg
 * @defgroup	stm32f407vg_fsmc FSMC
 */

namespace xpcc
{
	namespace stm32
	{
		namespace fsmc
		{
			/**
			 * Configure NOR-Flash or (P)SRAM
			 *
			 * NOR non-multiplexed
			 * - CLK
			 * - A[25:0]
			 * - D[15:0]
			 * - NE[x]
			 * - NOE
			 * - NWE
			 * - NL(=NADV)
			 * - NWAIT
			 *
			 * NOR multiplexed
			 * - A[25:16]
			 * - AD[15:0]
			 *
			 * (P)SRAM
			 * - NBL[1]		- Upper byte enable (NUB)
			 * - NBL[0]		- Lower byte enable (NLB)
			 *
			 * Options:
			 * - multiplexed, non-multiplexed
			 * - asynchronous, synchronous
			 *
			 * Mode 1 (SRAM/CRAM)
			 * - NOE directly low
			 * - NWE after address setup
			 * - Timings: address setup, data phase
			 *
			 * Mode A (CRAM)
			 * - NOE, NWE low after address setup
			 * - Timings: address setup, data phase
			 *
			 * Mode 2/B (NOR Flash)
			 * - NADV low during address setup
			 * - NOE directly low
			 * - Mode 2: NWE low after address setup
			 * - Mode B: NWE directly low
			 *
			 * Mode C (NOR Flash)
			 * - NADV low during address setup
			 * - NOE, NWE low after address setup
			 *
			 * Mode D
			 * - Mode C with additional address hold step (NADV, NOE, NWE high)
			 * - Timings: address setup, address hold, data phase
			 *
			 * Mode muxed
			 * - Mode D with lower address bits on data lanes during
			 *   address setup step
			 *
			 * Async wait: only data phase stage is prolonged, address setup
			 * and address hold are not affected.
			 *
			 * Memory Type (MTYP):
			 * - 00 SRAM/ROM 					(asynchronous, non-multiplexed)
			 * - 01 PSRAM/Cellular RAM: CRAM	((a)synchronous read/write, (non-)multiplexed)
			 * - 10 NOR Flash/One NAND Flash	((a)synchronous read, (non-)multiplexed)
			 *
			 * Multiplexed mode only valid for NOR and PSRAM
			 *
			 * Synchronous => burst mode?
			 * NOR Flash and burst write?
			 *
			 * @ingroup stm32f407vg_fsmc
			 */
			class NorSram
			{
			public:
				/**
				 * Corresponds to NE1..4.
				 */
				enum Region
				{
					CHIP_SELECT_1 = 0,
					CHIP_SELECT_2 = 1,
					CHIP_SELECT_3 = 2,
					CHIP_SELECT_4 = 3,
				};

				enum WaitPolarity
				{
					WAIT_HIGH_ACTIVE,
					WAIT_LOW_ACTIVE,
				};

				enum BusType
				{
					NO_MULTIPLEX_8BIT = 0,
					NO_MULTIPLEX_16BIT = FSMC_BCR1_MWID_0,
					ADDRESS_DATA_MULIPLEX_8BIT = FSMC_BCR1_MUXEN,
					ADDRESS_DATA_MULIPLEX_16BIT = FSMC_BCR1_MUXEN | FSMC_BCR1_MWID_0,
				};

				enum MemoryType
				{
					SRAM_ROM = 0,
					PSRAM = FSMC_BCR1_MTYP_0, ///< PSRAM (CRAM)
					NOR = FSMC_BCR1_MTYP_1, ///< NOR Flash/OneNAND Flash
				};

				enum AccessMode
				{
					MODE_A = 0,	///< access mode A
					MODE_B = FSMC_BTR1_ACCMOD_0, ///< access mode B
					MODE_C = FSMC_BTR1_ACCMOD_1, ///< access mode C
					MODE_D = FSMC_BTR1_ACCMOD_0 | FSMC_BTR1_ACCMOD_1 ///< access mode D
				};

				enum class ExtendedMode : uint32_t
				{
					Disable = 0,
					Enable  = FSMC_BCR1_EXTMOD,
				};

				/**
				 * Timing for asynchronous access
				 */
				struct AsynchronousTiming
				{
					uint8_t readAddressSetup;	///< 0..15

					/// (only for muxed I/O) 1..15
					uint8_t readAddressHold;
					uint8_t readDataPhase;		///< 1..256

					uint8_t writeAddressSetup;	///< 0..15

					/// (only for muxed I/O) 1..15
					uint8_t writeAddressHold;
					uint8_t writeDataPhase;		///< 1..256

					/**
					 * Bus turn around time
					 *
					 * Time from NEx high to NEx low => time between two bus
					 * accesses (0..15 HCLK cycles).
					 */
					uint8_t busTurnAround;
				};

				/**
				 * Timing for synchronous access
				 */
				struct SynchronousTiming
				{
					uint8_t busTurnAround;		///< 0..15

					/** Number of HCLK cycles for one CLK cycle, [1..16] */
					uint8_t clockDivideRatio;

					uint8_t dataLatency;		///< 2..17 CLK cycles
				};

			public:
				static void
				resetRegion(Region region);

				static inline void
				enableRegion(Region region, bool enable = true)
				{
					if (enable) {
						FSMC_Bank1->BTCR[region] |= FSMC_BCR1_MBKEN;
					}
					else {
						FSMC_Bank1->BTCR[region] &= ~FSMC_BCR1_MBKEN;
					}

				}

				/**
				 * Configure a region of Bank 1 for synchronous access.
				 *
				 * The region is disabled afterwards and has to be enabled
				 * via enableRegion().
				 */
				static void
				configureSynchronousRegion(Region region,
						BusType multiplex,
						MemoryType memoryType,
						SynchronousTiming timing);

				static void
				configureAsynchronousRegion(Region region,
						BusType multiplex,
						MemoryType memoryType,
						AccessMode accessMode,
						AsynchronousTiming timing,
						 ExtendedMode extended = ExtendedMode::Enable);

				static inline void
				enableAsynchronousWait(Region region,
						WaitPolarity polarity = WAIT_LOW_ACTIVE)
				{
					uint32_t btcr = FSMC_BCR1_ASYNCWAIT;
					if (polarity != WAIT_LOW_ACTIVE)
					{
						btcr |= FSMC_BCR1_WAITPOL;
					}
					FSMC_Bank1->BTCR[region] = btcr;
				}

				/**
				 * Get mapped memory address of a region.
				 *
				 * Each region is 64 MB in size.
				 */
				template<typename T>
				static constexpr inline T*
				getRegionPointer(Region region)
				{
					return 	(region == CHIP_SELECT_1)? (T *)(0x60000000) :
							(region == CHIP_SELECT_2)? (T *)(0x64000000) :
							(region == CHIP_SELECT_3)? (T *)(0x68000000) :
							(region == CHIP_SELECT_4)? (T *)(0x6C000000) :
															(0x00000000);
				}
			};

			class FsmcNand
			{
				// TODO
			};

			class FsmcPcCard
			{
				// TODO
			};
		}

		/**
		 * Flexible static memory controller.
		 *
		 * Memory Map:
		 * 0x6000 0000 - 0x6fff ffff : Bank 1 4x NOR or [P]SRAM devices
		 * 0x7000 0000 - 0x7fff ffff : Bank 2 NAND Flash device
		 * 0x8000 0000 - 0x8fff ffff : Bank 3 NAND Flash device
		 * 0x9000 0000 - 0x9fff ffff : Bank 4 PC Card device
		 *   each bank is 4x64 = 256 MB wide
		 *
		 * NOR/PSRAM/SRAM Flash signals:
		 * CLK       - Clock (for synchronous burst)
		 * A[25:0]   - Address Bus
		 * AD[15:0]  - 16-bit multiplexed, bidirectional address/data bus or data bus
		 * NE[x]     - Chip select, x=1..4
		 * NOE       - Output enable
		 * NWE       - Write enable
		 * NL(=NADV) - Latch enable (this signal is called address valid,
		 *             NADV, by some NOR Flash devices)
		 * NWAIT     - NOR Flash wait input signal to the FSMC
		 * NBL1      - Upper byte enable (memory signal name: NUB)
		 * NBL0      - Lowed byte enable (memory signal name: NLB)
		 *
		 *
		 * \author	Fabian Greif
		 */
		class Fsmc
		{
		public:
			/// TypeId used to connect GPIO pins to the FsmcD0.
			static const TypeId::FsmcD0 D0;
			/// TypeId used to connect GPIO pins to the FsmcD1.
			static const TypeId::FsmcD1 D1;
			/// TypeId used to connect GPIO pins to the FsmcD2.
			static const TypeId::FsmcD2 D2;
			/// TypeId used to connect GPIO pins to the FsmcD3.
			static const TypeId::FsmcD3 D3;
			/// TypeId used to connect GPIO pins to the FsmcD4.
			static const TypeId::FsmcD4 D4;
			/// TypeId used to connect GPIO pins to the FsmcD5.
			static const TypeId::FsmcD5 D5;
			/// TypeId used to connect GPIO pins to the FsmcD6.
			static const TypeId::FsmcD6 D6;
			/// TypeId used to connect GPIO pins to the FsmcD7.
			static const TypeId::FsmcD7 D7;
			/// TypeId used to connect GPIO pins to the FsmcD8.
			static const TypeId::FsmcD8 D8;
			/// TypeId used to connect GPIO pins to the FsmcD9.
			static const TypeId::FsmcD9 D9;
			/// TypeId used to connect GPIO pins to the FsmcD10.
			static const TypeId::FsmcD10 D10;
			/// TypeId used to connect GPIO pins to the FsmcD11.
			static const TypeId::FsmcD11 D11;
			/// TypeId used to connect GPIO pins to the FsmcD12.
			static const TypeId::FsmcD12 D12;
			/// TypeId used to connect GPIO pins to the FsmcD13.
			static const TypeId::FsmcD13 D13;
			/// TypeId used to connect GPIO pins to the FsmcD14.
			static const TypeId::FsmcD14 D14;
			/// TypeId used to connect GPIO pins to the FsmcD15.
			static const TypeId::FsmcD15 D15;
			/// TypeId used to connect GPIO pins to the FsmcD16.
			static const TypeId::FsmcD16 D16;
			/// TypeId used to connect GPIO pins to the FsmcD17.
			static const TypeId::FsmcD17 D17;
			/// TypeId used to connect GPIO pins to the FsmcD18.
			static const TypeId::FsmcD18 D18;
			/// TypeId used to connect GPIO pins to the FsmcD19.
			static const TypeId::FsmcD19 D19;
			/// TypeId used to connect GPIO pins to the FsmcD20.
			static const TypeId::FsmcD20 D20;
			/// TypeId used to connect GPIO pins to the FsmcD21.
			static const TypeId::FsmcD21 D21;
			/// TypeId used to connect GPIO pins to the FsmcD22.
			static const TypeId::FsmcD22 D22;
			/// TypeId used to connect GPIO pins to the FsmcD23.
			static const TypeId::FsmcD23 D23;
			/// TypeId used to connect GPIO pins to the FsmcD24.
			static const TypeId::FsmcD24 D24;
			/// TypeId used to connect GPIO pins to the FsmcD25.
			static const TypeId::FsmcD25 D25;
			/// TypeId used to connect GPIO pins to the FsmcD26.
			static const TypeId::FsmcD26 D26;
			/// TypeId used to connect GPIO pins to the FsmcD27.
			static const TypeId::FsmcD27 D27;
			/// TypeId used to connect GPIO pins to the FsmcD28.
			static const TypeId::FsmcD28 D28;
			/// TypeId used to connect GPIO pins to the FsmcD29.
			static const TypeId::FsmcD29 D29;
			/// TypeId used to connect GPIO pins to the FsmcD30.
			static const TypeId::FsmcD30 D30;
			/// TypeId used to connect GPIO pins to the FsmcD31.
			static const TypeId::FsmcD31 D31;
			/// TypeId used to connect GPIO pins to the FsmcA16.
			static const TypeId::FsmcA16 A16;
			/// TypeId used to connect GPIO pins to the FsmcA17.
			static const TypeId::FsmcA17 A17;
			/// TypeId used to connect GPIO pins to the FsmcA18.
			static const TypeId::FsmcA18 A18;
			/// TypeId used to connect GPIO pins to the FsmcA19.
			static const TypeId::FsmcA19 A19;
			/// TypeId used to connect GPIO pins to the FsmcA20.
			static const TypeId::FsmcA20 A20;
			/// TypeId used to connect GPIO pins to the FsmcA21.
			static const TypeId::FsmcA21 A21;
			/// TypeId used to connect GPIO pins to the FsmcA22.
			static const TypeId::FsmcA22 A22;
			/// TypeId used to connect GPIO pins to the FsmcA23.
			static const TypeId::FsmcA23 A23;
			/// TypeId used to connect GPIO pins to the FsmcNoe.
			static const TypeId::FsmcNoe Noe;
			/// TypeId used to connect GPIO pins to the FsmcNwe.
			static const TypeId::FsmcNwe Nwe;
			/// TypeId used to connect GPIO pins to the FsmcNl.
			static const TypeId::FsmcNl Nl;
			/// TypeId used to connect GPIO pins to the FsmcNe1.
			static const TypeId::FsmcNe1 Ne1;

		public:
			/**
			 * Reset all NAND/NOR/SRAM/... settings
			 */
			static void
			initialize();

		private:
			static inline void
			enable()
			{
				RCC->AHB3ENR |= RCC_AHB3ENR_FSMCEN;
			}

			static inline void
			disable()
			{
				RCC->AHB3ENR &= ~RCC_AHB3ENR_FSMCEN;
			}
		};
	}
}

#endif