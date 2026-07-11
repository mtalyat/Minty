#pragma once

#include "Library/Vulkan/Vulkan.h"
#include "Core/Data/Vector.h"
#include "Render/Type/Handle.h"

namespace Minty
{
    struct Vulkan_RenderTargetData
    {
        SurfaceHandle surface = INVALID_HANDLE;
        Vector<TextureHandle> images = {};
    };
}