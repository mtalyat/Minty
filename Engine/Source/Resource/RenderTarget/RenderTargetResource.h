#pragma once

/**
 * @file RenderTargetResource.h
 * @brief Header file for the RenderTargetResource struct.
 * @author Mitchell Talyat
 */

#include "Core/Data/Vector.h"
#include "Core/Serialize/Serializer.h"
#include "Resource/Type/Handle.h"

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