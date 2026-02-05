#ifndef MINTY_RENDER_STOREOPERATION_H
#define MINTY_RENDER_STOREOPERATION_H

/**
 * @file StoreOperation.h
 * @brief Header file defining the StoreOperation enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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
	
	template<>
	struct Parser<StoreOperation>
	{
		static Bool parse(StringView const str, StoreOperation& value);
		static String to_string(StoreOperation const& obj);
	};
}

#endif // MINTY_RENDER_STOREOPERATION_H