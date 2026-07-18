#pragma once

#include "Core/Time/Timestep.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Event/Event/Event.hpp"

namespace Minty
{
    template <typename T>
    concept HasOnFrameUpdate = requires(T &system, Timestep const &timestep) {
        { system.frame_update(timestep) } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnFixedUpdate = requires(T &system, Timestep const &timestep) {
        { system.fixed_update(timestep) } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnFinalize = requires(T &system, Timestep const &timestep) {
        { system.finalize(timestep) } -> std::same_as<void>;
    };

    template<typename T>
    concept HasOnRender = requires(T &system, Timestep const &timestep) {
        { system.render(timestep) } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnEvent = requires(T &system, Event &event) {
        { system.on_event(event) } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnLoad = requires(T &system) {
        { system.load() } -> std::same_as<void>;
    };

    template <typename T>
    concept HasOnUnload = requires(T &system) {
        { system.unload() } -> std::same_as<void>;
    };
}