#pragma once

#include "Library/Vulkan/Vulkan.h"
#include "Core/Data/Vector.h"
#include "Render/Type/Handle.h"

namespace Minty
{
    struct Vulkan_RenderPassData
    {
        VkRenderPass renderPass = VK_NULL_HANDLE;
        RenderTargetHandle renderTarget = INVALID_HANDLE;
        ViewportHandle viewport = INVALID_HANDLE;
        VkClearColorValue clearColor{};
        float clearDepth = 1.0f;
        uint32_t clearStencil = 0;
        Vector<VkFramebuffer> framebuffers = {};
    };
}