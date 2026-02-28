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
        if(reader.indent("Constraints"))
        {
            reader.read("Rotation", info.rotationConstraints);
            // TODO: position constraints
            reader.outdent();
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
