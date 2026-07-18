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