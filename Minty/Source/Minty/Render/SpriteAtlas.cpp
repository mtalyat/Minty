#include "pch.h"
#include "SpriteAtlas.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Render/Sprite.h"

using namespace Minty;

Minty::SpriteAtlas::SpriteAtlas(SpriteAtlasBuilder const& builder)
	: Asset(builder.id)
	, m_texture(builder.texture)
	, m_automaticSlices(builder.automaticSlices)
	, m_manualSlices(builder.manualSlices)
	, m_automaticSprites()
	, m_manualSprites()
{
	MINTY_ASSERT(builder.texture != nullptr, "Cannot create a SpriteAtlas without a Texture.");
	MINTY_ASSERT(!builder.manualSlices.is_empty(), "Cannot create a SpriteAtlas without at least one slice.");

	// resize the sprites vector to the number of slices
	Size automaticCount = 0;
	for (auto const& [slice, count] : builder.automaticSlices)
	{
		automaticCount += static_cast<Size>(count.x) * static_cast<Size>(count.y);
	}
	m_automaticSprites.reserve(automaticCount * 2);
	m_manualSprites.reserve(m_manualSlices.get_size());
}

void Minty::SpriteAtlas::on_load()
{
	AssetManager& assetManager = AssetManager::get_singleton();

	SpriteBuilder spriteBuilder{};
	spriteBuilder.texture = m_texture;

	// create all of the Sprites
	Int group = 0;
	Size index = 0;
	for (Size i = 0; i < m_automaticSlices.get_size(); i++)
	{
		// get the data
		auto const& pair = m_automaticSlices[i];
		spriteBuilder.slice = pair.get_first();
		Int2 const count = pair.get_second();

		Float2 offset = spriteBuilder.slice.offset;
		Float2 size = spriteBuilder.slice.size;

		// create the Sprites for the automatic slices
		for (Int y = 0; y < count.y; y++)
		{
			for (Int x = 0; x < count.x; x++)
			{
				spriteBuilder.id = UUID::create();
				spriteBuilder.slice.offset = offset + Float2(static_cast<Float>(x) * size.x, static_cast<Float>(y) * size.y);
				Ref<Sprite> sprite = assetManager.create<Sprite>(spriteBuilder);
				m_automaticSprites[group].add(Int2(x, y), std::move(sprite));
			}
		}
		
		// go to the next group
		group++;
	}

	for (Size i = 0; i < m_manualSlices.get_size(); i++)
	{
		// get the data
		auto const& pair = m_manualSlices[i];
		spriteBuilder.slice = pair.get_first();
		spriteBuilder.id = pair.get_second();

		// create the sprite
		m_manualSprites.add(assetManager.create<Sprite>(spriteBuilder));
	}
}

void Minty::SpriteAtlas::on_unload()
{
	AssetManager& assetManager = AssetManager::get_singleton();

	// unload all Sprites
	for (auto const& sprite : m_manualSprites)
	{
		if (sprite != nullptr)
		{
			assetManager.unload(sprite->get_id());
		}
	}
	for (auto& [group, sprites] : m_automaticSprites)
	{
		for (auto const& [coords, sprite] : sprites)
		{
			if (sprite != nullptr)
			{
				assetManager.unload(sprite->get_id());
			}
		}
	}

	// remove references
	m_manualSprites.clear();
	m_automaticSprites.clear();
}

Owner<SpriteAtlas> Minty::SpriteAtlas::create(SpriteAtlasBuilder const& builder)
{
	return Owner<SpriteAtlas>(new SpriteAtlas(builder));
}
