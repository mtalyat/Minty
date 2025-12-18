#ifndef MINTY_DATA_RECT_H
#define MINTY_DATA_RECT_H

/**
 * @file Rect.h
 * @brief Defines the Rect struct for representing rectangles.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	/**
	 * @brief Represents a rectangle defined by its position and size.
	 */
	struct Rect
	{
		union
		{
			struct
			{
				/**
				 * @brief The x coordinate of the rectangle.
				 */
				Float x;
				
				/**
				 * @brief The y coordinate of the rectangle.
				 */
				Float y;

				/**
				 * @brief The width of the rectangle.
				 */
				Float width;

				/**
				 * @brief The height of the rectangle.
				 */
				Float height;
			};
			struct 
			{
				/**
				 * @brief The position of the rectangle.
				 */
				Float2 position;

				/**
				 * @brief The size of the rectangle.
				 */
				Float2 size;
			};
			/**
			 * @brief The rectangle as a Float4.
			 */
			Float4 rect;
		};

		/**
		 * @brief Creates an empty rectangle.
		 */
		Rect()
			: rect()
		{
		}

		/**
		 * @brief Creates a rectangle with the given position and size.
		 * @param x The x coordinate.
		 * @param y The y coordinate.
		 * @param width The width.
		 * @param height The height.
		 */
		Rect(Float const x, Float const y, Float const width, Float const height)
			: x(x), y(y), width(width), height(height)
		{
		}
		
		/**
		 * @brief Creates a rectangle with the given position and size.
		 * @param position The position.
		 * @param size The size.
		 */
		Rect(Float2 const position, Float2 const size)
			: position(position), size(size)
		{
		}

		/**
		 * @brief Creates a rectangle from the given Float4.
		 * @param rect The Float4 representing the rectangle.
		 */
		Rect(Float4 const rect)
			: rect(rect)
		{
		}

		/**
		 * @brief Checks if the given point is inside this rectangle.
		 * @param point The point to check.
		 * @return True if the point is inside, otherwise false.
		 */
		Bool contains(Float2 const point) const
		{
			return (point.x >= x) && (point.x <= x + width) && (point.y >= y) && (point.y <= y + height);
		}
	};
}

#endif // MINTY_DATA_RECT_H