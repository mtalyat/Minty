#pragma once

#include "Core/Time/Timestep.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Event/Event/Event.hpp"

namespace Minty
{
    template <typename T>
    concept HasOnFrameUpdate = requires(T &system, Timestep const &timestep) {
        { system.on_frame_update(timestep) } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnFixedUpdate = requires(T &system, Timestep const &timestep) {
        { system.on_fixed_update(timestep) } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnFinalize = requires(T &system) {
        { system.on_finalize() } -> std::same_as<void>;
    };

    template<typename T>
    concept HasOnRender = requires(T &system) {
        { system.on_render() } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnEvent = requires(T &system, Event &event) {
        { system.on_event(event) } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnLoad = requires(T &system) {
        { system.on_load() } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnUnload = requires(T &system) {
        { system.on_unload() } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnEnable = requires(T &system) {
        { system.on_enable() } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnDisable = requires(T &system) {
        { system.on_disable() } -> std::same_as<void>;
    };
}