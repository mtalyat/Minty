#ifndef MINTY_RENDER_STOREOPERATION_H
#define MINTY_RENDER_STOREOPERATION_H

/**
 * @file StoreOperation.h
 * @brief Header file defining the StoreOperation enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/**
	 * @brief The store operation.
	 */
	enum class StoreOperation
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
	};

	String to_string(StoreOperation const obj);
	StoreOperation parse_to_store_operation(String const& string);
	Bool parse_try_store_operation(String const& string, StoreOperation& value);
	template<>
	inline StoreOperation parse_to<StoreOperation>(String const& string) { return parse_to_store_operation(string); }
	template<>
	inline Bool parse_try<StoreOperation>(String const& string, StoreOperation& value) { return parse_try_store_operation(string, value); }
}

#endif // MINTY_RENDER_STOREOPERATION_H