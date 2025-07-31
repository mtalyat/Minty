#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Library/GLM.h"
#include <limits>

namespace Minty
{
#pragma region Types

	using Bool2 = glm::bvec2;
	using Bool3 = glm::bvec3;
	using Bool4 = glm::bvec4;

	using Int2 = glm::ivec2;
	using Int3 = glm::ivec3;
	using Int4 = glm::ivec4;

	using UInt2 = glm::uvec2;
	using UInt3 = glm::uvec3;
	using UInt4 = glm::uvec4;

	using Long2 = glm::vec<2, Long>;
	using Long3 = glm::vec<3, Long>;
	using Long4 = glm::vec<4, Long>;

	using ULong2 = glm::vec<2, ULong>;
	using ULong3 = glm::vec<3, ULong>;
	using ULong4 = glm::vec<4, ULong>;

	using Float2 = glm::vec2;
	using Float3 = glm::vec3;
	using Float4 = glm::vec4;

	using Double2 = glm::dvec2;
	using Double3 = glm::dvec3;
	using Double4 = glm::dvec4;

	using Quaternion = glm::quat;

	using Matrix2 = glm::mat2;
	using Matrix3 = glm::mat3;
	using Matrix4 = glm::mat4;

#pragma endregion

#pragma region Math

	namespace Math
	{
#pragma region Constants

		/// <summary>
		/// PI.
		/// </summary>
		constexpr Float PI = 3.14159265358979323846f;

		/// <summary>
		/// PI * 2.
		/// </summary>
		constexpr Float TAU = 6.28318530717958647692f;

		/// <summary>
		/// Euler's number.
		/// </summary>
		constexpr Float E = 2.71828182845904523536f;

		/// <summary>
		/// The smallest value that is considered to be zero in floating point calculations.
		/// </summary>
		constexpr Float EPSILON = 0.00001f;

		/// <summary>
		/// 180 / PI.
		/// </summary>
		constexpr Float RAD2DEG = 57.2957795130823208768f;

		/// <summary>
		/// PI / 180.
		/// </summary>
		constexpr Float DEG2RAD = 0.01745329251994329577f;

		/// <summary>
		/// Infinity.
		/// </summary>
		constexpr Float INF = std::numeric_limits<Float>::infinity();

		/// <summary>
		/// Forward direction in 3D space.
		/// </summary>
		constexpr Float3 FORWARD = Float3(0.0f, 0.0f, 1.0f);

		/// <summary>
		/// Backward direction in 3D space.
		/// </summary>
		constexpr Float3 BACKWARD = Float3(0.0f, 0.0f, -1.0f);

		/// <summary>
		/// Up direction in 3D space.
		/// </summary>
		constexpr Float3 UP = Float3(0.0f, 1.0f, 0.0f);

		/// <summary>
		/// Down direction in 3D space.
		/// </summary>
		constexpr Float3 DOWN = Float3(0.0f, -1.0f, 0.0f);

		/// <summary>
		/// Left direction in 3D space.
		/// </summary>
		constexpr Float3 LEFT = Float3(-1.0f, 0.0f, 0.0f);

		/// <summary>
		/// Right direction in 3D space.
		/// </summary>
		constexpr Float3 RIGHT = Float3(1.0f, 0.0f, 0.0f);

		/// <summary>
		/// Zero vector in 3D space.
		/// </summary>
		constexpr Float3 ZERO = Float3(0.0f, 0.0f, 0.0f);

		/// <summary>
		/// One vector in 3D space.
		/// </summary>
		constexpr Float3 ONE = Float3(1.0f, 1.0f, 1.0f);

#pragma endregion

#pragma region Functions

		/// <summary>
		/// Returns the minimum of the two given values.
		/// </summary>
		/// <typeparam name="T">The type of value.</typeparam>
		/// <param name="a">The first value.</param>
		/// <param name="b">The second value.</param>
		/// <returns>The lower of the two values.</returns>
		template<typename T>
		constexpr T min(T const a, T const b)
		{
			return a < b ? a : b;
		}

		/// <summary>
		/// Returns the minimum of the given values.
		/// </summary>
		/// <typeparam name="T">The type of value.</typeparam>
		/// <typeparam name="...Args">The type of value.</typeparam>
		/// <param name="a">The first value.</param>
		/// <param name="...args">The other values.</param>
		/// <returns>The lowest of the values.</returns>
		template<typename T, typename... Args>
		constexpr T min(T const a, Args const... args)
		{
			return min(a, min(args...));
		}

		/// <summary>
		/// Returns the maximum of the two given values.
		/// </summary>
		/// <typeparam name="T">The type of value.</typeparam>
		/// <param name="a">The first value.</param>
		/// <param name="b">The second value.</param>
		/// <returns>The higher of the two values.</returns>
		template<typename T>
		constexpr T max(T const a, T const b)
		{
			return a > b ? a : b;
		}

