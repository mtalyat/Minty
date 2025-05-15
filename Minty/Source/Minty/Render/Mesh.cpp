#include "pch.h"
#include "Mesh.h"

using namespace Minty;

Minty::Mesh::Mesh(MeshBuilder const& builder)
	: Asset(builder.id)
	, m_vertices()
	, m_vertexBuffer(nullptr)
	, m_indices()
	, m_indexBuffer(nullptr)
{
	MINTY_ASSERT(builder.type == MeshType::Custom || (builder.vertices.is_empty() && builder.indices.is_empty()), "Non-custom meshes should not be given vertex or index arguments.");
	MINTY_ASSERT(builder.type != MeshType::Custom || (!builder.vertices.is_empty() && !builder.indices.is_empty()), "Custom meshes require both vertex and index arguments.");

	switch (builder.type)
	{
	case MeshType::Empty:
		break;
	case MeshType::Custom:
		initialize(builder);
		break;
	case MeshType::Quad:
		initialize_quad();
		break;
	case MeshType::Cube:
		initialize_cube();
		break;
	default:
		MINTY_ASSERT(false, "Unknown Mesh type.");
		break;
	}
}

void Minty::Mesh::initialize(MeshBuilder const& builder)
{
	m_vertices = builder.vertices;
	BufferBuilder vertexBufferBuilder{};
	vertexBufferBuilder.data = m_vertices.get_data();
	vertexBufferBuilder.size = m_vertices.get_size();
	vertexBufferBuilder.usage = BufferUsage::Vertex;
	vertexBufferBuilder.frequent = false;
	m_vertexBuffer = Buffer::create(vertexBufferBuilder);

	m_indices = builder.indices;
	BufferBuilder indexBufferBuilder{};
	indexBufferBuilder.data = m_indices.get_data();
	indexBufferBuilder.size = m_indices.get_size();
	indexBufferBuilder.usage = BufferUsage::Index;
	indexBufferBuilder.frequent = false;
	m_indexBuffer = Buffer::create(indexBufferBuilder);
}

void Minty::Mesh::initialize_quad()
{
	// create mesh data
#define SIZE 0.5f

#define LEFT_TOP_BACK -SIZE, 0.0f, -SIZE
#define LEFT_TOP_FRONT -SIZE, 0.0f, SIZE
#define RIGHT_TOP_BACK SIZE, 0.0f, -SIZE
#define RIGHT_TOP_FRONT SIZE, 0.0f, SIZE

#define UP 0.0f, -1.0f, 0.0f

#define TOP_LEFT 0.0f, 0.0f
#define TOP_RIGHT 1.0f, 0.0f
#define BOTTOM_LEFT 0.0f, 1.0f
#define BOTTOM_RIGHT 1.0f, 1.0f

	// create data
	Float vertices[] =
	{
		LEFT_TOP_BACK, UP, TOP_LEFT,
		LEFT_TOP_FRONT, UP, BOTTOM_LEFT,
		RIGHT_TOP_BACK, UP, TOP_RIGHT,
		RIGHT_TOP_FRONT, UP, BOTTOM_RIGHT
	};
	UShort indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	// create builder
	MeshBuilder builder{};
	Size const vertexStride = sizeof(Float) * 8;
	builder.vertices = ListContainer(vertices, vertexStride, sizeof(vertices) / vertexStride);
	Size const indexStride = sizeof(UShort);
	builder.indices = ListContainer(indices, indexStride, sizeof(indices) / indexStride);

	initialize(builder);

#undef SIZE
#undef LEFT_TOP_BACK 
#undef LEFT_TOP_FRONT
#undef RIGHT_TOP_BACK
#undef RIGHT_TOP_FRONT
#undef UP
#undef TOP_LEFT
#undef TOP_RIGHT
#undef BOTTOM_LEFT
#undef BOTTOM_RIGHT
}

