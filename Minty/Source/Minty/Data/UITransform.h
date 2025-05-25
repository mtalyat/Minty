#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Rect.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/UI/AnchorMode.h"

namespace Minty
{
	/// <summary>
	/// A Transform for UI elements.
	/// </summary>
	class UITransform
		: public SerializableObject
	{
#pragma region Variables

	private:
		AnchorMode m_anchorMode;
		Float x;
		Float y;
		Float z; // depth
		Float width;
		Float height;

		Rect m_globalRect;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty UITransform.
		/// </summary>
		UITransform()
			: m_anchorMode(AnchorMode::TopLeft)
			, x(0.0f)
			, y(0.0f)
			, z(0.0f)
			, width(0.0f)
			, height(0.0f)
			, m_globalRect()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the AnchorMode of this UI element.
		/// </summary>
		/// <returns>The AnchorMode.</returns>
		inline AnchorMode get_anchor_mode() const { return m_anchorMode; }

		/// <summary>
		/// Sets the AnchorMode of this UI element.
		/// </summary>
		/// <param name="anchorMode">The AnchorMode.</param>
		inline void set_anchor_mode(AnchorMode const& anchorMode)
		{
			m_anchorMode = anchorMode;
		}

		/// <summary>
		/// Gets the x position of this UI element.
		/// </summary>
		/// <returns>The x position.</returns>
		inline Float get_x() const { return x; }

		/// <summary>
		/// Sets the x position of this UI element.
		/// </summary>
		/// <param name="x">The x position.</param>
		inline void set_x(Float const& x)
		{
			this->x = x;
		}

		/// <summary>
		/// Gets the left position of this UI element.
		/// </summary>
		/// <returns>The left position (same as x).</returns>
		inline Float get_left() const { return x; }

		/// <summary>
		/// Sets the left position of this UI element.
		/// </summary>
		/// <param name="left">The left position.</param>
		inline void set_left(Float const& left)
		{
			this->x = left;
		}

		/// <summary>
		/// Gets the y position of this UI element.
		/// </summary>
		/// <returns>The y position.</returns>
		inline Float get_y() const { return y; }

		/// <summary>
		/// Sets the y position of this UI element.
		/// </summary>
		/// <param name="y">The y position.</param>
		inline void set_y(Float const& y)
		{
			this->y = y;
		}

		/// <summary>
		/// Gets the top position of this UI element.
		/// </summary>
		/// <returns>The top position (same as y).</returns>
		inline Float get_top() const { return y; }

		/// <summary>
		/// Sets the top position of this UI element.
		/// </summary>
		/// <param name="top">The top position.</param>
		inline void set_top(Float const& top)
		{
			this->y = top;
		}

		/// <summary>
		/// Gets the z position (depth) of this UI element.
		/// </summary>
		/// <returns>The z position (depth).</returns>
		inline Float get_z() const { return z; }

		/// <summary>
		/// Sets the z position (depth) of this UI element.
		/// </summary>
		/// <param name="z">The z position (depth).</param>
		inline void set_z(Float const& z)
		{
			this->z = z;
		}

		/// <summary>
		/// Gets the depth (z position) of this UI element.
		/// </summary>
		/// <returns>The depth (z position).</returns>
		inline Float get_depth() const { return z; }

		/// <summary>
		/// Sets the depth (z position) of this UI element.
		/// </summary>
		/// <param name="depth">The depth (z position).</param>
		inline void set_depth(Float const& depth)
		{
			this->z = depth;
		}

		/// <summary>
		/// Gets the width of this UI element.
		/// </summary>
		/// <returns>The width.</returns>
		inline Float get_width() const { return width; }

		/// <summary>
		/// Sets the width of this UI element.
		/// </summary>
		/// <param name="width">The width.</param>
		inline void set_width(Float const& width)
		{
			this->width = width;
		}

		/// <summary>
		/// Gets the right position of this UI element.
		/// </summary>
		/// <returns>The right position.</returns>
		inline Float get_right() const { return width; }

		/// <summary>
		/// Sets the right position of this UI element.
		/// </summary>
		/// <param name="right">The right position.</param>
		inline void set_right(Float const& right)
		{
			this->width = right;
		}

		/// <summary>
		/// Gets the height of this UI element.
		/// </summary>
		/// <returns>The height.</returns>
		inline Float get_height() const { return height; }

		/// <summary>
		/// Sets the height of this UI element.
		/// </summary>
		/// <param name="height">The height.</param>
		inline void set_height(Float const& height)
		{
			this->height = height;
		}

		/// <summary>
		/// Gets the bottom position of this UI element.
		/// </summary>
		/// <returns>The bottom position.</returns>
		inline Float get_bottom() const { return height; }

		/// <summary>
		/// Sets the bottom position of this UI element.
		/// </summary>
		/// <param name="bottom">The bottom position.</param>
		inline void set_bottom(Float const& bottom)
		{
			this->height = bottom;
		}

		/// <summary>
		/// Gets the global rectangle of this UI element.
		/// </summary>
		/// <returns>The global Rect.</returns>
		inline Rect get_global_rect() const { return m_globalRect; }

		/// <summary>
		/// Sets the global rectangle of this UI element.
		/// </summary>
		/// <param name="rect">The global Rect.</param>
		inline void set_global_rect(Rect const& rect)
		{
			m_globalRect = rect;
		}

		/// <summary>
		/// Updates the global rectangle of this UI element based on the given parent rectangle.
		/// </summary>
		/// <param name="parentRect">The rectangle of the parent.</param>
		void update_global_rect(Rect const& parentRect);

		/// <summary>
		/// Sets the position of this UI element.
		/// </summary>
		/// <param name="x">The x coordinate.</param>
		/// <param name="y">The y coordinate.</param>
		inline void set_position(Float const& x, Float const& y)
		{
			this->x = x;
			this->y = y;
		}

		/// <summary>
		/// Sets the size of this UI element.
		/// </summary>
		/// <param name="width">The width.</param>
		/// <param name="height">The height.</param>
		inline void set_size(Float const& width, Float const& height)
		{
			this->width = width;
			this->height = height;
		}

#pragma endregion

#pragma region Methods

	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}