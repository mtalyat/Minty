#pragma once

#include "World/Entity/Entity.hpp"
#include "Library/EnTT/EnTT.hpp"
#include "Core/Data/Registry.hpp"
#include "Core/Data/UUID.hpp"
#include "Core/Data/StringView.hpp"
#include "World/Entity/EntityView.hpp"

namespace Minty
{
    class Scene;
    struct RelationshipComponent;
    struct EntityManagerInfo;

    class EntityManager
    {
#pragma region Constructor

    public:
        EntityManager(EntityManagerInfo const &info, Scene &scene);

        EntityManager(EntityManager const &) = delete;

#pragma endregion

#pragma region Operator

    public:
        EntityManager &operator=(EntityManager const &) = delete;

#pragma endregion

#pragma region Accessor

    public:
        inline Bool is_valid(EntityHandle const entity) const { return m_registry.valid(minty_to_entt(entity)); }

        inline void set_scene(Scene &scene) { mp_scene = &scene; }

#pragma endregion

#pragma region Method

    public:
        EntityHandle create();
        void destroy(EntityHandle const entity);
        EntityHandle find(UUID const id) const;
        String to_string(EntityHandle const entity) const;

        template <typename Component, typename... Args>
        decltype(auto) add(EntityHandle const entity, Args &&...args);

        template <typename Component, typename... Args>
        decltype(auto) get_or_add(EntityHandle const entity, Args &&...args);

        template <typename Component, typename... Args>
        decltype(auto) add_or_replace(EntityHandle const entity, Args &&...args);

        Bool add_by_name(EntityHandle const entity, StringView const componentName);

        template <typename Component>
        decltype(auto) get(EntityHandle const entity);

        template <typename Component>
        decltype(auto) get(EntityHandle const entity) const;

        template <typename Component>
        Component *try_get(EntityHandle const entity);

        template <typename Component>
        Component const *try_get(EntityHandle const entity) const;

        template <typename Component>
        Bool has(EntityHandle const entity) const;

        template <typename... Components>
        Bool has_all(EntityHandle const entity) const;

        template <typename... Components>
        Bool has_any(EntityHandle const entity) const;

        template <typename Component>
        void remove(EntityHandle const entity);

        template <typename Component>
        void register_component(StringView const name);

        inline entt::registry &get_registry() { return m_registry; }

        inline entt::registry const &get_registry() const { return m_registry; }

        template <typename... Components>
        auto view();

        template <typename... Components>
        auto view() const;

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
        Scene *mp_scene;
        entt::registry m_registry;
        Bool m_needsSorted;

        Registry<EntityHandle> m_registeredComponents;

#pragma endregion
    };
}

#include "EntityManager.inl"