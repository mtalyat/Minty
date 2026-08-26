#pragma once

/**
 * @file Vulkan_Viewport.hpp
 * @brief Header file defining the Vulkan_Viewport class.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.hpp"

namespace Minty
{
    struct Vulkan_ViewportData
    {
        Bool dynamic = false;
        Float2 normalizedPosition = { 0.0f, 0.0f };
        Float2 normalizedSize = { 1.0f, 1.0f };
        Float2 normalizedScissorPosition = { 0.0f, 0.0f };
        Float2 normalizedScissorSize = { 1.0f, 1.0f };
        VkViewport viewport{};
        VkRect2D scissor{};
    };
}