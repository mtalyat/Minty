#include "Bullet_Collider.h"
#include "Minty/Data/Transform.h"
#include "Minty/Physics/ColliderInfo.h"
#include "Platform/Bullet/Bullet_Object.h"

using namespace Minty;

Minty::Bullet_Collider::Bullet_Collider(ColliderInfo const &info)
    : Collider(info), mp_root(nullptr), mp_shape(nullptr), mp_object(nullptr), mp_meshInterface(nullptr)
{
    btVector3 size = btVector3(static_cast<btScalar>(info.size.x), static_cast<btScalar>(info.size.y), static_cast<btScalar>(info.size.z));

    // create shape based on info
    switch (info.shape)
    {
    case Shape::Box:
        MINTY_ASSERT(info.size.x > 0 && info.size.y > 0 && info.size.z > 0, ErrorCode::Argument_ExpectedAboveZero);
        mp_shape = new btBoxShape(size * btScalar(0.5)); // Bullet uses half extents for box shapes
        break;
    case Shape::Sphere:
        MINTY_ASSERT(info.size.x > 0, ErrorCode::Argument_ExpectedAboveZero);
        mp_shape = new btSphereShape(size.x() * btScalar(0.5)); // Bullet uses radius for sphere shapes, so take the x size and divide by 2
        break;
    case Shape::Custom:
    {
        MINTY_ASSERT(info.shape == Shape::Custom, ErrorCode::Argument_InvalidValue);
        MINTY_ASSERT(info.mesh != nullptr, ErrorCode::Argument_ExpectedNonNull);

        Shared<Mesh> const &mesh = info.mesh;
        ListContainer const &vertices = mesh->get_vertices();
        ListContainer const &indices = mesh->get_indices();

        // create the mesh interface
        mp_meshInterface = new btTriangleIndexVertexArray();

        // set up an indexed mesh
        btIndexedMesh indexedMesh;
        indexedMesh.m_numTriangles = static_cast<int>(indices.get_count() / 3);
        indexedMesh.m_triangleIndexBase = static_cast<unsigned char const *>(indices.get_data());
        indexedMesh.m_triangleIndexStride = static_cast<int>(indices.get_stride() * 3); // 3 indices per triangle
        indexedMesh.m_numVertices = static_cast<int>(vertices.get_count());
        indexedMesh.m_vertexBase = static_cast<unsigned char const *>(vertices.get_data());
        indexedMesh.m_vertexStride = static_cast<int>(vertices.get_stride());
        if (indices.get_stride() == sizeof(UInt16))
        {
            indexedMesh.m_indexType = PHY_SHORT; // use short indices
        }
        else if (indices.get_stride() == sizeof(UInt32))
        {
            indexedMesh.m_indexType = PHY_INTEGER; // use integer indices
        }
        else
        {
            MINTY_ABORT_F(ErrorCode::Asset_Mesh_InvalidStride, indices.get_stride());
        }

        // add it to the interface
        mp_meshInterface->addIndexedMesh(indexedMesh, indexedMesh.m_indexType);

        // create the bvh shape
        mp_shape = new btBvhTriangleMeshShape(mp_meshInterface, true, true);
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
}

Minty::Bullet_Collider::~Bullet_Collider()
{
    if(mp_root == mp_shape)
    {
        // if the same, only destruct once
        delete mp_root;
    } else
    {
        // if different, destruct both
        delete mp_root;
        delete mp_shape;
    }
    delete mp_meshInterface;
}

void Minty::Bullet_Collider::bind_collision_object(btCollisionObject *const collisionObject)
{
    MINTY_ASSERT(mp_object == nullptr, ErrorCode::Object_AlreadyRegistered);

    // set the collision object reference and update the properties on the collision object
    mp_object = collisionObject;

    if (collisionObject)
    {
        // static
        set_static(*collisionObject, is_static());

        // trigger
        set_trigger(*collisionObject, is_trigger());

        // physics material properties
        Shared<PhysicsMaterial> const &material = get_material();
        collisionObject->setFriction(material->get_dynamic_friction());
        collisionObject->setRollingFriction(material->get_static_friction());
        collisionObject->setRestitution(material->get_bounce());
    }
}

void Minty::Bullet_Collider::set_static(btCollisionObject &object, Bool const isStatic)
{
    if (isStatic)
    {
        object.setCollisionFlags(object.getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
    }
    else
    {
        object.setCollisionFlags(object.getCollisionFlags() & ~btCollisionObject::CF_STATIC_OBJECT);
    }
}

void Minty::Bullet_Collider::set_trigger(btCollisionObject &object, Bool const isTrigger)
{
    if (isTrigger)
    {
        object.setCollisionFlags(object.getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }
    else
    {
        object.setCollisionFlags(object.getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }
}
