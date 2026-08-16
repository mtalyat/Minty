#pragma once

/**
 * @file FontResource.hpp
 * @brief Header file defining the FontResource class and FontInfo struct.
 * @author Mitchell Talyat
 */

#include "FontFlags.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Resource/Type/Handle.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Resource/Font/FontVariant.hpp"
	
namespace Minty
{
	struct FontResource
	{
		String name;
		Map<WUInt, FontVariant> variants;
	};
	
	template<>
	struct Serializer<FontResource>
	{
		static Bool serialize(Writer &writer, FontResource const &value);
		static Bool deserialize(Reader &reader, FontResource &value);
	};
}
