#include "pch.h"
#include "SpriteAtlas.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Render/Sprite.h"

using namespace Minty;

Minty::SpriteAtlas::SpriteAtlas(SpriteAtlasInfo const& info)
	: Asset(info.id)
	, m_texture(info.texture)
	, m_groups(info.groups)
{
	MINTY_ASSERT(info.texture != nullptr, "Cannot create a SpriteAtlas without a Texture.");
	MINTY_ASSERT(!info.groups.is_empty(), "Cannot create a SpriteAtlas without at least one group.");
}

Ref<Sprite> Minty::SpriteAtlas::get_sprite(Int const groupIndex, Int2 const index) const
{
	AssetManager& assetManager = AssetManager::get_singleton();
	return assetManager.get<Sprite>(get_sprite_id(groupIndex, index));
}

Ref<Sprite> Minty::SpriteAtlas::get_sprite(Int const groupIndex, Int const index) const
{
	AssetManager& assetManager = AssetManager::get_singleton();
	return assetManager.get<Sprite>(get_sprite_id(groupIndex, index));
}

void Minty::SpriteAtlas::on_load()
{
	AssetManager& assetManager = AssetManager::get_singleton();

	SpriteInfo spriteInfo{};
	spriteInfo.texture = m_texture;

	// create all of the Sprites
	for (Size i = 0; i < m_groups.get_size(); i++)
	{
		SpriteGroup const& group = m_groups[i];
		Int2 const count = group.get_count();
		for (Int y = 0; y < count.y; y++)
		{
			for (Int x = 0; x < count.x; x++)
			{
				SpriteSlice const& slice = group.get_slice();
				UUID id = group.get_id(x, y);
				spriteInfo.id = id;
				spriteInfo.slice = slice;
				spriteInfo.slice.offset = slice.offset + Float2(static_cast<Float>(x), static_cast<Float>(y)) * slice.size;

				// create the Sprite
				assetManager.create<Sprite>(spriteInfo);
			}
		}
	}
}

void Minty::SpriteAtlas::on_unload()
{
	AssetManager& assetManager = AssetManager::get_singleton();

	// unload all Sprites
	for (auto const& group : m_groups)
	{
		for (UUID const id : group.get_ids())
		{
			// unload the Sprite
			assetManager.unload(id);
		}
	}
}

Owner<SpriteAtlas> Minty::SpriteAtlas::create(SpriteAtlasInfo const& info)
{
	return Owner<SpriteAtlas>(new SpriteAtlas(info));
}
