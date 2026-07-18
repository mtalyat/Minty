#pragma once

// #include "Scene/Type/Handle.h"
#include "World/Entity/EntityManager.hpp"
#include "World/System/SystemManager.hpp"

namespace Minty
{
    struct SceneInfo;
    struct Timestep;
    class Event;

    class Scene
    {
#pragma region Constructor

    public:
        Scene(SceneInfo const &info);
        ~Scene() = default;

        Scene(Scene const &) = delete;
        Scene(Scene &&);

#pragma endregion

#pragma region Operator

    public:
        Scene &operator=(Scene const &) = delete;
        Scene &operator=(Scene &&);

#pragma endregion

#pragma region Accessor

    public:
        inline EntityManager &get_entity_manager() { return *mp_entityManager; }
        inline SystemManager &get_system_manager() { return *mp_systemManager; }
        inline Priority get_priority() const { return m_priority; }

#pragma endregion

#pragma region Method

    public:
        void on_frame_update(Timestep const &timestep);
        void on_fixed_update(Timestep const &timestep);
        void on_finalize();
        void on_render();
        void on_event(Event const &event);

#pragma endregion

#pragma region Variables

    private:
        EntityManager *mp_entityManager;
        SystemManager *mp_systemManager;
        Priority m_priority;

#pragma endregion
    };
}