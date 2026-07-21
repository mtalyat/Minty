#pragma once

/**
 * @file PipelineAttribute.hpp
 * @brief Header file defining the PipelineAttribute struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Meta/Type.hpp"

namespace Minty
{
	/**
	 * @brief Information for an attribute in a Shader.
	 */
	struct PipelineAttribute
	{
		/**
		 * @brief The location of the attribute in the shader.
		 */
		UInt location = 0;

		/**
		 * @brief The type of the attribute.
		 */
		Type type = TypeEnum::Undefined;
	};
}
