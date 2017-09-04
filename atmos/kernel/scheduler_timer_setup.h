#pragma once

#include <avr/io.h>

#include <stdint.h>

#include "timer_params.h"

namespace atmos
{

namespace detail
{
///Helper class for timer setup, that is needed to save several bytes of program memory,
///when prescaler control register and mode control register have same addresses.
template<uint16_t PrescalerRegister, uint16_t ModeRegister>
struct timer_setup_helper final
{
	///Setup timer according to ATMOS_TIMER_INDEX and ATMOS_TICK_PERIOD_US macro values.
	static inline void setup()
	{
		ATMOS_TIMER_PRESCALER_CONTROL = ATMOS_TIMER_PRESCALER_CONTROL_VALUE;
		ATMOS_TIMER_MODE_CONTROL = _BV(ATMOS_TIMER_CTC_MODE_BIT);
	}
};

///Specialization of timer_setup_helper struct.
template<uint16_t PrescalerRegister>
struct timer_setup_helper<PrescalerRegister, PrescalerRegister> final
{
	static inline void setup()
	{
		ATMOS_TIMER_PRESCALER_CONTROL = ATMOS_TIMER_PRESCALER_CONTROL_VALUE | _BV(ATMOS_TIMER_CTC_MODE_BIT);
	}
};
} //namespace detail

///Initializes scheduler timer according to ATMOS_TIMER_INDEX and ATMOS_TICK_PERIOD_US macro values.
///These parameters are set in config.h.
inline void initialize_scheduler_timer()
{
	ATMOS_TIMER_COMPARE_REGISTER = ATMOS_TIMER_TOP_VALUE;
	
#ifdef ATMOS_TIMER_MODE_CONTROL
	detail::timer_setup_helper<(reinterpret_cast<uint16_t>(&ATMOS_TIMER_PRESCALER_CONTROL)),
		(reinterpret_cast<uint16_t>(&ATMOS_TIMER_MODE_CONTROL))>::setup();
#else //ATMOS_TIMER_MODE_CONTROL
	ATMOS_TIMER_PRESCALER_CONTROL = ATMOS_TIMER_PRESCALER_CONTROL_VALUE;
#endif //ATMOS_TIMER_MODE_CONTROL
	
	ATMOS_TIMER_INTERRUPT_CONTROL = _BV(ATMOS_TIMER_COMPARE_INTERRUPT_BIT);
}

} //namespace atmos
