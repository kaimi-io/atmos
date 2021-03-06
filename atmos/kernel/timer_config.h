#pragma once

#include <avr/io.h>

/** \file Timer configuration macros definitions for supported MCUs.
 *  "x" below is a timer number.
 *  ATMOS_TIMERx_BITS - number of bits of timer counter register (usually 8 or 16).
 *  ATMOS_TIMERx_PRESCALER_CONTROL - register that contains timer prescaler control bits.
 *  ATMOS_TIMERx_MODE_CONTROL - register that contains mode bit to switch timer to Clear Timer on Compare match (CTC) mode.
 *                              This definition can be absent, if timer is by default in CTC mode.
 *  ATMOS_TIMERx_CTC_MODE_BIT - bit that enables timer CTC mode. Can be absent (see ATMOS_TIMERx_MODE_CONTROL).
 *  ATMOS_TIMERx_INTERRUPT_CONTROL - register that controls timer interrupts.
 *  ATMOS_TIMERx_COMPARE_INTERRUPT_BIT - bit that enables timer CTC interrupt (or overflow interrupt, if timer is always in CTC mode).
 *  ATMOS_TIMERx_COMPARE_REGISTER - register that is used for comparing timer value during CTC operation.
 *  ATMOS_TIMERx_INTERRUPT_NAME - timer CTC interrupt name (or overflow interrupt name, if timer is always in CTC mode).
 *  ATMOS_TIMERx_COUNTER - timer counter register.
 *  Optional defines:
 *  ATMOS_TIMERx_PRESCALER_HAS_32_128 - indicates that timer prescaler can be set up to divide controller frequency by 32 or 128.
 *                                      If this define is absent, it is assumed that prescaler can be set up to divide by 1, 8, 64, 256, 1024 only.
 *  ATMOS_TIMERx_PRESCALER_HAS_16384 - indicates that timer prescaler can be set up to divide frequency by 1/2/4/8/16/32/64/128/256/512/1024/2048/4196/8192/16384
 *                                     and has four configuration bits.
 *  ATMOS_TIMERx_HAS_16BIT_MODE - indicates that timer is 8-bit, but supports 16-bit mode.
 *  ATMOS_TIMERx_16BIT_MODE_CONTROL - control register that is used to enable 16-bit mode for timer.
 *  ATMOS_TIMERx_16BIT_MODE_BIT - bit that is used to enable 16-bit mode for timer.
 *  ATMOS_TIMERx_16BIT_MODE_HIGH_BYTE_COMPARE_REGISTER - high-byte part of timer CTC compare register used in 16-bit mode.
 *  ATMOS_TIMERx_16BIT_MODE_HIGH_BYTE_COUNTER_REGISTER - high-byte part of timer counter register used in 16-bit mode. */

#if defined(__AVR_ATmega8A__) || defined(__AVR_ATmega8__) \
	|| defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) \
	|| defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__)
	
#	if !defined(__AVR_ATmega8A__) && !defined(__AVR_ATmega8__)

#		define ATMOS_TIMER0_BITS 8
#		define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0
#		define ATMOS_TIMER0_MODE_CONTROL TCCR0
#		define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#		define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK
#		define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0
#		define ATMOS_TIMER0_COMPARE_REGISTER OCR0
#		define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMP_vect
#		define ATMOS_TIMER0_COUNTER TCNT0

#	endif

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#	if !defined(__AVR_ATmega8515__)

#		define ATMOS_TIMER2_BITS 8
#		define ATMOS_TIMER2_PRESCALER_CONTROL TCCR2
#		define ATMOS_TIMER2_PRESCALER_HAS_32_128
#		define ATMOS_TIMER2_MODE_CONTROL TCCR2
#		define ATMOS_TIMER2_CTC_MODE_BIT WGM21
#		define ATMOS_TIMER2_INTERRUPT_CONTROL TIMSK
#		define ATMOS_TIMER2_COMPARE_INTERRUPT_BIT OCIE2
#		define ATMOS_TIMER2_COMPARE_REGISTER OCR2
#		define ATMOS_TIMER2_INTERRUPT_NAME TIMER2_COMP_vect
#		define ATMOS_TIMER2_COUNTER TCNT2

