#include "Bullet_Collider.h"
#include "Minty/Data/Transform.h"
#include "Minty/Physics/ColliderInfo.h"
#include "Platform/Bullet/Bullet_Object.h"

using namespace Minty;

Minty::Bullet_Collider::Bullet_Collider(ColliderInfo const &info)
    : Collider(info), mp_root(nullptr), mp_shape(nullptr), mp_object(nullptr)
{
    btVector3 size = btVector3(static_cast<btScalar>(info.size.x), static_cast<btScalar>(info.size.y), static_cast<btScalar>(info.size.z));

    // create shape based on info
    switch (info.shape)
    {
    case Shape::Box:
        MINTY_ASSERT(info.size.x > 0 && info.size.y > 0 && info.size.z > 0, ErrorCode::Argument_ExpectedAboveZero);
        mp_shape = new btBoxShape(size * btScalar(0.5)); // Bullet uses half extents for box shapes
        break;
    case Shape::Custom:
    {
        MINTY_ASSERT(info.shape == Shape::Custom, ErrorCode::Argument_InvalidValue);
        MINTY_ASSERT(info.mesh != nullptr, ErrorCode::Argument_ExpectedNonNull);

        Shared<Mesh> const &mesh = info.mesh;
        ListContainer const &vertices = mesh->get_vertices();
        ListContainer const &indices = mesh->get_indices();

        // create the mesh interface
        btTriangleIndexVertexArray *meshInterface = new btTriangleIndexVertexArray();

        // set up an indexed mesh
        btIndexedMesh indexedMesh;
        indexedMesh.m_numTriangles = static_cast<int>(indices.get_count() / 3);
        indexedMesh.m_triangleIndexBase = static_cast<unsigned char const *>(indices.get_data());
        indexedMesh.m_triangleIndexStride = static_cast<int>(indices.get_stride() * 3); // 3 indices per triangle
        indexedMesh.m_numVertices = static_cast<int>(vertices.get_count());
        indexedMesh.m_vertexBase = static_cast<unsigned char const *>(vertices.get_data());
        indexedMesh.m_vertexStride = static_cast<int>(vertices.get_stride());
        if (indices.get_stride() == sizeof(UShort))
        {
            indexedMesh.m_indexType = PHY_SHORT; // use short indices
        }
        else if (indices.get_stride() == sizeof(UInt))
        {
            indexedMesh.m_indexType = PHY_INTEGER; // use integer indices
        }
        else
        {
            MINTY_ABORT_F(ErrorCode::Asset_Mesh_InvalidStride, indices.get_stride());
        }

        // add it to the interface
        meshInterface->addIndexedMesh(indexedMesh, indexedMesh.m_indexType);

        // create the bvh shape
        mp_shape = new btBvhTriangleMeshShape(meshInterface, true, true);
    }
    break;
    default:
        MINTY_NOT_IMPLEMENTED();
        break;
    }

    // if an offset given, apply it
    btVector3 offset = btVector3(static_cast<btScalar>(info.offset.x), static_cast<btScalar>(info.offset.y), static_cast<btScalar>(info.offset.z));
    if (info.offset != Math::ZERO)
    {
        btCompoundShape *const root = new btCompoundShape();
        btTransform localTransform = btTransform::getIdentity();
        localTransform.setOrigin(offset);
        root->addChildShape(localTransform, mp_shape);
        mp_root = root;
    }
    else
    {
        mp_root = mp_shape;
    }

    // if static, create a collision object
    if (info.isStatic)
    {
        // create transform data
        btTransform btTransform = btTransform::getIdentity();
        btTransform.setOrigin(offset);

        // create the collision object
        btCollisionObject *collisionObject = new btCollisionObject();
        collisionObject->setCollisionShape(mp_root);
        collisionObject->setWorldTransform(btTransform);

        // create object data
        Bullet_Object *objectData = new Bullet_Object();
        collisionObject->setUserPointer(objectData);

        // update collider
        set_collision_object(collisionObject);
    }
}

