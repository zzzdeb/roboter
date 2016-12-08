/*
 *                           LINKER  SCRIPT
 *
 * The Linker Script defines how the code and data emitted by the GNU C compiler
 * and assembler are  to be loaded into memory (code goes into FLASH, variables
 * go into RAM).
 *
 * Any symbols defined in the Linker Script are automatically global and
 * available to the rest of the program.
 *
 * Example for STM32F427:
 *
 *                        MEMORY MAP (BACKUP)
 *
 * Backup internal SRAM (4 kB):
 *                |                                 | 0x4002 5000 <---- __backup_end
 *      +-------> |---------------------------------| 0x4002 4FFF
 *      |         |                                 |
 *   .backup      |                                 |
 *      |         |                                 |
 *      +-------> |---------------------------------| 0x4002 4000 <--- __backup_start
 *
 *                          MEMORY MAP (RAM)
 *
 * Auxiliary internal SRAM3 (64 kB):
 *   only accessible by CPU via S-Bus (less efficient than I-Bus), otherwise fully DMA capable
 *                |                                 | 0x2003 0000 <---- __ram_end, __heap3_end
 *      +-------> |---------------------------------| 0x2002 FFFF
 *      |         |                                 |
 *   .heap3       |         not available on        |
 *      |         |        F40./F41. devices!       |
 *      +-------> |---------------------------------| 0x2002 0000 <--- __heap3_start
 *
 * Auxiliary internal SRAM2 (16 kB):
 *   only accessible by CPU via S-Bus (less efficient than I-Bus), otherwise fully DMA capable
 *                |                                 | 0x2002 0000 <---- (__ram_end, __heap_end), __heap2_end
 *      +-------> |---------------------------------| 0x2001 FFFF
 *      |         |                                 |
 *   .heap2       |                                 |
 *      |         |                                 |
 *      +-------> |---------------------------------| 0x2001 C000 <--- __heap2_start
 *
 *
 * Main internal SRAM1 (112 kB):
 *                |                                 | 0x2001 C000 <---- __heap1_end
 *      +-------> |---------------------------------| 0x2001 BFFF
 *      |         |                                 |
 *      |         |               ^                 |
 *   .heap1       |               |                 |
 *      |         |            Heap Area            |
 *      |         |         (grows upwards)         | <------- __heap1_start
 *      +-------> |---------------------------------| <------- __noinit_end
 *      |         |                                 |
 *   .noinit      |     Global data not cleared     |
 *      |         |           after reset           | <------- __noinit_start
 *      +-------> |---------------------------------| <------- __bss_end
 *      |         |                                 |
 *    .bss        |     uninitialized variables     |
 *      |         |                                 | <------- __bss_start
 *      +-------> |---------------------------------| <------- __data_end
 *      |         |                                 |
 *      |         |                                 |
 *    .data       |     initialized variables       |
 *      |         |                                 |
 *      |         |                                 | <------- __data_start
 *      +-------> |---------------------------------| <------- __vector_table_ram_end
 *      |         |                                 |
 *  .vectors      |    Interrupt Vectors (in RAM)   |
 *      |         |        (if re-mapped)           | <------- __vector_table_ram_start
 *      +-------> |---------------------------------| 0x2000 0000 <--- __ram_start
 *
 *
 * CCM (Core Coupled memory) (64 kB):
 *   only accessible by the CPU (no DMA) via D-Bus, not I-Bus!
 *                |                                 | 0x1001 0000 <---- __heap0_end
 *      +-------> |---------------------------------| 0x1000 FFFF
 *      |         |                                 |
 *   .heap0       |           Unused RAM            |
 *      |         |                                 | <------- __heap0_start
 *      +-------> |---------------------------------| <------- __fastdata_end
 *      |         |                                 |
 *  .fastdata     |     initialized variables       |
 *      |         |                                 | <------- __fastdata_start
 *      +-------> |---------------------------------| <------- __process_stack_top, __stack_end
 *      |         |       Process Stack (psp)       |
 *      |         |       (grows downwards)         |
 *      |         |               |                 |
 *      |         |               v                 |
 *   .stack       |---------------------------------| <------- __main_stack_top
 *      |         |        Main Stack (msp)         |
 *      |         |       (grows downwards)         |
 *      |         |               |                 |
 *      |         |               v                 | <------- __stack_start
 *      +-------> |---------------------------------| 0x1000 0000
 *
 *
 *                          MEMORY MAP (Flash)
 *
 *                |                                 | 0x0802 0000 <--- __rom_end
 *                |---------------------------------| 0x0801 FFFF
 *                |                                 |
 *                |                                 |
 *                |                                 |
 *                |          Unused flash           |
 *                |                                 |
 *                |                                 |
 *                |                                 |
 *      +-------> |---------------------------------|
 *      |         |                                 |
 *      |         |                                 |
 *      |         |                                 |
 *    .data       |      copy of .data area         |
 *      |         |                                 |
 *      |         |                                 |
 *      |         |                                 | <------- __data_load
 *      +-------> |---------------------------------|
 *      |         |    Static Constructors (C++)    |
 *      |         | ------------------------------- |
 *      |         |                                 |
 *    .text       |                                 |
 *      |         |          C/C++ code             |
 *      |         |     (contains .fastcode)        |
 *      |         |                                 | <------- __fastcode_load, __fastcode_start, __fastcode_end
 *      +-------> |---------------------------------|
 *      |         |                                 |
 *  .fastdata     |     Variables to be loaded      |
 *      |         |         into CCM RAM            | <------- __fastdata_load
 *      +-------> |---------------------------------|
 *      |         |                                 |
 *   .reset       |   Interrupt Vectors (in FLASH)  |
 *      |         |       (copy of .vectors)        | <------- __vector_table_rom_start, __vector_table_ram_load
 *      +-------> |---------------------------------| 0x0800 0000 <--- __rom_start
 *
 * The first two words (32-bit) in the Flash defines the initial stack pointer
 * location and the reset handler location.
 */

