// coding: utf-8
/* Copyright (c) 2013-2016, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------
/**
 * @ingroup 	stm32f407vg
 * @defgroup	stm32f407vg_core Core
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <reent.h>
#include <errno.h>

// ----------------------------------------------------------------------------
extern void xpcc_heap_table_find_largest(const uint32_t, uint32_t **, uint32_t **);

uint8_t *__brkval = 0;
uint8_t *heap_end = 0;

void __xpcc_initialize_memory(void)
{
	// find the largest heap that is DMA-able and S-Bus accessible
	xpcc_heap_table_find_largest(0x9, (uint32_t **) &__brkval, (uint32_t **) &heap_end);
	if (!__brkval) exit(ENOMEM);
}

/* Support function. Adjusts end of heap to provide more memory to
 * memory allocator. Simple and dumb with no sanity checks.
 *
 *  struct _reent *r -- re-entrancy structure, used by newlib to
 *                      support multiple threads of operation.
 *  ptrdiff_t size   -- number of bytes to add.
 *                      Returns pointer to start of new heap area.
 *
 *  Note:  This implementation is not thread safe (despite taking a
 *         _reent structure as a parameter).
 *         Since the _reent struct is not used in the current implementation,
 *         the following messages must be suppressed.
 */
void *
_sbrk_r(struct _reent *r,  ptrdiff_t size)
{
	(void) r;
	// move heap pointer
	uint8_t *heap = __brkval;
	__brkval += size;

	if (__brkval >= heap_end) {
		// ERROR: out of memory!
		exit(ENOMEM);
	}

	//  Return pointer to start of new heap area.
	return heap;
}

// FIXME: "Unwrap" the malloc for newlib allocator
void *__real__malloc_r(struct _reent *r, size_t size);
void *__wrap__malloc_r(struct _reent *r, size_t size) {
	return __real__malloc_r(r, size);
}
void *__real__calloc_r(struct _reent *r, size_t size);
void *__wrap__calloc_r(struct _reent *r, size_t size) {
	return __real__calloc_r(r, size);
}
void *__real__realloc_r(struct _reent *r, void *p, size_t size);
void *__wrap__realloc_r(struct _reent *r, void *p, size_t size) {
	return __real__realloc_r(r, p, size);
}
void __real__free_r(struct _reent *r, void *p);
void __wrap__free_r(struct _reent *r, void *p) {
	__real__free_r(r, p);
}

// memory traits are ignored for newlib allocator
void *malloc_tr(size_t size, uint32_t traits)
{
	(void) traits;
	return malloc(size);
}
