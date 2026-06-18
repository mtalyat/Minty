#pragma once

/**
 * @file PipelineAttribute.h
 * @brief Header file defining the PipelineAttribute struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Meta/Type.h"

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
