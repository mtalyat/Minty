#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

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

	String to_string(MeshType const obj);
	MeshType parse_to_mesh_type(String const& string);
	Bool parse_try_mesh_type(String const& string, MeshType& value);
	template<>
	inline MeshType parse_to<MeshType>(String const& string) { return parse_to_mesh_type(string); }
	template<>
	inline Bool parse_try<MeshType>(String const& string, MeshType& value) { return parse_try_mesh_type(string, value); }
}