#pragma once
#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/SpriteSlice.h"

namespace Minty
{
	/// <summary>
	/// Holds information for a group of Sprites within a SpriteAtlas.
	/// </summary>
	class SpriteGroup
	{
	private:
		/// <summary>
		/// The slice data for the group. All Sprites in this group share the same slice data.
		/// </summary>
		SpriteSlice m_slice;

		/// <summary>
		/// The 2D count of the Sprites in this group.
		/// </summary>
		Int2 m_count;

		/// <summary>
		/// The IDs for all of the Sprites within this group.
		/// </summary>
		Vector<UUID> m_ids;

	public:
		/// <summary>
		/// Creates a new SpriteGroup with the given slice, count, and IDs.
		/// </summary>
		/// <param name="slice">The slice data.</param>
		/// <param name="count">The 2D count.</param>
		/// <param name="ids">The IDs for the Sprites. Size must be equal to count.x * count.y.</param>
		SpriteGroup(SpriteSlice&& slice, Int2 const count, Vector<UUID>&& ids)
			: m_slice(std::move(slice))
			, m_count(count)
			, m_ids(std::move(ids))
		{
			MINTY_ASSERT(m_slice.coordinateMode != CoordinateMode::Undefined, "Slice coordinate mode must be defined.");
			MINTY_ASSERT(m_slice.pixelsPerUnit > 0.0f, "Pixels per unit (PPU) must be greater than zero.");
			MINTY_ASSERT(m_count.x > 0 && m_count.y > 0, "Count must be greater than zero.");
			MINTY_ASSERT(m_ids.get_size() == static_cast<Size>(m_count.x) * static_cast<Size>(m_count.y), "IDs size must match the count of Sprites.");
		}

		/// <summary>
		/// Gets the slice data.
		/// </summary>
		/// <returns>The SpriteSlice used for each Sprite.</returns>
		inline SpriteSlice const& get_slice() const { return m_slice; }

		/// <summary>
		/// Gets the 2D count of Sprites in this group.
		/// </summary>
		/// <returns>The count.</returns>
		inline Int2 get_count() const { return m_count; }

		/// <summary>
		/// Gets the IDs of all Sprites in this group.
		/// </summary>
		/// <returns>The Vector of Sprite UUIDs.</returns>
		inline Vector<UUID> const& get_ids() const { return m_ids; }

		/// <summary>
		/// Gets the ID of the Sprite at the given index.
		/// </summary>
		/// <param name="x">The X index of the Sprite ID.</param>
		/// <param name="y">The Y index of the Sprite ID.</param>
		/// <returns>The Sprite's ID.</returns>
		UUID get_id(Int const x, Int const y) const
		{
			MINTY_ASSERT(x >= 0 && x < m_count.x && y >= 0 && y < m_count.y, "Index out of bounds.");
			Size const i = static_cast<Size>(y) * m_count.x + x;
			MINTY_ASSERT(i < m_ids.get_size(), "Index out of bounds.");
			return m_ids[i];
		}

		/// <summary>
		/// Gets the ID of the Sprite at the given index.
		/// </summary>
		/// <param name="index">The 2D index of the Sprite ID.</param>
		/// <returns>The Sprite's ID.</returns>
		inline UUID get_id(Int2 const index) const
		{
			return get_id(index.x, index.y);
		}
	};
}