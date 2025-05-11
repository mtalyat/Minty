#pragma once

namespace Minty
{
	/// <summary>
	/// The type of Mesh.
	/// </summary>
	enum class MeshType
	{
		/// <summary>
		/// An empty Mesh.
		/// </summary>
		Empty,

		/// <summary>
		/// A custom Mesh.
		/// </summary>
		Custom,

		/// <summary>
		/// A square Mesh.
		/// </summary>
		Quad,

		/// <summary>
		/// A cube Mesh.
		/// </summary>
		Cube,
	};
}