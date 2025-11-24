#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Rect.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/CoordinateMode.h"
#include "Minty/Render/SpriteSlice.h"
#include "Minty/Render/SpriteGroup.h"

namespace Minty
{
	class AssetManager;
	class Texture;
	class Sprite;

	/// <summary>
	/// The arguments to build a SpriteAtlas.
	/// </summary>
	struct SpriteAtlasInfo
	{
		/// <summary>
		/// The ID of this Atlas.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The Texture that this Atlas uses.
		/// </summary>
		Ref<Texture> texture = nullptr;

		/// <summary>
		/// The Sprite groups within this Atlas.
		/// </summary>
		Vector<SpriteGroup> groups;
	};

	/// <summary>
	/// A SpriteAtlas is a collection of Sprites that share the same Texture.
	/// </summary>
	class SpriteAtlas
		: public Asset
	{
#pragma region Variables

	private:
		Ref<Texture> m_texture;
		Vector<SpriteGroup> m_groups;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new SpriteAtlas with the given arguments.
		/// </summary>
		/// <param name="info">The arguments.</param>
		SpriteAtlas(SpriteAtlasInfo const& info);

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Texture used by this SpriteAtlas.
		/// </summary>
		/// <returns></returns>
		inline Ref<Texture> const& get_texture() const { return m_texture; }

		/// <summary>
		/// Gets the Group with the given index.
		/// </summary>
		/// <param name="index">The index of the Group.</param>
		/// <returns>The Group.</returns>
		inline SpriteGroup const& get_group(Int const index) const
		{
			MINTY_ASSERT(index >= 0 && index < m_groups.get_size(), "Index out of bounds.");
			return m_groups[index];
		}

		/// <summary>
		/// Gets the ID of the Sprite at the given index in the specified group.
		/// </summary>
		/// <param name="groupIndex">The Group the Sprite ID is in.</param>
		/// <param name="index">The 2D index of the Sprite ID.</param>
		/// <returns>The Sprite ID.</returns>
		inline UUID get_sprite_id(Int const groupIndex, Int2 const index) const
		{
			MINTY_ASSERT(groupIndex >= 0 && groupIndex < m_groups.get_size(), "Index out of bounds.");
			return m_groups[groupIndex].get_id(index);
		}

		/// <summary>
		/// Gets the ID of the Sprite at the given index in the specified group.
		/// </summary>
		/// <param name="groupIndex">The Group the Sprite ID is in.</param>
		/// <param name="index">The 1D index of the Sprite ID.</param>
		/// <returns>The Sprite ID.</returns>
		inline UUID get_sprite_id(Int const groupIndex, Int const index) const
		{
			MINTY_ASSERT(groupIndex >= 0 && groupIndex < m_groups.get_size(), "Index out of bounds.");
			Int const width = m_groups[groupIndex].get_count().x;
			Int const indexY = index / width;
			Int const indexX = index - indexY * width;
			return m_groups[groupIndex].get_id(indexX, indexY);
		}

		/// <summary>
		/// Gets the Sprite at the given index in the specified group.
		/// </summary>
		/// <param name="groupIndex">The Group the Sprite is in.</param>
		/// <param name="index">The 2D index of the Sprite.</param>
		/// <returns>The Sprite.</returns>
		Ref<Sprite> get_sprite(Int const groupIndex, Int2 const index) const;

		/// <summary>
		/// Gets the Sprite at the given index in the specified group.
		/// </summary>
		/// <param name="groupIndex">The Group the Sprite is in.</param>
		/// <param name="index">The 1D index of the Sprite.</param>
		/// <returns>The Sprite.</returns>
		Ref<Sprite> get_sprite(Int const groupIndex, Int const index) const;

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when the Asset is loaded into the AssetManager.
		/// </summary>
		void on_load();

		/// <summary>
		/// Called when the Asset is unloaded from the AssetManager.
		/// </summary>
		void on_unload();

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>The AssetType.</returns>
		constexpr AssetType get_asset_type() const { return AssetType::SpriteAtlas; }

#pragma endregion

#pragma region Static

	public:
		/// <summary>
		/// Creates a new SpriteAtlas with the given arguments.
		/// </summary>
		/// <param name="info">The arguments.</param>
		/// <returns>A SpriteAtlas Owner.</returns>
		static Owner<SpriteAtlas> create(SpriteAtlasInfo const& info = {});

#pragma endregion

	};
}