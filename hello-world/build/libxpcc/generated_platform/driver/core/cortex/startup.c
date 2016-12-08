// coding: utf-8
/* Copyright (c) 2013-2016, Roboterclub Aachen e.V.
 * All Rights Reserved.
 *
 * The file is part of the xpcc library and is released under the 3-clause BSD
 * license. See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------





#include <stdint.h>
#include <xpcc/architecture/utils.hpp>
#include "../../../device.hpp"
#include "xpcc_config.hpp"



// ----------------------------------------------------------------------------
/*
 * Provide weak aliases for each Exception handler to defaultHandler.
 * As they are weak aliases, any function with the same name will override
 * this definition.
 */
void Reset_Handler(void)				__attribute__((noreturn));
void NMI_Handler(void)					__attribute__ ((weak, alias("defaultHandler")));
void HardFault_Handler(void);

void WWDG_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void PVD_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void TAMP_STAMP_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void RTC_WKUP_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void FLASH_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void RCC_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void EXTI0_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void EXTI1_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void EXTI2_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void EXTI3_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void EXTI4_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void DMA1_Stream0_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA1_Stream1_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA1_Stream2_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA1_Stream3_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA1_Stream4_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA1_Stream5_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA1_Stream6_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void ADC_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void CAN1_TX_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void CAN1_RX0_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void CAN1_RX1_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void CAN1_SCE_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void EXTI9_5_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void TIM1_BRK_TIM9_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void TIM1_UP_TIM10_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void)__attribute__ ((weak, alias("defaultHandler")));
void TIM1_CC_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void TIM2_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void TIM3_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void TIM4_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void I2C1_EV_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void I2C1_ER_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void I2C2_EV_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void I2C2_ER_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void SPI1_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void SPI2_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void USART1_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void USART2_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void USART3_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void EXTI15_10_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void RTC_Alarm_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void OTG_FS_WKUP_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void TIM8_BRK_TIM12_IRQHandler(void)	__attribute__ ((weak, alias("defaultHandler")));
void TIM8_UP_TIM13_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void TIM8_TRG_COM_TIM14_IRQHandler(void)__attribute__ ((weak, alias("defaultHandler")));
void TIM8_CC_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void DMA1_Stream7_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void FSMC_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void SDIO_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void TIM5_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void SPI3_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void UART4_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void UART5_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void TIM6_DAC_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void TIM7_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void DMA2_Stream0_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA2_Stream1_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA2_Stream2_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA2_Stream3_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA2_Stream4_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void ETH_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void ETH_WKUP_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void CAN2_TX_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void CAN2_RX0_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void CAN2_RX1_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void CAN2_SCE_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void OTG_FS_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void DMA2_Stream5_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA2_Stream6_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void DMA2_Stream7_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void USART6_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void I2C3_EV_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void I2C3_ER_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void OTG_HS_EP1_OUT_IRQHandler(void)	__attribute__ ((weak, alias("defaultHandler")));
void OTG_HS_EP1_IN_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void OTG_HS_WKUP_IRQHandler(void)		__attribute__ ((weak, alias("defaultHandler")));
void OTG_HS_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void DCMI_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void HASH_RNG_IRQHandler(void)			__attribute__ ((weak, alias("defaultHandler")));
void FPU_IRQHandler(void)				__attribute__ ((weak, alias("defaultHandler")));
void SysTick_Handler(void)				__attribute__ ((weak, alias("defaultHandler")));
void MemManage_Handler(void)			__attribute__ ((weak, alias("defaultHandler")));
void BusFault_Handler(void)				__attribute__ ((weak, alias("defaultHandler")));
void UsageFault_Handler(void)			__attribute__ ((weak, alias("defaultHandler")));
void SVC_Handler(void)					__attribute__ ((weak, alias("defaultHandler")));
void DebugMon_Handler(void)				__attribute__ ((weak, alias("defaultHandler")));
void PendSV_Handler(void)				__attribute__ ((weak, alias("defaultHandler")));
// ----------------------------------------------------------------------------
// Interrupt vectors
typedef void (* const FunctionPointer)(void);

// defined in the linkerscript
extern uint32_t __main_stack_top[];
extern uint32_t __process_stack_top[];

