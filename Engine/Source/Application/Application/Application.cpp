#include "pch.hpp"
#include "Application.hpp"
#include "Platform/Platform/Platform.hpp"
#include "Application/Application/ApplicationInfo.hpp"
#include "Scene/Manager/SceneManager.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Audio/Manager/AudioManager.hpp"
#include "Render/Manager/RenderManager.hpp"
#include "Input/Manager/InputManager.hpp"
#include "Script/Manager/ScriptManager.hpp"
#include "Core/Time/TimeController.hpp"
#include "Event/Event/Event.hpp"
#include "Window/Window/Window.hpp"
#include "Window/Window/WindowInfo.hpp"

using namespace Minty;

Minty::Application::Application(ApplicationInfo const &info)
    : m_data(info.data),
      mp_window(nullptr),
      mp_sceneManager(nullptr),
      mp_resourceManager(nullptr),
      mp_audioManager(nullptr),
      mp_renderManager(nullptr),
      mp_inputManager(nullptr),
      mp_scriptManager(nullptr),
      mp_timeController(nullptr),
      m_running(false),
      m_status(),
      keyListener(nullptr),
      mouseButtonListener(nullptr),
      mouseMoveListener(nullptr),
      mouseScrollListener(nullptr),
      resizeListener(nullptr)
{
    m_status.promote_to(StatusEnum::Created);

    // Initialize the platform
    Platform::initialize();

    // Create the window
    mp_window = new Window(info.windowInfo);

    // Create the managers
    mp_sceneManager = new SceneManager(info.sceneManagerInfo);
    mp_resourceManager = new ResourceManager(info.resourceManagerInfo);
    mp_audioManager = new AudioManager(info.audioManagerInfo);
    mp_renderManager = new RenderManager(info.renderManagerInfo);
    mp_inputManager = new InputManager(info.inputManagerInfo);
    mp_scriptManager = new ScriptManager(info.scriptManagerInfo);
    mp_timeController = new TimeController(info.timeControllerInfo);

    m_status.promote_to(StatusEnum::Loaded);
}

Minty::Application::~Application()
{
    // Delete the managers
    delete mp_sceneManager;
    delete mp_resourceManager;
    delete mp_audioManager;
    delete mp_renderManager;
    delete mp_inputManager;
    delete mp_scriptManager;
    delete mp_timeController;

    // Delete the window
    delete mp_window;

    // Shutdown the platform
    Platform::shutdown();
}

Minty::Application::Application(Application &&app)
    : mp_sceneManager(app.mp_sceneManager),
      mp_resourceManager(app.mp_resourceManager),
      mp_audioManager(app.mp_audioManager),
      mp_renderManager(app.mp_renderManager),
      mp_inputManager(app.mp_inputManager),
      mp_scriptManager(app.mp_scriptManager),
      mp_timeController(app.mp_timeController),
      m_running(app.m_running),
      m_status(app.m_status),
      keyListener(app.keyListener),
      mouseButtonListener(app.mouseButtonListener),
      mouseMoveListener(app.mouseMoveListener),
      mouseScrollListener(app.mouseScrollListener),
      resizeListener(app.resizeListener)
{
    app.mp_sceneManager = nullptr;
    app.mp_resourceManager = nullptr;
    app.mp_audioManager = nullptr;
    app.mp_renderManager = nullptr;
    app.mp_inputManager = nullptr;
    app.mp_scriptManager = nullptr;
    app.mp_timeController = nullptr;
    app.m_running = false;
    app.keyListener = nullptr;
    app.mouseButtonListener = nullptr;
    app.mouseMoveListener = nullptr;
    app.mouseScrollListener = nullptr;
    app.resizeListener = nullptr;
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
        delete mp_scriptManager;
        delete mp_timeController;

        mp_sceneManager = app.mp_sceneManager;
        mp_resourceManager = app.mp_resourceManager;
        mp_audioManager = app.mp_audioManager;
        mp_renderManager = app.mp_renderManager;
        mp_inputManager = app.mp_inputManager;
        mp_scriptManager = app.mp_scriptManager;
        mp_timeController = app.mp_timeController;
        m_running = app.m_running;
        m_status = app.m_status;

        app.mp_sceneManager = nullptr;
        app.mp_resourceManager = nullptr;
        app.mp_audioManager = nullptr;
        app.mp_renderManager = nullptr;
        app.mp_inputManager = nullptr;
        app.mp_scriptManager = nullptr;
        app.mp_timeController = nullptr;
        app.m_running = false;
        app.m_status = Status();
        app.keyListener = nullptr;
        app.mouseButtonListener = nullptr;
        app.mouseMoveListener = nullptr;
        app.mouseScrollListener = nullptr;
        app.resizeListener = nullptr;
    }
    return *this;
}

Int Minty::Application::run()
{
    Int fixedUpdates, i;

    load();
    enable();

    m_running = true;
    while (m_running && mp_window->is_open())
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

    disable();
    unload();

    return 0;
}

void Minty::Application::quit()
{
    m_running = false;
}

void Minty::Application::load()
{
    // Register Window events to InputManager
    keyListener = [this](KeyEnum key, KeyActionEnum action, KeyModifierFlagsEnum mods)
    {
        mp_inputManager->set_key(key, action != KeyActionEnum::Up);
    };
    mouseButtonListener = [this](MouseButtonEnum button, MouseActionEnum action)
    {
        mp_inputManager->set_mouse_button(button, action != MouseActionEnum::Up);
    };
    mouseMoveListener = [this](Float2 position)
    {
        mp_inputManager->set_mouse_position(position);
    };
    mouseScrollListener = [this](Float2 scroll)
    {
        mp_inputManager->set_mouse_scroll(scroll);
    };
    resizeListener = [this](Int2 size)
    {
        mp_renderManager->notify_framebuffer_resized(size);
    };

    mp_window->on_key += keyListener;
    mp_window->on_mouse_button += mouseButtonListener;
    mp_window->on_mouse_move += mouseMoveListener;
    mp_window->on_mouse_scroll += mouseScrollListener;
    mp_window->on_resize += resizeListener;

    // Trigger promotions after loading the application
    trigger_promotion(StatusEnum::Loaded);
}

void Minty::Application::unload()
{
    // Trigger demotions before unloading the application
    trigger_demotion(StatusEnum::Unloaded);

    // Unregister Window events from InputManager
    mp_window->on_key -= keyListener;
    mp_window->on_mouse_button -= mouseButtonListener;
    mp_window->on_mouse_move -= mouseMoveListener;
    mp_window->on_mouse_scroll -= mouseScrollListener;
    mp_window->on_resize -= resizeListener;

    keyListener = nullptr;
    mouseButtonListener = nullptr;
    mouseMoveListener = nullptr;
    mouseScrollListener = nullptr;
    resizeListener = nullptr;
}

void Minty::Application::enable()
{
    m_running = true;

    // Trigger promotions
    trigger_promotion(StatusEnum::Enabled);
}

void Minty::Application::disable()
{
    // Trigger demotions
    trigger_demotion(StatusEnum::Disabled);

    m_running = false;
}

void Minty::Application::trigger_promotion(StatusEnum status)
{
    m_status.value = status;
    mp_sceneManager->trigger_promotion(m_status.value);
}

void Minty::Application::trigger_demotion(StatusEnum status)
{
    m_status.value = status;
    mp_sceneManager->trigger_demotion(m_status.value);
}
