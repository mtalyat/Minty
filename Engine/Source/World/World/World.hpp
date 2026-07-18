#pragma once

#include "World/Entity/Entity.hpp"
#include "Library/EnTT/EnTT.hpp"

#include <utility>

namespace Minty
{
    struct WorldInfo;

    class World
    {
#pragma region Type

    private:
        struct Impl
        {
            explicit Impl(WorldInfo const &) {}

            entt::registry world;
        };

#pragma endregion

#pragma region Constructor

    public:
        World(WorldInfo const &info);
        ~World();

        World(World const &) = delete;
        World(World &&) = delete;

#pragma endregion

#pragma region Operator

    public:
        World &operator=(World const &) = delete;
        World &operator=(World &&) = delete;

#pragma endregion

#pragma region Methods

    public:
        template <typename T, typename... Args>
        T &add_component(EntityHandle const entity, Args &&...args)
        {
            return mp_impl->world.emplace<T>(
                static_cast<entt::entity>(entity),
                std::forward<Args>(args)...
            );
        }

        template <typename T, typename... Args>
        T &add_system(Args &&...args)
        {
            return mp_impl->world.ctx().emplace<T>(std::forward<Args>(args)...);
        }

#pragma endregion

#pragma region Variables

    private:
        Impl *mp_impl;

#pragma endregion
    };
}