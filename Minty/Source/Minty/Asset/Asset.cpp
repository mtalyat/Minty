#include "pch.h"
#include "Asset.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Map.h"

#include "Minty/Render/Image.h"
#include "Minty/Render/Texture.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Minty/Render/Shader.h"
#include "Minty/Render/ShaderModule.h"
#include "Minty/Render/RenderPass.h"
#include "Minty/Render/RenderTarget.h"
#include "Minty/Render/Camera.h"
#include "Minty/Render/Sprite.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Audio/AudioClip.h"
#include "Minty/Animation/Animation.h"
#include "Minty/Animation/Animator.h"
#include "Minty/Wrap/Wrap.h"
#include "Minty/Render/Font.h"
#include "Minty/Render/FontVariant.h"
#include "Minty/Asset/GenericAsset.h"

using namespace Minty;

AssetType Minty::Asset::get_asset_type(Path const& path)
{
	MINTY_ASSERT(!path.is_empty(), "Cannot get asset type from empty path.");

	static Map<Path, AssetType> types
	{
		{ EXTENSION_SCRIPT, AssetType::Script},

		{ EXTENSION_BITMAP, AssetType::Image },

		{ EXTENSION_JPG, AssetType::Texture },
		{ EXTENSION_JPEG, AssetType::Texture },
		{ EXTENSION_PNG, AssetType::Texture },

		{ EXTENSION_RENDER_PASS, AssetType::RenderPass },

		{ EXTENSION_RENDER_TARGET, AssetType::RenderTarget },

		{ EXTENSION_CAMERA, AssetType::Camera },

		{ EXTENSION_SPRITE, AssetType::Sprite },

		{ EXTENSION_MATERIAL, AssetType::Material },

		{ EXTENSION_MATERIAL_TEMPLATE, AssetType::MaterialTemplate },

		{ EXTENSION_SHADER, AssetType::Shader },

		{ EXTENSION_SHADER_MODULE, AssetType::ShaderModule },

		{ EXTENSION_SHADER_CODE, AssetType::ShaderCode },
		{ EXTENSION_SHADER_CODE_FRAGMENT, AssetType::ShaderCode },
		{ EXTENSION_SHADER_CODE_VERTEX, AssetType::ShaderCode },

		{ EXTENSION_MESH_OBJECT, AssetType::Mesh },

		{ EXTENSION_AUDIO_CLIP_WAV, AssetType::AudioClip },
		{ EXTENSION_AUDIO_CLIP_MP3, AssetType::AudioClip },

		{ EXTENSION_ANIMATION, AssetType::Animation },

		{ EXTENSION_ANIMATOR, AssetType::Animator },

		{ EXTENSION_WRAP, AssetType::Wrap },

		{ EXTENSION_FONT_VARIANT, AssetType::FontVariant },
		{ EXTENSION_FONT, AssetType::Font }
	};

	auto found = types.find(path.get_extension_full());

	// if not found, try just the last extension
	if (found == types.end())
	{
		found = types.find(path.get_extension());
	}

	// extension not found
	if (found == types.end())
	{
		MINTY_ERROR(F("Asset type not found for path: {}. Creating Generic Asset.", path));
		return AssetType::Generic;
	}

	return found->get_second();
}

AssetType Minty::Asset::get_asset_type(TypeID const& typeId)
{
	static Map<TypeID, AssetType> types
	{
		{ typeid(Image), AssetType::Image},

		{ typeid(Texture), AssetType::Texture},

		{ typeid(RenderPass), AssetType::RenderPass},

		{ typeid(RenderTarget), AssetType::RenderTarget },

		{ typeid(Camera), AssetType::Camera },

		{ typeid(Sprite), AssetType::Sprite },

		{ typeid(Material), AssetType::Material },

		{ typeid(MaterialTemplate), AssetType::MaterialTemplate },

		{ typeid(Shader), AssetType::Shader },

		{ typeid(ShaderModule), AssetType::ShaderModule },

		{ typeid(Mesh), AssetType::Mesh },

		{ typeid(AudioClip), AssetType::AudioClip },

		{ typeid(Animation), AssetType::Animation },

		{ typeid(Animator), AssetType::Animator },

		{ typeid(Wrap), AssetType::Wrap },

		{ typeid(FontVariant), AssetType::FontVariant },

		{ typeid(Font), AssetType::Font},
	};

	auto found = types.find(typeId);

	// extension not found
	if (found == types.end())
	{
		MINTY_ABORT("Asset type not found for type.");
		return AssetType::Generic;
	}

	return found->get_second();
}

Path Minty::Asset::get_meta_path(Path const& path)
{
	MINTY_ASSERT(!path.is_empty(), "Cannot get meta path from empty path.");

	return Path(path.get_string() + EXTENSION_META);
}