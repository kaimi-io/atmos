#include <avr/io.h>
#include <avr/interrupt.h>

#include "kernel/scheduler_timer_setup.h"

int main()
{
	DDRC |= _BV(PC0);
	
	atmos::initialize_scheduler_timer();
	
	sei();
	
    while(true) 
    {
    }
}

ISR(ATMOS_TIMER_INTERRUPT_NAME)
{
	PORTC ^= _BV(PC0);
}
