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

namespace minty
{
    Scene::Scene(std::string const& name, Game* const game)
        : m_name(name)
        , mp_registry(game->registry())
        , mp_game(game)
        , mp_engine(game->engine())
        , m_systemManager()
        , m_mainCamera(createEntity_camera())
        , mp_inputSystem(new InputSystem(mp_registry))
        , mp_renderSystem(new RenderSystem(mp_registry, &m_mainCamera, mp_engine->screen()))
    {
        // ensure camera is not destroyed across scene transitions
        mp_registry->emplace<NoDestroy>(m_mainCamera);

        // emplace input system
        m_systemManager.emplace(mp_inputSystem);
    }

    Scene::~Scene()
    {
        delete mp_renderSystem;
    }

    int Scene::load()
    {
        m_systemManager.load();

        return onLoad();
    }

    int Scene::update()
    {
        m_systemManager.update();

        int result = onUpdate();

        if (!result)
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

        // let systems clean up
        m_systemManager.unload();

        // let scene clean up
        int result = onUnload();

        // destroy entities
        auto destroyView = mp_registry->view<Destroy>();
        mp_registry->destroy(destroyView.begin(), destroyView.end());

        return result;
    }

    entt::entity Scene::createEntity_camera(float const pivotX, float const pivotY)
    {
        entt::entity camera = mp_registry->create();

        mp_registry->emplace<Position>(camera);
        mp_registry->emplace<Size>(camera, static_cast<float>(mp_engine->screen()->width), static_cast<float>(mp_game->engine()->screen()->height));
        mp_registry->emplace<Camera>(camera, -pivotX * mp_engine->screen()->width, -pivotY * mp_engine->screen()->height);
        mp_registry->emplace<Renderable>(camera);

        return camera;
    }

    entt::entity Scene::createEntity_sprite(std::string const& path, float const x, float const y, int const layer, int const order, float const pivotX, float const pivotY)
    {
        return createEntity_sprite(resources_load_sprite(path, mp_engine->renderer(), PointF(pivotX, pivotY)), x, y, layer, order);
    }

    entt::entity Scene::createEntity_sprite(Sprite* const sprite, float const x, float const y, int const layer, int const order)
    {
        entt::entity entity = mp_registry->create();

        mp_registry->emplace<Position>(entity, x, y);
        mp_registry->emplace<SpriteRenderer>(entity, sprite);
        mp_registry->emplace<Renderable>(entity, RendererType::Sprite, layer, order);

        return entity;
    }

    entt::entity Scene::createEntity_spriteWithCollider(std::string const& path, float const x, float const y, int const layer, int const order, float const pivotX, float const pivotY, bool const isTrigger, bool const isStatic, bool const isDynamic, Rect const* const rect)
    {
        // create entity with sprite
        entt::entity entity = createEntity_sprite(path, x, y, layer, order);

        // get sprite renderer
        SpriteRenderer const& renderer = mp_registry->get<SpriteRenderer>(entity);

        Rect bounds;

        if (rect)
        {
            bounds = *rect;
        }
        else
        {
            bounds = Rect(0, 0, renderer.sprite->width, renderer.sprite->height);
        }

        // add to collider
        mp_registry->emplace<Collider>(entity, bounds, isTrigger, isStatic, (isDynamic || !renderer.sprite) ? nullptr : renderer.sprite->getMask());

        return entity;
    }
    
    entt::entity Scene::createEntity_ui(std::string const& path, float const x, float const y, int const layer, int const order, float const pivotX, float const pivotY, float const anchorX, float const anchorY)
    {
        return createEntity_ui(resources_load_sprite(path, mp_engine->renderer()), x, y, layer, order, pivotX, pivotY, anchorX, anchorY);
    }
    
    entt::entity Scene::createEntity_ui(Sprite* const sprite, float const x, float const y, int const layer, int const order, float const pivotX, float const pivotY, float const anchorX, float const anchorY)
    {
        entt::entity entity = mp_registry->create();

        sprite->setPivot(PointF(pivotX, pivotY));
        mp_registry->emplace<SpriteRenderer>(entity, sprite);
        mp_registry->emplace<Renderable>(entity, RendererType::Sprite, layer, order);
        mp_registry->emplace<UI>(entity, x, y, anchorX, anchorY);

        return entity;
    }
    
    entt::entity Scene::createEntity_ui_text(Text* const text, float const x, float const y, int const layer, int const order, float const anchorX, float const anchorY)
    {
        entt::entity entity = mp_registry->create();

        mp_registry->emplace<TextRenderer>(entity, text);
        mp_registry->emplace<Renderable>(entity, RendererType::Text, layer, order);
        mp_registry->emplace<UI>(entity, x, y, anchorX, anchorY);

        return entity;
    }
}
