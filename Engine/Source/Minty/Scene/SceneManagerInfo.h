#ifndef MINTY_SCENE_SCENEMANAGERINFO_H
#define MINTY_SCENE_SCENEMANAGERINFO_H

/**
 * @file SceneManagerInfo.h
 * @brief Defines the SceneManagerInfo struct used for creating SceneManagers.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Path.h"

namespace Minty
{
    /**
     * @brief The arguments for creating a SceneManager.
     */
    struct SceneManagerInfo
    {
        /**
         * @brief The path to the first scene to load.
         */
        Path initialScene = {};
    };
}

#endif // MINTY_SCENE_SCENEMANAGERINFO_H