#include "RigidBodyComponent.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Physics/RigidBodyInfo.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Entity/EntitySerializationData.h"

using namespace Minty;

void Minty::Serializer<RigidBodyComponent>::serialize(Writer &writer, RigidBodyComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

void Minty::Serializer<RigidBodyComponent>::deserialize(Reader &reader, RigidBodyComponent &value)
{
    if (!value.rigidBody)
    {
        // get rigid body info
        RigidBodyInfo info{};
        reader.read("Kinematic", info.isKinematic);
        reader.read("Static", info.isStatic);
        reader.read("Mass", info.mass);
        reader.read("Friction", info.friction);
        reader.read("Bounce", info.bounce);
        if(reader.indent("Constraints"))
        {
            reader.read("Rotation", info.rotationConstraints);
            reader.outdent();
        }
        
        if(!reader.read("Collider", info.collider))
        {
            // if no collider given, check this entity for one
            EntitySerializationData const* entityData = static_cast<EntitySerializationData const*>(reader.get_user_data());
            MINTY_ASSERT(entityData != nullptr, ErrorCode::Serialization_InvalidData);
            Entity const entity = entityData->entity;
            ColliderComponent const* const colliderComp = entityData->entityManager->try_get_component<ColliderComponent>(entity);
            if(colliderComp != nullptr)
            {
                info.collider = colliderComp->collider;
            }
        }

        // create new rigid body
        value.rigidBody = RigidBody::create(info);
    }
    else
    {
        // override existing rigid body
        Bool tempBool;
        if(reader.read("Kinematic", tempBool))
        {
            value.rigidBody->set_kinematic(tempBool);
        }
        if(reader.read("Static", tempBool))
        {
            value.rigidBody->set_static(tempBool);
        }
        Float tempFloat;
        if(reader.read("Mass", tempFloat))
        {
            value.rigidBody->set_mass(tempFloat);
        }
        if(reader.read("Friction", tempFloat))
        {
            value.rigidBody->set_friction(tempFloat);
        }
        if(reader.read("Bounciness", tempFloat))
        {
            value.rigidBody->set_bounce(tempFloat);
        }
        Shared<Collider> tempCollider;
        if(reader.read("Collider", tempCollider) && tempCollider != nullptr && tempCollider != value.rigidBody->get_collider())
        {
            // changing collider of existing rigid body is not supported
            MINTY_ERROR(ErrorCode::Component_InvalidState);
        }
    }
}
