#pragma once

///Packed structs/classes (with 1-byte aligned members).
#define ATMOS_PACKED __attribute__((packed))

///Functions that do not return.
#define ATMOS_NORETURN __attribute__((noreturn))

///Functions without parameters, prologue/epilogue and return instruction.
#define ATMOS_NAKED __attribute__((naked))

///Often called functions.
#define ATMOS_HOT __attribute__((hot))

///Rarely called functions.
#define ATMOS_COLD __attribute__((cold))

///Used functions.
#define ATMOS_USED __attribute__((used))

///OS task functions - do not save call-saved registers, interrupt-safe.
#define ATMOS_OS_TASK __attribute__((OS_task))

///OS main functions - do not save call-saved registers, interrupt-unsafe.
#define ATMOS_OS_MAIN __attribute__((OS_main))

///Non-null function parameters.
#define ATMOS_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))

//Call and jump assembler device-specific instructions.
#ifdef __AVR_HAVE_JMP_CALL__
#	define ATMOS_CALL "call "
#	define ATMOS_JUMP "jmp "
#else //__AVR_HAVE_JMP_CALL__
#	define ATMOS_CALL "rcall "
#	define ATMOS_JUMP "rjmp "
#endif //__AVR_HAVE_JMP_CALL__
