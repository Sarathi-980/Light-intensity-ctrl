/******************************************************************
 * This linker script for STM32F103C6T6 blue pill board.
 * The STM32F103C6T6 has 32 kb of flash starting at 0x80000000
 * In CMSIS repository file stm32f103x6.h has all board definitions.
 * ******************************************************************/

/* Since we are developing bare-metal code, this is the program entry point.
 * this setup for debugging purpose, as we directly enter the entry function 
 * via the vector table at 0x00000008. Upon chip reset, the CPU automatically
 * jump to the address held in the vector table. but this entry option is 
 * useful when we develop on linux, so linux will update PC(program counter)
 * using this entry function adress.
 */
ENTRY(program_entry_point)

MEMORY {
	FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 32k  /* origin and size of the flash */
	RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 10k
}

SECTIONS {
	.text :	 /* Program code and vector table */
	{
		KEEP(*(.isr_vector))
		*(.startup*)
		*(.text*)
		*(.rodata*)

	} > FLASH

	. = ALIGN(4);
	_etext = .;

	.data : AT(_etext)	/* Initialized data */
	{
		. = ALIGN(4);
		_sdata = .;	  /* Virtual Memory Address is section lives during runtime */
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	} > RAM

	. = ALIGN(4);
	_sidata = LOADADDR(.data); /* Load Memory Address is flash address */

	.bss : /* uninitialized data */
	{
		. = ALIGN(4);
		__bss_start__ = .;
		_sbss = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
		_ebss = .;
	} > RAM

	end = .;
	__end = .;
}

_eram = ORIGIN(RAM) + LENGTH(RAM); /* because RAM grows upward, so we should give end point */