Minty::Bullet_Collider::~Bullet_Collider()
{
    delete mp_shape;
    if (mp_object)
    {
        delete static_cast<Bullet_Object *>(mp_object->getUserPointer());
        delete mp_object;
    }
}

Float3 Minty::Bullet_Collider::get_position() const
{
    // get the position from the root object
    btVector3 const btPosition = mp_object->getWorldTransform().getOrigin();
    return Float3(static_cast<Float>(btPosition.x()), static_cast<Float>(btPosition.y()), static_cast<Float>(btPosition.z()));
}

void Minty::Bullet_Collider::set_position(Float3 const &position)
{
    // set the position on the root object
    btVector3 const btPosition = btVector3(static_cast<btScalar>(position.x), static_cast<btScalar>(position.y), static_cast<btScalar>(position.z));
    btTransform transform = mp_object->getWorldTransform();
    transform.setOrigin(btPosition);
    mp_object->setWorldTransform(transform);
}

Quaternion Minty::Bullet_Collider::get_rotation() const
{
    // get the rotation from the root object
    btQuaternion const btRotation = mp_object->getWorldTransform().getRotation();
    return Quaternion(static_cast<Float>(btRotation.w()), static_cast<Float>(btRotation.x()), static_cast<Float>(btRotation.y()), static_cast<Float>(btRotation.z()));
}

void Minty::Bullet_Collider::set_rotation(Quaternion const &rotation)
{
    // set the rotation on the root object
    btQuaternion const btRotation = btQuaternion(static_cast<btScalar>(rotation.x), static_cast<btScalar>(rotation.y), static_cast<btScalar>(rotation.z), static_cast<btScalar>(rotation.w));
    btTransform transform = mp_object->getWorldTransform();
    transform.setRotation(btRotation);
    mp_object->setWorldTransform(transform);
}

void Minty::Bullet_Collider::get_transform(Transform &out_transform) const
{
    // get the transform from the root object
    btTransform const btTransform = mp_object->getWorldTransform();
    out_transform.set_local_position(Float3(static_cast<Float>(btTransform.getOrigin().x()), static_cast<Float>(btTransform.getOrigin().y()), static_cast<Float>(btTransform.getOrigin().z())));
    btQuaternion const btRotation = btTransform.getRotation();
    out_transform.set_local_rotation(Quaternion(static_cast<Float>(btRotation.w()), static_cast<Float>(btRotation.x()), static_cast<Float>(btRotation.y()), static_cast<Float>(btRotation.z())));
}

void Minty::Bullet_Collider::set_transform(Transform const &transform)
{
    // set the transform on the root object
    btVector3 const btPosition = btVector3(static_cast<btScalar>(transform.get_global_position().x), static_cast<btScalar>(transform.get_global_position().y), static_cast<btScalar>(transform.get_global_position().z));
    Quaternion const rotation = transform.get_global_rotation();
    btQuaternion const btRotation = btQuaternion(static_cast<btScalar>(rotation.x), static_cast<btScalar>(rotation.y), static_cast<btScalar>(rotation.z), static_cast<btScalar>(rotation.w));
    btTransform btTransform = btTransform::getIdentity();
    btTransform.setOrigin(btPosition);
    btTransform.setRotation(btRotation);
    mp_object->setWorldTransform(btTransform);
}

void Minty::Bullet_Collider::set_collision_object(btCollisionObject *const object)
{
    MINTY_ASSERT(mp_object == nullptr || object == nullptr, ErrorCode::Object_InvalidState);
    mp_object = object;

    // set flags if not null
    if (mp_object != nullptr)
    {
        // if static, set the flag
        if (is_static())
        {
            mp_object->setCollisionFlags(mp_object->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
        }

        // if a trigger, set the flag
        if (is_trigger())
        {
            mp_object->setCollisionFlags(mp_object->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
        }
    }
}