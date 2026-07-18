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
#include <concepts>

namespace Minty
{
    struct SystemManagerInfo;
    struct Timestep;
    class Event;

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
        SystemManager(SystemManagerInfo const &info);

        SystemManager(SystemManager &&) = delete;

#pragma endregion

#pragma region Operator

    public:
        SystemManager &operator=(SystemManager &&) = delete;

#pragma endregion

#pragma region Method

    public:
        template <typename T, typename... Args>
        T &create_system(Args &&...args);

        template <typename T>
        void destroy_system();

        template <typename T>
        void register_system(StringView const name, Int const priority);

        // Events
        void on_frame_update(Timestep const &timestep);
        void on_fixed_update(Timestep const &timestep);
        void on_finalize();
        void on_render();
        void on_event(Event &event);

#pragma endregion

#pragma region Variable

    private:
        Map<TypeID, Pointer> m_systems;
        PriorityVector<UpdateEventHook> m_frameUpdateHooks;
        PriorityVector<UpdateEventHook> m_fixedUpdateHooks;
        PriorityVector<EventHook> m_finalizeHooks;
        PriorityVector<EventHook> m_renderHooks;
        PriorityVector<EventEventHook> m_eventHooks;
        PriorityVector<EventHook> m_loadHooks;
        PriorityVector<EventHook> m_unloadHooks;
        Registry<Pointer> m_registeredSystems;

#pragma endregion
    };
}

#include "SystemManager.inl"