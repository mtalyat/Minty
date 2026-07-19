#pragma once

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    struct ApplicationInfo;
    class SceneManager;
    class WindowManager;
    class ResourceManager;
    class AudioManager;
    class RenderManager;
    class InputManager;
    class TimeController;
    class Event;

    class Application
    {
#pragma region Constructor

    public:
        Application(ApplicationInfo const &info);
        ~Application();

        Application(Application const &) = delete;
        Application(Application &&);

#pragma endregion

#pragma region Operator

    public:
        Application &operator=(Application const &) = delete;
        Application &operator=(Application &&);

#pragma endregion

#pragma region Accessor

    public:
        inline Bool is_running() const { return m_running; }
        inline SceneManager &get_scene_manager() { return *mp_sceneManager; }
        inline WindowManager &get_window_manager() { return *mp_windowManager; }
        inline ResourceManager &get_resource_manager() { return *mp_resourceManager; }
        inline AudioManager &get_audio_manager() { return *mp_audioManager; }
        inline RenderManager &get_render_manager() { return *mp_renderManager; }
        inline InputManager &get_input_manager() { return *mp_inputManager; }
        inline TimeController &get_time_controller() { return *mp_timeController; }

#pragma endregion

#pragma region Method

    public:
        void run();

        void quit();

    private:
        void on_event(Event &event);

#pragma endregion

#pragma region Variables

    private:
        SceneManager *mp_sceneManager;
        WindowManager *mp_windowManager;
        ResourceManager *mp_resourceManager;
        AudioManager *mp_audioManager;
        RenderManager *mp_renderManager;
        InputManager *mp_inputManager;
        TimeController *mp_timeController;
        Bool m_running;

#pragma endregion
    };
}