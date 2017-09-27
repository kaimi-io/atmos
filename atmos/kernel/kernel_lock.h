#pragma once

#include <stdint.h>

#include <avr/interrupt.h>
#include <avr/io.h>

#include "noncopyable.h"

namespace atmos
{

///Disables all interrupts in constructor, restores in destructor.
class kernel_lock : public nonmovable
{
public:
	kernel_lock()
		: prev_sreg_(SREG)
	{
		cli();
	}
	
	~kernel_lock()
	{
		SREG = prev_sreg_;
	}
	
private:
	uint8_t prev_sreg_;
};	

} //namespace atmos
