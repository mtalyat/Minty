#ifndef MINTY_UI_CANVAS_H
#define MINTY_UI_CANVAS_H

/**
 * @file Canvas.h
 * @brief Header file defining the Canvas class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Rect.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	/**
	 * @brief A canvas is a 2D space where UI elements are drawn.
	 */
	class Canvas
	{
		friend struct Serializer<Canvas>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Canvas.
		 */
		Canvas();

		/**
		 * @brief Creates a new canvas with the given resolution.
		 * @param resolution The resolution of the canvas.
		 */
		Canvas(Int2 const resolution)
			: m_resolution(resolution)
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the resolution of the canvas.
		 * @return The resolution of the canvas.
		 */
		inline Int2 get_resolution() const { return m_resolution; }

		/**
		 * @brief Sets the resolution of the canvas.
		 * @param resolution The resolution of the canvas.
		 */
		inline void set_resolution(Int2 const resolution) { m_resolution = resolution; }

		/**
		 * @brief Gets the rectangle of this Canvas.
		 * @return A Rect that resembles this Canvas area.
		 */
		inline Rect get_rect() const { return Rect(0, 0, static_cast<Float>(m_resolution.x), static_cast<Float>(m_resolution.y)); }

#pragma endregion

#pragma region Variables

	private:
		// the resolution that the canvas emulates
		Int2 m_resolution;

#pragma endregion
	};

	template<>
	struct Serializer<Canvas>
	{
		static void serialize(Writer &writer, Canvas const &value);
		static void deserialize(Reader &reader, Canvas &value);
	};
}

#endif // MINTY_UI_CANVAS_H