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

void Minty::Serializer<SpriteComponent>::serialize(Writer &writer, SpriteComponent const &value)
{
	writer.write("Sprite", value.sprite);
	writer.write("MaterialTemplate", value.materialTemplate);
	writer.write("Color", value.color);
	writer.write("FlipX", value.flipX);
	writer.write("FlipY", value.flipY);
}

void Minty::Serializer<SpriteComponent>::deserialize(Reader &reader, SpriteComponent &value)
{
	AssetManager& assetManager = AssetManager::get_singleton();

	// read the ID
	UUID id;
	if (reader.read("Sprite", id))
	{
		// get the asset with the given ID
		value.source = assetManager.get_asset_ref(id);
		MINTY_ASSERT_F(value.source != nullptr, ErrorCode::Asset_MissingDependency, id);
	}

	if(value.source != nullptr)
	{
		AssetType assetType = value.source->get_asset_type();
		MINTY_ASSERT_F(assetType == AssetType::Sprite || assetType == AssetType::SpriteAtlas, ErrorCode::Asset_InvalidDependencyType, id);

		// handle different types
		switch (assetType)
		{
		case AssetType::Sprite:
			value.sprite = value.source.cast<Sprite>();
			break;
		case AssetType::SpriteAtlas:
		{
			Ref<SpriteAtlas> atlas = value.source.cast<SpriteAtlas>();
			// read the group of the index
			reader.read("Group", value.group);

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
				if (Parser<Int>::parse(indexText, index1d))
				{
					// convert into 2D index
					Int2 count = atlas->get_group(value.group).get_count();
					index2d.y = index1d / count.x;
					index2d.x = index1d - index2d.y * count.x;
				}
				else if (Parser<Int2>::parse(indexText, index2d))
				{
					// do nothing
				}
				else
				{
					MINTY_ABORT_F(ErrorCode::Asset_InvalidConfiguration, id, indexText);
					return;
				}
			}

			// get the sprite from the atlas
			id = atlas->get_sprite_id(value.group, index2d);
			value.sprite = assetManager.get_ref<Sprite>(id);

			break;
		}
		}
	}

	if (reader.read("MaterialTemplate", id))
	{
		value.materialTemplate = assetManager.get_ref<MaterialTemplate>(id);
	}

	reader.read("Color", value.color);
	reader.read("FlipX", value.flipX);
	reader.read("FlipY", value.flipY);
}
