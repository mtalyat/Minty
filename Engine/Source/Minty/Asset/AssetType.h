#ifndef MINTY_ASSET_ASSETTYPE_H
#define MINTY_ASSET_ASSETTYPE_H

/**
 * @file AssetType.h
 * @brief Header file defining the AssetType enum and related functions.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

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
		Info, // application info
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

	String to_string(AssetType const obj);
	AssetType parse_to_asset_type(String const& string);
	Bool parse_try_asset_type(String const& string, AssetType& value);
	template<>
	inline AssetType parse_to<AssetType>(StringView const string) { return parse_to_asset_type(string); }
	template<>
	inline Bool parse_try<AssetType>(StringView const string, AssetType& value) { return parse_try_asset_type(string, value); }
}

#endif // MINTY_ASSET_ASSETTYPE_H