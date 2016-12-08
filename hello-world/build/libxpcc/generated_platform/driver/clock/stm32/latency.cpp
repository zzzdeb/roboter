/* Copyright (c) 2016, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
* ------------------------------------------------------------------------ */

#include "clock.hpp"

/*
For the 405, 407, 415, 417 devices, the maximum frequency of the SYSCLK and HCLK is
168 MHz, PCLK2 84 MHz and PCLK1 42 MHz. Depending on the device voltage range, the
maximum frequency should be adapted accordingly:
+---------------+---------------------------------------------------------------------+
| Latency       |                HCLK clock frequency (MHz)                           |
|               |---------------------------------------------------------------------|
|               | voltage range  | voltage range  |  voltage range  |  voltage range  |
|               | 2.7 V - 3.6 V  | 2.4 V - 2.7 V  |  2.1 V - 2.4 V  |  1.8 V - 2.1 V  |
|---------------|----------------|----------------|-----------------|-----------------|
|0WS(1CPU cycle)|  0< HCLK <=  30|  0< HCLK <=  24|  0 < HCLK <=  22|  0 < HCLK <=  20|
|---------------|----------------|----------------|-----------------|-----------------|
|1WS(2CPU cycle)| 30< HCLK <=  60| 24< HCLK <=  48| 22 < HCLK <=  44| 20 < HCLK <=  40|
|---------------|----------------|----------------|-----------------|-----------------|
|2WS(3CPU cycle)| 60< HCLK <=  90| 48< HCLK <=  72| 44 < HCLK <=  66| 40 < HCLK <=  60|
|---------------|----------------|----------------|-----------------|-----------------|
|3WS(4CPU cycle)| 90< HCLK <= 120| 72< HCLK <=  96| 66 < HCLK <=  88| 60 < HCLK <=  80|
|---------------|----------------|----------------|-----------------|-----------------|
|4WS(5CPU cycle)|120< HCLK <= 150| 96< HCLK <= 120| 88 < HCLK <= 110| 80 < HCLK <= 100|
|---------------|----------------|----------------|-----------------|-----------------|
|5WS(6CPU cycle)|150< HCLK <= 168|120< HCLK <= 144|110 < HCLK <= 132|100 < HCLK <= 120|
|---------------|----------------|----------------|-----------------|-----------------|
|6WS(7CPU cycle)|      NA        |144< HCLK <= 168|132 < HCLK <= 154|120 < HCLK <= 140|
|---------------|----------------|----------------|-----------------|-----------------|
|7WS(8CPU cycle)|      NA        |      NA        |154 < HCLK <= 168|140 < HCLK <= 160|
+---------------+----------------+----------------+-----------------+-----------------+
*/
		
static const uint32_t
flash_latency_2100[] =
{
	20000000,
	40000000,
	60000000,
	80000000,
	100000000,
	120000000,
	140000000,
	160000000,
};
static const uint32_t
flash_latency_2400[] =
{
	22000000,
	44000000,
	66000000,
	88000000,
	110000000,
	132000000,
	154000000,
	168000000,
};
static const uint32_t
flash_latency_2700[] =
{
	24000000,
	48000000,
	72000000,
	96000000,
	120000000,
	144000000,
	168000000,
};
static const uint32_t
flash_latency_3600[] =
{
	30000000,
	60000000,
	90000000,
	120000000,
	150000000,
	168000000,
};
uint32_t
xpcc::stm32::ClockControl::setFlashLatency(const uint32_t CPU_Frequency, const uint16_t mV)
{
	const uint32_t *lut(flash_latency_3600);
	uint8_t lut_size(sizeof(flash_latency_3600) / sizeof(uint32_t));
	// find the right table for the voltage
	if (mV < 2100) {
		lut = flash_latency_2100;
		lut_size = sizeof(flash_latency_2100) / sizeof(uint32_t);
	}
	else if (mV < 2400) {
		lut = flash_latency_2400;
		lut_size = sizeof(flash_latency_2400) / sizeof(uint32_t);
	}
	else if (mV < 2700) {
		lut = flash_latency_2700;
		lut_size = sizeof(flash_latency_2700) / sizeof(uint32_t);
	}
	// find the next highest frequency in the table
	uint8_t latency(0);
	uint32_t max_freq(0);
	while (latency < lut_size)
	{
		if (CPU_Frequency <= (max_freq = lut[latency]))
			break;
		latency++;
	}

	if (CPU_Frequency <= max_freq)
	{
		uint32_t acr = FLASH->ACR & ~FLASH_ACR_LATENCY;
		// set flash latency
		acr |= latency;
		// enable flash prefetch and data and instruction cache
		acr |= FLASH_ACR_PRFTEN | FLASH_ACR_DCEN | FLASH_ACR_ICEN;
		FLASH->ACR = acr;
	}
	return max_freq;
}