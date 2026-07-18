#pragma once

/**
 * @file WindowManagerInfo.h
 * @brief Header file defining the WindowManagerInfo struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Event/Type/EventCallback.hpp"

namespace Minty
{
    /**
     * @brief The arguments for creating a WindowManager.
     */
    struct WindowManagerInfo
    {
        /**
         * @brief The callback function for window events.
         */
        EventCallback eventCallback = nullptr;
    };
}