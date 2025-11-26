#ifndef MINTY_APPLICATION_APPLICATIONINFO_H
#define MINTY_APPLICATION_APPLICATIONINFO_H

/**
 * @file ApplicationInfo.h
 * @brief Defines the ApplicationInfo struct used for creating Applications.
 * @author Mitchell Talyat
 */

namespace Minty
{
    struct LoggerInfo;
    struct WindowInfo;
    struct MemoryManagerInfo;
    struct JobManagerInfo;
    struct AudioManagerInfo;
    struct LayerManagerInfo;
    struct PhysicsManagerInfo;
    struct AssetManagerInfo;
    struct InputManagerInfo;
    struct RenderManagerInfo;
    struct SceneManagerInfo;
    struct TimeManagerInfo;

    /**
     * @brief The arguments for an Application.
     */
    struct ApplicationInfo
    {
        /**
         * @brief The Logger info to use for the Application.
         */
        LoggerInfo* loggerInfo = nullptr;

        /**
         * @brief The Window info to use for the Application.
         */
        WindowInfo* windowInfo = nullptr;

        /**
         * @brief The Memory Manager info to use for the Application.
         */
        MemoryManagerInfo* memoryManagerInfo = nullptr;

        /**
         * @brief The Job Manager info to use for the Application.
         */
        JobManagerInfo* jobManagerInfo = nullptr;

        /**
         * @brief The Audio Manager info to use for the Application.
         */
        AudioManagerInfo* audioManagerInfo = nullptr;

        /**
         * @brief The Layer Manager info to use for the Application.
         */
        LayerManagerInfo* layerManagerInfo = nullptr;

        /**
         * @brief The Physics Manager info to use for the Application.
         */
        PhysicsManagerInfo* physicsManagerInfo = nullptr;

        /**
         * @brief The Asset Manager info to use for the Application.
         */
        AssetManagerInfo* assetManagerInfo = nullptr;

        /**
         * @brief The Input Manager info to use for the Application.
         */
        InputManagerInfo* inputManagerInfo = nullptr;

        /**
         * @brief The Render Manager info to use for the Application.
         */
        RenderManagerInfo* renderManagerInfo = nullptr;

        /**
         * @brief The Scene Manager info to use for the Application.
         */
        SceneManagerInfo* sceneManagerInfo = nullptr;

        /**
         * @brief The Time Manager info to use for the Application.
         */
        TimeManagerInfo* timeManagerInfo = nullptr;
    };
}

#endif // MINTY_APPLICATION_APPLICATIONINFO_H