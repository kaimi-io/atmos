#pragma once

#include "config.h"

//I bit number in SREG register.
#define ATMOS_AVR_INTERRUPT_BIT 7
//__AVR_ARCH__ macro value for avrtiny architecture
#define ATMOS_AVRTINY_ARCH_ID 100

/** Save R31 and SREG on stack. Can be called from scheduler timer interrupt only. */
#define save_r31_and_sreg_from_scheduler() __asm__ __volatile__ ( \
	/* Save R31 on stack to make it available for later use. */ \
	"push r31           \n\t" \
	/* Save SREG on stack and set I flag value to 1. This macro called from scheduler, so interrupts */ \
	/* must be enabled after we return from the scheduler interrupt, and we set #7 bit (I bit) to 1. */ \
	"in r31, __SREG__   \n\t" \
	"ori r31, (1 << %0) \n\t" \
	"push r31           \n\t" \
	:: "I" (ATMOS_AVR_INTERRUPT_BIT) \
)

/** Save R31 and SREG on stack. Can be called from OS process only. */
#define save_r31_and_sreg_from_task() __asm__ __volatile__ ( \
	/* Save R31 on stack to make it available for later use. */ \
	"push r31         \n\t" \
	/* Save SREG on stack and disable interrupts. This is called from task, so interrupts */ \
	/* must be disabled before the context switch. */ \
	"in r31, __SREG__ \n\t" \
	"cli              \n\t" \
	"push r31         \n\t" \
	:: \
)

/** Save process context on stack (except R31 and SREG). */
#if __AVR_ARCH__ == ATMOS_AVRTINY_ARCH_ID //avrtiny, absent R0-R15 registers.
#	define save_context_except_r31_and_sreg() __asm__ __volatile__ ( \
		"push r16        \n\t" \
		"push r17        \n\t" \
		/* Clear R17 after saving to satisfy GCC calling convention. R17 is always zero. */ \
		"clr r17         \n\t" \
		"push r18        \n\t" \
		"push r19        \n\t" \
		"push r20        \n\t" \
		"push r21        \n\t" \
		"push r22        \n\t" \
		"push r23        \n\t" \
		"push r24        \n\t" \
		"push r25        \n\t" \
		"push r26        \n\t" \
		"push r27        \n\t" \
		"push r28        \n\t" \
		"push r29        \n\t" \
		"push r30        \n\t" \
		:: \
	)
#else //not avrtiny
#	if ATMOS_OPTIMIZE_CONTEXT_SWITCH_SIZE
#		define save_context_except_r31_and_sreg() __asm__ __volatile__ ( \
			"push r30       \n\t" \
			"push r29       \n\t" \
			"clr r30        \n\t" \
			"clr r31        \n\t" \
			"1:             \n\t" \
			"ld r29, Z+     \n\t" \
			"push r29       \n\t" \
			"cpi r30, 29    \n\t" \
			"brne 1b        \n\t" \
			"clr r1         \n\t" \
			:: \
		);
#	else //ATMOS_OPTIMIZE_CONTEXT_SWITCH_SIZE
#		define save_context_except_r31_and_sreg() __asm__ __volatile__ ( \
			"push r0         \n\t" \
			"push r1         \n\t" \
			/* Clear R1 after saving to satisfy GCC calling convention. R1 is always zero. */ \
			"clr r1          \n\t" \
			"push r2         \n\t" \
			"push r3         \n\t" \
			"push r4         \n\t" \
			"push r5         \n\t" \
			"push r6         \n\t" \
			"push r7         \n\t" \
			"push r8         \n\t" \
			"push r9         \n\t" \
			"push r10        \n\t" \
			"push r11        \n\t" \
			"push r12        \n\t" \
			"push r13        \n\t" \
			"push r14        \n\t" \
			"push r15        \n\t" \
			"push r16        \n\t" \
			"push r17        \n\t" \
			"push r18        \n\t" \
			"push r19        \n\t" \
			"push r20        \n\t" \
			"push r21        \n\t" \
			"push r22        \n\t" \
			"push r23        \n\t" \
			"push r24        \n\t" \
			"push r25        \n\t" \
			"push r26        \n\t" \
			"push r27        \n\t" \
			"push r28        \n\t" \
			"push r29        \n\t" \
			"push r30        \n\t" \
			:: \
		)
