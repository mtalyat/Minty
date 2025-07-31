#include "pch.h"
#include "SpriteComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Render/SpriteAtlas.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::SpriteComponent::serialize(Writer& writer) const
{
	writer.write("Sprite", sprite);
	writer.write("Color", color);
	writer.write("FlipX", flipX);
	writer.write("FlipY", flipY);
}

Bool Minty::SpriteComponent::deserialize(Reader& reader)
{
	AssetManager& assetManager = AssetManager::get_singleton();

	// read the ID
	UUID id;
	if (reader.read_default(id) || reader.read("Sprite", id))
	{
		// get the asset with the given ID
		Ref<Asset> asset = assetManager.get_asset(id);

		MINTY_ASSERT(asset != nullptr, F("SpriteComponent: Asset with ID {} does not exist.", id));

		AssetType assetType = asset->get_asset_type();

		MINTY_ASSERT(assetType == AssetType::Sprite || assetType == AssetType::SpriteAtlas,
			F("SpriteComponent: Asset with ID {} is not a Sprite or SpriteAtlas.", id));

		// handle different types
		switch (assetType)
		{
		case AssetType::Sprite:
			sprite = asset.cast_to<Sprite>();
			break;
		case AssetType::SpriteAtlas:
		{
			Ref<SpriteAtlas> atlas = asset.cast_to<SpriteAtlas>();

			// read the group of the index, which defaults to group 0
			Int groupIndex;
			reader.read("Group", groupIndex, 0);

			// read the index of the sprite in the atlas
			// could be either a 1D or 2D index
			String indexText;
			if (!reader.read("Index", indexText))
			{
				MINTY_ABORT(F("SpriteComponent: Failed to read Index for SpriteAtlas with ID {}.", id));
				return false;
			}
			Int index1d;
			Int2 index2d;
			if (try_int(indexText, index1d))
			{
				// convert into 2D index
				Int2 count = atlas->get_group(groupIndex).get_count();
				index2d.y = index1d / count.x;
				index2d.x = index1d - index2d.y * count.x;
			}
			else if (try_int2(indexText, index2d))
			{
				// do nothing
			}
			else
			{
				MINTY_ABORT(F("SpriteComponent: Invalid Index format for SpriteAtlas with ID {}: {}", id, indexText));
				return false;
			}

			// get the sprite from the atlas
			id = atlas->get_sprite_id(groupIndex, index2d);
			sprite = assetManager.get<Sprite>(id);

			break;
		}
		}
	}

	reader.read("Color", color);
	reader.read("FlipX", flipX);
	reader.read("FlipY", flipY);

	return true;
}
