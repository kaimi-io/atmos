#pragma once

#include <avr/io.h>

#include <stdint.h>

#include "timer_selector.h"
#include "utils.h"

/** \file The logic here calculates which timer configuration to use.
 *  After this file is included, you will have ATMOS_TIMER_PRESCALER_CONTROL_VALUE and ATMOS_TIMER_TOP_VALUE
 *  macros defined.
 *  ATMOS_TIMER_PRESCALER_CONTROL_VALUE - bit mask that should be used to configure timer prescaler;
 *  ATMOS_TIMER_TOP_VALUE - value that should be written to timer CTC compare register. */

#if ATMOS_TIMER_BITS == 8
#	define ATMOS_MAX_TIMER_VALUE UINT8_MAX
#elif ATMOS_TIMER_BITS == 16
#	define ATMOS_MAX_TIMER_VALUE UINT16_MAX
#else //ATMOS_TIMER_BITS
static_cast("Unsupported ATMOS_TIMER_BITS value");
#endif //ATMOS_TIMER_BITS

#pragma message ("Selected timer #" STRINGIFY(ATMOS_TIMER_INDEX) " (" STRINGIFY(ATMOS_TIMER_BITS) "-bit)")
#pragma message ("Selected timer tick period " STRINGIFY(ATMOS_TICK_PERIOD_US) " us")

//Try to get required timer parameters for all possible timer prescaler values.
#define ATMOS_TIMER_PRESCALER_VALUE 1
#include "timer_params_calc.h"
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 2
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 4
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 8
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 16
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 32
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 64
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 128
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 256
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 512
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 1024
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 2048
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 4196
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 8192
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	define ATMOS_TIMER_PRESCALER_VALUE 16384
#	include "timer_params_calc.h"
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE

#ifndef ATMOS_TIMER_PRESCALER_CONTROL_VALUE
static_assert(false, "Unable to deduce timer prescaler and limiting values");
#else //ATMOS_TIMER_PRESCALER_CONTROL_VALUE
#	pragma message ("Selected timer prescaler " STRINGIFY(ATMOS_TIMER_PRESCALER_VALUE) \
		", top value " STRINGIFY(ATMOS_TIMER_TOP_VALUE) \
		", prescaler bits: " STRINGIFY(ATMOS_TIMER_PRESCALER_CONTROL_VALUE))
#endif //ATMOS_TIMER_PRESCALER_CONTROL_VALUE

#undef ATMOS_MAX_TIMER_VALUE
