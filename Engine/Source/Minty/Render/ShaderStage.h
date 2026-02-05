#ifndef MINTY_RENDER_SHADERSTAGE_H
#define MINTY_RENDER_SHADERSTAGE_H

/**
 * @file ShaderStage.h
 * @brief Header file defining the ShaderStage enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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
	
	template<>
	struct Parser<ShaderStage>
	{
		static Bool parse(StringView const str, ShaderStage& value);
		static String to_string(ShaderStage const& obj);
	};
}

#endif // MINTY_RENDER_SHADERSTAGE_H