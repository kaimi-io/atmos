#include "kernel.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-larger-than="

#include <avr/interrupt.h>
#include <avr/io.h>

#include "config.h"
#include "context_switch.h"
#include "defines.h"
#include "forward_list.h"
#include "kernel_lock.h"
#include "process.h"
#include "process_memory.h"
#include "scheduler_timer_setup.h"
#include "utils.h"

#pragma GCC diagnostic pop

namespace
{

using process_list_element = atmos::process::process_list_element;
using process_list_element_tagged = atmos::process::process_list_element_tagged;

///List of running processes.
using process_list = atmos::container::forward_list_tagged<process_list_element_tagged>;

///Currently running process.
process_list_element_tagged* current_process = nullptr;

#if ATMOS_ENABLE_SYSTEM_PROCESS
process_list_element_tagged* system_process = nullptr;
#endif //ATMOS_ENABLE_SYSTEM_PROCESS

///List of running processes.
process_list running_processes{};
	
#if ATMOS_SUPPORT_SLEEP
process_list_element_tagged* next_process = nullptr;
process_list waiting_processes{};
process_list waiting_processes_overflown{};
atmos::process::tick_t tick_counter = 0;
#endif //ATMOS_SUPPORT_SLEEP

#if ATMOS_SUPPORT_SLEEP
///<summary>Increments tick count and wakes up required processes.</summary>
void ATMOS_ALWAYS_INLINE tick_and_wake_up_processes()
{
	if(!++tick_counter)
	{
		auto temp = waiting_processes;
		waiting_processes = waiting_processes_overflown;
		waiting_processes_overflown = temp;
	}
	
	process_list_element_tagged* prev = nullptr;
	process_list_element_tagged* current = waiting_processes.first();
	while(current)
	{
		if(tick_counter < (*current)->process.sleep_until)
			break;
		
		prev = current;
		current = process_list::next(current);
	}
	
	if(prev)
	{
		process_list::set_next(prev, running_processes.first());
		running_processes.set_first(waiting_processes.first());
		waiting_processes.set_first(current);
	}
}
#endif //ATMOS_SUPPORT_SLEEP

///<summary>Performs process context switch preparations. Decides which process will run next.</summary>
///<returns>Stack pointer of a process to be run next.</returns>
#if ATMOS_SUPPORT_SLEEP
atmos::process::stack_pointer_type ATMOS_HOT ATMOS_USED save_sp_and_choose_next_process(uint8_t increment_tick_count)
	asm("save_sp_and_choose_next_process");
atmos::process::stack_pointer_type save_sp_and_choose_next_process(uint8_t increment_tick_count)
#else //ATMOS_SUPPORT_SLEEP
atmos::process::stack_pointer_type ATMOS_HOT ATMOS_USED save_sp_and_choose_next_process()
asm("save_sp_and_choose_next_process");
atmos::process::stack_pointer_type save_sp_and_choose_next_process()
#endif //ATMOS_SUPPORT_SLEEP
{
#if ATMOS_SUPPORT_SLEEP
	if(increment_tick_count)
		tick_and_wake_up_processes();
#endif //ATMOS_SUPPORT_SLEEP
	
	process_list_element_tagged* current;
#if ATMOS_SUPPORT_SLEEP
	current = current_process;
	if(current)
		(*current)->process.stack_pointer = SP;
	
	current = next_process;
	if(!current)
		current = running_processes.first();
	
	if(current)
	{
		next_process = process_list::next(current);
	}
	else
	{
#	if ATMOS_ENABLE_SYSTEM_PROCESS
		current = system_process;
#	endif //ATMOS_ENABLE_SYSTEM_PROCESS
	}
#else //ATMOS_SUPPORT_SLEEP
	current = current_process;
	auto* first = running_processes.first();
	if(!current)
	{
		current = first;
	}
	else
	{
		(*current)->process.stack_pointer = SP;
		current = process_list::next(current);
		//If we do not have next process to run, just take the first one available.
		if(!current)
			current = first;
	}
#endif //ATMOS_SUPPORT_SLEEP

	//Save current process pointer.
	current_process = current;
	
	//Return stack pointer of process to be run.
	return (*current)->process.stack_pointer;
}
//We compile the target kernel.cpp with -Wframe-larger-than=0 check.
//This is needed to ensure that choose_next_process() stack frame size is zero.
#pragma GCC diagnostic ignored "-Wframe-larger-than="

///<summary>Converts any process list element to process ID.</summary>
///<param name="elem">process_list_element, process_list_element_tagged or forward_list_element pointer.</param>
///<returns>Process ID.</returns>
template<typename ListElement>
atmos::process::id_type to_pid(ListElement* elem)
{
	//Process ID is essentially pointer to its process_list_element.
	static_assert(sizeof(process_list_element*) == sizeof(atmos::process::id_type),
		"Unsupported pointer type size");
	return reinterpret_cast<atmos::process::id_type>(static_cast<process_list_element*>(elem));
}

///<summary>Switches process context and runs next available process.</summary>
///<remarks>This function expects that interrupts are disabled.
///Currently running process context should be already saved before this function is called.</remarks>
void ATMOS_HOT ATMOS_NAKED ATMOS_USED save_context_and_switch_to_next_process_context_func()
	asm("save_context_and_switch_to_next_process_context_func");
///Helper macro that just jumps to switch_to_next_process_context_func function and contains a memory barrier.
#define save_context_and_switch_to_next_process_context() __asm__ __volatile__ \
	(ATMOS_JUMP "save_context_and_switch_to_next_process_context_func" ::: "memory")
void save_context_and_switch_to_next_process_context_func()
{
	save_context_except_r31_and_sreg();
	
	//Switch to next process
	//and set the stack pointer register value to the stack pointer of that process.
	__asm__ __volatile__ (
		"pop r28                                    \n\t"
		"pop r29                                    \n\t"
#ifdef __AVR_3_BYTE_PC__
		"pop r2                                     \n\t"
#endif //__AVR_3_BYTE_PC__
#if ATMOS_SUPPORT_SLEEP
		"clr r24                                    \n\t"
		"bld r24, 0                                 \n\t"
#endif //ATMOS_SUPPORT_SLEEP
		ATMOS_CALL "save_sp_and_choose_next_process \n\t"
#ifdef __AVR_3_BYTE_PC__
		"push r2                                    \n\t"
#endif //__AVR_3_BYTE_PC__
		"push r29                                   \n\t"
		"push r28                                   \n\t"
		"switch_to_stack:                           \n\t"
#if !defined(__AVR_HAVE_8BIT_SP__) && !defined(__AVR_SP8__)
		"out __SP_H__, r25                          \n\t"
#endif //16-bit stack
		"out __SP_L__, r24                          \n\t"
		::
	);
	
	//Now restore process context and run that process.
	restore_context_except_r31_and_sreg();
	restore_r31_and_sreg_and_switch_context();
}

#if ATMOS_ENABLE_SYSTEM_PROCESS
void ATMOS_NAKED system_process_entry_point()
{
	__asm__ __volatile__ (
		"1: jmp 1b    \n\t"
		::
	);
}
#endif //ATMOS_ENABLE_SYSTEM_PROCESS

///<summary>Push address to the bottom of the process stack.</summary>
///<remarks>Assumes that stack memory is zero-filled.</remarks>
///<param name="address">Address to push to stack.</param>
///<param name="stack_bottom">Address of stack bottom.</param>
///<returns>New bottom of the stack value.</returns>
uint8_t* push_function_address(const void* address, uint8_t* stack_bottom) ATMOS_NONNULL(1, 2);
uint8_t* push_function_address(const void* address, uint8_t* stack_bottom)
{
	*--stack_bottom = static_cast<uint8_t>(reinterpret_cast<uint16_t>(address));
	*--stack_bottom = static_cast<uint8_t>(reinterpret_cast<uint16_t>(address) >> 8);
#ifdef __AVR_3_BYTE_PC__
	--stack_bottom;
#endif //__AVR_3_BYTE_PC__

	return stack_bottom;
}

///<summary>Prepare new process context.</summary>
///<remarks>Assumes that stack memory is zero-filled. Pushes
///return address to process entry point, all general purpose register values and SREG value.</remarks>
///<param name="entry_point">Process entry point address.</param>
///<param name="stack_bottom">Address of stack bottom.</param>
///<returns>New bottom of the stack value.</returns>
uint8_t* prepare_process_context(atmos::process::entry_point_type entry_point,
	uint8_t* stack_bottom) ATMOS_NONNULL(1, 2);
uint8_t* prepare_process_context(atmos::process::entry_point_type entry_point, uint8_t* stack_bottom)
{
	//Push the return address to process entry point.
	stack_bottom = push_function_address(reinterpret_cast<const void*>(entry_point), stack_bottom);
	
	//Push general purpose register values.
	//First GPR - this will be R31 (see save_r31_and_sreg_from_scheduler, save_r31_and_sreg_from_task).
	--stack_bottom;
	//Then goes SREG: Interrupts are enabled by default.
	*--stack_bottom = _BV(ATMOS_AVR_INTERRUPT_BIT);
	//Then go 31 more general purpose registers (or 15 for avrtiny architecture)
	stack_bottom -= (atmos::process::gpr_size - 1);
	return --stack_bottom;
}

///<summary>Creates process using pre-allocated memory.</summary>
///<param name="entry_point">Process entry point address.</param>
///<param name="process_memory">Pre-allocated process memory. Must have at least minimal_context_size bytes size.</param>
///<param name="memory_size">Size of pre-allocated memory.</param>
///<returns>Pointer to initialized process_list_element (which is equal to process_memory value).</returns>
process_list_element* create_process(atmos::process::entry_point_type entry_point,
	atmos::process::stack_pointer_type process_memory, size_t memory_size)
{
	//Just prepare process context and control block.
	auto* elem = reinterpret_cast<process_list_element*>(process_memory);
	auto* stack_bottom = reinterpret_cast<uint8_t*>(process_memory) + memory_size;
	elem->process.stack_pointer = static_cast<atmos::process::stack_pointer_type>(
		reinterpret_cast<uint16_t>(prepare_process_context(entry_point, stack_bottom)));
	return elem;
}

} //namespace

