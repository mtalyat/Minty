#pragma once

#include "M_Object.h"

namespace minty
{
	/// <summary>
	/// Holds two of any two types.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="U"></typeparam>
	template<typename T, typename U = T>
	struct MINTY_API Pair
		: public Object
	{
		T first;
		U second;

		Pair()
			: first(), second()
		{}

		Pair(T one, U two)
			: first(one), second(two)
		{}

		Pair(Pair<T, U> const& other)
			: first(other.first), second(other.second)
		{}

		Pair<T, U>& operator=(Pair<T, U> const& other)
		{
			first = other.first;
			second = other.second;

			return *this;
		}

		bool operator ==(const Pair<T, U>& other) const
		{
			return first == other.first && second == other.second;
		}
	};
}