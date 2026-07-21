#pragma once

/**
 * @file RenderManagerInfo.hpp
 * @brief Header file for the RenderManager class, containing type definitions and forward declarations.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    class Window;
    
    struct RenderManagerInfo
    {
        /**
         * @brief The window to render to.
         * @note If nullptr, the RenderManager will use the main window from the WindowManager.
         */
        Window* window = nullptr;
    };
}