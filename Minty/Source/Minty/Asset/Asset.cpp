#include "pch.h"
#include "Asset.h"
#include "Minty/Core/Constant.h"
#include "Minty/Data/Map.h"

using namespace Minty;

AssetType Minty::Asset::get_asset_type(Path const& path)
{
	MINTY_ASSERT(!path.is_empty(), "Cannot get asset type from empty path.");

	static Map<Path, AssetType> types
	{
		{ EXTENSION_SCRIPT, AssetType::Script},

		{ EXTENSION_BITMAP, AssetType::Image },
		{ EXTENSION_JPG, AssetType::Image },
		{ EXTENSION_JPEG, AssetType::Image },
		{ EXTENSION_PNG, AssetType::Image },

		{ EXTENSION_SPRITE, AssetType::Sprite },

		{ EXTENSION_MATERIAL, AssetType::Material },

		{ EXTENSION_MATERIAL_TEMPLATE, AssetType::MaterialTemplate },

		{ EXTENSION_SHADER, AssetType::Shader },

		{ EXTENSION_SHADER_MODULE, AssetType::ShaderModule },

		{ EXTENSION_SHADER_CODE, AssetType::ShaderCode },
		{ EXTENSION_SHADER_CODE_FRAGMENT, AssetType::ShaderCode },
		{ EXTENSION_SHADER_CODE_VERTEX, AssetType::ShaderCode },

		{ EXTENSION_SCENE, AssetType::Scene },

		{ EXTENSION_MESH_OBJECT, AssetType::Mesh },

		{ EXTENSION_AUDIO_CLIP_WAV, AssetType::AudioClip },
		{ EXTENSION_AUDIO_CLIP_MP3, AssetType::AudioClip },

		{ EXTENSION_ANIMATION, AssetType::Animation },

		{ EXTENSION_ANIMATOR, AssetType::Animator },

		{ EXTENSION_WRAP, AssetType::Wrap },

		{ EXTENSION_FONT_VARIANT, AssetType::FontVariant },
		{ EXTENSION_FONT, AssetType::Font }
	};

	auto found = types.find(path.get_extension());

	// extension not found
	if (found == types.end()) return AssetType::Generic;

	return found->second;
}

AssetType Minty::Asset::get_asset_type(TypeID const& typeId)
{
	return AssetType::Generic;
}

Path Minty::Asset::get_meta_path(Path const& path)
{
	MINTY_ASSERT(!path.is_empty(), "Cannot get meta path from empty path.");

	return Path(path.get_string() + EXTENSION_META);
}