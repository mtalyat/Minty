#pragma once

/**
 * @file RenderManagerInfo.h
 * @brief Header file for the RenderManager class, containing type definitions and forward declarations.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Window/Type/Handle.h"

namespace Minty
{
    struct RenderManagerInfo
    {
        /**
         * @brief The window to render to.
         * @note If INVALID_HANDLE, the RenderManager will use the main window from the WindowManager.
         */
        WindowHandle window = INVALID_HANDLE;
    };
}