#include "pch.hpp"
#include "CollisionManager.hpp"

using namespace Minty;

CollisionManager* Minty::CollisionManager::sp_singleton = nullptr;

Minty::CollisionManager::CollisionManager(CollisionManagerInfo const &info)
: m_nameToCollision(),
  m_collisionToName()
{
    MINTY_ASSERT(!sp_singleton, ErrorCodeEnum::Singleton_AlreadyExists);
    sp_singleton = this;
}

Minty::CollisionManager::~CollisionManager()
{
    MINTY_ASSERT(sp_singleton == this, ErrorCodeEnum::Singleton_DifferentObject);
    sp_singleton = nullptr;
}

Collision Minty::CollisionManager::get_collision(String const &name) const
{
    MINTY_ASSERT(m_nameToCollision.contains(name), ErrorCodeEnum::Layer_NotFound, name);
    return m_nameToCollision[name];
}

String Minty::CollisionManager::get_collision_name(Collision const collision) const
{
    MINTY_ASSERT(is_valid(collision), ErrorCodeEnum::Layer_NotFound, collision);
    return m_collisionToName[collision.value];
}

CollisionMask Minty::CollisionManager::get_collision_mask(Collision const collision) const
{
    MINTY_ASSERT(is_valid(collision), ErrorCodeEnum::Layer_NotFound, collision);
    return m_collisionMasks[collision.value];
}

Bool Minty::CollisionManager::is_valid(Collision const collision) const
{
    if (collision.value >= COLLISION_COUNT)
    {
        return false;
    }
    return !m_collisionToName[collision.value].is_empty();
}

Bool Minty::CollisionManager::is_valid(String const &name) const
{
    return m_nameToCollision.contains(name);
}

Collision Minty::CollisionManager::create_collision(String const &name, CollisionMask const mask)
{
    MINTY_ASSERT(!name.is_empty(), ErrorCodeEnum::Argument_ExpectedNonEmpty);

    // iterate and find an empty collision
    for (CollisionType i = 0; i < COLLISION_COUNT; ++i)
    {
        if (m_collisionToName[i].is_empty())
        {
            Collision collision(i);
            create_collision(name, mask, collision);
            return collision;
        }
    }

    MINTY_ABORT(ErrorCodeEnum::Layer_MaxLayersReached);
    return COLLISION_DEFAULT;
}

void Minty::CollisionManager::create_collision(String const &name, CollisionMask const mask, Collision const collision)
{
    MINTY_ASSERT(!name.is_empty(), ErrorCodeEnum::Argument_ExpectedNonEmpty);
    MINTY_ASSERT(!is_valid(collision), ErrorCodeEnum::Layer_AlreadyExists);

    // add the collision data
    m_nameToCollision[name] = collision;
    m_collisionToName[collision.value] = name;
    m_collisionMasks[collision.value] = mask;

    // add the collision to all masks that have it
    CollisionMask const collisionMask = collision.to_mask();
    for (CollisionType i = 0; i < COLLISION_COUNT; ++i)
    {
        if (mask.has_collision(i) || i == collision)
        {
            m_collisionMasks[i] |= collisionMask;
        }
    }
}

void Minty::CollisionManager::destroy_collision(Collision const collision)
{
    MINTY_ASSERT(collision != COLLISION_DEFAULT, ErrorCodeEnum::Layer_Protected);
    MINTY_ASSERT(is_valid(collision), ErrorCodeEnum::Layer_NotFound, collision);

    // remove the collision from all masks
    CollisionMask invertedCollisionMask = ~collision.to_mask();
    for (CollisionType i = 0; i < COLLISION_COUNT; ++i)
    {
        m_collisionMasks[i] &= invertedCollisionMask;
    }

    // remove collision data
    String const& name = m_collisionToName[collision.value];
    m_nameToCollision.remove(name);
    m_collisionToName[collision.value] = String();
    m_collisionMasks[collision.value] = CollisionMask();
}

CollisionManager &Minty::CollisionManager::get_singleton()
{
    MINTY_ASSERT(sp_singleton, ErrorCodeEnum::Singleton_DoesNotExist);
    return *sp_singleton;
}
