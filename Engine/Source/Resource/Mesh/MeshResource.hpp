#pragma once

/**
 * @file MeshResource.hpp
 * @brief Header file defining the MeshResource struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Core/Data/ListContainer.hpp"

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