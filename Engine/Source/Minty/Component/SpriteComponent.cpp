#include "pch.h"
#include "SpriteComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Minty/Render/Sprite.h"
#include "Minty/Render/SpriteAtlas.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

void Minty::SpriteComponent::serialize(Writer& writer) const
{
	writer.write("Sprite", sprite);
	writer.write("MaterialTemplate", materialTemplate);
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
		source = assetManager.get_asset_ref(id);
		MINTY_ASSERT_F(source != nullptr, ErrorCode::Asset_MissingDependency, id);
	}

	if(source != nullptr)
	{
		AssetType assetType = source->get_asset_type();
		MINTY_ASSERT_F(assetType == AssetType::Sprite || assetType == AssetType::SpriteAtlas, ErrorCode::Asset_InvalidDependencyType, id);

		// handle different types
		switch (assetType)
		{
		case AssetType::Sprite:
			sprite = source.cast<Sprite>();
			break;
		case AssetType::SpriteAtlas:
		{
			Ref<SpriteAtlas> atlas = source.cast<SpriteAtlas>();

			// read the group of the index
			reader.read("Group", group);

			// read the index of the sprite in the atlas
			// could be either a 1D or 2D index
			String indexText;
			Int index1d;
			Int2 index2d;
			if (!reader.read("Index", indexText))
			{
				// default to index of (0,0)
				index2d = Int2();
			}
			else
			{
				// parse index
				if (try_int(indexText, index1d))
				{
					// convert into 2D index
					Int2 count = atlas->get_group(group).get_count();
					index2d.y = index1d / count.x;
					index2d.x = index1d - index2d.y * count.x;
				}
				else if (try_int2(indexText, index2d))
				{
					// do nothing
				}
				else
				{
					MINTY_ABORT_F(ErrorCode::Asset_InvalidConfiguration, id, indexText);
					return false;
				}
			}

			// get the sprite from the atlas
			id = atlas->get_sprite_id(group, index2d);
			sprite = assetManager.get_ref<Sprite>(id);

			break;
		}
		}
	}

	if (reader.read("MaterialTemplate", id))
	{
		materialTemplate = assetManager.get_ref<MaterialTemplate>(id);
	}

	reader.read("Color", color);
	reader.read("FlipX", flipX);
	reader.read("FlipY", flipY);

	return true;
}
