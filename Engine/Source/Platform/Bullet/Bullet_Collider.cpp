#include "Bullet_Collider.h"
#include "Minty/Physics/ColliderInfo.h"
#include "Platform/Bullet/Bullet_Object.h"

Minty::Bullet_Collider::Bullet_Collider(ColliderInfo const &info)
    : Collider(info), mp_shape(nullptr), mp_object(nullptr)
{
    btVector3 size = btVector3(static_cast<btScalar>(info.size.x), static_cast<btScalar>(info.size.y), static_cast<btScalar>(info.size.z));
    btVector3 offset = btVector3(static_cast<btScalar>(info.offset.x), static_cast<btScalar>(info.offset.y), static_cast<btScalar>(info.offset.z));

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

    // if static, create a collision object
    if (info.isStatic)
    {
        // create transform data
        btTransform btTransform = btTransform::getIdentity();
        btTransform.setOrigin(offset);

        // create the collision object
        btCollisionObject *collisionObject = new btCollisionObject();
        collisionObject->setCollisionShape(mp_shape);
        collisionObject->setWorldTransform(btTransform);

        // create object data
        Bullet_Object *objectData = new Bullet_Object();
        collisionObject->setUserPointer(objectData);

        // update collider
        mp_object = collisionObject;
    }
}

Minty::Bullet_Collider::~Bullet_Collider()
{
    delete mp_shape;
    if(mp_object)
    {
        delete static_cast<Bullet_Object *>(mp_object->getUserPointer());
        delete mp_object;
    }
}

