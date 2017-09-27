#pragma once

#define STRINGIFY(s) XSTRINGIFY(s)
#define XSTRINGIFY(s) #s

template<typename T1, typename T2>
inline size_t constexpr offset_of(T1 T2::*member)
{
	constexpr T2 object{};
	return reinterpret_cast<size_t>(&(object.*member)) - reinterpret_cast<size_t>(&object);
}
