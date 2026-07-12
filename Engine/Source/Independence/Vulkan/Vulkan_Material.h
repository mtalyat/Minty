#pragma once

/**
 * @file Vulkan_Material.h
 * @brief Header file defining the Vulkan material data.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.h"
#include "Core/Data/Vector.h"
#include "Core/Data/Map.h"
#include "Core/Data/Array.h"
#include "Render/Type/Handle.h"
#include "Vulkan_Pipeline.h"

namespace Minty
{
    struct Vulkan_MaterialData
    {
        PipelineHandle pipelineHandle = INVALID_HANDLE;
        Vector<Array<VkDescriptorSet, FRAMES_PER_FLIGHT>> descriptorSets = {};
        Map<String, Vulkan_BufferInputStateData> inputs = {};
    };
}