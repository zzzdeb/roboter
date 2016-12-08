// coding: utf-8
/* Copyright (c) 2013-2016, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------
/**
 * @file	syscalls.cpp
 * @brief	Stubs for newlib
 *
 * Except for _sbrk_r() (which is needed for malloc()) all these stubs are
 * only dummy functions which don't do anything useful.
 *
 * _exit() and exit() are defined in the file "startup.S". They are marked
 * as weak references, so they can be easily overwritten by user code.
 */
// ----------------------------------------------------------------------------

/**
 * @ingroup 	{{target.string}}
 * @defgroup	{{target.string}}_core Core
 */

#include <stdlib.h>
#include <reent.h>
#include <sys/stat.h>

// ----------------------------------------------------------------------------
int
_open_r(struct _reent *r, const char *name, int flags, int mode)
{
	(void) r;
	(void) name;
	(void) flags;
	(void) mode;
	return -1;
}

_ssize_t
_read_r(struct _reent *r, int file, void *ptr, size_t len)
{
	(void) r;
	(void) file;
	(void) ptr;
	(void) len;
	return 0;
}

_ssize_t
_write_r(struct _reent *r, int file, const void *ptr, size_t len)
{
	(void) r;
	(void) file;
	(void) ptr;
	(void) len;
	return 0;
}

int
_close_r(struct _reent *r, int file)
{
	(void) r;
	(void) file;
	return 0;
}

// ----------------------------------------------------------------------------
_off_t
_lseek_r(struct _reent *r, int file, _off_t ptr, int dir)
{
	(void) r;
	(void) file;
	(void) ptr;
	(void) dir;
	return (_off_t) 0;		// Always indicate we are at file beginning.
}

// ----------------------------------------------------------------------------
int
_fstat_r(struct _reent *r, int file, struct stat *st)
{
	(void) r;
	(void) file;
	st->st_mode = S_IFCHR;	// Always set as character device.
	return 0;
}

// ----------------------------------------------------------------------------
int
_isatty(int file)
{
	(void) file;
	return 1;
}
