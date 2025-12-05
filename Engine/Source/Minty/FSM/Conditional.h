#ifndef MINTY_FSM_CONDITIONAL_H
#define MINTY_FSM_CONDITIONAL_H

/**
 * @file Conditional.h
 * @brief Header file for FSM Conditional enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/**
	 * @brief An equality condition.
	 */
	enum class Conditional
	{
		/**
		 * @brief ==
		 */
		Equal,

		/**
		 * @brief !=
		 */
		NotEqual,

		/**
		 * @brief >
		 */
		GreaterThan,

		/**
		 * @brief >=
		 */
		GreaterThanOrEqual,

		/**
		 * @brief <
		 */
		LessThan,

		/**
		 * @brief <=
		 */
		LessThanOrEqual,
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
		case Conditional::GreaterThanOrEqual:
			return left >= right;
		case Conditional::LessThan:
			return left < right;
		case Conditional::LessThanOrEqual:
			return left <= right;
		}
		return false;
	}

	String to_string(Conditional const obj);
	Conditional parse_to_conditional(String const& string);
	Bool parse_try_conditional(String const& string, Conditional& value);
	template<>
	inline Conditional parse_to<Conditional>(StringView const string) { return parse_to_conditional(string); }
	template<>
	inline Bool parse_try<Conditional>(StringView const string, Conditional& value) { return parse_try_conditional(string, value); }
}

#endif // MINTY_FSM_CONDITIONAL_H