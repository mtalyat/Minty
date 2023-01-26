#include "pch.h"
#include "M_Scene.h"

#define NOMINMAX

#include "M_Engine.h"
#include "M_Game.h"
#include "M_Input.h"
#include "M_Screen.h"
#include "M_Resources.h"
//#include "UI_Canvas.h"

#include "M_SceneManager.h"

#include "M_C_Position.h"
#include "M_C_Size.h"
#include "M_C_Camera.h"
#include "M_C_SpriteRenderer.h"

namespace minty
{
    Scene::Scene(std::string const& name, Game* const game)
        : m_name(name)
        , mp_registry(game->registry())
        , m_mainCamera()
        //, mp_mainCanvas(new UI_Canvas(game->engine()->screen()))
        , mp_game(game)
        , mp_engine(game->engine())
    {}

    Scene::~Scene()
    {
        //delete mp_mainCanvas;
    }

    entt::entity Scene::create_basic_camera()
    {
        entt::entity camera = mp_registry->create();

        mp_registry->emplace<Position>(camera);
        mp_registry->emplace<Size>(camera, static_cast<float>(mp_engine->screen()->width), static_cast<float>(mp_game->engine()->screen()->height));
        mp_registry->emplace<Camera>(camera);

        return camera;
    }

    entt::entity Scene::create_basic_sprite(float const x, float const y, std::string const& path, int const order)
    {
        entt::entity entity = mp_registry->create();

        mp_registry->emplace<Position>(entity, x, y);

        SDL_Surface* surface = resources_load_image(path);

        if (surface == nullptr)
        {
            // no surface loaded
            return entity;
        }

        mp_registry->emplace<Size>(entity, static_cast<float>(surface->w), static_cast<float>(surface->h));
        mp_registry->emplace<SpriteRenderer>(entity, new Sprite(surface, mp_engine->screen()->renderer()), order);

        return entity;
    }
}
