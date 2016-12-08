// coding: utf-8
/* Copyright (c) 2011-2013, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

#ifndef XPCC_CORTEX_CORE_HPP
#define XPCC_CORTEX_CORE_HPP

#include <stdint.h>

namespace xpcc
{

namespace cortex
{

typedef void (*InterruptHandler)(void);

/// @ingroup	stm32f407vg_core
class Core
{
public:
	/**
	 * Get unique device id (96-bits)
	 *
	 * @param offset	0..2
	 * @return	32-bit of the unique id
	 */
	uint32_t
	getUniqueId(uint8_t offset)
	{
		if (offset > 2) return 0;
		uint32_t *baseaddress = (uint32_t*) 0x1FFF7A10;
		return *(baseaddress + offset);
	}
};

}

}

#endif	// XPCC_CORTEX_CORE_HPP