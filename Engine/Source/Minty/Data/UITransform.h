#ifndef MINTY_DATA_UITRANSFORM_H
#define MINTY_DATA_UITRANSFORM_H

/**
 * @file UITransform.h
 * @brief Defines the UITransform class for UI element transformations.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Rect.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/UI/AnchorMode.h"

namespace Minty
{
	/**
	 * @class UITransform
	 * @brief Represents a transformation for UI elements.
	 */
	class UITransform
		: public SerializableObject
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new UITransform with default values.
		 */
		UITransform();

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the AnchorMode of this UI element.
		 * @returns The AnchorMode.
		 */
		inline AnchorMode get_anchor_mode() const { return m_anchorMode; }

		/**
		 * @brief Sets the AnchorMode of this UI element.
		 * @param anchorMode The new AnchorMode.
		 */
		inline void set_anchor_mode(AnchorMode const& anchorMode) { m_anchorMode = anchorMode; }

		/**
		 * @brief Gets the x position of this UI element.
		 * @returns The x position.
		 */
		inline Float get_x() const { return x; }

		/**
		 * @brief Sets the x position of this UI element.
		 * @param x The x position.
		 */
		inline void set_x(Float const& x) { this->x = x; }

		/**
		 * @brief Gets the left position of this UI element.
		 * @returns The left position (same as x).
		 */
		inline Float get_left() const { return x; }

		/**
		 * @brief Sets the left position of this UI element.
		 * @param left The left position.
		 */
		inline void set_left(Float const& left) { this->x = left; }

		/**
		 * @brief Gets the y position of this UI element.
		 * @returns The y position.
		 */
		inline Float get_y() const { return y; }

		/**
		 * @brief Sets the y position of this UI element.
		 * @param y The y position.
		 */
		inline void set_y(Float const& y) { this->y = y; }

		/**
		 * @brief Gets the top position of this UI element.
		 * @returns The top position.
		 */
		inline Float get_top() const { return y; }

		/**
		 * @brief Sets the top position of this UI element.
		 * @param top The top position.
		 */
		inline void set_top(Float const& top) { this->y = top; }

		/**
		 * @brief Gets the z position (depth) of this UI element.
		 * @returns The z position (depth).
		 */
		inline Float get_z() const { return z; }

		/**
		 * @brief Sets the z position (depth) of this UI element.
		 * @param z The z position (depth).
		 */
		inline void set_z(Float const& z) { this->z = z; }

		/**
		 * @brief Gets the depth (z position) of this UI element.
		 * @returns The depth.
		 */
		inline Float get_depth() const { return z; }

		/**
		 * @brief Sets the depth (z position) of this UI element.
		 * @param depth The depth (z position).
		 */
		inline void set_depth(Float const& depth) { this->z = depth; }

		/**
		 * @brief Gets the width of this UI element.
		 * @returns The width.
		 */
		inline Float get_width() const { return width; }

		/**
		* @brief Sets the width of this UI element.
		* @param width The width.
		*/
		inline void set_width(Float const& width) { this->width = width; }

		/**
		 * @brief Gets the right position of this UI element.
		 * @returns The right position.
		 */
		inline Float get_right() const { return width; }

		/**
		 * @brief Sets the right position of this UI element.
		 * @param right The right position.
		 */
		inline void set_right(Float const& right)
		{
			this->width = right;
		}

		/**
		 * @brief Gets the height of this UI element.
		 * @returns The height.
		 */
		inline Float get_height() const { return height; }

		/**
		 * @brief Sets the height of this UI element.
		 * @param height The height.
		 */
		inline void set_height(Float const& height) { this->height = height; }

		/**
		 * @brief Gets the bottom position of this UI element.
		 * @returns The bottom position.
		 */
		inline Float get_bottom() const { return height; }

		/**
		 * @brief Sets the bottom position of this UI element.
		 * @param bottom The bottom position.
		 */
		inline void set_bottom(Float const& bottom) { this->height = bottom; }

		/**
		 * @brief Gets the rotation of this UI element.
		 * @returns The rotation in radians.
		 */
		inline Float get_rotation() const { return rotation; }

		/**
		 * @brief Sets the rotation of this UI element.
		 * @param rotation The rotation in radians.
		 */
		inline void set_rotation(Float const& rotation) { this->rotation = rotation; }

		/**
		 * @brief Gets the global rotation of this UI element.
		 * @returns The global rotation in radians.
		 */
		inline Float get_global_rotation() const { return m_globalRotation; }

		/**
		 * @brief Sets the position of this UI element.
		 * @param x The x coordinate.
		 * @param y The y coordinate.
		 */
		inline void set_position(Float const& x, Float const& y) { this->x = x; this->y = y; }

		/**
		 * @brief Sets the size of this UI element.
		 * @param width The width.
		 * @param height The height.
		 */
		inline void set_size(Float const& width, Float const& height) { this->width = width; this->height = height; }

		/**
		 * @brief Gets the global rectangle of this UI element.
		 * @returns The global Rect.
		 */
		inline Rect get_global_rect() const { return m_globalRect; }

		/**
		 * @brief Gets the global depth of this UI element.
		 * @returns The global depth.
		 */
		inline Float get_global_depth() const { return m_globalDepth; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Updates the global rectangle of this UI element based on the given parent UITransform.
		 * @param parentTransform The parent's UITransform.
		 */
		inline void update(UITransform const& parentTransform)
		{
			update(parentTransform.get_global_rect(), parentTransform.get_global_depth(), parentTransform.get_global_rotation());
		}

		/**
		 * @brief Updates the global rectangle of this UI element based on the given parent rectangle, depth, and rotation.
		 * @param parentRect The parent's Rect.
		 * @param parentDepth The parent's depth.
		 * @param parentRotation The parent's rotation.
		 */
		void update(Rect const& parentRect, Float const parentDepth, Float const parentRotation);

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion

#pragma region Variables

	private:
		AnchorMode m_anchorMode;
		Float x;
		Float y;
		Float z; // depth
		Float width;
		Float height;
		Float rotation;

		Float m_globalDepth;
		Rect m_globalRect;
		Float m_globalRotation;

#pragma endregion
	};
}

#endif // MINTY_DATA_UITRANSFORM_H