#	endif
	
#elif defined(__AVR_ATmega64__) || defined(__AVR_ATmega64A__) \
	|| defined(__AVR_ATmega128__) || defined(__AVR_ATmega128A__)
	
#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0
#	define ATMOS_TIMER0_PRESCALER_HAS_32_128
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0
#	define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMP_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#	define ATMOS_TIMER2_BITS 8
#	define ATMOS_TIMER2_PRESCALER_CONTROL TCCR2
#	define ATMOS_TIMER2_MODE_CONTROL TCCR2
#	define ATMOS_TIMER2_CTC_MODE_BIT WGM21
#	define ATMOS_TIMER2_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER2_COMPARE_INTERRUPT_BIT OCIE2
#	define ATMOS_TIMER2_COMPARE_REGISTER OCR2
#	define ATMOS_TIMER2_INTERRUPT_NAME TIMER2_COMP_vect
#	define ATMOS_TIMER2_COUNTER TCNT2

#	define ATMOS_TIMER3_BITS 16
#	define ATMOS_TIMER3_PRESCALER_CONTROL TCCR3B
#	define ATMOS_TIMER3_MODE_CONTROL TCCR3B
#	define ATMOS_TIMER3_CTC_MODE_BIT WGM32
#	define ATMOS_TIMER3_INTERRUPT_CONTROL ETIMSK
#	define ATMOS_TIMER3_COMPARE_INTERRUPT_BIT OCIE3A
#	define ATMOS_TIMER3_COMPARE_REGISTER OCR3A
#	define ATMOS_TIMER3_INTERRUPT_NAME TIMER3_COMPA_vect
#	define ATMOS_TIMER3_COUNTER TCNT3

#elif defined(__AVR_ATmega162__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0
#	define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMP_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#	define ATMOS_TIMER2_BITS 8
#	define ATMOS_TIMER2_PRESCALER_CONTROL TCCR2
#	define ATMOS_TIMER2_MODE_CONTROL TCCR2
#	define ATMOS_TIMER2_CTC_MODE_BIT WGM21
#	define ATMOS_TIMER2_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER2_COMPARE_INTERRUPT_BIT OCIE2
#	define ATMOS_TIMER2_COMPARE_REGISTER OCR2
#	define ATMOS_TIMER2_INTERRUPT_NAME TIMER2_COMP_vect
#	define ATMOS_TIMER2_COUNTER TCNT2

#	define ATMOS_TIMER3_BITS 16
#	define ATMOS_TIMER3_PRESCALER_CONTROL TCCR3B
#	define ATMOS_TIMER3_PRESCALER_HAS_32_128
#	define ATMOS_TIMER3_MODE_CONTROL TCCR3B
#	define ATMOS_TIMER3_CTC_MODE_BIT WGM32
#	define ATMOS_TIMER3_INTERRUPT_CONTROL ETIMSK
#	define ATMOS_TIMER3_COMPARE_INTERRUPT_BIT OCIE3A
#	define ATMOS_TIMER3_COMPARE_REGISTER OCR3A
#	define ATMOS_TIMER3_INTERRUPT_NAME TIMER3_COMPA_vect
#	define ATMOS_TIMER3_COUNTER TCNT3

