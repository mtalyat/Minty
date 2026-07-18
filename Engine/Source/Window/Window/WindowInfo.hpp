#pragma once

/**
 * @file WindowInfo.h
 * @brief Window information struct definition, containing details about a window such as its title, size, and other properties.
 * @author Mitchell Talyat
 */

#include "Core/Type/Int2.hpp"
#include "Core/Type/UInt2.hpp"
#include "Core/Data/StringView.hpp"
#include "Core/Constant/Invalid.hpp"
#include "Core/Constant/Info.hpp"
#include "Event/Type/EventCallback.hpp"
#include "Resource/Type/Handle.hpp"

namespace Minty
{
    /**
     * @brief The WindowInfo struct contains information about a window, such as its title, size, position, and event callback.
     */
    struct WindowInfo
    {
        /**
         * @brief The position of the Window.
         */
		Int2 position = { 100, 100 };

        /**
         * @brief The size of the Window.
         */
		UInt2 size = { 960, 540 };

        /**
         * @brief The title of the Window.
         */
		StringView title = MINTY_NAME;

        /**
         * @brief The icon of the Window.
         */
		ImageResourceHandle icon = INVALID_INDEX;

		/**
		 * @brief Called when an Event is triggered.
		 */
		EventCallback eventCallback = nullptr;
    };
}