// Define the vector table
__attribute__(( section(".reset") ))
FunctionPointer flashVectors[] =
{
	(FunctionPointer)__main_stack_top,		// -16: stack pointer
	Reset_Handler,							// -15: code entry point
	NMI_Handler,							// -14: Non Maskable Interrupt handler
	HardFault_Handler,						// -13: hard fault handler
	MemManage_Handler,						// -12
	BusFault_Handler,						// -11
	UsageFault_Handler,						// -10
	0,										//  -9
	0,										//  -8
	0,										//  -7
	0,										//  -6
	SVC_Handler,							//  -5
	DebugMon_Handler,						//  -4
	0,										//  -3
	PendSV_Handler,							//  -2
	SysTick_Handler,						//  -1
	WWDG_IRQHandler,						//   0
	PVD_IRQHandler,							//   1
	TAMP_STAMP_IRQHandler,					//   2
	RTC_WKUP_IRQHandler,					//   3
	FLASH_IRQHandler,						//   4
	RCC_IRQHandler,							//   5
	EXTI0_IRQHandler,						//   6
	EXTI1_IRQHandler,						//   7
	EXTI2_IRQHandler,						//   8
	EXTI3_IRQHandler,						//   9
	EXTI4_IRQHandler,						//  10
	DMA1_Stream0_IRQHandler,				//  11
	DMA1_Stream1_IRQHandler,				//  12
	DMA1_Stream2_IRQHandler,				//  13
	DMA1_Stream3_IRQHandler,				//  14
	DMA1_Stream4_IRQHandler,				//  15
	DMA1_Stream5_IRQHandler,				//  16
	DMA1_Stream6_IRQHandler,				//  17
	ADC_IRQHandler,							//  18
	CAN1_TX_IRQHandler,						//  19
	CAN1_RX0_IRQHandler,					//  20
	CAN1_RX1_IRQHandler,					//  21
	CAN1_SCE_IRQHandler,					//  22
	EXTI9_5_IRQHandler,						//  23
	TIM1_BRK_TIM9_IRQHandler,				//  24
	TIM1_UP_TIM10_IRQHandler,				//  25
	TIM1_TRG_COM_TIM11_IRQHandler,			//  26
	TIM1_CC_IRQHandler,						//  27
	TIM2_IRQHandler,						//  28
	TIM3_IRQHandler,						//  29
	TIM4_IRQHandler,						//  30
	I2C1_EV_IRQHandler,						//  31
	I2C1_ER_IRQHandler,						//  32
	I2C2_EV_IRQHandler,						//  33
	I2C2_ER_IRQHandler,						//  34
	SPI1_IRQHandler,						//  35
	SPI2_IRQHandler,						//  36
	USART1_IRQHandler,						//  37
	USART2_IRQHandler,						//  38
	USART3_IRQHandler,						//  39
	EXTI15_10_IRQHandler,					//  40
	RTC_Alarm_IRQHandler,					//  41
	OTG_FS_WKUP_IRQHandler,					//  42
	TIM8_BRK_TIM12_IRQHandler,				//  43
	TIM8_UP_TIM13_IRQHandler,				//  44
	TIM8_TRG_COM_TIM14_IRQHandler,			//  45
	TIM8_CC_IRQHandler,						//  46
	DMA1_Stream7_IRQHandler,				//  47
	FSMC_IRQHandler,						//  48
	SDIO_IRQHandler,						//  49
	TIM5_IRQHandler,						//  50
	SPI3_IRQHandler,						//  51
	UART4_IRQHandler,						//  52
	UART5_IRQHandler,						//  53
	TIM6_DAC_IRQHandler,					//  54
	TIM7_IRQHandler,						//  55
	DMA2_Stream0_IRQHandler,				//  56
	DMA2_Stream1_IRQHandler,				//  57
	DMA2_Stream2_IRQHandler,				//  58
	DMA2_Stream3_IRQHandler,				//  59
	DMA2_Stream4_IRQHandler,				//  60
	ETH_IRQHandler,							//  61
	ETH_WKUP_IRQHandler,					//  62
	CAN2_TX_IRQHandler,						//  63
	CAN2_RX0_IRQHandler,					//  64
	CAN2_RX1_IRQHandler,					//  65
	CAN2_SCE_IRQHandler,					//  66
	OTG_FS_IRQHandler,						//  67
	DMA2_Stream5_IRQHandler,				//  68
	DMA2_Stream6_IRQHandler,				//  69
	DMA2_Stream7_IRQHandler,				//  70
	USART6_IRQHandler,						//  71
	I2C3_EV_IRQHandler,						//  72
	I2C3_ER_IRQHandler,						//  73
	OTG_HS_EP1_OUT_IRQHandler,				//  74
	OTG_HS_EP1_IN_IRQHandler,				//  75
	OTG_HS_WKUP_IRQHandler,					//  76
	OTG_HS_IRQHandler,						//  77
	DCMI_IRQHandler,						//  78
	0,										//  79
	HASH_RNG_IRQHandler,					//  80
	FPU_IRQHandler,							//  81
};

// ----------------------------------------------------------------------------
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.
extern uint32_t __stack_start[];
extern uint32_t __stack_end[];

extern uint32_t __table_copy_intern_start[];
extern uint32_t __table_copy_intern_end[];

extern uint32_t __table_zero_intern_start[];
extern uint32_t __table_zero_intern_end[];

extern uint32_t __table_copy_extern_start[];
extern uint32_t __table_copy_extern_end[];

extern uint32_t __table_zero_extern_start[];
extern uint32_t __table_zero_extern_end[];

extern uint32_t __vector_table_rom_start[];
extern uint32_t __vector_table_ram_start[];

// Application's main function
int
main(void);

// calls CTORS of static objects
void
__libc_init_array(void);

extern void
exit(int) __attribute__ ((noreturn, weak));

// default implementation is empty and does nothing
void xpcc_hook_hardware_init(void) __attribute__(( weak ));
void xpcc_hook_hardware_init(void) {}

