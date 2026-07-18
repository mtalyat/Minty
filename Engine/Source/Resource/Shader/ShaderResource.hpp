#pragma once

/**
 * @file ShaderModule.h
 * @brief Header file defining the ShaderModule class and ShaderModuleInfo struct.
 * @author Mitchell Talyat
 */

#include "Resource/Constant/Resource.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Resource/Shader/ShaderStage.hpp"

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
