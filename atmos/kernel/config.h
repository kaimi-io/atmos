#pragma once

/** Defines which AVR timer to use for scheduler. */
#define ATMOS_TIMER_INDEX 1

/** Defines time in microseconds between two scheduler timer ticks. */
#define ATMOS_TICK_PERIOD_US 10000ul

/** If set to 1, then context switch code will be slower, but smaller. */
#define ATMOS_OPTIMIZE_CONTEXT_SWITCH_SIZE 1

/** If set to 1, then system process will be created. This process is run when
 *  all other processes are suspended. If there is a possibility, that all processes
 *  will be suspended in the system, system process has to be enabled. */
#define ATMOS_ENABLE_SYSTEM_PROCESS 1

/** If set to 1, process::yield method will be enabled. You may also need to enable system
 *  process (see ATMOS_ENABLE_SYSTEM_PROCESS). */
#define ATMOS_SUPPORT_YIELD 1

/** If set to 1, process::sleep and process::yield methods will be enabled.
 *  This will lead to enabling of tick counter and list of waiting processes. 
 *  You may also need to enable system process (see ATMOS_ENABLE_SYSTEM_PROCESS). */
#define ATMOS_SUPPORT_SLEEP 1

/** Tick counter type. Used to track sleeping processes wake time (see ATMOS_SUPPORT_SLEEP).
 *  Can be uint8_t, uint16_t, __uint24, uint32_t, uint64_t. Process will not be able to sleep for longer
 *  than (max value of ATMOS_TICK_COUNTER_TYPE) * ATMOS_TICK_PERIOD_US. */
#define ATMOS_TICK_COUNTER_TYPE uint8_t
