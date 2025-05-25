#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// A rectangle.
	/// </summary>
	struct Rect
	{
		union
		{
			struct
			{
				/// <summary>
				/// The x coordinate of the rectangle.
				/// </summary>
				Float x;
				
				/// <summary>
				/// The y coordinate of the rectangle.
				/// </summary>
				Float y;

				/// <summary>
				/// The width of the rectangle.
				/// </summary>
				Float width;

				/// <summary>
				/// The height of the rectangle.
				/// </summary>
				Float height;
			};
			struct 
			{
				/// <summary>
				/// The position of the rectangle.
				/// </summary>
				Float2 position;

				/// <summary>
				/// The size of the rectangle.
				/// </summary>
				Float2 size;
			};
			/// <summary>
			/// The rectangle as a Float4.
			/// </summary>
			Float4 rect;
		};

		/// <summary>
		/// Creates an empty rectangle.
		/// </summary>
		Rect()
			: rect()
		{
		}

		/// <summary>
		/// Creates a rectangle with the given x, y, width and height.
		/// </summary>
		/// <param name="x">The x coordinate.</param>
		/// <param name="y">The y coordinate.</param>
		/// <param name="width">The width.</param>
		/// <param name="height">The height.</param>
		Rect(Float const x, Float const y, Float const width, Float const height)
			: x(x), y(y), width(width), height(height)
		{
		}

		/// <summary>
		/// Creates a rectangle with the given position and size.
		/// </summary>
		/// <param name="position">The position.</param>
		/// <param name="size">The size.</param>
		Rect(Float2 const position, Float2 const size)
			: position(position), size(size)
		{
		}

		/// <summary>
		/// Creates a rectangle with the given Float4.
		/// </summary>
		/// <param name="rect"></param>
		Rect(Float4 const rect)
			: rect(rect)
		{
		}
	};
}