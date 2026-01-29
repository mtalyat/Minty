#ifndef MINTY_RENDER_DEPTHMODE_H
#define MINTY_RENDER_DEPTHMODE_H

/**
 * @file DepthMode.h
 * @brief Header file defining the DepthMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines how depth buffering is handled.
	 */
	enum class DepthMode
	{
		/**
		 * @brief Do not use depth buffer.
		 */
		None,

		/**
		 * @brief Write to the depth buffer.
		 */
		Write,

		/**
		 * @brief Test the depth buffer.
		 */
		Test
	};
	
	template<>
	struct Parser<DepthMode>
	{
		static Bool parse(StringView const str, DepthMode& value);
		static String to_string(DepthMode const& obj);
	};
}

#endif // MINTY_RENDER_DEPTHMODE_H