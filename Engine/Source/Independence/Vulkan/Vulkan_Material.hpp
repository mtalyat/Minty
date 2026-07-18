#pragma once

/**
 * @file Vulkan_Material.h
 * @brief Header file defining the Vulkan material data.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Data/Array.hpp"
#include "Render/Type/Handle.hpp"
#include "Vulkan_Pipeline.hpp"

namespace Minty
{
    struct Vulkan_MaterialData
    {
        PipelineHandle pipelineHandle = INVALID_HANDLE;
        Vector<Array<VkDescriptorSet, FRAMES_PER_FLIGHT>> descriptorSets = {};
        Map<String, Vulkan_BufferInputStateData> inputs = {};
    };
}