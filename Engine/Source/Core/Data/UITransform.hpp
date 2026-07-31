#pragma once

/**
 * @file UITransform.hpp
 * @brief Defines the UITransform class for UI element transformations.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Type/Rect.hpp"
#include "Core/Type/Anchor.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
	/**
	 * @class UITransform
	 * @brief Represents a transformation for UI elements.
	 */
	class UITransform
	{
		friend struct Serializer<UITransform>;

#pragma region Constructors

	public:
		UITransform();

		UITransform(Float const x, Float const y, Float const width, Float const height);

		UITransform(Float const x, Float const y, Float const width, Float const height, Anchor const anchor);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the AnchorEnumFlags of this UI element.
		 * @returns The Anchor.
		 */
		inline Anchor get_anchor() const { return m_anchor; }

		/**
		 * @brief Sets the Anchor of this UI element.
		 * @param anchor The new Anchor.
		 */
		inline void set_anchor(Anchor const anchor) { m_anchor = anchor; m_dirty = true; }

		/**
		 * @brief Gets the x position of this UI element.
		 * @returns The x position.
		 */
		inline Float get_x() const { return m_x; }

		/**
		 * @brief Sets the x position of this UI element.
		 * @param x The x position.
		 */
		inline void set_x(Float const& x) { m_x = x; m_dirty = true; }

		/**
		 * @brief Gets the left position of this UI element.
		 * @returns The left position (same as x).
		 */
		inline Float get_left() const { return m_x; }

		/**
		 * @brief Sets the left position of this UI element.
		 * @param left The left position.
		 */
		inline void set_left(Float const& left) { m_x = left; m_dirty = true; }

		/**
		 * @brief Gets the y position of this UI element.
		 * @returns The y position.
		 */
		inline Float get_y() const { return m_y; }

		/**
		 * @brief Sets the y position of this UI element.
		 * @param y The y position.
		 */
		inline void set_y(Float const& y) { m_y = y; m_dirty = true; }

		/**
		 * @brief Gets the top position of this UI element.
		 * @returns The top position.
		 */
		inline Float get_top() const { return m_y; }

		/**
		 * @brief Sets the top position of this UI element.
		 * @param top The top position.
		 */
		inline void set_top(Float const& top) { m_y = top; m_dirty = true; }

		/**
		 * @brief Gets the z position (depth) of this UI element.
		 * @returns The z position (depth).
		 */
		inline Float get_z() const { return m_z; }

		/**
		 * @brief Sets the z position (depth) of this UI element.
		 * @param z The z position (depth).
		 */
		inline void set_z(Float const& z) { m_z = z; m_dirty = true; }

		/**
		 * @brief Gets the depth (z position) of this UI element.
		 * @returns The depth.
		 */
		inline Float get_depth() const { return m_z; }

		/**
		 * @brief Sets the depth (z position) of this UI element.
		 * @param depth The depth (z position).
		 */
		inline void set_depth(Float const& depth) { m_z = depth; m_dirty = true; }

		/**
		 * @brief Gets the width of this UI element.
		 * @returns The width.
		 */
		inline Float get_width() const { return m_width; }

		/**
		* @brief Sets the width of this UI element.
		* @param width The width.
		*/
		inline void set_width(Float const& width) { m_width = width; m_dirty = true; }

		/**
		 * @brief Gets the right position of this UI element.
		 * @returns The right position.
		 */
		inline Float get_right() const { return m_width; }

		/**
		 * @brief Sets the right position of this UI element.
		 * @param right The right position.
		 */
		inline void set_right(Float const& right) { m_width = right; m_dirty = true; }

		/**
		 * @brief Gets the height of this UI element.
		 * @returns The height.
		 */
		inline Float get_height() const { return m_height; }

		/**
		 * @brief Sets the height of this UI element.
		 * @param height The height.
		 */
		inline void set_height(Float const& height) { m_height = height; m_dirty = true; }

		/**
		 * @brief Gets the bottom position of this UI element.
		 * @returns The bottom position.
		 */
		inline Float get_bottom() const { return m_height; }

		/**
		 * @brief Sets the bottom position of this UI element.
		 * @param bottom The bottom position.
		 */
		inline void set_bottom(Float const& bottom) { m_height = bottom; m_dirty = true; }

		/**
		 * @brief Gets the rotation of this UI element.
		 * @returns The rotation in radians.
		 */
		inline Float get_rotation() const { return m_rotation; }

		/**
		 * @brief Sets the rotation of this UI element.
		 * @param rotation The rotation in radians.
		 */
		inline void set_rotation(Float const& rotation) { m_rotation = rotation; m_dirty = true; }

		/**
		 * @brief Sets the position of this UI element.
		 * @param x The x coordinate.
		 * @param y The y coordinate.
		 */
		inline void set_position(Float const& x, Float const& y) { m_x = x; m_y = y; m_dirty = true; }

		/**
		 * @brief Sets the size of this UI element.
		 * @param width The width.
		 * @param height The height.
		 */
		inline void set_size(Float const& width, Float const& height) { m_width = width; m_height = height; m_dirty = true; }

		/**
		 * @brief Gets the local rectangle of this UI element.
		 * @returns The local rectangle.
		 */
		Rect const& get_local_rect() const;

		/**
		 * @brief Gets the global rectangle of this UI element.
		 * @returns The global rectangle.
		 */
		Rect const& get_global_rect() const;

#pragma endregion

#pragma region Variables

	private:
		Anchor m_anchor;
		Float m_x;
		Float m_y;
		Float m_width;
		Float m_height;
		Float m_z; // depth
		Float m_rotation;
		
		// Cached local rect
		Rect mutable m_local;
		Bool mutable m_dirty;

#pragma endregion
	};

	template<>
	struct Serializer<UITransform>
	{
		static void serialize(Writer& writer, UITransform const& value);
		static Bool deserialize(Reader& reader, UITransform& value);
	};
}
