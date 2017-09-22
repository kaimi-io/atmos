#pragma once

/** Defines which AVR timer to use for scheduler. */
#define ATMOS_TIMER_INDEX 1

/** Defines time in microseconds between two scheduler timer ticks. */
#define ATMOS_TICK_PERIOD_US 1000000

/** If set to 1, then context switch code will be slower, but smaller. */
#define ATMOS_OPTIMIZE_CONTEXT_SWITCH_SIZE 1