		/// <summary>
		/// Returns the maximum of the given values.
		/// </summary>
		/// <typeparam name="T">The type of value.</typeparam>
		/// <typeparam name="...Args">The type of value.</typeparam>
		/// <param name="a">The first value.</param>
		/// <param name="...args">The other values.</param>
		/// <returns>The highest of the values.</returns>
		template<typename T, typename... Args>
		constexpr T max(T const a, Args const... args)
		{
			return max(a, max(args...));
		}

		/// <summary>
		/// Clamps the given value between the given minimum and maximum values.
		/// </summary>
		/// <typeparam name="T">The type of value.</typeparam>
		/// <param name="value">The value to clamp.</param>
		/// <param name="min">The minimum value.</param>
		/// <param name="max">The maximum value.</param>
		/// <returns>The value, clamped between min and max.</returns>
		template<typename T>
		constexpr T clamp(T const value, T const min, T const max)
		{
			return value < min ? min : (value > max ? max : value);
		}

		/// <summary>
		/// Rounds the given value, and casts it to the given type, if necessary.
		/// </summary>
		/// <typeparam name="T_In">The input type.</typeparam>
		/// <typeparam name="T_Out">The output type.</typeparam>
		/// <param name="value">The value to round.</param>
		/// <returns>The result.</returns>
		template<typename T_In, typename T_Out = T_In>
		constexpr T_Out round(T_In const value)
		{
			return static_cast<T_Out>(std::round(value));
		}

		/// <summary>
		/// Rounds the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to round.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Float2 round(Float2 const value)
		{
			return Float2(std::round(value.x), std::round(value.y));
		}

		/// <summary>
		/// Rounds the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to round.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Float3 round(Float3 const value)
		{
			return Float3(std::round(value.x), std::round(value.y), std::round(value.z));
		}

		/// <summary>
		/// Rounds the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to round.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Float4 round(Float4 const value)
		{
			return Float4(std::round(value.x), std::round(value.y), std::round(value.z), std::round(value.w));
		}

		/// <summary>
		/// Rounds the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to round.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Double2 round(Double2 const value)
		{
			return Double2(std::round(value.x), std::round(value.y));
		}

		/// <summary>
		/// Rounds the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to round.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Double3 round(Double3 const value)
		{
			return Double3(std::round(value.x), std::round(value.y), std::round(value.z));
		}

		/// <summary>
		/// Rounds the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to round.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Double4 round(Double4 const value)
		{
			return Double4(std::round(value.x), std::round(value.y), std::round(value.z), std::round(value.w));
		}

		/// <summary>
		/// Rounds the given value to the nearest value based on the given precision. The precision is the number of decimal places to round to.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to round.</param>
		/// <param name="precision">The precision, equal to (10 ^ precision). Ex. 2 will round the value to the closest 100.</param>
		/// <returns>The value, rounded.</returns>
		template<typename T>
		constexpr T round(T const value, Int const precision)
		{
			return static_cast<T>(std::round(value / std::pow(10, precision)) * std::pow(10, precision));
		}

		/// <summary>
		/// Snaps the given value to the nearest value based on the given snap value.
		/// </summary>
		/// <typeparam name="T">The type to snap.</typeparam>
		/// <param name="value">The value to snap.</param>
		/// <param name="snapValue">The value to snap by.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T snap(T const value, T const snapValue)
		{
			return static_cast<T>(std::round(value / snapValue) * snapValue);
		}

		/// <summary>
		/// Snaps the given value to the nearest value based on the given snap value.
		/// </summary>
		/// <typeparam name="T">The type to snap.</typeparam>
		/// <param name="value">The value to snap.</param>
		/// <param name="snapValue">The value to snap by.</param>
		/// <returns>The result.</returns>
		constexpr Float2 snap(Float2 const value, Float const snapValue)
		{
			return Float2(std::round(value.x / snapValue) * snapValue, std::round(value.y / snapValue) * snapValue);
		}

		/// <summary>
		/// Snaps the given value to the nearest value based on the given snap value.
		/// </summary>
		/// <typeparam name="T">The type to snap.</typeparam>
		/// <param name="value">The value to snap.</param>
		/// <param name="snapValue">The value to snap by.</param>
		/// <returns>The result.</returns>
		constexpr Float3 snap(Float3 const value, Float const snapValue)
		{
			return Float3(
				std::round(value.x / snapValue) * snapValue,
				std::round(value.y / snapValue) * snapValue,
				std::round(value.z / snapValue) * snapValue);
		}

		/// <summary>
		/// Snaps the given value to the nearest value based on the given snap value.
		/// </summary>
		/// <typeparam name="T">The type to snap.</typeparam>
		/// <param name="value">The value to snap.</param>
		/// <param name="snapValue">The value to snap by.</param>
		/// <returns>The result.</returns>
		constexpr Float4 snap(Float4 const value, Float const snapValue)
		{
			return Float4(
				std::round(value.x / snapValue) * snapValue,
				std::round(value.y / snapValue) * snapValue,
				std::round(value.z / snapValue) * snapValue,
				std::round(value.w / snapValue) * snapValue);
		}

