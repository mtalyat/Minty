#include "pch.h"
#include "EntityManager.h"
#include "EntityManagerInfo.h"

#include "World/Component/NameComponent.h"
#include "World/Component/UUIDComponent.h"

using namespace Minty;

Minty::EntityManager::EntityManager(EntityManagerInfo const &info)
    : m_registry(),
      m_registeredComponents()
{
}

Minty::EntityManager::~EntityManager()
{
}

EntityHandle Minty::EntityManager::create_entity()
{
    return entt_to_minty(m_registry.create());
}

void Minty::EntityManager::destroy_entity(EntityHandle const entity)
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);

    // remove the entity
    m_registry.destroy(minty_to_entt(entity));
}

Bool Minty::EntityManager::add_component_by_name(EntityHandle const entity, StringView const componentName)
{
    MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
    MINTY_ASSERT(m_registeredComponents.is_registered(componentName), ErrorCodeEnum::Component_NotRegistered);
    MINTY_ASSERT(!m_registeredComponents.has(componentName, entity), ErrorCodeEnum::Object_InvalidState); // already has component
    m_registeredComponents.add(componentName, entity);
    return true;
}
