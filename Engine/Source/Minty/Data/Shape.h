#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// Defines a shape for a collider or a mesh.
	/// </summary>
	enum class Shape
	{
		/// <summary>
		/// No shape.
		/// </summary>
		Empty,

		/// <summary>
		/// A rectangular prism.
		/// </summary>
		Box,

		/// <summary>
		/// A sphere.
		/// </summary>
		Sphere,

		/// <summary>
		/// A capsule.
		/// </summary>
		Capsule,

		/// <summary>
		/// A cylinder.
		/// </summary>
		Cylinder,

		/// <summary>
		/// A cone.
		/// </summary>
		Cone,

		/// <summary>
		/// A custom shape.
		/// </summary>
		Custom,
	};

	String to_string(Shape const obj);
	Shape parse_to_shape(String const& string);
	Bool parse_try_shape(String const& string, Shape& value);
	template<>
	inline Shape parse_to<Shape>(String const& string) { return parse_to_shape(string); }
	template<>
	inline Bool parse_try<Shape>(String const& string, Shape& value) { return parse_try_shape(string, value); }
}