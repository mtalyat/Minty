#pragma once

#include "Scene/Type/handle.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Data/PriorityVector.hpp"
#include "Core/Data/HandlePool.hpp"
#include "Core/Data/StringView.hpp"
#include "Core/Type/Status.hpp"

namespace Minty
{
    struct SceneManagerInfo;
    struct SceneInfo;
    struct Timestep;
    class Scene;
    class Event;

    class SceneManager
    {
#pragma region Constructor

    public:
        SceneManager(SceneManagerInfo const &info);
        ~SceneManager();

#pragma endregion

#pragma region Method

    public:
        // Scene functions
        SceneHandle create(SceneInfo const &info);
        void destroy(SceneHandle const handle);
        Scene &at(SceneHandle const handle);
        Scene const &at(SceneHandle const handle) const;
        SceneHandle find(StringView const name) const;
        void enable(SceneHandle const handle);
        void disable(SceneHandle const handle);

        // Event actions
        void on_frame_update(Timestep const &timestep);
        void on_fixed_update(Timestep const &timestep);
        void on_finalize();
        void on_render();
        void on_event(Event &event);

        // Status functions
        void trigger_promotion(StatusEnum const status);
        void trigger_demotion(StatusEnum const status);

#pragma endregion

#pragma region Variables

    private:
        HandlePool<Scene> m_scenes;
        PriorityVector<SceneHandle> m_activeScenes;
        StatusEnum m_parentStatus;

#pragma endregion
    };
}