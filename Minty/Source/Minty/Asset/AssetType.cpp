#include "pch.h"
#include "AssetType.h"

using namespace Minty;

String Minty::to_string(AssetType const obj)
{
	switch (obj)
	{
	case AssetType::Generic: return "Generic";
	case AssetType::Wrap: return "Wrap";
	case AssetType::Script: return "Script";
	case AssetType::AudioClip: return "AudioClip";
	case AssetType::Animation: return "Animation";
	case AssetType::Animator: return "Animator";
	case AssetType::Viewport: return "Viewport";
	case AssetType::Image: return "Image";
	case AssetType::Texture: return "Texture";
	case AssetType::Surface: return "Surface";
	case AssetType::RenderPass: return "RenderPass";
	case AssetType::RenderTarget: return "RenderTarget";
	case AssetType::Camera: return "Camera";
	case AssetType::ShaderCode: return "ShaderCode";
	case AssetType::ShaderModule: return "ShaderModule";
	case AssetType::Shader: return "Shader";
	case AssetType::MaterialTemplate: return "MaterialTemplate";
	case AssetType::Material: return "Material";
	case AssetType::Sprite: return "Sprite";
	case AssetType::FontVariant: return "FontVariant";
	case AssetType::Font: return "Font";
	case AssetType::Mesh: return "Mesh";

	default: return "";
	}
}

AssetType Minty::parse_to_asset_type(String const& string)
{
	if (string == "Generic") return AssetType::Generic;
	if (string == "Wrap") return AssetType::Wrap;
	if (string == "Script") return AssetType::Script;
	if (string == "AudioClip") return AssetType::AudioClip;
	if (string == "Animation") return AssetType::Animation;
	if (string == "Animator") return AssetType::Animator;
	if (string == "Viewport") return AssetType::Viewport;
	if (string == "Image") return AssetType::Image;
	if (string == "Texture") return AssetType::Texture;
	if (string == "Surface") return AssetType::Surface;
	if (string == "RenderPass") return AssetType::RenderPass;
	if (string == "RenderTarget") return AssetType::RenderTarget;
	if (string == "Camera") return AssetType::Camera;
	if (string == "ShaderCode") return AssetType::ShaderCode;
	if (string == "ShaderModule") return AssetType::ShaderModule;
	if (string == "Shader") return AssetType::Shader;
	if (string == "MaterialTemplate") return AssetType::MaterialTemplate;
	if (string == "Material") return AssetType::Material;
	if (string == "Sprite") return AssetType::Sprite;
	if (string == "FontVariant") return AssetType::FontVariant;
	if (string == "Font") return AssetType::Font;
	if (string == "Mesh") return AssetType::Mesh;

	return AssetType();
}

Bool Minty::parse_try_asset_type(String const& string, AssetType& value)
{
	value = parse_to_asset_type(string);
	return true;
}