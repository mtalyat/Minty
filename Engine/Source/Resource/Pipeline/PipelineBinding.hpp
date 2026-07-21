#pragma once

/**
 * @file PipelineBinding.hpp
 * @brief Header file defining the PipelineBinding struct.
 * @author Mitchell Talyat
 */

#include "PipelineInputRate.hpp"
#include "PipelineAttribute.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Data/Vector.hpp"

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
