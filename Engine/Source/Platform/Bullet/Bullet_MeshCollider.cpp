#include "pch.h"
#include "Bullet_MeshCollider.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Physics/ColliderInfo.h"

using namespace Minty;

Minty::Bullet_MeshCollider::Bullet_MeshCollider(ColliderInfo const& info)
	: Bullet_Collider(info)
{
	MINTY_ASSERT(info.shape == Shape::Custom, ErrorCode::Argument_InvalidValue);
	MINTY_ASSERT(info.mesh != nullptr, ErrorCode::Argument_ExpectedNonNull);

	Ref<Mesh> mesh = info.mesh;
	ListContainer const& vertices = mesh->get_vertices();
	ListContainer const& indices = mesh->get_indices();

	// create the mesh interface
	btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray();

	// set up an indexed mesh
	btIndexedMesh indexedMesh;
	indexedMesh.m_numTriangles = static_cast<int>(indices.get_count() / 3);
	indexedMesh.m_triangleIndexBase = static_cast<unsigned char const*>(indices.get_data());
	indexedMesh.m_triangleIndexStride = static_cast<int>(indices.get_stride() * 3); // 3 indices per triangle
	indexedMesh.m_numVertices = static_cast<int>(vertices.get_count());
	indexedMesh.m_vertexBase = static_cast<unsigned char const*>(vertices.get_data());
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
