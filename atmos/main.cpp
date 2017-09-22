#include "kernel/context_switch.h"

int main()
{
	__asm__ __volatile__ (
		"clr r30           \n\t"
		"clr r31           \n\t"
		"ldi r29, 1        \n\t"
		"1:                \n\t"
		"st Z+, r29        \n\t"
		"inc r29           \n\t"
		"cpi r29, 30       \n\t"
		"brne 1b           \n\t"
		"ldi r31, 123      \n\t"
		"out __SREG__, r31 \n\t"
		"ldi r29, 30       \n\t"
		"ldi r30, 31       \n\t"
		"ldi r31, 32       \n\t"
		::
	);
	
	save_r31_and_sreg_from_task();
	save_context_except_r31_and_sreg();
	
	__asm__ __volatile__ (
		"clr r30           \n\t"
		"clr r31           \n\t"
		"clr r29           \n\t"
		"1:                \n\t"
		"st Z+, r29        \n\t"
		"cpi r30, 29       \n\t"
		"brne 1b           \n\t"
		"clr r30           \n\t"
		"out __SREG__, r31 \n\t"
		::
	);
	
	restore_context_except_r31_and_sreg();
	restore_r31_and_sreg();
	
    while(true) {}
}