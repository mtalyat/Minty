#pragma once

/**
 * @file MeshResource.h
 * @brief Header file defining the MeshResource class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Serialize/Serializer.h"
#include "Core/Data/ListContainer.h"

namespace Minty
{
    struct MeshResource
    {
        ListContainer vertexContainer;
        ListContainer indexContainer;
    };

    template<>
    struct Serializer<MeshResource>
    {
        static Bool serialize(Writer& writer, MeshResource const& value);
        static Bool deserialize(Reader& reader, MeshResource& value);
    };
}