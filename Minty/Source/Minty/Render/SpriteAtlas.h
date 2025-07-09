#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Rect.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/CoordinateMode.h"
#include "Minty/Render/SpriteSlice.h"

namespace Minty
{
	class AssetManager;
	class Texture;
	class Sprite;

	/// <summary>
	/// The arguments to build a SpriteAtlas.
	/// </summary>
	struct SpriteAtlasBuilder
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
		/// The slices automatically generated from the Texture.
		/// </summary>
		Vector<Tuple<SpriteSlice, Int2>> automaticSlices;

		/// <summary>
		/// The slices manually added to this Atlas.
		/// </summary>
		Vector<Tuple<SpriteSlice, UUID>> manualSlices;
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
		Vector<Tuple<SpriteSlice, Int2>> m_automaticSlices;
		Vector<Tuple<SpriteSlice, UUID>> m_manualSlices;
		Map<Int, Map<Int2, Ref<Sprite>>> m_automaticSprites;
		Vector<Ref<Sprite>> m_manualSprites;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new SpriteAtlas with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		SpriteAtlas(SpriteAtlasBuilder const& builder);

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Texture used by this SpriteAtlas.
		/// </summary>
		/// <returns></returns>
		inline Ref<Texture> const& get_texture() const { return m_texture; }

		/// <summary>
		/// Gets the manually generated Sprite from this SpriteAtlas by its index.
		/// </summary>
		/// <param name="index">The index of the Sprite.</param>
		/// <returns>The Sprite.</returns>
		inline Ref<Sprite> const& get_manual_sprite(Size const index) const
		{
			MINTY_ASSERT(index < m_manualSprites.get_size(), "Index out of bounds for manual sprites.");
			return m_manualSprites[index];
		}

		/// <summary>
		/// Gets the number of manually generated Sprites in this SpriteAtlas.
		/// </summary>
		/// <returns>The count.</returns>
		inline Size get_manual_sprite_count() const
		{
			return m_manualSprites.get_size();
		}

		/// <summary>
		/// Gets the specific automatically generated Sprite from this SpriteAtlas by its 2D index and group index.
		/// </summary>
		/// <param name="index">The 2D index.</param>
		/// <param name="groupIndex">The group index.</param>
		/// <returns>The Sprite.</returns>
		inline Ref<Sprite> const& get_automatic_sprite(Int2 const index, Int const groupIndex = 0)
		{
			MINTY_ASSERT(groupIndex < m_automaticSprites.get_size(), "Group index out of bounds for automatic sprites.");
			auto const& group = m_automaticSprites[groupIndex];
			MINTY_ASSERT(group.contains(index), "Index out of bounds for automatic sprites.");
			return group.at(index);
		}

		/// <summary>
		/// Gets the number of automatic Sprite groups.
		/// </summary>
		/// <returns>The count.</returns>
		inline Int get_automatic_sprite_group_count() const
		{
			return static_cast<Int>(m_automaticSprites.get_size());
		}

		/// <summary>
		/// Gets the size of the automatic Sprite group at the given index.
		/// </summary>
		/// <param name="groupIndex">The index of the automatic Sprite group.</param>
		/// <returns>The 2D count of the group.</returns>
		inline Int2 get_automatic_sprite_group_size(Int const groupIndex) const
		{
			MINTY_ASSERT(groupIndex >= 0 && groupIndex < m_automaticSlices.get_size(), "Group index out of bounds for automatic sprites.");
			return m_automaticSlices.at(groupIndex).get_second();
		}

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
		/// <param name="builder">The arguments.</param>
		/// <returns>A SpriteAtlas Owner.</returns>
		static Owner<SpriteAtlas> create(SpriteAtlasBuilder const& builder = {});

#pragma endregion

	};
}