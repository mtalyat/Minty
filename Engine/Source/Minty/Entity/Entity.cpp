#include "pch.h"
#include "Entity.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Data/UUID.h"

using namespace Minty;

Bool Minty::Parser<Entity>::parse(StringView const str, Entity &value)
{
    EntityManager& entityManager = EntityManager::get_singleton();
    UUID id;
    if(Parser<UUID>::parse(str, id))
    {
        value = entityManager.get_entity(id);
        return true;
    }
    return false;
}

String Minty::Parser<Entity>::to_string(Entity const &value)
{
    EntityManager& entityManager = EntityManager::get_singleton();
    UUID id = entityManager.get_id(value);
    return Parser<UUID>::to_string(id);
}