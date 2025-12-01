#ifndef MINTY_RENDER_STENCILMODE_H
#define MINTY_RENDER_STENCILMODE_H

/**
 * @file StencilMode.h
 * @brief Header file defining the StencilMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief Determines how stencil buffering is handled.
	 */
	enum class StencilMode
	{
		/**
		 * @brief Do not use stencil buffer.
		 */
		None,

		/**
		 * @brief Write to the stencil buffer.
		 */
		Write,

		/**
		 * @brief Test the stencil buffer.
		 */
		Test
	};

	String to_string(StencilMode const obj);
	StencilMode parse_to_stencil_mode(String const& string);
	Bool parse_try_stencil_mode(String const& string, StencilMode& value);
	template<>
	inline StencilMode parse_to<StencilMode>(String const& string) { return parse_to_stencil_mode(string); }
	template<>
	inline Bool parse_try<StencilMode>(String const& string, StencilMode& value) { return parse_try_stencil_mode(string, value); }
}

#endif // MINTY_RENDER_STENCILMODE_H