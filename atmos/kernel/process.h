#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "defines.h"
#include "forward_list.h"
#include "static_class.h"

namespace atmos
{

template<size_t RequiredStackSize>
class ATMOS_PACKED process_memory_block;

///OS process definitions and API functions.
class process final : public static_class
{
public:
	///Process entry point type.
	using entry_point_type = void(*)();
	
	///Process stack pointer type.
#if defined(__AVR_HAVE_8BIT_SP__) || defined(__AVR_SP8__)
	using stack_pointer_type = uint8_t;
#else //16-bit stack pointer
	using stack_pointer_type = uint16_t;
#endif //16-bit stack pointer

	///Process ID type.
	using id_type = uint16_t;

public:
	///Process control block.
	struct ATMOS_PACKED control_block
	{
		///Saved process stack pointer.
		stack_pointer_type stack_pointer = 0;
	};
	
public:
	struct process_list_tag;
	struct process_list_element;
	///Special tag that is used to initialize global process list.
	using process_list_element_tagged = container::forward_list_element_tagged<
		process_list_tag, process_list_element>;

	///Element of process list.
	struct ATMOS_PACKED process_list_element : process_list_element_tagged
	{
		control_block process;
	};

public:
	///Invalid process ID.
	static constexpr id_type invalid_process_id = 0u;

	///Program counter size in bytes (depends on AVR device type).
#ifdef __AVR_3_BYTE_PC__
	static constexpr size_t program_counter_size = 3;
#elif defined(__AVR_2_BYTE_PC__)
	static constexpr size_t program_counter_size = 2;
#else //__AVR_3_BYTE_PC__
	static_assert(false, "Unknown program counter size");
#endif //__AVR_3_BYTE_PC__
	
	///Size of all general purpose registers in bytes.
#if __AVR_ARCH__ == 100 //avrtiny, absent r0-r15 registers
	static constexpr size_t gpr_size = sizeof(uint8_t) * 16;
#else //avrtiny
	static constexpr size_t gpr_size = sizeof(uint8_t) * 32;
#endif //avrtiny
	
	///Size of SREG register in bytes.
	static constexpr size_t sreg_size = sizeof(uint8_t);
	
	///Minimal process context size.
	static constexpr size_t minimal_context_size = gpr_size
		+ sreg_size
		+ program_counter_size //return address to process
		+ sizeof(process_list_element);
	
public:
	///<summary>Creates new process with specified entry point
	///         and process stack memory.</summary>
	///<param name="entry_point">Process entry point.</param>
	///<param name="memory">Pre-allocated process memory.</param>
	///<returns>New process ID.</returns>
	template<size_t RequiredStackSize>
	static id_type create(entry_point_type entry_point,
		process_memory_block<RequiredStackSize>& memory)
	{
		return create(entry_point, memory.get_memory(), RequiredStackSize + minimal_context_size);
	}
	
private:
	///<summary>Creates new process with specified entry point,
	///         process stack memory and user stack size.</summary>
	///<param name="entry_point">Process entry point.</param>
	///<param name="process_memory">Pointer to process pre-allocated memory.
	///                             Must be at least minimal_context_size bytes long.</param>
	///<param name="memory_size">Pre-allocated process memory size in bytes.</param>
	///<returns>New process ID.</returns>
	static id_type create(entry_point_type entry_point,
		stack_pointer_type process_memory, size_t memory_size);
};

} //namespace atmos