#elif defined(__AVR_ATtiny20__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0B
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIM0_COMPA_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIM1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#elif defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0B
#	define ATMOS_TIMER0_PRESCALER_HAS_32_128
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK0
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMPA_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK1
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) \
	|| defined(__AVR_ATtiny24A__) || defined(__AVR_ATtiny44A__) || defined(__AVR_ATtiny84A__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0B
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK0
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIM0_COMPA_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK1
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIM1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#elif defined(__AVR_ATtiny48__) || defined(__AVR_ATtiny88__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0A
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT CTC0
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK0
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMPA_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK1
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#elif defined(__AVR_ATtiny441__) || defined(__AVR_ATtiny841__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0A
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK0
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMPA_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK1
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#	define ATMOS_TIMER2_BITS 16
#	define ATMOS_TIMER2_PRESCALER_CONTROL TCCR2B
#	define ATMOS_TIMER2_MODE_CONTROL TCCR2B
#	define ATMOS_TIMER2_CTC_MODE_BIT WGM22
#	define ATMOS_TIMER2_INTERRUPT_CONTROL TIMSK2
#	define ATMOS_TIMER2_COMPARE_INTERRUPT_BIT OCIE2A
#	define ATMOS_TIMER2_COMPARE_REGISTER OCR2A
#	define ATMOS_TIMER2_INTERRUPT_NAME TIMER2_COMPA_vect
#	define ATMOS_TIMER2_COUNTER TCNT2

#elif defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny2313A__) || defined(__AVR_ATtiny4313__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0B
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMPA_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#elif defined(__AVR_ATtiny261__) || defined(__AVR_ATtiny461__) || defined(__AVR_ATtiny861__) \
	|| defined(__AVR_ATtiny261A__) || defined(__AVR_ATtiny461A__) || defined(__AVR_ATtiny861A__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_HAS_16BIT_MODE
#	define ATMOS_TIMER0_16BIT_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_16BIT_MODE_BIT TCW0
#	define ATMOS_TIMER0_16BIT_MODE_HIGH_BYTE_COMPARE_REGISTER OCR0B
#	define ATMOS_TIMER0_16BIT_MODE_HIGH_BYTE_COUNTER_REGISTER TCNT0H
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0B
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM00
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMPA_vect
#	define ATMOS_TIMER0_COUNTER TCNT0L

#	define ATMOS_TIMER1_BITS 8
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_PRESCALER_HAS_16384
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT TOIE1
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1C
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_OVF_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#elif defined(__AVR_ATtiny40__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0B
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIM0_COMPA_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 8
#	define ATMOS_TIMER1_HAS_16BIT_MODE
#	define ATMOS_TIMER1_16BIT_MODE_CONTROL TCCR1A
#	define ATMOS_TIMER1_16BIT_MODE_BIT TCW1
#	define ATMOS_TIMER1_16BIT_MODE_HIGH_BYTE_COMPARE_REGISTER OCR1B
#	define ATMOS_TIMER1_16BIT_MODE_HIGH_BYTE_COUNTER_REGISTER TCNT1H
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIM1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1L

#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0B
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMPA_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 8
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1
#	define ATMOS_TIMER1_PRESCALER_HAS_16384
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1
#	define ATMOS_TIMER1_CTC_MODE_BIT CTC1
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT TOIE1
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1C
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_OVF_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#elif defined(__AVR_ATtiny26__)

#	define ATMOS_TIMER1_BITS 8
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_PRESCALER_HAS_16384
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT CTC1
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT TOIE1
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1C
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_OVF1_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#elif defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164PA__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324PA__) \
	 || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644PA__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) \
	 || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__) \
	 || defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) \
	 || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega168P__) \
	 || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88PA__) \
	 || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) \
	 || defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) \
	 || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__) \
	 || defined(__AVR_ATmega8U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega32U2__) \
	 || defined(__AVR_ATmega64M1__) || defined(__AVR_ATmega16M1__) || defined(__AVR_ATmega32M1__) \
	 || defined(__AVR_ATmega64C1__) || defined(__AVR_ATmega32C1__) \
	 || defined(__AVR_ATtiny828__) \
	 || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0B
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK0
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMPA_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK1
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#	if !defined(__AVR_ATmega8U2__) && !defined(__AVR_ATmega16U2__) && !defined(__AVR_ATmega32U2__) \
		&& !defined(__AVR_ATmega64M1__) && !defined(__AVR_ATmega16M1__) && !defined(__AVR_ATmega32M1__) \
		&& !defined(__AVR_ATmega64C1__) && !defined(__AVR_ATmega32C1__) && !defined(__AVR_ATtiny828__) \
		&& !defined(__AVR_ATmega32U4__) && !defined(__AVR_ATmega16U4__)

