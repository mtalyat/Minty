#ifndef MINTY_WINDOW_WINDOWINFO_H
#define MINTY_WINDOW_WINDOWINFO_H

/**
 * @file WindowInfo.h
 * @brief Header file for the WindowInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    /**
     * @brief Configuration information for creating a Window.
     */
	struct WindowInfo
	{
        /**
         * @brief The ID of the Window.
         */
		UUID id = {};

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
		String title = MINTY_NAME;

        /**
         * @brief The icon of the Window.
         */
		Path icon = TEXT_EMPTY;

		/**
		 * @brief Called when an Event is triggered.
		 */
		EventCallback eventCallback = nullptr;
	};
}

#endif // MINTY_WINDOW_WINDOWINFO_H