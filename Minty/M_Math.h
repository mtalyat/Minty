#pragma once

#include "M_Main.h"

namespace minty
{
#pragma region float

    /// <summary>
    /// Returns the higher of the two given values.
    /// </summary>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <returns></returns>
    MINTY_API inline float math_max(float const left, float const right);

    /// <summary>
    /// Returns the smaller of the two given values.
    /// </summary>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <returns></returns>
    MINTY_API inline float math_min(float const left, float const right);

    /// <summary>
    /// Returns the value, clamped between the min and max values.
    /// </summary>
    /// <param name="value"></param>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    MINTY_API inline float math_clamp(float const value, float const min, float const max);

    /// <summary>
    /// Lerps between the left and right values.
    /// </summary>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <param name="t"></param>
    /// <returns></returns>
    MINTY_API inline float math_lerp(float const left, float const right, float const t);

    /// <summary>
    /// Rounds the given value.
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    MINTY_API inline float math_round(float const value);

    /// <summary>
    /// Rounds the value to the nearest r.
    /// </summary>
    /// <param name="value"></param>
    /// <param name="r"></param>
    /// <returns></returns>
    MINTY_API inline float math_round(float const value, float const r = 1.0f);

    /// <summary>
    /// Floors the given value.
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    MINTY_API inline float math_floor(float const value);

    /// <summary>
    /// Ceils the given value.
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    MINTY_API inline float math_ceil(float const value);

    /// <summary>
    /// Returns the absolute value of the given value.
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    MINTY_API inline float math_abs(float const value);

    /// <summary>
    /// Performs the modulus operation on a floating point value.
    /// </summary>
    /// <param name="value"></param>
    /// <param name="mod"></param>
    /// <returns></returns>
    MINTY_API inline float math_mod(float const value, float const mod);

    /// <summary>
    /// Finds the center, given a position x, width w, and center (normalized) c.
    /// </summary>
    /// <param name="x"></param>
    /// <param name="w"></param>
    /// <param name="c"></param>
    /// <returns></returns>
    MINTY_API inline float math_center(float const x, float const w, float const c);

    /// <summary>
    /// Converts the given degrees into radians.
    /// </summary>
    /// <param name="deg"></param>
    /// <returns></returns>
    MINTY_API inline float math_deg2rad(float const deg);

    /// <summary>
    /// Converts the given radians into degrees.
    /// </summary>
    /// <param name="rad"></param>
    /// <returns></returns>
    MINTY_API inline float math_rad2deg(float const rad);

#pragma endregion

#pragma region int

    /// <summary>
    /// Returns the higher of the two values.
    /// </summary>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <returns></returns>
    MINTY_API inline int math_max(int const left, int const right);

    /// <summary>
    /// Returns the lower of the two values.
    /// </summary>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <returns></returns>
    MINTY_API inline int math_min(int const left, int const right);

    /// <summary>
    /// Returns the value, clamped between the min and max values.
    /// </summary>
    /// <param name="value"></param>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    MINTY_API inline int math_clamp(int const value, int const min, int const max);

    /// <summary>
    /// Lerps between the two given values.
    /// </summary>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <param name="t"></param>
    /// <returns></returns>
    MINTY_API inline int math_lerp(int const left, int const right, float const t);

    /// <summary>
    /// Returns the absolute value of the given value.
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    MINTY_API inline int math_abs(int const value);

    /// <summary>
    /// Rounds the given float value to an integer.
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    MINTY_API inline int math_roundToInt(float const value);

    /// <summary>
    /// Rounds the given float value to the closest r, then to an integer.
    /// </summary>
    /// <param name="value"></param>
    /// <param name="r"></param>
    /// <returns></returns>
    MINTY_API inline int math_roundToInt(float const value, float const r);

    /// <summary>
    /// Floors the given float value to the nearest int.
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    MINTY_API inline int math_floorToInt(float const value);

    /// <summary>
    /// Ceils the given float value to the nearest int.
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    MINTY_API inline int math_ceilToInt(float const value);

    /// <summary>
    /// Returns true if the given value is between min (inclusive) and max (inclusive).
    /// </summary>
    /// <param name="value"></param>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    MINTY_API inline bool math_contains_ii(int const value, int const min, int const max);

    /// <summary>
    /// Returns true if the given value is between min (inclusive) and max (exclusive).
    /// </summary>
    /// <param name="value"></param>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    MINTY_API inline bool math_contains_ie(int const value, int const min, int const max);

    /// <summary>
    /// Returns true if the given value is between min (exclusive) and max (exclusive).
    /// </summary>
    /// <param name="value"></param>
    /// <param name="min"></param>
    /// <param name="max"></param>
    /// <returns></returns>
    MINTY_API inline bool math_contains_ee(int const value, int const min, int const max);

    /// <summary>
    /// Performs the modulus operation on a value, and ensures the output is positive.
    /// </summary>
    /// <param name="value"></param>
    /// <param name="mod"></param>
    /// <returns></returns>
    MINTY_API inline int math_mod_positive(int const value, int const mod);

#pragma endregion
}