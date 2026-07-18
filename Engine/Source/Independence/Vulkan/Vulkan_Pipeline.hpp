#pragma once

#include "Vulkan_Descriptor.hpp"
#include "Library/Vulkan/Vulkan.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Data/String.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Data/Object.hpp"
#include "Core/Data/Array.hpp"
#include "Render/Type/Handle.hpp"
#include "Render/Constant/Render.hpp"
#include "Resource/Pipeline/PipelineInputType.hpp"

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