//Scheduler interrupt. Saves current process context and then switches context to next process.
ISR(ATMOS_TIMER_INTERRUPT_NAME, ISR_NAKED ATMOS_HOT)
{
	save_r31_and_sreg_from_scheduler();
	
#if ATMOS_SUPPORT_SLEEP
	__asm__ __volatile__ (
		"set \n\t"
		::
	);
#endif //ATMOS_SUPPORT_SLEEP

	save_context_and_switch_to_next_process_context();
}

namespace atmos
{

void kernel::run()
{
#if ATMOS_ENABLE_SYSTEM_PROCESS
	static atmos::process_memory_block<0> system_process_memory;
	system_process = create_process(system_process_entry_point, system_process_memory.get_memory(),
		decltype(system_process_memory)::memory_block_size);
#endif //ATMOS_ENABLE_SYSTEM_PROCESS
	
	initialize_scheduler_timer();
	//Run kernel: switch to first available process and run it.
	__asm__ __volatile__ (
#if ATMOS_SUPPORT_SLEEP
		"clt                                        \n\t"
#endif //ATMOS_SUPPORT_SLEEP
		ATMOS_CALL "save_sp_and_choose_next_process \n\t"
		ATMOS_JUMP "switch_to_stack                 \n\t"
		::
	);
	__builtin_unreachable();
}

//Creates new process.
process::id_type process::create(process::entry_point_type entry_point,
	process::stack_pointer_type process_memory, size_t memory_size)
{
	//Prepare process stack and context.
	auto* process = create_process(entry_point, process_memory, memory_size);
	
	{
		//Add new process to the list of running processes.
		atmos::kernel_lock lock;
		running_processes.push_front(process);
	}
	
	//Return process ID.
	return to_pid(process);
}

#if ATMOS_SUPPORT_SLEEP || ATMOS_SUPPORT_YIELD
void process::yield()
{
	save_r31_and_sreg_from_task();

#	if ATMOS_SUPPORT_SLEEP
	__asm__ __volatile__ (
		"clt \n\t"
		::
	);
#	endif //ATMOS_SUPPORT_SLEEP
	
	save_context_and_switch_to_next_process_context();
}
#endif //ATMOS_SUPPORT_SLEEP || ATMOS_SUPPORT_YIELD

#if ATMOS_SUPPORT_SLEEP
void process::sleep_ticks(tick_t ticks)
{
	if(!ticks)
	{
		yield();
		return;
	}
	
	atmos::kernel_lock lock;
	
	tick_t sleep_until = tick_counter + ticks;
	(*current_process)->process.sleep_until = sleep_until;
	running_processes.remove(current_process);
	
	auto& target_list = sleep_until < ticks ? waiting_processes_overflown : waiting_processes;
	target_list.insert_before(current_process, [sleep_until](const auto* before)
	{
		return before->process.sleep_until > sleep_until;
	});
	
	yield();
}
#endif //ATMOS_SUPPORT_SLEEP

} //namespace atmos
