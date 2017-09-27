#pragma once

namespace atmos
{

///Base class for noncopyable classes.
class noncopyable
{
public:
	noncopyable() = default;
	noncopyable(const noncopyable&) = delete;
	noncopyable& operator=(const noncopyable&) = delete;
};

///Base class for nonmovable classes.
class nonmovable : public noncopyable
{
public:
	nonmovable() = default;
	nonmovable(nonmovable&&) = delete;
	nonmovable& operator=(nonmovable&&) = delete;
};

} //namespace atmos
