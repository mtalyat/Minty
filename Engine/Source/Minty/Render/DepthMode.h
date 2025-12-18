#ifndef MINTY_RENDER_DEPTHMODE_H
#define MINTY_RENDER_DEPTHMODE_H

/**
 * @file DepthMode.h
 * @brief Header file defining the DepthMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

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

	String to_string(DepthMode const obj);
	DepthMode parse_to_depth_mode(String const& string);
	Bool parse_try_depth_mode(String const& string, DepthMode& value);
	template<>
	inline DepthMode parse_to<DepthMode>(StringView const string) { return parse_to_depth_mode(string); }
	template<>
	inline Bool parse_try<DepthMode>(StringView const string, DepthMode& value) { return parse_try_depth_mode(string, value); }
}

#endif // MINTY_RENDER_DEPTHMODE_H