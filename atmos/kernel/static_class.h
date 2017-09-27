#pragma once

#include "noncopyable.h"

namespace atmos
{
	
///Base class for static classes.
class static_class : public nonmovable
{
public:
	static_class() = delete;
};

} //namespace atmos
