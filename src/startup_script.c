#include "system_exceptions.h"

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void program_entry_point(void);
extern int main();

extern uint32_t _eram;

__attribute__((section(".isr_vector")))
uint32_t const vector_table[] = {
	(uint32_t)&_eram,					// Main stack pointer(MSP)
	(uint32_t)program_entry_point,		// Reset
	(uint32_t)NMI_handler,							// Non-Maskable Interrupt handler, useful for clock failure, any hardware failure
	(uint32_t)HardFault_handler,							// Hard-Fault triggered by Invalid memory access, Unaligned access
	(uint32_t)MemoryManage_handler,						// Preventing unauthorized access to MPU and memory violations
	(uint32_t)BusFault_handler,							// Memory access error exception
	(uint32_t)UsageFault_handler,							// Exception triggered when invalid use cases like Invalid instruction arch(thumb/arm)
	0,											// 7 - 10 reserved
	0,
	0,
	0,
	(uint32_t)SVC_handler,								// Supervisor call exception
	(uint32_t)DebugMonitor_handler,						// Debug monitor
	0,											// 13 reserved
	(uint32_t)PendSVC_handler,							// Pendable service call
	(uint32_t)system_tick_handler							// system_tick_timer
};

void program_entry_point(void)
{
	uint32_t *src = &_sidata;
	uint32_t *dest = &_sdata;
	uint32_t *end = &_edata;

	// Copy of initialized data from flash to RAM
	while (dest < end) {
		*dest++ = *src++;
	}

	dest = &_sbss;
	// Setting zero to uninitialized data to RAM
	while (dest < &_ebss) {
		*dest++ = 0;
	}

	main();

	while(1);
}


