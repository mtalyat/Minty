#pragma once

/**
 * @file StoreOperation.h
 * @brief Header file defining the StoreOperation enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.h"
#include "Core/Type/Enum.h"

namespace Minty
{
	/**
	 * @brief The store operation.
	 */
	enum class StoreOperationEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined,

		/**
		 * @brief Does nothing with the current data.
		 */
		DontCare,

		/**
		 * @brief Stores the current data.
		 */
		Store,

		Count,
	};

	MINTY_ENABLE_ENUM_OPERATORS(StoreOperationEnum)

	struct StoreOperation
	{
		StoreOperationEnum value; 

		constexpr StoreOperation() : value(StoreOperationEnum::Undefined) {}
		constexpr StoreOperation(StoreOperationEnum const value) : value(value) {}
		constexpr operator StoreOperationEnum() const { return value; }
	};
	
	template<>
	struct Parser<StoreOperationEnum>
	{
		static Bool parse(StringView const str, StoreOperationEnum& value);
		static String to_string(StoreOperationEnum const& obj);
	};

	template<>
	struct Parser<StoreOperation>
	{
		inline static Bool parse(StringView const str, StoreOperation& value) { return Parser<StoreOperationEnum>::parse(str, value.value); }
		inline static String to_string(StoreOperation const& obj) { return Parser<StoreOperationEnum>::to_string(obj.value); }
	};
}
