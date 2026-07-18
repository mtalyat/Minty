#pragma once

#include "Library/Vulkan/Vulkan.hpp"
#include "Core/Data/Vector.hpp"
#include "Render/Type/Handle.hpp"

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