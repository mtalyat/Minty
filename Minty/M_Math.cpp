#include "pch.h"
#include "M_Math.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>

namespace minty
{
	float MINTY_API math_max(float const left, float const right)
	{
		return left > right ? left : right;
	}

	float MINTY_API math_min(float const left, float const right)
	{
		return left < right ? left : right;
	}

	float MINTY_API math_clamp(float const value, float const min, float const max)
	{
		return math_max(min, math_min(max, value));
	}

	float MINTY_API math_lerp(float const left, float const right, float const t)
	{
		return ((right - left) * math_clamp(t, 0.0f, 1.0f) + left);
	}

	float MINTY_API math_round(float const value)
	{
		return static_cast<float>(round(value));
	}

	float MINTY_API math_round(float const value, float const r)
	{
		return static_cast<float>(round(value / r) * r);
	}

	float MINTY_API math_floor(float const value)
	{
		return static_cast<float>(floor(value));
	}

	float MINTY_API math_ceil(float const value)
	{
		return static_cast<float>(ceil(value));
	}

	float MINTY_API math_abs(float const value)
	{
		return value < 0.0f ? -value : value;
	}

	float MINTY_API math_mod(float const value, float const mod)
	{
		return value - static_cast<int>(value / mod) * mod;
	}

	float MINTY_API math_center(float const x, float const w, float const c)
	{
		return x + w * c;
	}

	MINTY_API float math_deg2rad(float const deg)
	{
		return static_cast<float>(deg * (M_PI / 180.0f));
	}

	MINTY_API float math_rad2deg(float const rad)
	{
		return static_cast<float>(rad * (180.0f / M_PI));
	}

	int MINTY_API math_max(int const left, int const right)
	{
		return left > right ? left : right;
	}

	int MINTY_API math_min(int const left, int const right)
	{
		return left < right ? left : right;
	}

	int MINTY_API math_clamp(int const value, int const min, int const max)
	{
		return math_max(min, math_min(max, value));
	}

	int MINTY_API math_lerp(int const left, int const right, float const t)
	{
		return static_cast<int>(math_lerp(static_cast<float>(left), static_cast<float>(right), t));
	}

	int MINTY_API math_abs(int const value)
	{
		return value < 0 ? -value : value;
	}

	int MINTY_API math_roundToInt(float const value)
	{
		return static_cast<int>(round(value));
	}

	int MINTY_API math_roundToInt(float const value, float const r)
	{
		return static_cast<int>(round(value / r) * r);
	}

	int MINTY_API math_floorToInt(float const value)
	{
		return static_cast<int>(floor(value));
	}

	int MINTY_API math_ceilToInt(float const value)
	{
		return static_cast<int>(ceil(value));
	}

	bool MINTY_API math_contains_ii(int const value, int const min, int const max)
	{
		return value >= min && value <= max;
	}

	bool MINTY_API math_contains_ie(int const value, int const min, int const max)
	{
		return value >= min && value < max;
	}

	bool MINTY_API math_contains_ee(int const value, int const min, int const max)
	{
		return value > min && value < max;
	}

	int MINTY_API math_mod_positive(int const value, int const mod)
	{
		return value < 0 ? (value % mod + mod) : (value % mod);
	}
}
