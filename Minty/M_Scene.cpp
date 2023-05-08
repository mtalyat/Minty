#include "pch.h"
#include "M_Scene.h"

#define NOMINMAX

#include "M_Engine.h"
#include "M_Game.h"
#include "M_Input.h"
#include "M_System.h"
#include "M_Screen.h"
#include "M_Resources.h"
#include "M_Time.h"
#include "M_Sprite.h"
#include "M_Templates.h"

#include "M_SceneManager.h"

#include "M_C_Position.h"
#include "M_C_Scale.h"
#include "M_C_Size.h"
#include "M_C_Camera.h"
#include "M_C_SpriteRenderer.h"
#include "M_C_TextRenderer.h"
#include "M_C_Renderable.h"
#include "M_C_Collider.h"
#include "M_T_Destroy.h"
#include "M_C_DestroyTimer.h"
#include "M_C_UI.h"
#include "M_C_Center.h"
#include "M_T_NoDestroy.h"
#include "M_C_Clickable.h"
#include "M_C_MouseClick.h"
#include "M_C_MouseDown.h"
#include "M_C_MouseUp.h"
#include "M_C_MouseHover.h"
#include "M_C_MouseEnter.h"
#include "M_C_MouseExit.h"

namespace minty
{
    Scene::Scene(std::string const& name, Game* const game)
        : m_name(name)
        , mp_registry(game->registry())
        , mp_game(game)
        , mp_engine(game->engine())
        , m_systemManager()
        , m_mainCamera(entt::null)
        , mp_inputSystem(new InputSystem(mp_registry))
        , mp_renderSystem(new RenderSystem(mp_registry, &m_mainCamera, mp_engine->screen()))
        , mp_audioSystem(new AudioSystem(mp_registry))
        , mp_uiSystem(new UserInterfaceSystem(mp_registry))
    {
        // emplace input system
        m_systemManager.emplace(mp_inputSystem);
        m_systemManager.emplace(mp_renderSystem);
        m_systemManager.emplace(mp_audioSystem);
        m_systemManager.emplace(mp_uiSystem);
    }

    Scene::~Scene()
    {
        
    }

    int Scene::load()
    {
        // create camera
        m_mainCamera = templates_entity_camera(mp_registry, mp_engine->screen());

        // load systems
        m_systemManager.load();

        return onLoad();
    }

    int Scene::update()
    {
        m_systemManager.update();

        int result = onUpdate();

        if (!result)
        {
            cleanup();
        }

        return result;
    }

    int Scene::fixedUpdate()
    {
        m_systemManager.fixedUpdate();

        int result = onFixedUpdate();

        if (!result)
        {
            cleanup();
        }

        return result;
    }

    int Scene::unload()
    {
        // delete all entities that do not have the NoDestroy tag
        mp_registry->each([this](auto entity)
            {
                if (mp_registry->valid(entity) && !mp_registry->any_of<NoDestroy>(entity))
                {
                    // does not have the NoDestroy tag
                    mp_registry->emplace<Destroy>(entity);
                }
            });

        // cleanup
        m_mainCamera = entt::null;
        m_systemManager.unload();

        // let scene clean up
        int result = onUnload();

        // destroy entities
        auto destroyView = mp_registry->view<Destroy>();
        mp_registry->destroy(destroyView.begin(), destroyView.end());

        return result;
    }

    void Scene::cleanup()
    {
        // successfully updated, so delete entities
        float deltaTime = Time::deltaTime();

        // destroy timers
        for (auto [entity, timer] : mp_registry->view<DestroyTimer>().each())
        {
            // increment time
            timer.timer -= deltaTime;

            // if <= 0.0, then timer is up, destroy now
            if (timer.timer <= 0.0f)
            {
                mp_registry->emplace<Destroy>(entity);
            }
        }

        // destroy entities that are needing to be destroyed
        auto destroyView = mp_registry->view<Destroy>();
        mp_registry->destroy(destroyView.begin(), destroyView.end());
    }
}
