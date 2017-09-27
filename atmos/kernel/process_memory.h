#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "defines.h"
#include "process.h"

namespace atmos
{

///Pre-allocated process memory block.
template<size_t RequiredStackSize>
class ATMOS_PACKED process_memory_block
{
public:
	///Creates process memory block with required stack size.
	///Fills memory with nullbytes.
	constexpr process_memory_block()
		: memory_{}
	{
	}
	
	///Returns pointer to memory block.
	process::stack_pointer_type get_memory()
	{
		return reinterpret_cast<process::stack_pointer_type>(memory_);
	}
	
private:
	uint8_t memory_[RequiredStackSize + process::minimal_context_size];
};

} //namespace atmos
