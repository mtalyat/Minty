#pragma once

#include "Library/Vulkan/Vulkan.h"
#include "Platform/Type/Primitive.h"
#include "Core/Data/String.h"
#include "Core/Data/Map.h"
#include "Core/Data/Vector.h"
#include "Core/Data/Span.h"

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