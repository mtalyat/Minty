#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Application/Application/ApplicationData.hpp"
#include "Core/Type/Status.hpp"
#include "Input/Key/Key.hpp"
#include "Input/Key/KeyAction.hpp"
#include "Input/Key/KeyModifier.hpp"
#include "Input/Mouse/MouseButton.hpp"
#include "Input/Mouse/MouseAction.hpp"
#include "Core/Type/Function.hpp"
#include "Core/Type/Float2.hpp"
#include "Core/Type/Int2.hpp"

namespace Minty
{
    struct ApplicationInfo;
    class Window;
    class SceneManager;
    class ResourceManager;
    class AudioManager;
    class RenderManager;
    class InputManager;
    class ScriptManager;
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
        inline Window& get_window() const { return *mp_window; }
        inline SceneManager &get_scene_manager() { return *mp_sceneManager; }
        inline ResourceManager &get_resource_manager() { return *mp_resourceManager; }
        inline AudioManager &get_audio_manager() { return *mp_audioManager; }
        inline RenderManager &get_render_manager() { return *mp_renderManager; }
        inline InputManager &get_input_manager() { return *mp_inputManager; }
        inline ScriptManager &get_script_manager() { return *mp_scriptManager; }
        inline TimeController &get_time_controller() { return *mp_timeController; }
        inline Status& get_status() { return m_status; }
        inline Status const& get_status() const { return m_status; }

#pragma endregion

#pragma region Method

    public:
        Int run();

        void quit();

    private:
        void load();
        void unload();
        void enable();
        void disable();

        void trigger_promotion(StatusEnum status);
        void trigger_demotion(StatusEnum status);

#pragma endregion

#pragma region Variables

    private:
        ApplicationData m_data;
        Window* mp_window;
        SceneManager *mp_sceneManager;
        ResourceManager *mp_resourceManager;
        AudioManager *mp_audioManager;
        RenderManager *mp_renderManager;
        InputManager *mp_inputManager;
        ScriptManager *mp_scriptManager;
        TimeController *mp_timeController;
        Bool m_running;
        Status m_status;

        Function<void(KeyEnum, KeyActionEnum, KeyModifierFlagsEnum)> keyListener;
        Function<void(MouseButtonEnum, MouseActionEnum)> mouseButtonListener;
        Function<void(Float2)> mouseMoveListener;
        Function<void(Float2)> mouseScrollListener;
        Function<void(Int2)> resizeListener;

#pragma endregion
    };
}