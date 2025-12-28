#include "pch.h"
#include "AssetType.h"

using namespace Minty;

static constexpr Size ASSETTYPE_COUNT = 26;
static constexpr Char const* ASSETTYPE_STRINGS[ASSETTYPE_COUNT] = {
	"Generic",
	"Wrap",
	"Info",
	"Script",
	"AudioClip",
	"Animation",
	"Animator",
	"Viewport",
	"Bitmap",
	"Image",
	"Texture",
	"Surface",
	"RenderPass",
	"RenderTarget",
	"Camera",
	"ShaderCode",
	"ShaderModule",
	"Shader",
	"MaterialTemplate",
	"Material",
	"Sprite",
	"SpriteAtlas",
	"FontVariant",
	"Font",
	"Mesh",
	"Prefab"
};

Bool Minty::Parser<AssetType>::parse(StringView const str, AssetType &value)
{
    return Tool::try_parse_enum(str, ASSETTYPE_STRINGS, ASSETTYPE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<AssetType>::to_string(AssetType const &value)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(value), ASSETTYPE_STRINGS, ASSETTYPE_COUNT);
}
