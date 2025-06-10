#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// Types of Assets that can be loaded into the engine.
	/// 
	/// This determines the loading order of the Assets when loading the Scene.
	/// </summary>
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
		FontVariant,
		Font,
		Mesh,
	};

	String to_string(AssetType const obj);
	AssetType parse_to_asset_type(String const& string);
	Bool parse_try_asset_type(String const& string, AssetType& value);
	template<>
	inline AssetType parse_to<AssetType>(String const& string) { return parse_to_asset_type(string); }
	template<>
	inline Bool parse_try<AssetType>(String const& string, AssetType& value) { return parse_try_asset_type(string, value); }
}