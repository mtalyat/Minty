#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Types of Assets that can be loaded into the engine.
	/// 
	/// This determines the loading order of the Assets when loading the Scene.
	/// </summary>
	enum class AssetType
	{
		None,
		Meta,
		Wrap,
		Info, // application info
		Text,
		Script,
		AudioClip,
		Animation,
		Animator,
		Viewport,
		Scissor,
		Image,
		Texture,
		RenderPass,
		RenderTarget,
		ShaderCode,
		ShaderModule,
		Shader,
		MaterialTemplate,
		Material,
		Sprite,
		FontVariant,
		Font,
		Mesh,
		Scene,
	};

	AssetType asset_type_typeid(TypeID const& typeId);
}