void Minty::Mesh::initialize_cube()
{
#define SIZE 0.5f

#define LEFT_BOTTOM_BACK -SIZE, SIZE, -SIZE
#define LEFT_BOTTOM_FRONT -SIZE, SIZE, SIZE
#define LEFT_TOP_BACK -SIZE, -SIZE, -SIZE
#define LEFT_TOP_FRONT -SIZE, -SIZE, SIZE
#define RIGHT_BOTTOM_BACK SIZE, SIZE, -SIZE
#define RIGHT_BOTTOM_FRONT SIZE, SIZE, SIZE
#define RIGHT_TOP_BACK SIZE, -SIZE, -SIZE
#define RIGHT_TOP_FRONT SIZE, -SIZE, SIZE

#define UP 0.0f, -1.0f, 0.0f
#define DOWN 0.0f, 1.0, 0.0f
#define LEFT -1.0f, 0.0f, 0.0f
#define RIGHT 1.0f, 0.0f, 0.0f
#define FORWARD 0.0f, 0.0f, 1.0f
#define BACKWARD 0.0f, 0.0f, -1.0f

#define TOP_LEFT 0.0f, 0.0f
#define TOP_RIGHT 1.0f, 0.0f
#define BOTTOM_LEFT 0.0f, 1.0f
#define BOTTOM_RIGHT 1.0f, 1.0f

	Float vertices[] =
	{
		// UP
		LEFT_TOP_BACK, UP, TOP_RIGHT,
		LEFT_TOP_FRONT, UP, BOTTOM_RIGHT,
		RIGHT_TOP_FRONT, UP, BOTTOM_LEFT,
		RIGHT_TOP_BACK, UP, TOP_LEFT,

		// DOWN
		RIGHT_BOTTOM_BACK, DOWN, TOP_RIGHT,
		RIGHT_BOTTOM_FRONT, DOWN, BOTTOM_RIGHT,
		LEFT_BOTTOM_FRONT, DOWN, BOTTOM_LEFT,
		LEFT_BOTTOM_BACK, DOWN, TOP_LEFT,

		// RIGHT
		RIGHT_BOTTOM_BACK, RIGHT, BOTTOM_LEFT,
		RIGHT_TOP_BACK, RIGHT, TOP_LEFT,
		RIGHT_TOP_FRONT, RIGHT, TOP_RIGHT,
		RIGHT_BOTTOM_FRONT, RIGHT, BOTTOM_RIGHT,

		// LEFT
		LEFT_BOTTOM_FRONT, LEFT, BOTTOM_LEFT,
		LEFT_TOP_FRONT, LEFT, TOP_LEFT,
		LEFT_TOP_BACK, LEFT, TOP_RIGHT,
		LEFT_BOTTOM_BACK, LEFT, BOTTOM_RIGHT,

		// FRONT
		RIGHT_BOTTOM_FRONT, FORWARD, BOTTOM_LEFT,
		RIGHT_TOP_FRONT, FORWARD, TOP_LEFT,
		LEFT_TOP_FRONT, FORWARD, TOP_RIGHT,
		LEFT_BOTTOM_FRONT, FORWARD, BOTTOM_RIGHT,

		// BACK
		LEFT_BOTTOM_BACK, BACKWARD, BOTTOM_LEFT,
		LEFT_TOP_BACK, BACKWARD, TOP_LEFT,
		RIGHT_TOP_BACK, BACKWARD, TOP_RIGHT,
		RIGHT_BOTTOM_BACK, BACKWARD, BOTTOM_RIGHT,
	};

	UShort indices[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23,
	};

	MeshBuilder builder{};
	Size const vertexStride = sizeof(Float) * 8;
	builder.vertices = ListContainer(vertices, vertexStride, sizeof(vertices) / (vertexStride));
	Size const indexStride = sizeof(UShort);
	builder.indices = ListContainer(indices, indexStride, sizeof(indices) / indexStride);
	initialize(builder);

#undef SIZE
#undef LEFT_BOTTOM_BACK
#undef LEFT_BOTTOM_FRONT 
#undef LEFT_TOP_BACK
#undef LEFT_TOP_FRONT
#undef RIGHT_BOTTOM_BACK 
#undef RIGHT_BOTTOM_FRONT
#undef RIGHT_TOP_BACK
#undef RIGHT_TOP_FRONT
#undef UP
#undef DOWN
#undef LEFT
#undef RIGHT
#undef FORWARD
#undef BACKWARD
#undef TOP_LEFT
#undef TOP_RIGHT
#undef BOTTOM_LEFT
#undef BOTTOM_RIGHT
}

Owner<Mesh> Minty::Mesh::create(MeshBuilder const& builder)
{
	return Owner<Mesh>(builder);
}
