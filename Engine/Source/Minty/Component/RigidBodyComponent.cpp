#include "RigidbodyComponent.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Physics/RigidbodyInfo.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Entity/EntitySerializationData.h"

using namespace Minty;

void Minty::Serializer<RigidbodyComponent>::serialize(Writer &writer, RigidbodyComponent const &value)
{
    MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<RigidbodyComponent>::deserialize(Reader &reader, RigidbodyComponent &value)
{
    if (!value.rigidbody)
    {
        // get rigid body info
        RigidbodyInfo info{};
        reader.read("Mass", info.mass);
        reader.read("Friction", info.friction);
        reader.read("Bounce", info.bounce);
        if(reader.indent("Constraints"))
        {
            reader.read("Rotation", info.rotationConstraints);
            // TODO: position constraints
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
        
        reader.read("Kinematic", info.isKinematic);
        reader.read("Static", info.isStatic);

        // create new rigid body
        value.rigidbody = Rigidbody::create(info);
    }
    else
    {
        // override existing rigid body
        Float tempFloat;
        if(reader.read("Mass", tempFloat))
        {
            value.rigidbody->set_mass(tempFloat);
        }
        if(reader.read("Friction", tempFloat))
        {
            value.rigidbody->set_friction(tempFloat);
        }
        if(reader.read("Bounce", tempFloat))
        {
            value.rigidbody->set_bounce(tempFloat);
        }

        Constraints tempConstraints;
        if(reader.indent("Constraints"))
        {
            if(reader.read("Rotation", tempConstraints))
            {
                value.rigidbody->set_rotation_constraints(tempConstraints);
            }
            // TODO: position constraints
            reader.outdent();
        }

        Shared<Collider> tempCollider;
        if(reader.read("Collider", tempCollider) && tempCollider != nullptr && tempCollider != value.rigidbody->get_collider())
        {
            // changing collider of existing rigid body is not supported
            MINTY_ERROR(ErrorCode::Component_InvalidState);
        }
        
        Bool tempBool;
        if(reader.read("Kinematic", tempBool))
        {
            value.rigidbody->set_kinematic(tempBool);
        }
        if(reader.read("Static", tempBool))
        {
            value.rigidbody->set_static(tempBool);
        }
    }
    return true;
}
