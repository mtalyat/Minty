#ifndef MINTY_RENDER_SHADERSTAGE_H
#define MINTY_RENDER_SHADERSTAGE_H

/**
 * @file ShaderStage.h
 * @brief Header file defining the ShaderStage enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief Determines the stage of the shader.
	 */
	enum class ShaderStage
	{
		/**
		 * @brief Invalid.
		 */
		Undefined,
		
		/**
		 * @brief The vertex shader stage.
		 */
		Vertex,

		/**
		 * @brief The fragment shader stage.
		 */
		Fragment
	};

	String to_string(ShaderStage const obj);
	ShaderStage parse_to_shader_stage(String const& string);
	Bool parse_try_shader_stage(String const& string, ShaderStage& value);
	template<>
	inline ShaderStage parse_to<ShaderStage>(StringView const string) { return parse_to_shader_stage(string); }
	template<>
	inline Bool parse_try<ShaderStage>(StringView const string, ShaderStage& value) { return parse_try_shader_stage(string, value); }
}

#endif // MINTY_RENDER_SHADERSTAGE_H