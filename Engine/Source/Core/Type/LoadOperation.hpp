#pragma once

/**
 * @file LoadOperation.hpp
 * @brief Header file defining the LoadOperation enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
	/**
	 * @brief The load operation.
	 */
	enum class LoadOperationEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined,

		/**
		 * @brief Do nothing with the previous data.
		 */
		DontCare,

		/**
		 * @brief Loads the previous data.
		 */
		Load,

		/**
		 * @brief Clears the previous data.
		 */
		Clear,

		Count,
	};

	MINTY_ENABLE_ENUM_OPERATORS(LoadOperationEnum)

	struct LoadOperation
	{
		LoadOperationEnum value; 

		constexpr LoadOperation() : value(LoadOperationEnum::Undefined) {}
		constexpr LoadOperation(LoadOperationEnum const value) : value(value) {}
		constexpr operator LoadOperationEnum() const { return value; }
	};
	
	template<>
	struct Parser<LoadOperationEnum>
	{
		static Bool parse(StringView const str, LoadOperationEnum& value);
		static String to_string(LoadOperationEnum const& obj);
	};

	template<>
	struct Parser<LoadOperation>
	{
		inline static Bool parse(StringView const str, LoadOperation& value) { return Parser<LoadOperationEnum>::parse(str, value.value); }
		inline static String to_string(LoadOperation const& obj) { return Parser<LoadOperationEnum>::to_string(obj.value); }
	};
}
