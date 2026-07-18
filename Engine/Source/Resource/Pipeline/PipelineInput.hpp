#pragma once

/**
 * @file PipelineInput.h
 * @brief Header file defining the PipelineInput struct.
 * @author Mitchell Talyat
 */

#include "PipelineInputType.hpp"
#include "Core/Data/String.hpp"
#include "Core/Data/Tuple.hpp"
#include "Core/Data/Variable.hpp"
#include "Core/Data/Vector.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Resource/Shader/ShaderStage.hpp"
#include "Core/Data/Object.hpp"

namespace Minty
{
	/**
	 * @brief Information for an input in a Shader.
	 */
	struct PipelineInput
	{
		/**
		 * @brief The name of this input.
		 */
		String name = "";

		/**
		 * @brief The type of the input.
		 */
		PipelineInputType type = PipelineInputTypeEnum::Undefined;

		/**
		 * @brief The stage of the Shader this input is used in.
		 */
		ShaderStage stage = ShaderStageEnum::Undefined;

		/**
		 * @brief The set of this input in the Shader.
		 */
		UInt set = 0;

		/**
		 * @brief The binding of this input in the Shader.
		 */
		UInt binding = 0;

		/**
		 * @brief The number of elements in this input. Should be 1 for non-array inputs.
		 */
		UInt count = 1;

		/**
		 * @brief The size of the input in bytes, for one element. Ex. For an array of 10 Floats, this would be sizeof(Float). Only use this for inputs that need a buffer (such as a uniform constant).
		 */
		Size size = 0;

		/**
		 * @brief The offset of the input in bytes.
		 */
		Size offset = 0;

		/**
		 * @brief When true, this input is optimized to be updated every frame.
		 */
		Bool frequent = false;

		/**
		 * @brief A collection of Variables that are within this input.
		 */
		Object object = {};
	};
}