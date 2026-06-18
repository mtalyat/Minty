#pragma once

/**
 * @file MaterialResource.h
 * @brief Header file defining the MaterialResource class and MaterialInfo struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Serialize/Serializer.h"
#include "Resource/Type/Handle.h"
#include "Core/Data/Cargo.h"

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
