#pragma once

#include "Library/Vulkan/Vulkan.h"
#include "Core/Data/Vector.h"
#include "Render/Type/Handle.h"

namespace Minty
{
    struct Vulkan_RenderTargetData
    {
        Vector<TextureHandle> images = {};
    };
}