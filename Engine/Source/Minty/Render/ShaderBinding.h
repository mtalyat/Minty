#ifndef MINTY_RENDER_SHADERBINDING_H
#define MINTY_RENDER_SHADERBINDING_H

/**
 * @file ShaderBinding.h
 * @brief Header file defining the ShaderBinding struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Type.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/ShaderAttribute.h"
#include "Minty/Render/ShaderInputRate.h"

namespace Minty
{
	/**
	 * @brief Information for a binding in a Shader.
	 */
	struct ShaderBinding
	{
		/**
		 * @brief The binding index of this binding in the Shader.
		 */
		UInt binding = 0;

		/**
		 * @brief The input rate of the binding.
		 */
		ShaderInputRate inputRate = ShaderInputRate::Undefined;

		/**
		 * @brief The attributes within this binding.
		 */
		Vector<ShaderAttribute> attributes;
	};
}

#endif // MINTY_RENDER_SHADERBINDING_H