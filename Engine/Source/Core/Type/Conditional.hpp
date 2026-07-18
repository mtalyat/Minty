#pragma once

/**
 * @file Conditional.h
 * @brief Header file for FSM Conditional enum.
 * @author Mitchell Talyat
 */

#include "Comparable.hpp"
#include "Core/Serialize/Parser.hpp"

namespace Minty
{
	/**
	 * @brief An equality condition.
	 */
	enum class ConditionalEnum
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

		Count,
	};

	MINTY_ENABLE_ENUM_OPERATORS(ConditionalEnum)

	struct Conditional
	{
		ConditionalEnum type;

		constexpr Conditional() : type(ConditionalEnum::Equal) {}
		constexpr Conditional(ConditionalEnum t) : type(t) {}
		constexpr operator ConditionalEnum() const { return type; }

		template <Comparable T>
		constexpr Bool evaluate(T const &left, T const &right) const
		{
			switch (type)
			{
			case ConditionalEnum::Equal:
				return left == right;
			case ConditionalEnum::NotEqual:
				return left != right;
			case ConditionalEnum::GreaterThan:
				return left > right;
			case ConditionalEnum::GreaterThanOrEqual:
				return left >= right;
			case ConditionalEnum::LessThan:
				return left < right;
			case ConditionalEnum::LessThanOrEqual:
				return left <= right;
			}
			return false;
		}
	};

	template <>
	struct Parser<ConditionalEnum>
	{
		static Bool parse(StringView const str, ConditionalEnum &value);
		static String to_string(ConditionalEnum const &value);
	};

	template <>
	struct Parser<Conditional>
	{
		inline static Bool parse(StringView const str, Conditional &value) { return Parser<ConditionalEnum>::parse(str, value.type); }
		inline static String to_string(Conditional const &value) { return Parser<ConditionalEnum>::to_string(value.type); }
	};
}
