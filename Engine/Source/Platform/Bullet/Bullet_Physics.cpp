#include "Bullet_Physics.h"
#include "Minty/Physics/PhysicsMaterial.h"

using namespace Minty;

btTransform Minty::Bullet_Physics::to_bullet(Transform const &transform)
{
    btTransform btTransform;
    btTransform.setIdentity();
    btTransform.setOrigin(to_bullet(transform.get_global_position()));
    btTransform.setRotation(to_bullet(transform.get_global_rotation()));
    return btTransform;
}
