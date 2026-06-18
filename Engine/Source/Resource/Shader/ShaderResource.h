#pragma once

/**
 * @file ShaderModule.h
 * @brief Header file defining the ShaderModule class and ShaderModuleInfo struct.
 * @author Mitchell Talyat
 */

#include "Resource/Constant/Resource.h"
#include "Core/Data/Vector.h"
#include "Core/Serialize/Serializer.h"
#include "Resource/Shader/ShaderStage.h"

namespace Minty
{
	/**
	 * @brief Represents a Shader program.
	 */
	struct ShaderResource
	{
		Vector<Byte> data = {};
		ShaderStage stage = ShaderStageEnum::Undefined;
		String entryPoint = DEFAULT_ENTRY_POINT;
	};

	template<>
	struct Serializer<ShaderResource>
	{
		static Bool serialize(Writer &writer, ShaderResource const &value);
		static Bool deserialize(Reader &reader, ShaderResource &value);
	};
}
