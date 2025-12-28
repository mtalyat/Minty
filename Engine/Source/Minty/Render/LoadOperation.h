#ifndef MINTY_RENDER_LOADOPERATION_H
#define MINTY_RENDER_LOADOPERATION_H

/**
 * @file LoadOperation.h
 * @brief Header file defining the LoadOperation enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief The load operation.
	 */
	enum class LoadOperation
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
	};
	
	template<>
	struct Parser<LoadOperation>
	{
		static Bool parse(StringView const str, LoadOperation& value);
		static String to_string(LoadOperation const& obj);
	};
}

#endif // MINTY_RENDER_LOADOPERATION_H