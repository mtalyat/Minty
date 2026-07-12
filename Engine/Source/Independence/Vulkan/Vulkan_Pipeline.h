#pragma once

#include "Vulkan_Descriptor.h"
#include "Library/Vulkan/Vulkan.h"
#include "Platform/Type/Primitive.h"
#include "Core/Data/String.h"
#include "Core/Data/Vector.h"
#include "Core/Data/Map.h"
#include "Core/Data/Object.h"
#include "Core/Data/Array.h"
#include "Render/Type/Handle.h"
#include "Render/Constant/Render.h"
#include "Resource/Pipeline/PipelineInputType.h"

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

    struct Vulkan_BufferInputStateData
    {
        UInt set = 0;
        UInt binding = 0;
        PipelineInputType type = PipelineInputTypeEnum::Undefined;
        Object object = {};
        Array<BufferHandle, FRAMES_PER_FLIGHT> buffers = {};
    };

    struct Vulkan_PipelineData
    {
        Vulkan_PipelineLayoutHandle layoutHandle = INVALID_HANDLE;
        VkPipeline pipeline = VK_NULL_HANDLE;
        Vector<Array<VkDescriptorSet, FRAMES_PER_FLIGHT>> descriptorSets;
        Map<String, Vulkan_BufferInputStateData> globalInputs;
        Map<String, Vulkan_BufferInputStateData> materialInputTemplates;
        Map<String, Vulkan_BufferInputStateData> objectInputs;
    };
    
    struct Vulkan_PipelineLayoutData
    {
        VkPipelineLayout layout = VK_NULL_HANDLE;
        Vector<Vulkan_DescriptorSetLayoutData> descriptorSetLayouts;
        Vector<Vulkan_PushConstantData> pushConstants;
    };
}