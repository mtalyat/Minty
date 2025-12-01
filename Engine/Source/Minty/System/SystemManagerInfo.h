#ifndef MINTY_SYSTEM_SYSTEMMANAGERINFO_H
#define MINTY_SYSTEM_SYSTEMMANAGERINFO_H

/**
 * @file SystemManagerInfo.h
 * @brief Header file defining the SystemManagerInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Pointer.h"

namespace Minty
{
    class Scene;

    /**
     * @brief The arguments for creating a SystemManager.
     */
    struct SystemManagerInfo
    {
        /**
         * @brief The Scene this SystemManager belongs to.
         */
        Ref<Scene> scene = nullptr;
    };
}
#endif // MINTY_SYSTEM_SYSTEMMANAGERINFO_H