#		define ATMOS_TIMER2_BITS 8
#		define ATMOS_TIMER2_PRESCALER_CONTROL TCCR2B
#		define ATMOS_TIMER2_PRESCALER_HAS_32_128
#		define ATMOS_TIMER2_MODE_CONTROL TCCR2A
#		define ATMOS_TIMER2_CTC_MODE_BIT WGM21
#		define ATMOS_TIMER2_INTERRUPT_CONTROL TIMSK2
#		define ATMOS_TIMER2_COMPARE_INTERRUPT_BIT OCIE2A
#		define ATMOS_TIMER2_COMPARE_REGISTER OCR2A
#		define ATMOS_TIMER2_INTERRUPT_NAME TIMER2_COMPA_vect
#		define ATMOS_TIMER2_COUNTER TCNT2

#	endif

#	if defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) \
		|| defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) \
		|| defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__) \
		|| defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)
		
#		define ATMOS_TIMER3_BITS 16
#		define ATMOS_TIMER3_PRESCALER_CONTROL TCCR3B
#		define ATMOS_TIMER3_MODE_CONTROL TCCR3B
#		define ATMOS_TIMER3_CTC_MODE_BIT WGM32
#		define ATMOS_TIMER3_INTERRUPT_CONTROL TIMSK3
#		define ATMOS_TIMER3_COMPARE_INTERRUPT_BIT OCIE3A
#		define ATMOS_TIMER3_COMPARE_REGISTER OCR3A
#		define ATMOS_TIMER3_INTERRUPT_NAME TIMER3_COMPA_vect
#		define ATMOS_TIMER3_COUNTER TCNT3

#	endif

#	if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)

#		define ATMOS_TIMER4_BITS 8
#		define ATMOS_TIMER4_PRESCALER_CONTROL TCCR4B
#		define ATMOS_TIMER4_PRESCALER_HAS_16384
#		define ATMOS_TIMER4_INTERRUPT_CONTROL TIMSK4
#		define ATMOS_TIMER4_COMPARE_INTERRUPT_BIT TOIE4
#		define ATMOS_TIMER4_COMPARE_REGISTER OCR4C
#		define ATMOS_TIMER4_INTERRUPT_NAME TIMER4_OVF_vect
#		define ATMOS_TIMER4_COUNTER TCNT4

#	endif

#	if defined(__AVR_ATmega640__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1281__) \
		|| defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__)
		
#		define ATMOS_TIMER4_BITS 16
#		define ATMOS_TIMER4_PRESCALER_CONTROL TCCR4B
#		define ATMOS_TIMER4_MODE_CONTROL TCCR4B
#		define ATMOS_TIMER4_CTC_MODE_BIT WGM42
#		define ATMOS_TIMER4_INTERRUPT_CONTROL TIMSK4
#		define ATMOS_TIMER4_COMPARE_INTERRUPT_BIT OCIE4A
#		define ATMOS_TIMER4_COMPARE_REGISTER OCR4A
#		define ATMOS_TIMER4_INTERRUPT_NAME TIMER4_COMPA_vect
#		define ATMOS_TIMER4_COUNTER TCNT4

#		define ATMOS_TIMER5_BITS 16
#		define ATMOS_TIMER5_PRESCALER_CONTROL TCCR5B
#		define ATMOS_TIMER5_MODE_CONTROL TCCR5B
#		define ATMOS_TIMER5_CTC_MODE_BIT WGM52
#		define ATMOS_TIMER5_INTERRUPT_CONTROL TIMSK5
#		define ATMOS_TIMER5_COMPARE_INTERRUPT_BIT OCIE5A
#		define ATMOS_TIMER5_COMPARE_REGISTER OCR5A
#		define ATMOS_TIMER5_INTERRUPT_NAME TIMER5_COMPA_vect
#		define ATMOS_TIMER5_COUNTER TCNT5

