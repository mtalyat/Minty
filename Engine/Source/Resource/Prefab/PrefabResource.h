#pragma once

#include "Core/Data/Vector.h"
#include "Core/Serialize/Serializer.h"

namespace Minty
{
    /**
     * @brief A pre-fabricated ("prefab") Entity for a Scene.
     */
    struct PrefabResource
    {
        /**
         * @brief The raw data of the prefab.
         */
        Vector<Byte> data = {};
    };
    
    template<>
    struct Serializer<PrefabResource>
    {
        static Bool serialize(Writer& writer, PrefabResource const& value);
        static Bool deserialize(Reader& reader, PrefabResource& value);
    };
}