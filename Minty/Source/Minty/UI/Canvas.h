#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Data/Rect.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/// <summary>
	/// A canvas is a 2D space where UI elements are drawn.
	/// </summary>
	class Canvas
		: public SerializableObject
	{
#pragma region Variables

	private:
		// the resolution that the canvas emulates
		Int2 m_resolution;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Canvas.
		/// </summary>
		Canvas();

		/// <summary>
		/// Creates a new canvas with the given resolution.
		/// </summary>
		/// <param name="resolution">The resolution of the canvas.</param>
		Canvas(Int2 const resolution)
			: m_resolution(resolution)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the resolution of the canvas.
		/// </summary>
		/// <returns>The resolution of the canvas.</returns>
		Int2 get_resolution() const
		{
			return m_resolution;
		}

		/// <summary>
		/// Sets the resolution of the canvas.
		/// </summary>
		/// <param name="resolution">The resolution of the canvas.</param>
		void set_resolution(Int2 const resolution)
		{
			m_resolution = resolution;
		}

		/// <summary>
		/// Gets the rectangle of this Canvas.
		/// </summary>
		/// <returns>A Rect that resembles this Canvas area.</returns>
		Rect get_rect() const
		{
			return Rect(0, 0, static_cast<Float>(m_resolution.x), static_cast<Float>(m_resolution.y));
		}

#pragma endregion

#pragma region Methods

	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}