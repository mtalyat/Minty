#ifndef MINTY_RENDER_SHADERFRONTFACE_H
#define MINTY_RENDER_SHADERFRONTFACE_H

/**
 * @file ShaderFrontFace.h
 * @brief Header file defining the ShaderFrontFace enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines which side of the polygon is the front.
	 */
	enum class ShaderFrontFace
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief The front face is determined by the counter-clockwise winding order.
		 */
		CounterClockwise = 1,

		/**
		 * @brief The front face is determined by the clockwise winding order.
		 */
		Clockwise = 2,
	};

	template<>
	struct Parser<ShaderFrontFace>
	{
		static Bool parse(StringView const str, ShaderFrontFace& value);
		static String to_string(ShaderFrontFace const& obj);
	};
}

#endif // MINTY_RENDER_SHADERFRONTFACE_H