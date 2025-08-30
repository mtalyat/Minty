#include "pch.h"
#include "SpriteAtlas.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Render/Sprite.h"

using namespace Minty;

Minty::SpriteAtlas::SpriteAtlas(SpriteAtlasBuilder const& builder)
	: Asset(builder.id)
	, m_texture(builder.texture)
	, m_groups(builder.groups)
{
	MINTY_ASSERT(builder.texture != nullptr, "Cannot create a SpriteAtlas without a Texture.");
	MINTY_ASSERT(!builder.groups.is_empty(), "Cannot create a SpriteAtlas without at least one group.");
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

	SpriteBuilder spriteBuilder{};
	spriteBuilder.texture = m_texture;

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
				spriteBuilder.id = id;
				spriteBuilder.slice = slice;
				spriteBuilder.slice.offset = slice.offset + Float2(static_cast<Float>(x), static_cast<Float>(y)) * slice.size;

				// create the Sprite
				assetManager.create<Sprite>(spriteBuilder);
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

Owner<SpriteAtlas> Minty::SpriteAtlas::create(SpriteAtlasBuilder const& builder)
{
	return Owner<SpriteAtlas>(new SpriteAtlas(builder));
}
