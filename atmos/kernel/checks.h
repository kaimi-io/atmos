#pragma once

#include "timer_config.h"

#ifdef __AVR_XMEGA__
static_assert(false, "AVR XMEGA architecture is not supported");
#endif //__AVR_XMEGA__

#if !defined(ATMOS_TIMER0_BITS) && !defined(ATMOS_TIMER1_BITS) \
	&& !defined(ATMOS_TIMER1_BITS) && !defined(ATMOS_TIMER2_BITS) \
	&& !defined(ATMOS_TIMER3_BITS) && !defined(ATMOS_TIMER4_BITS) \
	&& !defined(ATMOS_TIMER5_BITS)
static_assert(false, "No timers are defined for selected device. Add your device timer configuration to timer_config.h");
#endif

#ifndef F_CPU
static_assert(false, "You need to have F_CPU value defined");
#endif //F_CPU

#ifdef __NO_INTERRUPTS__
static_assert(false, "Interrupts must be enabled for ATMOS to work");
#endif //__NO_INTERRUPTS__
