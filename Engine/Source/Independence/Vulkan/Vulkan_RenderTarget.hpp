#pragma once

#include "Library/Vulkan/Vulkan.hpp"
#include "Core/Data/Vector.hpp"
#include "Render/Type/Handle.hpp"

namespace Minty
{
    struct Vulkan_RenderTargetData
    {
        SurfaceHandle surface = INVALID_HANDLE;
        Vector<TextureHandle> images = {};
    };
}