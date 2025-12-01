#ifndef MINTY_RENDER_SPRITEGROUP_H
#define MINTY_RENDER_SPRITEGROUP_H

/**
 * @file SpriteGroup.h
 * @brief Header file defining the SpriteGroup class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/SpriteSlice.h"

namespace Minty
{
	/**
	 * @brief Holds information for a group of Sprites within a SpriteAtlas.
	 */
	class SpriteGroup
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new SpriteGroup with the given slice, count, and IDs.
		 * @param slice The slice data.
		 * @param count The 2D count.
		 * @param ids The IDs for the Sprites. Size must be equal to count.x * count.y.
		 */
		SpriteGroup(SpriteSlice &&slice, Int2 const count, Vector<UUID> &&ids)
			: m_slice(std::move(slice)), m_count(count), m_ids(std::move(ids))
		{
			MINTY_ASSERT(m_slice.coordinateMode != CoordinateMode::Undefined, ErrorCode::Argument_ExpectedNonDefault);
			MINTY_ASSERT(m_slice.pixelsPerUnit > 0.0f, ErrorCode::Argument_ExpectedAboveZero);
			MINTY_ASSERT(m_count.x > 0 && m_count.y > 0, ErrorCode::Argument_ExpectedAboveZero);
			MINTY_ASSERT(m_ids.get_size() == static_cast<Size>(m_count.x) * static_cast<Size>(m_count.y), ErrorCode::Argument_ExpectedNonEmpty);
		}

#pragma endregion

#pragma region Accessors

		/**
		 * @brief Gets the slice data.
		 * @return The SpriteSlice used for each Sprite.
		 */
		inline SpriteSlice const &get_slice() const { return m_slice; }

		/**
		 * @brief Gets the 2D count of Sprites in this group.
		 * @return The count.
		 */
		inline Int2 get_count() const { return m_count; }

		/**
		 * @brief Gets the IDs of all Sprites in this group.
		 * @return The Vector of Sprite UUIDs.
		 */
		inline Vector<UUID> const &get_ids() const { return m_ids; }

		/**
		 * @brief Gets the ID of the Sprite at the given index.
		 * @param x The X index of the Sprite ID.
		 * @param y The Y index of the Sprite ID.
		 * @return The Sprite's ID.
		 */
		inline UUID get_id(Int const x, Int const y) const
		{
			MINTY_ASSERT(x >= 0 && x < m_count.x && y >= 0 && y < m_count.y, ErrorCode::Argument_OutOfBounds);
			Size const i = static_cast<Size>(y) * m_count.x + x;
			MINTY_ASSERT(i < m_ids.get_size(), ErrorCode::Argument_OutOfBounds);
			return m_ids[i];
		}

		/**
		 * @brief Gets the ID of the Sprite at the given index.
		 * @param index The 2D index of the Sprite ID.
		 * @return The Sprite's ID.
		 */
		inline UUID get_id(Int2 const index) const { return get_id(index.x, index.y); }

#pragma endregion

#pragma region Variables

	private:
		SpriteSlice m_slice;
		Int2 m_count;
		Vector<UUID> m_ids;

#pragma endregion
	};
}

#endif // MINTY_RENDER_SPRITEGROUP_H