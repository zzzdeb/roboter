// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC__PLATFORM_HPP
#define XPCC__PLATFORM_HPP

#include <stdint.h>

#include <xpcc/architecture/detect.hpp>		// sets XPCC__CPU_xx etc. macros
#include <xpcc/architecture/utils.hpp>

// Include generated Platform sources:
#include "../../../generated_platform/drivers.hpp"

#include <xpcc/architecture/platform/board/stm32f4_discovery/stm32f4_discovery.hpp>
#endif	// XPCC__PLATFORM_HPP