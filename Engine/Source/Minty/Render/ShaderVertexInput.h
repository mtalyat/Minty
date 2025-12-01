#ifndef MINTY_RENDER_SHADERVERTEXINPUT_H
#define MINTY_RENDER_SHADERVERTEXINPUT_H

/**
 * @file ShaderVertexInput.h
 * @brief Header file defining the ShaderVertexInput struct.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Vector.h"
#include "Minty/Render/ShaderBinding.h"

namespace Minty
{
	/**
	 * @brief Information for a vertex input in a Shader.
	 */
	struct ShaderVertexInput
	{
		/**
		 * @brief A collection of bindings within this vertex input.
		 */
		Vector<ShaderBinding> bindings;
	};
}

#endif // MINTY_RENDER_SHADERVERTEXINPUT_H