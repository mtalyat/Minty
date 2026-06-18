#pragma once

#include "Vulkan_Descriptor.h"
#include "Library/Vulkan/Vulkan.h"
#include "Platform/Type/Primitive.h"
#include "Core/Data/String.h"
#include "Core/Data/Vector.h"
#include "Core/Data/Map.h"

namespace Minty
{
    struct Vulkan_PipelineLayoutData;
    using Vulkan_PipelineLayoutHandle = Handle<Vulkan_PipelineLayoutData>;

    struct Vulkan_PushConstantData
    {
        UInt offset = 0;
        UInt size = 0;
        VkShaderStageFlags stageFlags = 0;
    };

    struct Vulkan_PipelineData
    {
        Vulkan_PipelineLayoutHandle layoutHandle = INVALID_HANDLE;
        VkPipeline pipeline = VK_NULL_HANDLE;
    };
    
    struct Vulkan_PipelineLayoutData
    {
        VkPipelineLayout layout = VK_NULL_HANDLE;
        Vector<Vulkan_DescriptorSetLayoutData> descriptorSetLayouts;
        Vector<Vulkan_PushConstantData> pushConstants;
    };
}