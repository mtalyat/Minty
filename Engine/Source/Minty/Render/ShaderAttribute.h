#ifndef MINTY_RENDER_SHADERATTRIBUTE_H
#define MINTY_RENDER_SHADERATTRIBUTE_H

/**
 * @file ShaderAttribute.h
 * @brief Header file defining the ShaderAttribute struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Type.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	/**
	 * @brief Information for an attribute in a Shader.
	 */
	struct ShaderAttribute
	{
		/**
		 * @brief The location of the attribute in the shader.
		 */
		UInt location = 0;

		/**
		 * @brief The type of the attribute.
		 */
		Type type = Type::Undefined;
	};
}

#endif // MINTY_RENDER_SHADERATTRIBUTE_H