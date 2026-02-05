#ifndef MINTY_DATA_SHAPE_H
#define MINTY_DATA_SHAPE_H

/**
 * @file Shape.h
 * @brief Defines the Shape enum for collider and mesh shapes.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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

	template<>
    struct Parser<Shape>
    {
        static Bool parse(StringView const str, Shape &value);
        static String to_string(Shape const &value);
    };
}

#endif // MINTY_DATA_SHAPE_H