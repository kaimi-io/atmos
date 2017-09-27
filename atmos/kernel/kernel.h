#pragma once

#include "defines.h"
#include "static_class.h"

namespace atmos
{

///ATMOS kernel API.
class kernel final : public static_class
{
public:
	///<summary>Runs ATMOS. Does not return.</summary>
	static void ATMOS_NORETURN ATMOS_NAKED run();
};

} //namespace atmos
