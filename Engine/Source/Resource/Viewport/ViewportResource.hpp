#pragma once

/**
 * @file ViewportResource.hpp
 * @brief Header file for the ViewportResource struct.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Serializer.hpp"
#include "Core/Type/Float2.hpp"
#include "Core/Type/Int2.hpp"
#include "Core/Type/UInt2.hpp"

namespace Minty
{
    struct ViewportResource
    {
        Bool dynamic = false;
        Float2 viewPosition = { 0.0f, 0.0f };
        Float2 viewSize = { 0.0f, 0.0f };
        Float minDepth = 0.0f;
        Float maxDepth = 1.0f;
        Int2 scissorPosition = { 0, 0 };
        UInt2 scissorSize = { 0, 0 };
    };

    template<>
    struct Serializer<ViewportResource>
    {
        static Bool serialize(Writer &writer, ViewportResource const &value);
        static Bool deserialize(Reader &reader, ViewportResource &value);
    };
}