		/// <summary>
		/// Snaps the given value to the nearest value based on the given snap value.
		/// </summary>
		/// <typeparam name="T">The type to snap.</typeparam>
		/// <param name="value">The value to snap.</param>
		/// <param name="snapValue">The value to snap by.</param>
		/// <returns>The result.</returns>
		constexpr Double2 snap(Double2 const value, Double const snapValue)
		{
			return Double2(std::round(value.x / snapValue) * snapValue, std::round(value.y / snapValue) * snapValue);
		}

		/// <summary>
		/// Snaps the given value to the nearest value based on the given snap value.
		/// </summary>
		/// <typeparam name="T">The type to snap.</typeparam>
		/// <param name="value">The value to snap.</param>
		/// <param name="snapValue">The value to snap by.</param>
		/// <returns>The result.</returns>
		constexpr Double3 snap(Double3 const value, Double const snapValue)
		{
			return Double3(
				std::round(value.x / snapValue) * snapValue,
				std::round(value.y / snapValue) * snapValue,
				std::round(value.z / snapValue) * snapValue);
		}

		/// <summary>
		/// Snaps the given value to the nearest value based on the given snap value.
		/// </summary>
		/// <typeparam name="T">The type to snap.</typeparam>
		/// <param name="value">The value to snap.</param>
		/// <param name="snapValue">The value to snap by.</param>
		/// <returns>The result.</returns>
		constexpr Double4 snap(Double4 const value, Double const snapValue)
		{
			return Double4(
				std::round(value.x / snapValue) * snapValue,
				std::round(value.y / snapValue) * snapValue,
				std::round(value.z / snapValue) * snapValue,
				std::round(value.w / snapValue) * snapValue);
		}

		/// <summary>
		/// Floors the given value, and casts it to the given type, if necessary.
		/// </summary>
		/// <typeparam name="T_In">The input type.</typeparam>
		/// <typeparam name="T_Out">The output type.</typeparam>
		/// <param name="value">The value to floor.</param>
		/// <returns>The result.</returns>
		template<typename T_In, typename T_Out = T_In>
		constexpr T_Out floor(T_In const value)
		{
			return static_cast<T_Out>(std::floor(value));
		}

		/// <summary>
		/// Floors the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to floor.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Float2 floor(Float2 const value)
		{
			return Float2(std::floor(value.x), std::floor(value.y));
		}

		/// <summary>
		/// Floors the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to floor.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Float3 floor(Float3 const value)
		{
			return Float3(std::floor(value.x), std::floor(value.y), std::floor(value.z));
		}

		/// <summary>
		/// Floors the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to floor.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Float4 floor(Float4 const value)
		{
			return Float4(std::floor(value.x), std::floor(value.y), std::floor(value.z), std::floor(value.w));
		}

		/// <summary>
		/// Floors the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to floor.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Double2 floor(Double2 const value)
		{
			return Double2(std::floor(value.x), std::floor(value.y));
		}

		/// <summary>
		/// Floors the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to floor.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Double3 floor(Double3 const value)
		{
			return Double3(std::floor(value.x), std::floor(value.y), std::floor(value.z));
		}

		/// <summary>
		/// Floors the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to floor.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Double4 floor(Double4 const value)
		{
			return Double4(std::floor(value.x), std::floor(value.y), std::floor(value.z), std::floor(value.w));
		}

		/// <summary>
		/// Floors the given value to the nearest value based on the given precision. The precision is the number of decimal places to floor to.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to floor.</param>
		/// <param name="precision">The precision, equal to (10 ^ precision). Ex. 2 will floor the value to the closest 100.</param>
		/// <returns>The value, floored.</returns>
		template<typename T>
		constexpr T floor(T const value, Int const precision)
		{
			return static_cast<T>(std::floor(value / std::pow(10, precision)) * std::pow(10, precision));
		}

		/// <summary>
		/// Ceilings the given value, and casts it to the given type, if necessary.
		/// </summary>
		/// <typeparam name="T_In">The input type.</typeparam>
		/// <typeparam name="T_Out">The output type.</typeparam>
		/// <param name="value">The value to ceiling.</param>
		/// <returns>The result.</returns>
		template<typename T_In, typename T_Out = T_In>
		constexpr T_Out ceiling(T_In const value)
		{
			return static_cast<T_Out>(std::ceil(value));
		}

		/// <summary>
		/// Ceilings the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to ceiling.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Float2 ceiling(Float2 const value)
		{
			return Float2(std::ceil(value.x), std::ceil(value.y));
		}

		/// <summary>
		/// Ceilings the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to ceiling.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Float3 ceiling(Float3 const value)
		{
			return Float3(std::ceil(value.x), std::ceil(value.y), std::ceil(value.z));
		}

		/// <summary>
		/// Ceilings the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to ceiling.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Float4 ceiling(Float4 const value)
		{
			return Float4(std::ceil(value.x), std::ceil(value.y), std::ceil(value.z), std::ceil(value.w));
		}

