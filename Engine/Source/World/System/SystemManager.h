#pragma once

#include "World/Entity/Entity.h"
#include "Library/EnTT/EnTT.h"
#include "Core/Data/Registry.h"
#include "Core/Data/UUID.h"
#include "Core/Data/StringView.h"
#include "Core/Data/Vector.h"
#include "Core/Type/Function.h"
#include "Core/Time/Timestep.h"
#include "Platform/Type/Primitive.h"
#include <concepts>

namespace Minty
{
    struct SystemManagerInfo;

    class SystemManager
    {
#pragma region Type

    private:
        struct FrameUpdateHook
        {
            Pointer system;
            Function<void(Pointer, Timestep const&)> frameUpdateFunction;
        };

        struct FixedUpdateHook
        {
            Pointer system;
            Function<void(Pointer, Timestep const&)> fixedUpdateFunction;
        };

        struct LateUpdateHook
        {
            Pointer system;
            Function<void(Pointer, Timestep const&)> lateUpdateFunction;
        };

        struct LoadHook
        {
            Pointer system;
            Function<void(Pointer)> loadFunction;
        };

        struct UnloadHook
        {
            Pointer system;
            Function<void(Pointer)> unloadFunction;
        };

#pragma endregion

#pragma region Constructor

    public:
        SystemManager(SystemManagerInfo const &info);
        ~SystemManager();

        SystemManager(SystemManager const &) = delete;
        SystemManager(SystemManager &&) = delete;

#pragma endregion

#pragma region Operator

    public:
        SystemManager &operator=(SystemManager const &) = delete;
        SystemManager &operator=(SystemManager &&) = delete;

#pragma endregion

#pragma region Method

    public:
        template <typename T, typename... Args>
        T &create_system(Args &&...args);

        template <typename System>
        void register_system(StringView const name);

#pragma endregion

#pragma region Variable

    private:
        Vector<Pointer> m_systems;
        Vector<FrameUpdateHook> m_frameUpdateHooks;
        Vector<FixedUpdateHook> m_fixedUpdateHooks;
        Vector<LateUpdateHook> m_lateUpdateHooks;
        Vector<LoadHook> m_loadHooks;
        Vector<UnloadHook> m_unloadHooks;
        Registry<> m_registeredSystems;

#pragma endregion
    };
}

#include "SystemManager.inl"