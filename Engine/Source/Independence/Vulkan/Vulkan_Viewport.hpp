#pragma once

/**
 * @file Vulkan_Viewport.h
 * @brief Header file defining the Vulkan_Viewport class.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.hpp"

namespace Minty
{
    struct Vulkan_ViewportData
    {
        Bool dynamic = false;
        VkViewport viewport;
        VkRect2D scissor;
    };
}