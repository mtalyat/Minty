#pragma once

#include "Library/Vulkan/Vulkan.hpp"

namespace Minty
{
    struct Vulkan_ShaderData
    {
        VkShaderModule module = VK_NULL_HANDLE;
        VkShaderStageFlags stageFlags = 0;
        String entryPoint = {};
    };
}