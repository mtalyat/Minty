#pragma once

/**
 * @file GeometryResource.h
 * @brief Header file defining the GeometryResource class and GeometryInfo struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Serialize/Serializer.h"
#include "Core/Data/ListContainer.h"

namespace Minty
{
    struct GeometryResource
    {
        ListContainer vertexContainer;
        ListContainer indexContainer;
    };

    template<>
    struct Serializer<GeometryResource>
    {
        static Bool serialize(Writer& writer, GeometryResource const& value);
        static Bool deserialize(Reader& reader, GeometryResource& value);
    };
}