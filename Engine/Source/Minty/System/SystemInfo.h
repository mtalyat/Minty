#ifndef MINTY_SYSTEM_SYSTEMINFO_H
#define MINTY_SYSTEM_SYSTEMINFO_H

/**
 * @file SystemInfo.h
 * @brief Header file for the SystemInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
    class Scene;
    struct SystemData;

    /**
     * @brief Information required to create a System.
     */
	struct SystemInfo
	{
        /**
         * @brief The priority of the System.
         */
		Int priority = 0;

        /**
         * @brief The Scene the System belongs to.
         */
		Ref<Scene> scene = nullptr;

        /**
         * @brief The SystemData for the System.
         */
		SystemData const* info = nullptr;
	};
}

#endif // MINTY_SYSTEM_SYSTEMINFO_H