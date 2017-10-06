#include <avr/io.h>

#include <stdint.h>

#include "kernel/defines.h"
#include "kernel/kernel.h"
#include "kernel/kernel_lock.h"
#include "kernel/process.h"
#include "kernel/process_memory.h"

using namespace atmos;

namespace
{
process_memory_block<16> process1_memory;
process_memory_block<16> process2_memory;
process_memory_block<16> process3_memory;

void ATMOS_OS_TASK process1();
void ATMOS_OS_TASK process2();
void ATMOS_OS_TASK process3();
void process1()
{
	uint8_t i = 20;
	while(true)
	{
		if(i && !--i)
		{
			process::create(process2, process2_memory);
			process::create(process3, process3_memory);
		}
		
		process::sleep_ms(100u);
		kernel_lock lock;
		PORTC ^= _BV(PC0);
	}
}

void process2()
{
	while(true)
	{
		process::sleep_ms(300u);
		kernel_lock lock;
		PORTC ^= _BV(PC1);
	}
}

void process3()
{
	while(true)
	{
		process::sleep_ms(1000u);
		kernel_lock lock;
		PORTC ^= _BV(PC2);
	}
}
} //namespace

int main()
{
	DDRC |= _BV(PC0) | _BV(PC1) | _BV(PC2);
	process::create(process1, process1_memory);
	kernel::run();
}
