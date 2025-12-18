#ifndef MINTY_SCENE_SCENEINFO_H
#define MINTY_SCENE_SCENEINFO_H

/**
 * @file SceneInfo.h
 * @brief Defines the SceneInfo struct used for creating Scenes.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    /**
     * @brief The arguments for creating a Scene.
     */
    struct SceneInfo
    {
        /**
         * @brief The UUID of the Scene.
         */
        UUID id = {};

        /**
         * @brief The name of the Scene.
         */
        String name = "Scene";
    };
}

#endif // MINTY_SCENE_SCENEINFO_H