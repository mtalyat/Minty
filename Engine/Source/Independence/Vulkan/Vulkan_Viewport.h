#pragma once

/**
 * @file Vulkan_Viewport.h
 * @brief Header file defining the Vulkan_Viewport class.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.h"

namespace Minty
{
    struct Vulkan_ViewportData
    {
        Bool dynamic = false;
        VkViewport viewport;
        VkRect2D scissor;
    };
}