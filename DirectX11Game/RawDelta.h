#pragma once
#include <math.h>


constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

struct RawDelta
{
	int x;
	int y;
};

template<typename T>

T wrap_angle(T theta) noexcept
{
	constexpr T twoPi = (T)2 * (T)PI_D;
	const T mod = (T)fmod(theta, twoPi);
	if (mod > (T)PI_D)
	{
		return mod - twoPi;
	}
	else if (mod < -(T)PI_D)
	{
		return mod + twoPi;
	}
	return mod;
}