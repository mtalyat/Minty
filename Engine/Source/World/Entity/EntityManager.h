#pragma once

#include "World/Entity/Entity.h"
#include "Library/EnTT/EnTT.h"
#include "Core/Data/Registry.h"
#include "Core/Data/UUID.h"
#include "Core/Data/StringView.h"

namespace Minty
{
    struct EntityManagerInfo;

    class EntityManager
    {
#pragma region Constructor

    public:
        EntityManager(EntityManagerInfo const &info);
        ~EntityManager();

        EntityManager(EntityManager const &) = delete;
        EntityManager(EntityManager &&) = delete;

#pragma endregion

#pragma region Operator

    public:
        EntityManager &operator=(EntityManager const &) = delete;
        EntityManager &operator=(EntityManager &&) = delete;

#pragma endregion

#pragma region Accessor

    public:
        inline Bool is_valid(EntityHandle const entity) const { return m_registry.valid(minty_to_entt(entity)); }

#pragma endregion

#pragma region Method

    public:
        EntityHandle create_entity();
        void destroy_entity(EntityHandle const entity);

        template<typename Component, typename... Args>
        decltype(auto) add_component(EntityHandle const entity, Args &&...args);

        template<typename Component, typename... Args>
        decltype(auto) get_or_add_component(EntityHandle const entity, Args &&...args);

        template<typename Component, typename... Args>
        decltype(auto) add_or_replace_component(EntityHandle const entity, Args &&...args);

        Bool add_component_by_name(EntityHandle const entity, StringView const componentName);

        template<typename Component>
        decltype(auto) get_component(EntityHandle const entity);

        template<typename Component>
        decltype(auto) get_component(EntityHandle const entity) const;

        template<typename Component>
        Bool has_component(EntityHandle const entity) const;

        template<typename... Components>
        Bool has_all_component(EntityHandle const entity) const;

        template<typename... Components>
        Bool has_any_component(EntityHandle const entity) const;

        template<typename Component>
        void remove_component(EntityHandle const entity);

        template<typename Component>
        void register_component(StringView const name);

    private:
        inline entt::entity minty_to_entt(EntityHandle const entity) const { return static_cast<entt::entity>(entity); }

        inline EntityHandle entt_to_minty(entt::entity const entity) const { return static_cast<EntityHandle>(entity); }

#pragma endregion

#pragma region Variable

    private:
        entt::registry m_registry;

        Registry<EntityHandle> m_registeredComponents;

#pragma endregion
    };
}

#include "EntityManager.inl"