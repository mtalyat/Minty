#ifndef MINTY_RENDER_STENCILMODE_H
#define MINTY_RENDER_STENCILMODE_H

/**
 * @file StencilMode.h
 * @brief Header file defining the StencilMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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
	
	template<>
	struct Parser<StencilMode>
	{
		static Bool parse(StringView const str, StencilMode& value);
		static String to_string(StencilMode const& obj);
	};
}

#endif // MINTY_RENDER_STENCILMODE_H