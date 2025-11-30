#ifndef MINTY_RENDER_MESH_H
#define MINTY_RENDER_MESH_H

/**
 * @file Mesh.h
 * @brief Header file for the Mesh class.
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/ListContainer.h"
#include "Minty/Render/Buffer.h"
#include "Minty/Render/MeshType.h"

namespace Minty
{
	struct MeshInfo;
	
	/**
	 * @class Mesh
	 * @brief Represents a 3D mesh asset.
	 */
	class Mesh
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Mesh.
		 * @param info The arguments.
		 */
		Mesh(MeshInfo const& info);

		~Mesh() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the vertices of this Mesh.
		 * @return The ListContainer with the data.
		 */
		ListContainer& get_vertices() { return m_vertices; }

		/**
		 * @brief Gets the vertices of this Mesh.
		 * @return The ListContainer with the data.
		 */
		ListContainer const& get_vertices() const { return m_vertices; }

		/**
		 * @brief Gets the vertex Buffer of this Mesh.
		 * @return The vertex Buffer.
		 */
		Ref<Buffer> get_vertex_buffer() const { return m_vertexBuffer.to_ref(); }

		/**
		 * @brief Gets the indices of this Mesh.
		 * @return The ListContainer with the data.
		 */
		ListContainer& get_indices() { return m_indices; }

		/**
		 * @brief Gets the indices of this Mesh.
		 * @return The ListContainer with the data.
		 */
		ListContainer const& get_indices() const { return m_indices; }

		/**
		 * @brief Gets the index Buffer of this Mesh.
		 * @return The index Buffer.
		 */
		Ref<Buffer> get_index_buffer() const { return m_indexBuffer.to_ref(); }

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return Mesh.
		 */
		AssetType get_asset_type() const override { return AssetType::Mesh; }

#pragma endregion

#pragma region Methods

	public:
		static Shared<Mesh> create(MeshInfo const& info);

	private:
		void initialize(MeshInfo const& info);

		void initialize_quad();

		void initialize_cube();

#pragma endregion

#pragma region Variables

	protected:
		ListContainer m_vertices;
		Shared<Buffer> m_vertexBuffer;

		ListContainer m_indices;
		Shared<Buffer> m_indexBuffer;

#pragma endregion
	};
}

#endif // MINTY_RENDER_MESH_H