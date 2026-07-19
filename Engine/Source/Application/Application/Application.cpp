#include "pch.hpp"
#include "Application.hpp"
#include "Application/Application/ApplicationInfo.hpp"
#include "Scene/Manager/SceneManager.hpp"
#include "Window/Manager/WindowManager.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Audio/Manager/AudioManager.hpp"
#include "Render/Manager/RenderManager.hpp"
#include "Core/Time/TimeController.hpp"

using namespace Minty;

Minty::Application::Application(ApplicationInfo const &info)
    : mp_sceneManager(new SceneManager(info.sceneManagerInfo)),
      mp_windowManager(new WindowManager(info.windowManagerInfo)),
      mp_resourceManager(new ResourceManager(info.resourceManagerInfo)),
      mp_audioManager(new AudioManager(info.audioManagerInfo)),
      mp_renderManager(new RenderManager(info.renderManagerInfo)),
      mp_timeController(new TimeController(info.timeControllerInfo)),
      m_running(false)
{
    mp_windowManager->set_event_callback([this](Event &event)
                                         { mp_sceneManager->on_event(event); });
}

Minty::Application::~Application()
{
    delete mp_sceneManager;
    delete mp_windowManager;
    delete mp_resourceManager;
    delete mp_audioManager;
    delete mp_renderManager;
    delete mp_timeController;
}

Minty::Application::Application(Application &&app)
    : mp_sceneManager(app.mp_sceneManager),
      mp_windowManager(app.mp_windowManager),
      mp_resourceManager(app.mp_resourceManager),
      mp_audioManager(app.mp_audioManager),
      mp_renderManager(app.mp_renderManager),
      mp_timeController(app.mp_timeController),
      m_running(app.m_running)
{
    app.mp_sceneManager = nullptr;
    app.mp_windowManager = nullptr;
    app.mp_resourceManager = nullptr;
    app.mp_audioManager = nullptr;
    app.mp_renderManager = nullptr;
    app.mp_timeController = nullptr;
    app.m_running = false;
}

Minty::Application &Minty::Application::operator=(Application &&app)
{
    if (this != &app)
    {
        delete mp_sceneManager;
        delete mp_windowManager;
        delete mp_resourceManager;
        delete mp_audioManager;
        delete mp_renderManager;
        delete mp_timeController;

        mp_sceneManager = app.mp_sceneManager;
        mp_windowManager = app.mp_windowManager;
        mp_resourceManager = app.mp_resourceManager;
        mp_audioManager = app.mp_audioManager;
        mp_renderManager = app.mp_renderManager;
        mp_timeController = app.mp_timeController;
        m_running = app.m_running;

        app.mp_sceneManager = nullptr;
        app.mp_windowManager = nullptr;
        app.mp_resourceManager = nullptr;
        app.mp_audioManager = nullptr;
        app.mp_renderManager = nullptr;
        app.mp_timeController = nullptr;
        app.m_running = false;
    }
    return *this;
}

void Minty::Application::run()
{
    Int fixedUpdates, i;

    while (m_running)
    {
        // Process window events
        mp_windowManager->process_events();

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
}

void Minty::Application::quit()
{
    m_running = false;
}
