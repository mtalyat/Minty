#ifndef MINTY_RENDER_LOADOPERATION_H
#define MINTY_RENDER_LOADOPERATION_H

/**
 * @file LoadOperation.h
 * @brief Header file defining the LoadOperation enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

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

	String to_string(LoadOperation const obj);
	LoadOperation parse_to_load_operation(String const& string);
	Bool parse_try_load_operation(String const& string, LoadOperation& value);
	template<>
	inline LoadOperation parse_to<LoadOperation>(String const& string) { return parse_to_load_operation(string); }
	template<>
	inline Bool parse_try<LoadOperation>(String const& string, LoadOperation& value) { return parse_try_load_operation(string, value); }
}

#endif // MINTY_RENDER_LOADOPERATION_H