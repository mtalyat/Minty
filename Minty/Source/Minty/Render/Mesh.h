#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/ListContainer.h"
#include "Minty/Render/Buffer.h"
#include "Minty/Render/MeshType.h"

namespace Minty
{
	/// <summary>
	/// The arguments for creating a Mesh.
	/// </summary>
	struct MeshBuilder
	{
		/// <summary>
		/// The UUID of the Mesh.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The type of the Mesh.
		/// </summary>
		MeshType type = MeshType::Empty;

		/// <summary>
		/// The vertex data.
		/// </summary>
		ListContainer vertices;

		/// <summary>
		/// The index data.
		/// </summary>
		ListContainer indices;
	};

	class Mesh
		: public Asset
	{
#pragma region Variables

	private:
		ListContainer m_vertices;
		Owner<Buffer> m_vertexBuffer;

		ListContainer m_indices;
		Owner<Buffer> m_indexBuffer;

#pragma endregion

#pragma region Constructors

	public:
		Mesh(MeshBuilder const& builder);

		~Mesh()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the vertices of this Mesh.
		/// </summary>
		/// <returns>The ListContainer with the data.</returns>
		ListContainer& get_vertices() { return m_vertices; }

		/// <summary>
		/// Gets the vertices of this Mesh.
		/// </summary>
		/// <returns>The ListContainer with the data.</returns>
		ListContainer const& get_vertices() const { return m_vertices; }

		/// <summary>
		/// Gets the indices of this Mesh.
		/// </summary>
		/// <returns>The ListContainer with the data.</returns>
		ListContainer& get_indices() { return m_indices; }

		/// <summary>
		/// Gets the indices of this Mesh.
		/// </summary>
		/// <returns>The ListContainer with the data.</returns>
		ListContainer const& get_indices() const { return m_indices; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when this Mesh is bound for rendering.
		/// </summary>
		virtual void on_bind() const = 0;

	private:
		void initialize(MeshBuilder const& builder);

		void initialize_quad();

		void initialize_cube();

#pragma endregion
	};
}