#ifndef MINTY_RENDER_SHADERINPUTRATE_H
#define MINTY_RENDER_SHADERINPUTRATE_H

/**
 * @file ShaderInputRate.h
 * @brief Header file defining the ShaderInputRate enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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
	
	template<>
	struct Parser<ShaderInputRate>
	{
		static Bool parse(StringView const str, ShaderInputRate& value);
		static String to_string(ShaderInputRate const& obj);
	};
}

#endif // MINTY_RENDER_SHADERINPUTRATE_H