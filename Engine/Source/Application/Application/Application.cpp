#include "pch.hpp"
#include "Application.hpp"
#include "Platform/Platform/Platform.hpp"
#include "Application/Application/ApplicationInfo.hpp"
#include "Scene/Manager/SceneManager.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Audio/Manager/AudioManager.hpp"
#include "Render/Manager/RenderManager.hpp"
#include "Input/Manager/InputManager.hpp"
#include "Core/Time/TimeController.hpp"
#include "Event/Event/Event.hpp"
#include "Window/Window/Window.hpp"
#include "Window/Window/WindowInfo.hpp"

using namespace Minty;

Minty::Application::Application(ApplicationInfo const &info)
    : m_data(info.data),
      mp_sceneManager(nullptr),
      mp_resourceManager(nullptr),
      mp_audioManager(nullptr),
      mp_renderManager(nullptr),
      mp_inputManager(nullptr),
      mp_timeController(nullptr),
      m_running(false)
{
    // Initialize the platform
    Platform::initialize();

    // Create the managers
    mp_sceneManager = new SceneManager(info.sceneManagerInfo);
    mp_resourceManager = new ResourceManager(info.resourceManagerInfo);
    mp_audioManager = new AudioManager(info.audioManagerInfo);
    mp_renderManager = new RenderManager(info.renderManagerInfo);
    mp_inputManager = new InputManager(info.inputManagerInfo);
    mp_timeController = new TimeController(info.timeControllerInfo);
}

Minty::Application::~Application()
{
    // Delete the managers
    delete mp_sceneManager;
    delete mp_resourceManager;
    delete mp_audioManager;
    delete mp_renderManager;
    delete mp_inputManager;
    delete mp_timeController;

    // Shutdown the platform
    Platform::shutdown();
}

Minty::Application::Application(Application &&app)
    : mp_sceneManager(app.mp_sceneManager),
      mp_resourceManager(app.mp_resourceManager),
      mp_audioManager(app.mp_audioManager),
      mp_renderManager(app.mp_renderManager),
      mp_inputManager(app.mp_inputManager),
      mp_timeController(app.mp_timeController),
      m_running(app.m_running)
{
    app.mp_sceneManager = nullptr;
    app.mp_resourceManager = nullptr;
    app.mp_audioManager = nullptr;
    app.mp_renderManager = nullptr;
    app.mp_inputManager = nullptr;
    app.mp_timeController = nullptr;
    app.m_running = false;
}

Minty::Application &Minty::Application::operator=(Application &&app)
{
    if (this != &app)
    {
        delete mp_sceneManager;
        delete mp_resourceManager;
        delete mp_audioManager;
        delete mp_renderManager;
        delete mp_inputManager;
        delete mp_timeController;

        mp_sceneManager = app.mp_sceneManager;
        mp_resourceManager = app.mp_resourceManager;
        mp_audioManager = app.mp_audioManager;
        mp_renderManager = app.mp_renderManager;
        mp_inputManager = app.mp_inputManager;
        mp_timeController = app.mp_timeController;
        m_running = app.m_running;

        app.mp_sceneManager = nullptr;
        app.mp_resourceManager = nullptr;
        app.mp_audioManager = nullptr;
        app.mp_renderManager = nullptr;
        app.mp_inputManager = nullptr;
        app.mp_timeController = nullptr;
        app.m_running = false;
    }
    return *this;
}

void Minty::Application::run()
{
    Int fixedUpdates, i;

    // Create a Window
    WindowInfo windowInfo{};
    windowInfo.title = m_data.name;
    Window window(windowInfo);

    // Register Window events to InputManager
    Function keyListener = [this](KeyEnum key, KeyActionEnum action, KeyModifierFlagsEnum mods)
    {
        mp_inputManager->set_key(key, action != KeyActionEnum::Up);
    };
    Function mouseButtonListener = [this](MouseButtonEnum button, MouseActionEnum action)
    {
        mp_inputManager->set_mouse_button(button, action != MouseActionEnum::Up);
    };
    Function mouseMoveListener = [this](Float2 position)
    {
        mp_inputManager->set_mouse_position(position);
    };
    Function mouseScrollListener = [this](Float2 scroll)
    {
        mp_inputManager->set_mouse_scroll(scroll);
    };

    window.on_key += keyListener;
    window.on_mouse_button += mouseButtonListener;
    window.on_mouse_move += mouseMoveListener;
    window.on_mouse_scroll += mouseScrollListener;

    while (m_running && window.is_open())
    {
        // Process events
        Platform::process_events();

        // TODO: Update input state

        // Update time controller
        fixedUpdates = mp_timeController->update();

        // Perform fixed updates, if any
        for (i = 0; i < fixedUpdates; ++i)
        {
            mp_sceneManager->on_fixed_update(mp_timeController->get_fixed_timestep());
        }

        // Perform frame update
        mp_sceneManager->on_frame_update(mp_timeController->get_frame_timestep());

        // Finalize the frame
        mp_sceneManager->on_finalize();

        // Render the frame
        mp_sceneManager->on_render();
    }

    // Sync the platform to ensure all events are processed before exiting
    Platform::sync();

    // Unregister Window events from InputManager
    window.on_key -= keyListener;
    window.on_mouse_button -= mouseButtonListener;
    window.on_mouse_move -= mouseMoveListener;
    window.on_mouse_scroll -= mouseScrollListener;
}

void Minty::Application::quit()
{
    m_running = false;
}
