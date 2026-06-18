#pragma once

/**
 * @file PipelineBinding.h
 * @brief Header file defining the PipelineBinding struct.
 * @author Mitchell Talyat
 */

#include "PipelineInputRate.h"
#include "PipelineAttribute.h"
#include "Platform/Type/Primitive.h"
#include "Core/Data/Vector.h"

namespace Minty
{
	/**
	 * @brief Information for a binding in a Shader.
	 */
	struct PipelineBinding
	{
		/**
		 * @brief The binding index of this binding in the Shader.
		 */
		UInt binding = 0;

		/**
		 * @brief The input rate of the binding.
		 */
		PipelineInputRateEnum inputRate = PipelineInputRateEnum::Undefined;

		/**
		 * @brief The attributes within this binding.
		 */
		Vector<PipelineAttribute> attributes = {};
	};
}
