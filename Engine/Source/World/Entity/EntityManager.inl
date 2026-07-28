#pragma once
#include "Core/Debug/Debug.hpp"
#include "EntityManager.hpp"

template <typename Component, typename... Args>
decltype(auto) Minty::EntityManager::add(EntityHandle const entity, Args &&...args)
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    return m_registry.emplace<Component>(minty_to_entt(entity), std::forward<Args>(args)...);
}

template <typename Component, typename... Args>
decltype(auto) Minty::EntityManager::get_or_add(EntityHandle const entity, Args &&...args)
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    return m_registry.get_or_emplace<Component>(minty_to_entt(entity), std::forward<Args>(args)...);
}

template <typename Component, typename... Args>
decltype(auto) Minty::EntityManager::add_or_replace(EntityHandle const entity, Args &&...args)
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    return m_registry.emplace_or_replace<Component>(minty_to_entt(entity), std::forward<Args>(args)...);
}

template <typename Component>
decltype(auto) Minty::EntityManager::get(EntityHandle const entity)
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    return m_registry.get<Component>(minty_to_entt(entity));
}

template <typename Component>
decltype(auto) Minty::EntityManager::get(EntityHandle const entity) const
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    return m_registry.get<Component>(minty_to_entt(entity));
}

template <typename Component>
Component *Minty::EntityManager::try_get(EntityHandle const entity)
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    return m_registry.try_get<Component>(minty_to_entt(entity));
}

template <typename Component>
Component const *Minty::EntityManager::try_get(EntityHandle const entity) const
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    return m_registry.try_get<Component>(minty_to_entt(entity));
}

template <typename Component>
Minty::Bool Minty::EntityManager::has(EntityHandle const entity) const
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    return m_registry.any_of<Component>(minty_to_entt(entity));
}

template <typename... Components>
Minty::Bool Minty::EntityManager::has_all(EntityHandle const entity) const
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    return m_registry.all_of<Components...>(minty_to_entt(entity));
}

template <typename... Components>
Minty::Bool Minty::EntityManager::has_any(EntityHandle const entity) const
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    return m_registry.any_of<Components...>(minty_to_entt(entity));
}

template <typename Component>
void Minty::EntityManager::remove(EntityHandle const entity)
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    m_registry.remove<Component>(minty_to_entt(entity));
}

template <typename Component>
void Minty::EntityManager::register_component(StringView const name)
{
    // ensure not already registered
    MINTY_ASSERT(!m_registeredComponents.is_registered<Component>(), ErrorCodeEnum::Component_AlreadyRegistered);

    // create component data
    RegistryData<EntityManager&, EntityHandle> componentData{};
    componentData.name = name;
    componentData.add = [this](EntityHandle const entity) { add<Component>(entity); };
    componentData.remove = [this](EntityHandle const entity) { remove<Component>(entity); };
    componentData.has = [this](EntityHandle const entity) { return has<Component>(entity); };

    // add to registered components
    m_registeredComponents.register_type<Component>(std::move(componentData));
}