#	endif //ATMOS_OPTIMIZE_CONTEXT_SWITCH_SIZE
#endif //avrtiny

/** Restore saved context (except R31 and SREG). */
#if __AVR_ARCH__ == ATMOS_AVRTINY_ARCH_ID //avrtiny, absent R0-R15 registers.
#	define restore_context_except_r31_and_sreg() __asm__ __volatile__ ( \
		"pop r30              \n\t" \
		"pop r29              \n\t" \
		"pop r28              \n\t" \
		"pop r27              \n\t" \
		"pop r26              \n\t" \
		"pop r25              \n\t" \
		"pop r24              \n\t" \
		"pop r23              \n\t" \
		"pop r22              \n\t" \
		"pop r21              \n\t" \
		"pop r20              \n\t" \
		"pop r19              \n\t" \
		"pop r18              \n\t" \
		"pop r17              \n\t" \
		"pop r16              \n\t" \
		:: \
	)
#else //not avrtiny
#	if ATMOS_OPTIMIZE_CONTEXT_SWITCH_SIZE
#		define restore_context_except_r31_and_sreg() __asm__ __volatile__ ( \
			"ldi r30, 29    \n\t" \
			"clr r31        \n\t" \
			"1:             \n\t" \
			"pop r29        \n\t" \
			"st -Z, r29     \n\t" \
			"tst r30        \n\t" \
			"brne 1b        \n\t" \
			"pop r29        \n\t" \
			"pop r30        \n\t" \
			:: \
		);
#	else //ATMOS_OPTIMIZE_CONTEXT_SWITCH_SIZE
#		define restore_context_except_r31_and_sreg() __asm__ __volatile__ ( \
			"pop r30              \n\t" \
			"pop r29              \n\t" \
			"pop r28              \n\t" \
			"pop r27              \n\t" \
			"pop r26              \n\t" \
			"pop r25              \n\t" \
			"pop r24              \n\t" \
			"pop r23              \n\t" \
			"pop r22              \n\t" \
			"pop r21              \n\t" \
			"pop r20              \n\t" \
			"pop r19              \n\t" \
			"pop r18              \n\t" \
			"pop r17              \n\t" \
			"pop r16              \n\t" \
			"pop r15              \n\t" \
			"pop r14              \n\t" \
			"pop r13              \n\t" \
			"pop r12              \n\t" \
			"pop r11              \n\t" \
			"pop r10              \n\t" \
			"pop r9               \n\t" \
			"pop r8               \n\t" \
			"pop r7               \n\t" \
			"pop r6               \n\t" \
			"pop r5               \n\t" \
			"pop r4               \n\t" \
			"pop r3               \n\t" \
			"pop r2               \n\t" \
			"pop r1               \n\t" \
			"pop r0               \n\t" \
			:: \
		)
#	endif //ATMOS_OPTIMIZE_CONTEXT_SWITCH_SIZE
#endif //avrtiny

/** Restore R31 and SREG and jump to the address saved on stack. */
#define restore_r31_and_sreg_and_switch_context()  __asm__ __volatile__ ( \
	/* Restore SREG and R31. */ \
	"pop r31              \n\t" \
	"sbrc r31, %0         \n\t" \
	"rjmp 1f              \n\t" \
	/* If bit I is cleared in saved SREG value, then just restore SREG and R31 and perform RET to the process. */ \
	"out __SREG__, r31    \n\t" \
	"pop r31              \n\t" \
	"ret                  \n\t" \
	/* Otherwise, clear bit I, restore SREG and R31 and perform RETI to return to the process and */ \
	/* enable interrupts at the same time. */ \
	"1:                   \n\t" \
	"andi r31, ~(1 << %0) \n\t" \
	"out __SREG__, r31    \n\t" \
	"pop r31              \n\t" \
	"reti                 \n\t" \
	:: "I" (ATMOS_AVR_INTERRUPT_BIT) \
)

/** Restore R31 and SREG. */
#define restore_r31_and_sreg()  __asm__ __volatile__ ( \
	/* Restore SREG and R31. */ \
	"pop r31              \n\t" \
	"out __SREG__, r31    \n\t" \
	"pop r31              \n\t" \
	:: \
)
