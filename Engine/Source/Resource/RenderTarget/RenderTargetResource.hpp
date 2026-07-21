#pragma once

/**
 * @file RenderTargetResource.hpp
 * @brief Header file for the RenderTargetResource struct.
 * @author Mitchell Talyat
 */

#include "Core/Data/Vector.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Resource/Type/Handle.hpp"

namespace Minty
{
    struct RenderTargetResource
    {
        Vector<TextureResourceHandle> images = {};
    };

    template<>
    struct Serializer<RenderTargetResource>
    {
        static Bool serialize(Writer &writer, RenderTargetResource const &value);
        static Bool deserialize(Reader &reader, RenderTargetResource &value);
    };
}