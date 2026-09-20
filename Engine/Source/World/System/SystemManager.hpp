#pragma once

#include "World/Entity/Entity.hpp"
#include "Library/EnTT/EnTT.hpp"
#include "Core/Data/Registry.hpp"
#include "Core/Data/UUID.hpp"
#include "Core/Data/StringView.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Type/Function.hpp"
#include "Core/Time/Timestep.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Data/PriorityVector.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Type/Status.hpp"
#include <concepts>

namespace Minty
{
    struct SystemManagerInfo;
    struct Timestep;
    class Event;
    class Scene;

    class SystemManager
    {
#pragma region Type

    private:
        struct UpdateEventHook
        {
            Pointer system;
            Function<void(Pointer, Timestep const&)> func;
        };

        struct EventEventHook
        {
            Pointer system;
            Function<void(Pointer, Event&)> func;
        };

        struct EventHook
        {
            Pointer system;
            Function<void(Pointer)> func;
        };

#pragma endregion

#pragma region Constructor

    public:
        SystemManager(SystemManagerInfo const &info, Scene& scene);

        ~SystemManager();

        SystemManager(SystemManager &&) = delete;

#pragma endregion

#pragma region Operator

    public:
        SystemManager &operator=(SystemManager &&) = delete;

#pragma endregion

#pragma region Accessor

    public:
        Status get_status() const { return m_status; }

#pragma endregion

#pragma region Method

    public:
        inline void set_scene(Scene &scene) { mp_scene = &scene; }

        template <typename T, typename... Args>
        T &create_system(Args &&...args);

        template <typename T>
        void destroy_system();

        // Events
        void on_frame_update(Timestep const &timestep);
        void on_fixed_update(Timestep const &timestep);
        void on_finalize();
        void on_render();
        void on_event(Event &event);

        // Status
        void trigger_promotion(StatusEnum const status);
        void trigger_demotion(StatusEnum const status);

        template <typename T>
        static void register_system(StringView const name, Int const priority = 0);

    private:
        void on_promotion();
        void on_demotion();
        
        void on_create();
        void on_destroy();
        void on_load();
        void on_unload();
        void on_enable();
        void on_disable();

#pragma endregion

#pragma region Variable

    private:
        Scene* mp_scene;
        Map<TypeID, Pointer> m_systems;
        PriorityVector<EventHook> m_createHooks;
        PriorityVector<EventHook> m_destroyHooks;
        PriorityVector<EventHook> m_loadHooks;
        PriorityVector<EventHook> m_unloadHooks;
        PriorityVector<EventHook> m_enableHooks;
        PriorityVector<EventHook> m_disableHooks;
        PriorityVector<UpdateEventHook> m_frameUpdateHooks;
        PriorityVector<UpdateEventHook> m_fixedUpdateHooks;
        PriorityVector<EventHook> m_finalizeHooks;
        PriorityVector<EventHook> m_renderHooks;
        PriorityVector<EventEventHook> m_eventHooks;
        Status m_status;

        static Registry<Pointer, SystemManager&> s_registeredSystems;

#pragma endregion
    };
}

#include "SystemManager.inl"