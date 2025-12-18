#ifndef MINTY_RENDER_SHADERCULLMODE_H
#define MINTY_RENDER_SHADERCULLMODE_H

/**
 * @file ShaderCullMode.h
 * @brief Header file defining the ShaderCullMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief Determines how the Shader culls faces.
	 */
	enum class ShaderCullMode
	{
		Undefined = 0,

		/**
		 * @brief There is no culling.
		 */
		None = 1,

		/**
		 * @brief The front side of a face is culled.
		 */
		Front = 2,

		/**
		 * @brief The back side of a face is culled.
		 */
		Back = 3,
		
		/**
		 * @brief Both sides of a face are culled.
		 */
		Both = 4,
	};

	String to_string(ShaderCullMode const obj);
	ShaderCullMode parse_to_shader_cull_mode(String const& string);
	Bool parse_try_shader_cull_mode(String const& string, ShaderCullMode& value);
	template<>
	inline ShaderCullMode parse_to<ShaderCullMode>(StringView const string) { return parse_to_shader_cull_mode(string); }
	template<>
	inline Bool parse_try<ShaderCullMode>(StringView const string, ShaderCullMode& value) { return parse_try_shader_cull_mode(string, value); }
}

#endif // MINTY_RENDER_SHADERCULLMODE_H