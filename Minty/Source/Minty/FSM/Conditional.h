#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// An equality condition.
	/// </summary>
	enum class Conditional
	{
		/// <summary>
		/// ==
		/// </summary>
		Equal,

		/// <summary>
		/// !=
		/// </summary>
		NotEqual,

		/// <summary>
		/// >
		/// </summary>
		GreaterThan,

		/// <summary>
		/// >=
		/// </summary>
		GreaterThanOrEqualTo,

		/// <summary>
		/// <
		/// </summary>
		LessThan,

		/// <summary>
		/// <=
		/// </summary>
		LessThanOrEqualTo,
	};

	template<Comparable T>
	Bool evaluate(T const& left, Conditional const conditional, T const& right)
	{
		switch (conditional)
		{
		case Conditional::Equal:
			return left == right;
		case Conditional::NotEqual:
			return left != right;
		case Conditional::GreaterThan:
			return left > right;
		case Conditional::GreaterThanOrEqualTo:
			return left >= right;
		case Conditional::LessThan:
			return left < right;
		case Conditional::LessThanOrEqualTo:
			return left <= right;
		}
		return false;
	}

	String to_string(Conditional const obj);
	Conditional parse_to_conditional(String const& string);
	Bool parse_try_conditional(String const& string, Conditional& value);
	template<>
	inline Conditional parse_to<Conditional>(String const& string) { return parse_to_conditional(string); }
	template<>
	inline Bool parse_try<Conditional>(String const& string, Conditional& value) { return parse_try_conditional(string, value); }
}