extern void __xpcc_initialize_memory(void);

extern void xpcc_gpio_enable(void);
static void
table_copy(uint32_t **table, uint32_t **end)
{
	while(table < end)
	{
		uint32_t *src  = table[0]; // load address
		uint32_t *dest = table[1]; // destination start
		while (dest < table[2])    // destination end
		{
			*(dest++) = *(src++);
		}
		table += 3;
	}
}

static void
table_zero(uint32_t **table, uint32_t **end)
{
	while(table < end)
	{
		uint32_t *dest = table[0]; // destination start
		while (dest < table[1])    // destination end
		{
			*(dest++) = 0;
		}
		table += 2;
	}
}

// ----------------------------------------------------------------------------
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied main() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
void
Reset_Handler(void)
{










// Only the more powerful F4 targets have CCM or Backup SRAM
#ifdef RCC_AHB1ENR_CCMDATARAMEN
	// Enable power to backup domain
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	// Enable write access to backup SRAM
	PWR->CR |= PWR_CR_DBP;
	// Enable Core Coupled Memory (CCM) and backup SRAM (BKPSRAM)
	RCC->AHB1ENR |= RCC_AHB1ENR_CCMDATARAMEN | RCC_AHB1ENR_BKPSRAMEN;
#endif


	// fill the stack with relative branches to __stack_start
	// where the undefined instruction is waiting to trigger the hard fault
	asm volatile (
		"ldr   r0, =__stack_start"      "\n\t"

		"ldr   r1, =0xE7FDDE00"         "\n\t" // b __stack_start, undef. instruction
		"stmia r0!, {r1}"               "\n\t"

		"ldr   r1, =__stack_end+4"      "\n\t"
		"ldr   r2, =0xE7FC"             "\n\t" // the 2's complement offset of -8/2 = -4
		"ldr   r3, =0xE401"             "\n\t" // largest negative relative branch value!

	"1:  strh  r2, [r0]"                "\n\t" // store the 16bit value into ram
		"add   r0, #2"                  "\n\t" // add sizeof(uint16_t) to the pointer

		"cmp   r2, r3"                  "\n\t" // compare value with 0xE401
		"beq   2f"                      "\n\t" // branch forward if equal
		"sub   r2, #1"                  "\n\t" // subtract only if not equal

	"2:  cmp   r0, r1"                  "\n\t" // compare pointer with end of stack address
		"bne   1b"                      "\n\t" // continue loop if not equal
	);

	// copy all internal memory declared in linkerscript table
	table_copy(	(uint32_t**)__table_copy_intern_start,
				(uint32_t**)__table_copy_intern_end);
	table_zero(	(uint32_t**)__table_zero_intern_start,
				(uint32_t**)__table_zero_intern_end);

	// Enable Tracing Debug Unit
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	// Enable CPU cycle counter
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	// Enable FPU in privileged and user mode
	SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));  // set CP10 and CP11 Full Access
	// Setup NVIC
	// Set vector table
	SCB->VTOR = (uint32_t)(__vector_table_rom_start);
	// Enables handlers with priority -1 or -2 to ignore data BusFaults caused by load and store instructions.
	// This applies to the hard fault, NMI, and FAULTMASK escalated handlers.
	// We use this to opportunistically restore LR, PC and xPSR in the hard fault handler.
	// Also enables trapping of divide by zero. Otherwise it would just be ignored.
	SCB->CCR |= SCB_CCR_BFHFNMIGN_Msk | SCB_CCR_DIV_0_TRP_Msk;

	// Lower priority level for all peripheral interrupts to lowest possible
	for (uint32_t i = 0; i < 81; i++) {
		NVIC->IP[i] = 0xff;
	}

	// Set the PRIGROUP[10:8] bits to
	// - 4 bits for pre-emption priority,
	// - 0 bits for subpriority
	NVIC_SetPriorityGrouping(3);

	// Enable fault handlers
	/*SCB->SHCSR |=
			SCB_SHCSR_BUSFAULTENA_Msk |
			SCB_SHCSR_USGFAULTENA_Msk |
			SCB_SHCSR_MEMFAULTENA_Msk;*/
	// Enable GPIO Clock
	xpcc_gpio_enable();
	// Use this hook to initialize external memories
	xpcc_hook_hardware_init();

	// copy all external memory declared in linkerscript table
	table_copy(	(uint32_t**)__table_copy_extern_start,
				(uint32_t**)__table_copy_extern_end);
	table_zero(	(uint32_t**)__table_zero_extern_start,
				(uint32_t**)__table_zero_extern_end);

	// initialize heap
	// needs to be done before calling the CTORS of static objects
	__xpcc_initialize_memory();

	// Call CTORS of static objects
	__libc_init_array();

	// Call the application's entry point
	main();

	exit(1);

	while (1)
	{
	}
}

// ----------------------------------------------------------------------------
/**
 * @brief	Default interrupt handler
 *
 * This functions gets called if an interrupt handler is not defined. It just
 * enters an infinite loop leaving the processor state intact for a debugger
 * to be examined.
*/
void
defaultHandler(void)
{
	while (1)
	{
	}
}