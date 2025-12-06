#ifndef MINTY_RENDER_SPRITEATLAS_H
#define MINTY_RENDER_SPRITEATLAS_H

/**
 * @file SpriteAtlas.h
 * @brief Header file defining the SpriteAtlas class.
 * @author Mitchell Talyat
 */

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
	struct SpriteAtlasInfo;

	/**
	 * @brief A SpriteAtlas is a collection of Sprites that share the same Texture.
	 */
	class SpriteAtlas
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new SpriteAtlas with the given arguments.
		 * @param info The arguments.
		 */
		SpriteAtlas(SpriteAtlasInfo const& info);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the Texture used by this SpriteAtlas.
		 * @return The Texture.
		 */
		inline Ref<Texture> const& get_texture() const { return m_texture; }

		/**
		 * @brief Gets the Group with the given index.
		 * @param index The index of the Group.
		 * @return The Group.
		 */
		inline SpriteGroup const& get_group(Int const index) const
		{
			MINTY_ASSERT(index >= 0 && index < m_groups.get_size(), ErrorCode::Argument_OutOfRange);
			return m_groups[index];
		}

		/**
		 * @brief Gets the ID of the Sprite at the given index in the specified group.
		 * @param groupIndex The Group the Sprite ID is in.
		 * @param index The 2D index of the Sprite ID.
		 * @return The Sprite ID.
		 */
		inline UUID get_sprite_id(Int const groupIndex, Int2 const index) const
		{
			MINTY_ASSERT(groupIndex >= 0 && groupIndex < m_groups.get_size(), ErrorCode::Argument_OutOfRange);
			return m_groups[groupIndex].get_id(index);
		}

		/**
		 * @brief Gets the ID of the Sprite at the given index in the specified group.
		 * @param groupIndex The Group the Sprite ID is in.
		 * @param index The 1D index of the Sprite ID.
		 * @return The Sprite ID.
		 */
		inline UUID get_sprite_id(Int const groupIndex, Int const index) const
		{
			MINTY_ASSERT(groupIndex >= 0 && groupIndex < m_groups.get_size(), ErrorCode::Argument_OutOfRange);
			Int const width = m_groups[groupIndex].get_count().x;
			Int const indexY = index / width;
			Int const indexX = index - indexY * width;
			return m_groups[groupIndex].get_id(indexX, indexY);
		}

		/**
		 * @brief Gets the Sprite at the given index in the specified group.
		 * @param groupIndex The Group the Sprite is in.
		 * @param index The 2D index of the Sprite.
		 * @return The Sprite.
		 */
		Ref<Sprite> get_sprite(Int const groupIndex, Int2 const index) const;

		/**
		 * @brief Gets the Sprite at the given index in the specified group.
		 * @param groupIndex The Group the Sprite is in.
		 * @param index The 1D index of the Sprite.
		 * @return The Sprite.
		 */
		Ref<Sprite> get_sprite(Int const groupIndex, Int const index) const;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when the Asset is loaded into the AssetManager.
		 */
		void on_load();

		/**
		 * @brief Called when the Asset is unloaded from the AssetManager.
		 */
		void on_unload();

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return The AssetType.
		 */
		inline AssetType get_asset_type() const { return AssetType::SpriteAtlas; }

		/**
		 * @brief Creates a new SpriteAtlas with the given arguments.
		 * @param info The arguments.
		 * @return A SpriteAtlas Owner.
		 */
		static Shared<SpriteAtlas> create(SpriteAtlasInfo const& info);

		/**
		 * @brief Creates a default SpriteAtlas.
		 * @return A SpriteAtlas Owner.
		 */
		static Shared<SpriteAtlas> create();

#pragma endregion

#pragma region Variables

	private:
		Ref<Texture> m_texture;
		Vector<SpriteGroup> m_groups;

#pragma endregion
	};
}

#endif // MINTY_RENDER_SPRITEATLAS_H