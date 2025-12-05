#ifndef MINTY_RENDER_SHADERINPUTRATE_H
#define MINTY_RENDER_SHADERINPUTRATE_H

/**
 * @file ShaderInputRate.h
 * @brief Header file defining the ShaderInputRate enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief Determines what data is being inputted to the shader.
	 */
	enum class ShaderInputRate
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief The shader is using vertex data.
		 */
		Vertex = 1,

		/**
		 * @brief The shader is using instance data.
		 */
		Instance = 2
	};

	String to_string(ShaderInputRate const obj);
	ShaderInputRate parse_to_shader_input_rate(String const& string);
	Bool parse_try_shader_input_rate(String const& string, ShaderInputRate& value);
	template<>
	inline ShaderInputRate parse_to<ShaderInputRate>(StringView const string) { return parse_to_shader_input_rate(string); }
	template<>
	inline Bool parse_try<ShaderInputRate>(StringView const string, ShaderInputRate& value) { return parse_try_shader_input_rate(string, value); }
}

#endif // MINTY_RENDER_SHADERINPUTRATE_H