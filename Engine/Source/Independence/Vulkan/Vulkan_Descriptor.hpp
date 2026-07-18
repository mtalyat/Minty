#pragma once

#include "Library/Vulkan/Vulkan.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Data/String.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Data/Span.hpp"

namespace Minty
{
    struct Vulkan_DescriptorAllocatorData
    {
        VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
        UInt poolSize = 0;
        UInt maxPoolSize = 0;
    };

    struct Vulkan_DescriptorSetLayoutData
    {
        VkDescriptorSetLayout layout = VK_NULL_HANDLE;
        Vulkan_DescriptorAllocatorData allocatorData;
        UInt id = 0;
        Map<String, VkDescriptorSetLayoutBinding> bindings; // variables/objects in the descriptor set, mapped by name for lookup when setting descriptor data
    };
}