#pragma once

#include <stdint.h>

#include "config.h"
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

namespace detail
{
template<typename T>
struct tick_counter_checker
{
	static constexpr bool is_valid = false;
};

struct valid_type
{
	static constexpr bool is_valid = true;
};

template<>
struct tick_counter_checker<uint8_t> : valid_type {};
template<>
struct tick_counter_checker<uint16_t> : valid_type {};
template<>
struct tick_counter_checker<__uint24> : valid_type {};
template<>
struct tick_counter_checker<uint32_t> : valid_type {};
template<>
struct tick_counter_checker<uint64_t> : valid_type {};
} //namespace detail

static_assert(detail::tick_counter_checker<ATMOS_TICK_COUNTER_TYPE>::is_valid,
	"ATMOS_TICK_COUNTER_TYPE does not name a valid tick counter type");
