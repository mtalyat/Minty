#pragma once

/**
 * @file MaterialResource.h
 * @brief Header file defining the MaterialResource class and MaterialInfo struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Resource/Type/Handle.hpp"
#include "Core/Data/Cargo.hpp"

namespace Minty
{
	struct MaterialResource
	{
		PipelineResourceHandle pipeline;
		Cargo cargo;
		UInt stencil;
	};

	template<>
	struct Serializer<MaterialResource>
	{
        static Bool serialize(Writer& writer, MaterialResource const& value);
        static Bool deserialize(Reader& reader, MaterialResource& value);
	};
}
