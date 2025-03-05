#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	template<typename T1, typename T2>
	class Pair
	{
#pragma region Variables

	public:
		T1 first;
		T2 second;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a pair using the given values.
		/// </summary>
		/// <param name="first">The first value.</param>
		/// <param name="second">The second value.</param>
		constexpr Pair(T1 const& first, T2 const& second)
			: first(first)
			, second(second)
		{}	

		/// <summary>
		/// Creates a pair using the given values.
		/// </summary>
		/// <param name="first">The first value.</param>
		/// <param name="second">The second value.</param>
		constexpr Pair(T1 const& first, T2&& second)
			: first(first)
			, second(std::move(second))
		{}

		/// <summary>
		/// Creates a pair using the given values.
		/// </summary>
		/// <param name="first">The first value.</param>
		/// <param name="second">The second value.</param>
		constexpr Pair(T1&& first, T2 const& second)
			: first(std::move(first))
			, second(second)
		{}

		/// <summary>
		/// Creates a pair using the given values.
		/// </summary>
		/// <param name="first">The first value.</param>
		/// <param name="second">The second value.</param>
		constexpr Pair(T1&& first, T2&& second)
			: first(std::move(first))
			, second(std::move(second))
		{}

		constexpr Pair(Pair const& other)
			: first(other.first)
			, second(other.second)
		{}

		constexpr Pair(Pair&& other) noexcept
			: first(std::move(other.first))
			, second(std::move(other.second))
		{}

		constexpr ~Pair()
		{}

#pragma endregion

#pragma region Operators

	public:
		constexpr Pair& operator=(Pair const& other)
		{
			first = other.first;
			second = other.second;
			return *this;
		}

		constexpr Pair& operator=(Pair&& other) noexcept
		{
			first = std::move(other.first);
			second = std::move(other.second);
			return *this;
		}

		constexpr Bool operator==(Pair const& other) const
		{
			return first == other.first && second == other.second;
		}

		constexpr Bool operator!=(Pair const& other) const
		{
			return first != other.first || second != other.second;
		}

		constexpr Bool operator<(Pair const& other) const
		{
			return first < other.first || (first == other.first && second < other.second);
		}

		constexpr Bool operator>(Pair const& other) const
		{
			return (other < *this);
		}

		constexpr Bool operator<=(Pair const& other) const
		{
			return !(other < *this);
		}

		constexpr Bool operator>=(Pair const& other) const
		{
			return !(*this < other);
		}

#pragma endregion
	};
}