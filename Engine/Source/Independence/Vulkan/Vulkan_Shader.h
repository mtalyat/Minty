#pragma once

#include "Library/Vulkan/Vulkan.h"

namespace Minty
{
    struct Vulkan_ShaderData
    {
        VkShaderModule module = VK_NULL_HANDLE;
        VkShaderStageFlags stageFlags = 0;
        String entryPoint = {};
    };
}