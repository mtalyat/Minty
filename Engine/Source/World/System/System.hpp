#pragma once

#include "Core/Time/Timestep.hpp"
#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    template <typename T>
    concept HasUpdate = requires(T &system, Timestep const &timestep) {
        { system.frame_update(timestep) } -> std::same_as<void>;
    };

    template <typename T>
    concept HasFixedUpdate = requires(T &system, Timestep const &timestep) {
        { system.fixed_update(timestep) } -> std::same_as<void>;
    };

    template <typename T>
    concept HasLateUpdate = requires(T &system, Timestep const &timestep) {
        { system.late_update(timestep) } -> std::same_as<void>;
    };

    template <typename T>
    concept HasLoad = requires(T &system) {
        { system.load() } -> std::same_as<void>;
    };

    template <typename T>
    concept HasUnload = requires(T &system) {
        { system.unload() } -> std::same_as<void>;
    };
}