MEMORY
{
	FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 1024k
	CCM (rw) : ORIGIN = 0x10000000, LENGTH = 64k
	SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 112k
	SRAM2 (rwx) : ORIGIN = 0x2001C000, LENGTH = 16k
	BACKUP (rwx) : ORIGIN = 0x40024000, LENGTH = 4k
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128k
	
}

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* First executable instruction in an output file */
ENTRY(Reset_Handler)

/* force linker to include the syscalls from libxpcc.a */
EXTERN(_sbrk_r)
EXTERN(_init)

PROVIDE(__ram_start = ORIGIN(RAM));
PROVIDE(__ram_end   = ORIGIN(RAM) + LENGTH(RAM));
PROVIDE(__rom_start = ORIGIN(FLASH));
PROVIDE(__rom_end   = ORIGIN(FLASH) + LENGTH(FLASH));

/* the thread stack is used only for reporting hard fault conditions! It may therefore be small. */
PROCESS_STACK_SIZE  = 32;
/* the handler stack is used for main program as well as interrupts */
MAIN_STACK_SIZE     = 3040;
/* combined stack size */
TOTAL_STACK_SIZE = MAIN_STACK_SIZE + PROCESS_STACK_SIZE;



SECTIONS
{
		.reset :
	{
		__vector_table_rom_start = .;
		__vector_table_ram_load = .;
		/* Initial stack address, Reset and NMI handler */
		KEEP(*(.reset))
		. = ALIGN(4);
	} >FLASH


		.vectors :  /* Vector table in RAM, only if remapped */
	{
		__vector_table_ram_start = .;

		/* used for vectors remapped to RAM */
		KEEP(*(.vectors))

		. = ALIGN(4);
		__vector_table_ram_end = .;
	} >RAM


		.stack (NOLOAD) :
	{
		__stack_start = .;

		. += MAIN_STACK_SIZE;
		. = ALIGN(8);
		__main_stack_top = .;

		. += PROCESS_STACK_SIZE;
		. = ALIGN(8);
		__process_stack_top = .;

		__stack_end = .;
	} >CCM


		.fastdata : ALIGN(4)
	{
		__fastdata_load = LOADADDR(.fastdata);
		__fastdata_start = .;

		*(.fastdata)

		. = ALIGN(4);
		__fastdata_end = .;
	} >CCM AT >FLASH


		.heap0 (NOLOAD) :
	{
		__heap0_start = .;

		. = ORIGIN(CCM) + LENGTH(CCM);
		__heap0_end = .;
	} >CCM


		.backup : ALIGN(4)
	{
		__backup_load = LOADADDR(.backup);
		__backup_start = .;

		*(.backup)

		. = ALIGN(4);
		__backup_end = .;
	} >BACKUP AT >FLASH


		.heap5 (NOLOAD) :
	{
		__heap5_start = .;

		. = ORIGIN(BACKUP) + LENGTH(BACKUP);
		__heap5_end = .;
	} >BACKUP

		.text : ALIGN(4)
	{
		*(.text .text.* .gnu.linkonce.t.*)
	} >FLASH

	.rodata : ALIGN(4)
	{
		*(.rodata .rodata.* .gnu.linkonce.r.*)

		. = ALIGN(4);
		KEEP(*(.init))

		. = ALIGN(4);
		PROVIDE_HIDDEN(__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN(__preinit_array_end = .);

		. = ALIGN(4);
		PROVIDE_HIDDEN(__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN(__init_array_end = .);

		. = ALIGN(4);
		KEEP(*(.fini))

		. = ALIGN(4);
		PROVIDE_HIDDEN(__fini_array_start = .);
		KEEP(*(.fini_array))
		KEEP(*(SORT(.fini_array.*)))
		PROVIDE_HIDDEN(__fini_array_end = .);

		/* These are for static constructors and destructors under ELF */
		PROVIDE(__ctors_start__ = .);
		KEEP(*crtbegin.o(.ctors))
		KEEP(*(EXCLUDE_FILE (*crtend.o) .ctors))
		KEEP(*(SORT(.ctors.*)))
		KEEP(*crtend.o(.ctors))
		PROVIDE(__ctors_end__ = .);

		/* We never call static constructors
		PROVIDE(__dtors_start__ = .);
		KEEP(*crtbegin.o(.dtors))
		KEEP(*(EXCLUDE_FILE (*crtend.o) .dtors))
		KEEP(*(SORT(.dtors.*)))
		KEEP(*crtend.o(.dtors))
		PROVIDE(__dtors_end__ = .);
		*/

		*(.init .init.*)
		*(.fini .fini.*)
	} >FLASH

	/* Unwind tables are used to unwind the stack for C++ exceptions.
	 * On xpcc these are disabled by default, so these sections are empty.
	.ARM.extab : ALIGN(4)
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} >FLASH

	.ARM.exidx : ALIGN(4)
	{
		__exidx_start = .;
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		__exidx_end = .;
	} >FLASH

	.eh_frame : ALIGN(4)
	{
		KEEP(*(.eh_frame*))
	} >FLASH
	 */


		.fastcode : ALIGN(4)
	{
		/* From the Cortex-M3 Technical Reference Manual:
		 *
		 * """
		 * 14.5 System Interface:
		 *
		 * The system interface is a 32-bit AHB-Lite bus. Instruction and vector fetches, and data and debug accesses to
		 * the System memory space, 0x20000000 - 0xDFFFFFFF, 0xE0100000 - 0xFFFFFFFF, are performed over this bus.
		 *
		 * 14.5.6 Pipelined instruction fetches:
		 *
		 * To provide a clean timing interface on the System bus, instruction and vector fetch requests to this bus are
		 * registered. This results in an additional cycle of latency because instructions fetched from the System bus
		 * take two cycles. This also means that back-to-back instruction fetches from the System bus are not possible.
		 *
		 *  Note:
		 *    Instruction fetch requests to the ICode bus are not registered.
		 *    Performance critical code must run from the ICode interface.
		 *
		 * """
		 *
		 * So for STM32's where the CCM is _not_ connected to the I-Bus, we execute .fastcode from Flash.
		 */
		*(.fastcode)
	} >FLASH


		/* initialized variables */
	.data : ALIGN(4)
	{
		__data_load = LOADADDR(.data);
		__data_start = .;
		*(.data .data.* .gnu.linkonce.d.*)
		. = ALIGN(4);
		__data_end = .;
	} >RAM AT >FLASH

	/* uninitialized variables */
	.bss :
	{
		__bss_start = . ;
		*(.bss .bss.* .gnu.linkonce.b.*)
		. = ALIGN(4);
		__bss_end = .;
	} >RAM

	/* Global data not cleared after reset.  */
	.noinit (NOLOAD) :
	{
		__noinit_start = .;
		*(.noinit*)
		. = ALIGN(4);
		__noinit_end = .;
	} >RAM


		.heap1 (NOLOAD) :
	{
		__heap1_start = .;

		. = ORIGIN(SRAM1) + LENGTH(SRAM1);
		__heap1_end = .;
	} >RAM


		.heap2 (NOLOAD) :
	{
		__heap2_start = .;

		. = ORIGIN(SRAM2) + LENGTH(SRAM2);
		__heap2_end = .;
	} >RAM

	

	/* TABLES! TABLES! ALL THE TABLES YOU COULD EVER WANT! TABLES! */
		.table.zero.intern : ALIGN(4)
	{
		__table_zero_intern_start = .;
		LONG(__bss_start)
		LONG(__bss_end)
		__table_zero_intern_end = .;
	} >FLASH


		.table.copy.intern : ALIGN(4)
	{
		__table_copy_intern_start = .;
		LONG(__data_load)
		LONG(__data_start)
		LONG(__data_end)
		LONG(__fastdata_load)
		LONG(__fastdata_start)
		LONG(__fastdata_end)
		LONG(__backup_load)
		LONG(__backup_start)
		LONG(__backup_end)
		__table_copy_intern_end = .;
	} >FLASH


		.table.zero.extern : ALIGN(4)
	{
		__table_zero_extern_start = .;
		
		__table_zero_extern_end = .;
	} >FLASH

	.table.copy.extern : ALIGN(4)
	{
		__table_copy_extern_start = .;
		
		__table_copy_extern_end = .;
	} >FLASH


		/* SRAM properties bit mask (16-bit):
	 *
	 * - 0x0001: accessible via S-Bus
	 * - 0x0002: accessible via D-Bus
	 * - 0x0004: accessible via I-Bus
	 * - 0x0008: accessible via DMA
	 * - 0x0010: accessible via DMA2D
	 *
	 * - 0x1FE0: reserved
	 *
	 * - 0x2000: Fast memory (Core- or Tightly-Coupled)
	 * - 0x4000: non-volatile (or battery backed) memory
	 * - 0x8000: external memory
	 */
	.table.section_heap : ALIGN(4)
	{
		__table_heap_start = .;
		LONG(0x001f)
		LONG(__heap1_start)
		LONG(__heap1_end)
		LONG(0x4009)
		LONG(__heap5_start)
		LONG(__heap5_end)
		LONG(0x0019)
		LONG(__heap2_start)
		LONG(__heap2_end)
		LONG(0x2002)
		LONG(__heap0_start)
		LONG(__heap0_end)
		
		__table_heap_end = .;
	} >FLASH


	/*
	. = ALIGN(4);
	_end = . ;
	__end = . ;
	PROVIDE(end = .);
*/


		/* Stabs debugging sections.  */
	.stab          0 : { *(.stab) }
	.stabstr       0 : { *(.stabstr) }
	.stab.excl     0 : { *(.stab.excl) }
	.stab.exclstr  0 : { *(.stab.exclstr) }
	.stab.index    0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment       0 : { *(.comment) }

	/* DWARF debug sections.
	 Symbols in the DWARF debugging sections are relative to the beginning
	 of the section so we begin them at 0.  */

	/* DWARF 1 */
	.debug          0 : { *(.debug) }
	.line           0 : { *(.line) }
	/* GNU DWARF 1 extensions */
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }
	/* DWARF 1.1 and DWARF 2 */
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	/* DWARF 2 */
	.debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	/* SGI/MIPS DWARF 2 extensions */
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames  0 : { *(.debug_varnames) }
	.debug_varnames  0 : { *(.debug_varnames) }

	.note.gnu.arm.ident 0 : { KEEP(*(.note.gnu.arm.ident)) }
	.ARM.attributes 0 : { KEEP(*(.ARM.attributes)) }
	/DISCARD/ : { *(.note.GNU-stack)  }

}