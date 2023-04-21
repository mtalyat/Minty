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
	struct Pair
		: public Object
	{
		T first;
		U second;

		/// <summary>
		/// Creates an empty Pair.
		/// </summary>
		Pair()
			: first(), second()
		{}

		/// <summary>
		/// Creates a pair using the two given objects.
		/// </summary>
		/// <param name="one">The first object.</param>
		/// <param name="two">The second object.</param>
		Pair(T one, U two)
			: first(one), second(two)
		{}

		// copy constructor
		Pair(Pair<T, U> const& other)
			: first(other.first), second(other.second)
		{}

		// assignment operator
		Pair<T, U>& operator=(Pair<T, U> const& other)
		{
			first = other.first;
			second = other.second;

			return *this;
		}

		// equals operator
		bool operator ==(const Pair<T, U>& other) const
		{
			return first == other.first && second == other.second;
		}
	};
}