// coding: utf-8
/* Copyright (c) 2015, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#include "../../../device.hpp"
#include "../../clock/generic/common_clock.hpp"

extern "C"
{


void xpcc_fastcode
_delay_ns(uint16_t ns)
{
	// ns_per_loop = nanoseconds per cycle times cycles per loop (3 cycles)
	asm volatile (
		".syntax unified"       "\n\t"
		"muls.n	%2, %2, %1"     "\n\t"  // multiply the overhead cycles with the ns per cycle:  1-2 cycles on cm3, up to 32 cycles on cm0
		"subs.n	%0, %0, %2"     "\n\t"  // subtract the overhead in ns from the input:          1 cycle
	"1:  subs.n	%0, %0, %1"     "\n\t"  // subtract the ns per loop from the input:             1 cycle
		"bpl.n	1b"             "\n\t"  // keep doing that while result is still positive:      2 cycles (when taken)
	:: "r" (ns), "r" (xpcc::clock::ns_per_loop), "r" (8));
	// => loop is 3 cycles long
}


void xpcc_fastcode
_delay_us(uint16_t us)
{
	if (!us) return;    // 1 cycle, or 2 when taken

	uint32_t start = DWT->CYCCNT;
	// prefer this for cores with fast hardware multiplication
	int32_t delay = int32_t(xpcc::clock::fcpu_MHz) * us - 25;

	while (int32_t(DWT->CYCCNT - start) < delay)
		;
}


void xpcc_fastcode
_delay_ms(uint16_t ms)
{
	if (!ms) return;    // 1 cycle, or 2 when taken

	uint32_t start = DWT->CYCCNT;
	int32_t delay = int32_t(xpcc::clock::fcpu_kHz) * ms - 25;

	while (int32_t(DWT->CYCCNT - start) < delay)
		;
}


}