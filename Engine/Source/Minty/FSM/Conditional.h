#ifndef MINTY_FSM_CONDITIONAL_H
#define MINTY_FSM_CONDITIONAL_H

/**
 * @file Conditional.h
 * @brief Header file for FSM Conditional enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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
	Bool evaluate_conditional(T const& left, Conditional const conditional, T const& right)
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

    template<>
    struct Parser<Conditional>
    {
        static Bool parse(StringView const str, Conditional &value);
        static String to_string(Conditional const &value);
    };
}

#endif // MINTY_FSM_CONDITIONAL_H