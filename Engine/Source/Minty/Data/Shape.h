#ifndef MINTY_DATA_SHAPE_H
#define MINTY_DATA_SHAPE_H

/**
 * @file Shape.h
 * @brief Defines the Shape enum for collider and mesh shapes.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/**
	 * @brief Enum representing different shapes.
	 */
	enum class Shape
	{
		/**
		 * @brief No shape.
		 */
		Empty,

		/**
		 * @brief A rectangular prism.
		 */
		Box,

		/**
		 * @brief A sphere.
		 */
		Sphere,

		/**
		 * @brief A capsule.
		 */
		Capsule,

		/**
		 * @brief A cylinder.
		 */
		Cylinder,

		/**
		 * @brief A cone.
		 */
		Cone,

		/**
		 * @brief A custom shape.
		 */
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

#endif // MINTY_DATA_SHAPE_H