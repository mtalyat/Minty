#ifndef MINTY_RENDER_SHADERFRONTFACE_H
#define MINTY_RENDER_SHADERFRONTFACE_H

/**
 * @file ShaderFrontFace.h
 * @brief Header file defining the ShaderFrontFace enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

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

	String to_string(ShaderFrontFace const obj);
	ShaderFrontFace parse_to_shader_front_face(String const& string);
	Bool parse_try_shader_front_face(String const& string, ShaderFrontFace& value);
	template<>
	inline ShaderFrontFace parse_to<ShaderFrontFace>(StringView const string) { return parse_to_shader_front_face(string); }
	template<>
	inline Bool parse_try<ShaderFrontFace>(StringView const string, ShaderFrontFace& value) { return parse_try_shader_front_face(string, value); }
}

#endif // MINTY_RENDER_SHADERFRONTFACE_H