#ifndef MINTY_ASSET_ASSETTYPE_H
#define MINTY_ASSET_ASSETTYPE_H

/**
 * @file AssetType.h
 * @brief Header file defining the AssetType enum and related functions.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @enum AssetType
	 * @brief Represents the type of an Asset.
	 */
	enum class AssetType
	{
		Generic,
		Wrap,
		Info,
		Script,
		AudioClip,
		Animation,
		Animator,
		Viewport,
		Bitmap,
		Image,
		Texture,
		Surface,
		RenderPass,
		RenderTarget,
		Camera,
		ShaderCode,
		ShaderModule,
		Shader,
		MaterialTemplate,
		Material,
		Sprite,
		SpriteAtlas,
		FontVariant,
		Font,
		Mesh,
		Prefab,
	};

	template<>
	struct Parser<AssetType>
	{
		static Bool parse(StringView const str, AssetType &value);
		static String to_string(AssetType const &value);
	};
}

#endif // MINTY_ASSET_ASSETTYPE_H