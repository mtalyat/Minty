#pragma once

#include "Library/Vulkan/Vulkan.h"
#include "Core/Data/Vector.h"

namespace Minty
{
    struct Vulkan_RenderTargetData
    {
        Vector<VkFramebuffer> framebuffers = {};
    };
}