#	endif

#elif defined(__AVR_ATmega165P__) || defined(__AVR_ATmega165A__) || defined(__AVR_ATmega165PA__) \
	|| defined(__AVR_ATmega325P__) || defined(__AVR_ATmega325A__) || defined(__AVR_ATmega325PA__) \
	|| defined(__AVR_ATmega3250P__) || defined(__AVR_ATmega3250A__) || defined(__AVR_ATmega3250PA__) \
	|| defined(__AVR_ATmega645P__) || defined(__AVR_ATmega645A__) \
	|| defined(__AVR_ATmega6450P__) || defined(__AVR_ATmega6450A__) \
	|| defined(__AVR_ATmega325__) || defined(__AVR_ATmega3250__) \
	|| defined(__AVR_ATmega645__) || defined(__AVR_ATmega6450__) \
	|| defined(__AVR_ATmega169P__) || defined(__AVR_ATmega169A__) || defined(__AVR_ATmega169PA__) \
	|| defined(__AVR_ATmega329__) || defined(__AVR_ATmega329P__) || defined(__AVR_ATmega329A__) || defined(__AVR_ATmega329PA__) \
	|| defined(__AVR_ATmega3290__) || defined(__AVR_ATmega3290P__) || defined(__AVR_ATmega3290A__) || defined(__AVR_ATmega3290PA__) \
	|| defined(__AVR_ATmega649__) || defined(__AVR_ATmega649A__) || defined(__AVR_ATmega649P__) \
	|| defined(__AVR_ATmega6490__) || defined(__AVR_ATmega6490A__) || defined(__AVR_ATmega6490P__)

#	define ATMOS_TIMER0_BITS 8
#	define ATMOS_TIMER0_PRESCALER_CONTROL TCCR0A
#	define ATMOS_TIMER0_MODE_CONTROL TCCR0A
#	define ATMOS_TIMER0_CTC_MODE_BIT WGM01
#	define ATMOS_TIMER0_INTERRUPT_CONTROL TIMSK0
#	define ATMOS_TIMER0_COMPARE_INTERRUPT_BIT OCIE0A
#	define ATMOS_TIMER0_COMPARE_REGISTER OCR0A
#	define ATMOS_TIMER0_INTERRUPT_NAME TIMER0_COMP_vect
#	define ATMOS_TIMER0_COUNTER TCNT0

#	define ATMOS_TIMER1_BITS 16
#	define ATMOS_TIMER1_PRESCALER_CONTROL TCCR1B
#	define ATMOS_TIMER1_MODE_CONTROL TCCR1B
#	define ATMOS_TIMER1_CTC_MODE_BIT WGM12
#	define ATMOS_TIMER1_INTERRUPT_CONTROL TIMSK1
#	define ATMOS_TIMER1_COMPARE_INTERRUPT_BIT OCIE1A
#	define ATMOS_TIMER1_COMPARE_REGISTER OCR1A
#	define ATMOS_TIMER1_INTERRUPT_NAME TIMER1_COMPA_vect
#	define ATMOS_TIMER1_COUNTER TCNT1

#	define ATMOS_TIMER2_BITS 8
#	define ATMOS_TIMER2_PRESCALER_CONTROL TCCR2A
#	define ATMOS_TIMER2_PRESCALER_HAS_32_128
#	define ATMOS_TIMER2_MODE_CONTROL TCCR2A
#	define ATMOS_TIMER2_CTC_MODE_BIT WGM21
#	define ATMOS_TIMER2_INTERRUPT_CONTROL TIMSK2
#	define ATMOS_TIMER2_COMPARE_INTERRUPT_BIT OCIE2A
#	define ATMOS_TIMER2_COMPARE_REGISTER OCR2A
#	define ATMOS_TIMER2_INTERRUPT_NAME TIMER2_COMP_vect
#	define ATMOS_TIMER2_COUNTER TCNT2

#endif
