#pragma once

#include "World/Entity/Entity.hpp"
#include "Library/EnTT/EnTT.hpp"
#include "Core/Data/Registry.hpp"
#include "Core/Data/UUID.hpp"
#include "Core/Data/StringView.hpp"

namespace Minty
{
    struct RelationshipComponent;
    struct EntityManagerInfo;

    class EntityManager
    {
#pragma region Constructor

    public:
        EntityManager(EntityManagerInfo const &info);

        EntityManager(EntityManager const &) = delete;

#pragma endregion

#pragma region Operator

    public:
        EntityManager &operator=(EntityManager const &) = delete;

#pragma endregion

#pragma region Accessor

    public:
        inline Bool is_valid(EntityHandle const entity) const { return m_registry.valid(minty_to_entt(entity)); }

#pragma endregion

#pragma region Method

    public:
        EntityHandle create_entity();
        void destroy_entity(EntityHandle const entity);
        EntityHandle find_entity(UUID const id) const;
        String to_string(EntityHandle const entity) const;

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
        Component* try_get_component(EntityHandle const entity);

        template<typename Component>
        Component const* try_get_component(EntityHandle const entity) const;

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

        void set_parent(EntityHandle const entity, EntityHandle const parent);

        EntityHandle get_parent(EntityHandle const entity) const;

    private:
        inline static entt::entity minty_to_entt(EntityHandle const entity) { return static_cast<entt::entity>(entity); }

        inline static EntityHandle entt_to_minty(entt::entity const entity) { return static_cast<EntityHandle>(entity); }

		void remove_from_parent(RelationshipComponent &relationshipComp, RelationshipComponent &parentRelationshipComp);

		void add_to_parent(EntityHandle const entity, RelationshipComponent &relationshipComp, RelationshipComponent &parentRelationshipComp);

#pragma endregion

#pragma region Variable

    private:
        entt::registry m_registry;
        Bool m_needsSorted;

        Registry<EntityHandle> m_registeredComponents;

#pragma endregion
    };
}

#include "EntityManager.inl"