		/// <summary>
		/// Ceilings the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to ceiling.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Double2 ceiling(Double2 const value)
		{
			return Double2(std::ceil(value.x), std::ceil(value.y));
		}

		/// <summary>
		/// Ceilings the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to ceiling.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Double3 ceiling(Double3 const value)
		{
			return Double3(std::ceil(value.x), std::ceil(value.y), std::ceil(value.z));
		}

		/// <summary>
		/// Ceilings the given value to the nearest whole number.
		/// </summary>
		/// <param name="value">The value to ceiling.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Double4 ceiling(Double4 const value)
		{
			return Double4(std::ceil(value.x), std::ceil(value.y), std::ceil(value.z), std::ceil(value.w));
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <typeparam name="T">The type of value to lerp.</typeparam>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<typename T>
		constexpr T lerp(T const left, T const right, Float const t)
		{
			return left + Math::floor<Float, T>((right - left) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Int2 lerp(Int2 const left, Int2 const right, Float const t)
		{
			return Int2(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Int3 lerp(Int3 const left, Int3 const right, Float const t)
		{
			return Int3(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t, left.z + (right.z - left.z) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Int4 lerp(Int4 const left, Int4 const right, Float const t)
		{
			return Int4(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t, left.z + (right.z - left.z) * t, left.w + (right.w - left.w) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr UInt2 lerp(UInt2 const left, UInt2 const right, Float const t)
		{
			return UInt2(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr UInt3 lerp(UInt3 const left, UInt3 const right, Float const t)
		{
			return UInt3(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t, left.z + (right.z - left.z) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr UInt4 lerp(UInt4 const left, UInt4 const right, Float const t)
		{
			return UInt4(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t, left.z + (right.z - left.z) * t, left.w + (right.w - left.w) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Float lerp(Float const left, Float const right, Float const t)
		{
			return left + (right - left) * t;
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Float2 lerp(Float2 const left, Float2 const right, Float const t)
		{
			return Float2(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Float3 lerp(Float3 const left, Float3 const right, Float const t)
		{
			return Float3(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t, left.z + (right.z - left.z) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Float4 lerp(Float4 const left, Float4 const right, Float const t)
		{
			return Float4(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t, left.z + (right.z - left.z) * t, left.w + (right.w - left.w) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Double lerp(Double const left, Double const right, Float const t)
		{
			return left + (right - left) * t;
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Double2 lerp(Double2 const left, Double2 const right, Float const t)
		{
			return Double2(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Double3 lerp(Double3 const left, Double3 const right, Float const t)
		{
			return Double3(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t, left.z + (right.z - left.z) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t.
		/// </summary>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<>
		constexpr Double4 lerp(Double4 const left, Double4 const right, Float const t)
		{
			return Double4(left.x + (right.x - left.x) * t, left.y + (right.y - left.y) * t, left.z + (right.z - left.z) * t, left.w + (right.w - left.w) * t);
		}

		/// <summary>
		/// Gets the position between left and right, based on t, and clamps it between left and right.
		/// </summary>
		/// <typeparam name="T">The type of value to lerp.</typeparam>
		/// <param name="left">The lower bound.</param>
		/// <param name="right">The upper bound.</param>
		/// <param name="t">The percentage to lerp by. 0.0 is left, 1.0 is right.</param>
		/// <returns>The lerped value.</returns>
		template<typename T>
		constexpr T lerp_clamped(T const left, T const right, Float const t)
		{
			return lerp(left, right, clamp(t, 0.0f, 1.0f));
		}

		/// <summary>
		/// Ceilings the given value to the nearest value based on the given precision. The precision is the number of decimal places to ceiling to.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to ceiling.</param>
		/// <param name="precision">The precision, equal to (10 ^ precision). Ex. 2 will ceiling the value to the closest 100.</param>
		/// <returns>The value, ceilinged.</returns>
		template<typename T>
		constexpr T ceiling(T const value, Int const precision)
		{
			return static_cast<T>(std::ceil(value / std::pow(10, precision)) * std::pow(10, precision));
		}

		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T abs(T const value)
		{
			return value < 0 ? -value : value;
		}

		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Float2 abs(Float2 const value)
		{
			return Float2(abs(value.x), abs(value.y));
		}
		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Float3 abs(Float3 const value)
		{
			return Float3(abs(value.x), abs(value.y), abs(value.z));
		}
		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Float4 abs(Float4 const value)
		{
			return Float4(abs(value.x), abs(value.y), abs(value.z), abs(value.w));
		}

		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Double2 abs(Double2 const value)
		{
			return Double2(abs(value.x), abs(value.y));
		}
		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Double3 abs(Double3 const value)
		{
			return Double3(abs(value.x), abs(value.y), abs(value.z));
		}
		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Double4 abs(Double4 const value)
		{
			return Double4(abs(value.x), abs(value.y), abs(value.z), abs(value.w));
		}

		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Int2 abs(Int2 const value)
		{
			return Int2(abs(value.x), abs(value.y));
		}
		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Int3 abs(Int3 const value)
		{
			return Int3(abs(value.x), abs(value.y), abs(value.z));
		}
		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Int4 abs(Int4 const value)
		{
			return Int4(abs(value.x), abs(value.y), abs(value.z), abs(value.w));
		}

		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Long2 abs(Long2 const value)
		{
			return Long2(abs(value.x), abs(value.y));
		}
		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Long3 abs(Long3 const value)
		{
			return Long3(abs(value.x), abs(value.y), abs(value.z));
		}
		/// <summary>
		/// Gets the absolute value of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<>
		inline Long4 abs(Long4 const value)
		{
			return Long4(abs(value.x), abs(value.y), abs(value.z), abs(value.w));
		}

		/// <summary>
		/// Gets the sine of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T sin(T const value)
		{
			return std::sin(value);
		}

		/// <summary>
		/// Gets the cosine of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T cos(T const value)
		{
			return std::cos(value);
		}

		/// <summary>
		/// Gets the tangent of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T tan(T const value)
		{
			return std::tan(value);
		}

		/// <summary>
		/// Gets the arcsine of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T asin(T const value)
		{
			return std::asin(value);
		}

		/// <summary>
		/// Gets the arccosine of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T acos(T const value)
		{
			return std::acos(value);
		}

		/// <summary>
		/// Gets the arctangent of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value to operate on.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T atan(T const value)
		{
			return std::atan(value);
		}

		/// <summary>
		/// Gets the arctangent 2 of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="y">The Y value.</param>
		/// <param name="x">The X value.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T atan2(T const y, T const x)
		{
			return std::atan2(y, x);
		}

		/// <summary>
		/// Gets the angle to the dx and dy values from the origin.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="dx">The X position.</param>
		/// <param name="dy">The Y position.</param>
		/// <returns>Thje angle based on the given position.</returns>
		template<typename T>
		constexpr T angle(T const dx, T const dy)
		{
			return atan2(dy, dx);
		}

		/// <summary>
		/// Gets the square root of the given value.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T sqrt(T const value)
		{
			return std::sqrt(value);
		}

		/// <summary>
		/// Gets the power of the given base to the given exponent.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="base">The base value.</param>
		/// <param name="exponent">The exponent value.</param>
		/// <returns>Base to the power of exponent.</returns>
		template<typename T>
		constexpr T pow(T const base, T const exponent)
		{
			if (exponent == 0) return 1;
			if (exponent == 1) return base;

			T temp = pow<T>(base, exponent / 2);
			if (exponent % 2 == 0)
			{
				return temp * temp;
			}

			return base * temp * temp;
		}

		/// <summary>
		/// Gets the power of the given base to the given exponent.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="base">The base value.</param>
		/// <param name="exponent">The exponent value.</param>
		/// <returns>Base to the power of exponent.</returns>
		template<>
		inline Float pow(Float const base, Float const exponent)
		{
			return std::powf(base, exponent);
		}

		/// <summary>
		/// Gets the power of the given base to the given exponent.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="base">The base value.</param>
		/// <param name="exponent">The exponent value.</param>
		/// <returns>Base to the power of exponent.</returns>
		template<>
		inline Double pow(Double const base, Double const exponent)
		{
			return std::pow(base, exponent);
		}

		/// <summary>
		/// Gets the distance from the origin to the given x and y values.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="x">The X position.</param>
		/// <param name="y">The Y position.</param>
		template<typename T>
		constexpr T magnitude(T const x, T const y)
		{
			return sqrt(x * x + y * y);
		}

		/// <summary>
		/// Gets the sign of the given value. 1 for positive, 0 for zero, and -1 for negative.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value.</param>
		/// <returns>1, 0 or -1.</returns>
		template<typename T>
		constexpr Int sign(T const value)
		{
			return value < 0 ? -1 : (value > 0 ? 1 : 0);
		}

		/// <summary>
		/// Gets the dot product of the two given Float3 values.
		/// </summary>
		/// <param name="a">The first value.</param>
		/// <param name="b">The second value.</param>
		/// <returns>The dot product.</returns>
		constexpr Float dot(Float3 const& a, Float3 const& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		/// <summary>
		/// Gets the cross product of the two given Float3 values.
		/// </summary>
		/// <param name="a">The first value.</param>
		/// <param name="b">The second value.</param>
		/// <returns>The cross product.</returns>
		constexpr Float3 cross(Float3 const& a, Float3 const& b)
		{
			return Float3(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			);
		}

		/// <summary>
		/// Performs a modulus operation on the given value and divisor.
		/// </summary>
		/// <typeparam name="T">The type.</typeparam>
		/// <param name="value">The value.</param>
		/// <param name="divisor">The divisor.</param>
		/// <returns>The result.</returns>
		template<typename T>
		constexpr T mod(T const value, T const divisor)
		{
			return value % divisor;
			return value - Math::floor(value / divisor) * divisor;
		}

		/// <summary>
		/// Performs a modulus operation on the given value and divisor.
		/// </summary>
		/// <param name="value">The value.</param>
		/// <param name="divisor">The divisor.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Float mod(Float const value, Float const divisor)
		{
			return value - Math::floor(value / divisor) * divisor;
		}

		/// <summary>
		/// Performs a modulus operation on the given value and divisor.
		/// </summary>
		/// <param name="value">The value.</param>
		/// <param name="divisor">The divisor.</param>
		/// <returns>The result.</returns>
		template<>
		constexpr Double mod(Double const value, Double const divisor)
		{
			return value - Math::floor(value / divisor) * divisor;
		}

#pragma endregion

#pragma region Utility

		/// <summary>
		/// Checks if the two given Float values are close to each other, within the given epsilon.
		/// </summary>
		/// <param name="a">The first value.</param>
		/// <param name="b">The second value.</param>
		/// <param name="epsilon">The epsilon.</param>
		/// <returns>True, if they are the same, or almost the same.</returns>
		constexpr Bool close(Float const a, Float const b, Float const epsilon = EPSILON)
		{
			return Math::abs(a - b) < epsilon;
		}

		/// <summary>
		/// Checks if the two given Float values are close to each other, within the given epsilon.
		/// </summary>
		/// <param name="a">The first value.</param>
		/// <param name="b">The second value.</param>
		/// <param name="epsilon">The epsilon.</param>
		/// <returns>True, if they are the same, or almost the same.</returns>
		constexpr Bool close(Float2 const& a, Float2 const& b, Float const epsilon = EPSILON)
		{
			return close(a.x, b.x, epsilon) && close(a.y, b.y, epsilon);
		}

		/// <summary>
		/// Checks if the two given Float values are close to each other, within the given epsilon.
		/// </summary>
		/// <param name="a">The first value.</param>
		/// <param name="b">The second value.</param>
		/// <param name="epsilon">The epsilon.</param>
		/// <returns>True, if they are the same, or almost the same.</returns>
		constexpr Bool close(Float3 const& a, Float3 const& b, Float const epsilon = EPSILON)
		{
			return close(a.x, b.x, epsilon) && close(a.y, b.y, epsilon) && close(a.z, b.z, epsilon);
		}

		/// <summary>
		/// Checks if the two given Float values are close to each other, within the given epsilon.
		/// </summary>
		/// <param name="a">The first value.</param>
		/// <param name="b">The second value.</param>
		/// <param name="epsilon">The epsilon.</param>
		/// <returns>True, if they are the same, or almost the same.</returns>
		constexpr Bool close(Float4 const& a, Float4 const& b, Float const epsilon = EPSILON)
		{
			return close(a.x, b.x, epsilon) && close(a.y, b.y, epsilon) && close(a.z, b.z, epsilon) && close(a.w, b.w, epsilon);
		}

		/// <summary>
		/// Normalizes the given Float3.
		/// </summary>
		/// <param name="value">The value.</param>
		/// <returns>The result.</returns>
		Float3 normalize(Float3 const& value);

		/// <summary>
		/// Gets the magnitude of the given Float3.
		/// </summary>
		/// <param name="value">The value.</param>
		/// <returns>The result.</returns>
		Float magnitude(Float3 const& value);

		/// <summary>
		/// Gets the forward vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 forward(Quaternion const& value);

		/// <summary>
		/// Gets the backward vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 backward(Quaternion const& value);

		/// <summary>
		/// Gets the up vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 up(Quaternion const& value);

		/// <summary>
		/// Gets the down vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 down(Quaternion const& value);

		/// <summary>
		/// Gets the right vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 right(Quaternion const& value);

		/// <summary>
		/// Gets the left vector of the given Quaternion.
		/// </summary>
		/// <param name="value">The rotation.</param>
		/// <returns>The result.</returns>
		Float3 left(Quaternion const& value);

		/// <summary>
		/// Creates a Quaternion from the given angle and axis.
		/// </summary>
		/// <param name="angle">The angle to use.</param>
		/// <param name="axis">The axis the given angle is on.</param>
		/// <returns>The rotation, as a Quaternion.</returns>
		Quaternion angle_axis(Float const angle, Float3 const& axis);

		/// <summary>
		/// Creates a Quaternion that looks at the target position from the given eye position, using the given up vector.
		/// </summary>
		/// <param name="eye">The location of the object that is looking.</param>
		/// <param name="target">The location to look at.</param>
		/// <param name="up">The up direction.</param>
		/// <returns>A Quaternion reflecting the given values.</returns>
		Quaternion look_at(Float3 const& eye, Float3 const& target, Float3 const& up = UP);

		/// <summary>
		/// Converts the given Quaternion to Euler angles.
		/// </summary>
		/// <param name="value">The rotation, as a Quaternion.</param>
		/// <returns>The rotation, as Euler angles.</returns>
		Float3 to_euler(Quaternion const& value);

		/// <summary>
		/// Converts the given Euler angles to a Quaternion.
		/// </summary>
		/// <param name="value">The rotation, as Euler angles.</param>
		/// <returns>The rotation, as a Quaternion.</returns>
		Quaternion to_cartesian(Float3 const& value);

		/// <summary>
		/// Converts the given Euler angles to a Quaternion.
		/// </summary>
		/// <param name="x">The rotation on the X axis.</param>
		/// <param name="y">The rotation on the Y axis.</param>
		/// <param name="z">The rotation on the Z axis.</param>
		/// <returns>The rotation, as a Quaternion.</returns>
		inline Quaternion to_cartesian(Float const x, Float const y, Float const z)
		{
			return to_cartesian(Float3(x, y, z));
		}

		/// <summary>
		/// Creates an identity of the given type.
		/// </summary>
		/// <typeparam name="T">The type to make an identity of.</typeparam>
		/// <returns>A new instance of the type as an identity.</returns>
		template<typename T>
		constexpr T identity()
		{
			return glm::identity<T>();
		}

		template<>
		constexpr Float4 identity()
		{
			return Float4(0.0f, 0.0f, 0.0f, 0.0f);
		}

		template<>
		constexpr Float3 identity()
		{
			return Float3(0.0f, 0.0f, 0.0f);
		}

		template<>
		constexpr Float2 identity()
		{
			return Float2(0.0f, 0.0f);
		}

		template<>
		constexpr Float identity()
		{
			return 0.0f;
		}

		/// <summary>
		/// Converts the given Quaternion to a 3D matrix.
		/// </summary>
		/// <param name="value">The Quaternion.</param>
		/// <returns>The matrix.</returns>
		Matrix4 to_matrix(Quaternion const& value);

		/// <summary>
		/// Translates the given matrix by the given value.
		/// </summary>
		/// <param name="matrix">The matrix to translate.</param>
		/// <param name="value">The amount to translate by.</param>
		/// <returns>A copy of the given Matrix, tranlated.</returns>
		Matrix4 translate(Matrix4 const& matrix, Float3 const value);

		/// <summary>
		/// Scales the given matrix by the given value.
		/// </summary>
		/// <param name="matrix">The matrix to scale.</param>
		/// <param name="value">The amount to scale by.</param>
		/// <returns>A copy of the given Matrix, scaled.</returns>
		Matrix4 scale(Matrix4 const& matrix, Float3 const value);

		/// <summary>
		/// Rotates the given matrix by the given angle around the given axis.
		/// </summary>
		/// <param name="matrix">The Matrix to rotate.</param>
		/// <param name="angle">The angle to rotate by.</param>
		/// <param name="axis">The axis to rotate on.</param>
		/// <returns>A copy of the given Matrix, rotated.</returns>
		Matrix4 rotate(Matrix4 const& matrix, Float const angle, Float3 const& axis);

		/// <summary>
		/// Rotates the given matrix by the given Quaternion.
		/// </summary>
		/// <param name="matrix">The Matrix to rotate.</param>
		/// <param name="value">The Quaternion to rotate by.</param>
		/// <returns>A copy of the given Matrix, rotated.</returns>
		Matrix4 rotate(Matrix4 const& matrix, Quaternion const& value);

		/// <summary>
		/// Gets the position from this 3D matrix.
		/// </summary>
		/// <param name="value">The matrix.</param>
		/// <returns>The position.</returns>
		Float3 extract_position(Matrix4 const& value);

		/// <summary>
		/// Gets the scale from this 3D matrix.
		/// </summary>
		/// <param name="value">The matrix.</param>
		/// <returns>The scale.</returns>
		Float3 extract_scale(Matrix4 const& value);

		/// <summary>
		/// Gets the rotation from this 3D matrix.
		/// </summary>
		/// <param name="value">The matrix.</param>
		/// <param name="scale">The scale of the matrix.</param>
		/// <returns>The rotation.</returns>
		Quaternion extract_rotation(Matrix4 const& value, Float3 const& scale);

		/// <summary>
		/// Gets the rotation from this 3D matrix.
		/// </summary>
		/// <param name="value">The matrix.</param>
		/// <returns>The rotation.</returns>
		Quaternion extract_rotation(Matrix4 const& value);

#pragma endregion

#pragma region Random

        /// <summary>
        /// Returns a random Float in the range [min, max).
        /// </summary>
        /// <param name="min">The minimum value (inclusive).</param>
        /// <param name="max">The maximum value (exclusive).</param>
        /// <returns>A random Float in the given range.</returns>
        Float random(Float const min, Float const max);

		/// <summary>
		/// Returns a random Float in the range [0.0, 1.0).
		/// </summary>
		/// <returns>A random Float.</returns>
		Float random_float();

		/// <summary>
		/// Returns a random Int in the range [min, max).
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (exclusive).</param>
		/// <returns>A random Int in the given range.</returns>
		Int random(Int const min, Int const max);

		/// <summary>
		/// Returns a random Int in the range [INT_MIN, INT_MAX].
		/// </summary>
		/// <returns>A random Int.</returns>
		Int random_int();

		/// <summary>
		/// Returns a random UInt in the range [min, max).
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (exclusive).</param>
		/// <returns>A random UInt in the given range.</returns>
		UInt random(UInt const min, UInt const max);

		/// <summary>
		/// Returns a random UInt in the range [UINT_MIN, UINT_MAX].
		/// </summary>
		/// <returns>A random UInt.</returns>
		UInt random_uint();

		/// <summary>
		/// Returns a random Double in the range [min, max).
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (exclusive).</param>
		/// <returns>A random Double in the given range.</returns>
		Double random(Double const min, Double const max);

		/// <summary>
		/// Returns a random Double in the range [0.0, 1.0).
		/// </summary>
		/// <returns>A random Double.</returns>
		Double random_double();

		/// <summary>
		/// Returns a random Long in the range [min, max).
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (exclusive).</param>
		/// <returns>A random Long in the given range.</returns>
		Long random(Long const min, Long const max);

		/// <summary>
		/// Returns a random Long in the range [LONG_MIN, LONG_MAX].
		/// </summary>
		/// <returns>A random Long.</returns>
		Long random_long();

		/// <summary>
		/// Returns a random ULong in the range [min, max).
		/// </summary>
		/// <param name="min">The minimum value (inclusive).</param>
		/// <param name="max">The maximum value (exclusive).</param>
		/// <returns>A random ULong in the given range.</returns>
		ULong random(ULong const min, ULong const max);

		/// <summary>
		/// Returns a random ULong in the range [ULONG_MIN, ULONG_MAX].
		/// </summary>
		/// <returns>A random ULong.</returns>
		ULong random_ulong();

#pragma endregion
	}

#pragma endregion
}

namespace std {
	template<>
	struct hash<Minty::Int2> {
		std::size_t operator()(Minty::Int2 const& v) const noexcept {
			std::size_t h1 = std::hash<Minty::Int>{}(v.x);
			std::size_t h2 = std::hash<Minty::Int>{}(v.y);
			return h1 ^ (h2 << 1);
		}
	};
	template<>
	struct hash<Minty::Int3> {
		std::size_t operator()(Minty::Int3 const& v) const noexcept {
			std::size_t h1 = std::hash<Minty::Int>{}(v.x);
			std::size_t h2 = std::hash<Minty::Int>{}(v.y);
			std::size_t h3 = std::hash<Minty::Int>{}(v.z);
			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};
	template<>
	struct hash<Minty::Int4> {
		std::size_t operator()(Minty::Int4 const& v) const noexcept {
			std::size_t h1 = std::hash<Minty::Int>{}(v.x);
			std::size_t h2 = std::hash<Minty::Int>{}(v.y);
			std::size_t h3 = std::hash<Minty::Int>{}(v.z);
			std::size_t h4 = std::hash<Minty::Int>{}(v.w);
			return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
		}
	};
	template<>
	struct hash<Minty::UInt2> {
		std::size_t operator()(Minty::UInt2 const& v) const noexcept {
			std::size_t h1 = std::hash<Minty::UInt>{}(v.x);
			std::size_t h2 = std::hash<Minty::UInt>{}(v.y);
			return h1 ^ (h2 << 1);
		}
	};
	template<>
	struct hash<Minty::UInt3> {
		std::size_t operator()(Minty::UInt3 const& v) const noexcept {
			std::size_t h1 = std::hash<Minty::UInt>{}(v.x);
			std::size_t h2 = std::hash<Minty::UInt>{}(v.y);
			std::size_t h3 = std::hash<Minty::UInt>{}(v.z);
			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};
	template<>
	struct hash<Minty::UInt4> {
		std::size_t operator()(Minty::UInt4 const& v) const noexcept {
			std::size_t h1 = std::hash<Minty::UInt>{}(v.x);
			std::size_t h2 = std::hash<Minty::UInt>{}(v.y);
			std::size_t h3 = std::hash<Minty::UInt>{}(v.z);
			std::size_t h4 = std::hash<Minty::UInt>{}(v.w);
			return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
		}
	};
	template<>
	struct hash<Minty::Float2> {
		std::size_t operator()(Minty::Float2 const& v) const noexcept {
			std::size_t h1 = std::hash<Minty::Float>{}(v.x);
			std::size_t h2 = std::hash<Minty::Float>{}(v.y);
			return h1 ^ (h2 << 1);
		}
	};
	template<>
	struct hash<Minty::Float3> {
		std::size_t operator()(Minty::Float3 const& v) const noexcept {
			std::size_t h1 = std::hash<Minty::Float>{}(v.x);
			std::size_t h2 = std::hash<Minty::Float>{}(v.y);
			std::size_t h3 = std::hash<Minty::Float>{}(v.z);
			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};
	template<>
	struct hash<Minty::Float4> {
		std::size_t operator()(Minty::Float4 const& v) const noexcept {
			std::size_t h1 = std::hash<Minty::Float>{}(v.x);
			std::size_t h2 = std::hash<Minty::Float>{}(v.y);
			std::size_t h3 = std::hash<Minty::Float>{}(v.z);
			std::size_t h4 = std::hash<Minty::Float>{}(v.w);
			return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
		}
	};
}