#include "pch.h"
#include "Bullet_MeshCollider.h"
#include "Minty/Render/Mesh.h"

using namespace Minty;

Minty::Bullet_MeshCollider::Bullet_MeshCollider(ColliderBuilder const& builder)
	: Bullet_Collider(builder)
{
	MINTY_ASSERT(builder.shape == Shape::Custom, "MeshCollider must have a Custom shape.");
	MINTY_ASSERT(builder.mesh != nullptr, "MeshCollider must have custom data.");

	Ref<Mesh> mesh = builder.mesh;
	ListContainer const& vertices = mesh->get_vertices();
	ListContainer const& indices = mesh->get_indices();

	// create the mesh interface
	btTriangleIndexVertexArray* meshInterface = new btTriangleIndexVertexArray(
		static_cast<int>(indices.get_count()),
		static_cast<int*>(indices.get_data()),
		static_cast<int>(indices.get_stride()),
		static_cast<int>(vertices.get_count()),
		static_cast<btScalar*>(vertices.get_data()),
		static_cast<int>(vertices.get_stride())
	);

	// create the bvh shape
	mp_shape = new btBvhTriangleMeshShape(meshInterface, true, true);
}
