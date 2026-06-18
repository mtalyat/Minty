#pragma once

/**
 * @file Vulkan_Material.h
 * @brief Header file defining the Vulkan material data.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.h"
#include "Core/Data/Vector.h"
#include "Render/Type/Handle.h"

namespace Minty
{
    struct Vulkan_MaterialData
    {
        PipelineHandle pipelineHandle = INVALID_HANDLE;
        Vector<VkDescriptorSet> descriptorSets = {};
    };
}