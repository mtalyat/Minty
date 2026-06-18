#include "pch.h"
#include "ImageFormat.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Size IMAGE_FORMAT_COUNT = static_cast<Size>(ImageFormatEnum::Count);
static constexpr Char const* IMAGE_FORMAT_STRINGS[IMAGE_FORMAT_COUNT] = {
    "Undefined",
	"R4G4_UNORM_PACK8",
	"R4G4B4A4_UNORM_PACK16",
	"B4G4R4A4_UNORM_PACK16",
	"R5G6B5_UNORM_PACK16",
	"B5G6R5_UNORM_PACK16",
	"R5G5B5A1_UNORM_PACK16",
	"B5G5R5A1_UNORM_PACK16",
	"A1R5G5B5_UNORM_PACK16",
	"R8_UNORM",
	"R8_SNORM",
	"R8_USCALED",
	"R8_SSCALED",
	"R8_UINT",
	"R8_SINT",
	"R8_SRGB",
	"R8G8_UNORM",
	"R8G8_SNORM",
	"R8G8_USCALED",
	"R8G8_SSCALED",
	"R8G8_UINT",
	"R8G8_SINT",
	"R8G8_SRGB",
	"R8G8B8_UNORM",
	"R8G8B8_SNORM",
	"R8G8B8_USCALED",
	"R8G8B8_SSCALED",
	"R8G8B8_UINT",
	"R8G8B8_SINT",
	"R8G8B8_SRGB",
	"B8G8R8_UNORM",
	"B8G8R8_SNORM",
	"B8G8R8_USCALED",
	"B8G8R8_SSCALED",
	"B8G8R8_UINT",
	"B8G8R8_SINT",
	"B8G8R8_SRGB",
	"R8G8B8A8_UNORM",
	"R8G8B8A8_SNORM",
	"R8G8B8A8_USCALED",
	"R8G8B8A8_SSCALED",
	"R8G8B8A8_UINT",
	"R8G8B8A8_SINT",
	"R8G8B8A8_SRGB",
	"B8G8R8A8_UNORM",
	"B8G8R8A8_SNORM",
	"B8G8R8A8_USCALED",
	"B8G8R8A8_SSCALED",
	"B8G8R8A8_UINT",
	"B8G8R8A8_SINT",
	"B8G8R8A8_SRGB",
	"A8B8G8R8_UNORM_PACK32",
	"A8B8G8R8_SNORM_PACK32",
	"A8B8G8R8_USCALED_PACK32",
	"A8B8G8R8_SSCALED_PACK32",
	"A8B8G8R8_UINT_PACK32",
	"A8B8G8R8_SINT_PACK32",
	"A8B8G8R8_SRGB_PACK32",
	"A2R10G10B10_UNORM_PACK32",
	"A2R10G10B10_SNORM_PACK32",
	"A2R10G10B10_USCALED_PACK32",
	"A2R10G10B10_SSCALED_PACK32",
	"A2R10G10B10_UINT_PACK32",
	"A2R10G10B10_SINT_PACK32",
	"A2B10G10R10_UNORM_PACK32",
	"A2B10G10R10_SNORM_PACK32",
	"A2B10G10R10_USCALED_PACK32",
	"A2B10G10R10_SSCALED_PACK32",
	"A2B10G10R10_UINT_PACK32",
	"A2B10G10R10_SINT_PACK32",
	"R16_UNORM",
	"R16_SNORM",
	"R16_USCALED",
	"R16_SSCALED",
	"R16_UINT",
	"R16_SINT",
	"R16_SFLOAT",
	"R16G16_UNORM",
	"R16G16_SNORM",
	"R16G16_USCALED",
	"R16G16_SSCALED",
	"R16G16_UINT",
	"R16G16_SINT",
	"R16G16_SFLOAT",
	"R16G16B16_UNORM",
	"R16G16B16_SNORM",
	"R16G16B16_USCALED",
	"R16G16B16_SSCALED",
	"R16G16B16_UINT",
	"R16G16B16_SINT",
	"R16G16B16_SFLOAT",
	"R16G16B16A16_UNORM",
	"R16G16B16A16_SNORM",
	"R16G16B16A16_USCALED",
	"R16G16B16A16_SSCALED",
	"R16G16B16A16_UINT",
	"R16G16B16A16_SINT",
	"R16G16B16A16_SFLOAT",
	"R32_UINT",
	"R32_SINT",
	"R32_SFLOAT",
	"R32G32_UINT",
	"R32G32_SINT",
	"R32G32_SFLOAT",
	"R32G32B32_UINT",
	"R32G32B32_SINT",
	"R32G32B32_SFLOAT",
	"R32G32B32A32_UINT",
	"R32G32B32A32_SINT",
	"R32G32B32A32_SFLOAT",
	"R64_UINT",
	"R64_SINT",
	"R64_SFLOAT",
	"R64G64_UINT",
	"R64G64_SINT",
	"R64G64_SFLOAT",
	"R64G64B64_UINT",
	"R64G64B64_SINT",
	"R64G64B64_SFLOAT",
	"R64G64B64A64_UINT",
	"R64G64B64A64_SINT",
	"R64G64B64A64_SFLOAT",
};

Bool Minty::Parser<ImageFormatEnum>::parse(StringView const str, ImageFormatEnum &value)
{
    // Check for aliases
    if (str == "R8G8B8A8")
    {
        value = ImageFormatEnum::R8G8B8A8_SRGB;
        return true;
    }
    else if (str == "R8G8B8")
    {
        value = ImageFormatEnum::R8G8B8_SRGB;
        return true;
    }
    else if (str == "R8G8")
    {
        value = ImageFormatEnum::R8G8_SRGB;
        return true;
    }
    else if (str == "R8")
    {
        value = ImageFormatEnum::R8_SRGB;
        return true;
    }
    if (str == "Gray")
    {
        value = ImageFormatEnum::Gray;
        return true;
    }
    else if (str == "GrayAlpha")
    {
        value = ImageFormatEnum::GrayAlpha;
        return true;
    }
    else if (str == "RGB")
    {
        value = ImageFormatEnum::RGB;
        return true;
    }
    else if (str == "RGBA")
    {
        value = ImageFormatEnum::RGBA;
        return true;
    }

    // Check for regular strings
    return Tool::try_parse_enum(str, IMAGE_FORMAT_STRINGS, IMAGE_FORMAT_COUNT, value);
}

String Minty::Parser<ImageFormatEnum>::to_string(ImageFormatEnum const &value)
{
    return Tool::to_string_enum(value, IMAGE_FORMAT_STRINGS, IMAGE_FORMAT_COUNT);
}

UInt32 Minty::ImageFormat::get_depth() const
{
    switch (value)
	{
	case ImageFormatEnum::R4G4_UNORM_PACK8:
	case ImageFormatEnum::R8_UNORM:
	case ImageFormatEnum::R8_SNORM:
	case ImageFormatEnum::R8_USCALED:
	case ImageFormatEnum::R8_SSCALED:
	case ImageFormatEnum::R8_UINT:
	case ImageFormatEnum::R8_SINT:
	case ImageFormatEnum::R8_SRGB:
		return sizeof(Byte) * 1;
	case ImageFormatEnum::R4G4B4A4_UNORM_PACK16:
	case ImageFormatEnum::B4G4R4A4_UNORM_PACK16:
	case ImageFormatEnum::R5G6B5_UNORM_PACK16:
	case ImageFormatEnum::B5G6R5_UNORM_PACK16:
	case ImageFormatEnum::R5G5B5A1_UNORM_PACK16:
	case ImageFormatEnum::B5G5R5A1_UNORM_PACK16:
	case ImageFormatEnum::A1R5G5B5_UNORM_PACK16:
	case ImageFormatEnum::R8G8_UNORM:
	case ImageFormatEnum::R8G8_SNORM:
	case ImageFormatEnum::R8G8_USCALED:
	case ImageFormatEnum::R8G8_SSCALED:
	case ImageFormatEnum::R8G8_UINT:
	case ImageFormatEnum::R8G8_SINT:
	case ImageFormatEnum::R8G8_SRGB:
	case ImageFormatEnum::R16_UNORM:
	case ImageFormatEnum::R16_SNORM:
	case ImageFormatEnum::R16_USCALED:
	case ImageFormatEnum::R16_SSCALED:
	case ImageFormatEnum::R16_UINT:
	case ImageFormatEnum::R16_SINT:
	case ImageFormatEnum::R16_SFLOAT:
		return sizeof(Byte) * 2;
	case ImageFormatEnum::R8G8B8_UNORM:
	case ImageFormatEnum::R8G8B8_SNORM:
	case ImageFormatEnum::R8G8B8_USCALED:
	case ImageFormatEnum::R8G8B8_SSCALED:
	case ImageFormatEnum::R8G8B8_UINT:
	case ImageFormatEnum::R8G8B8_SINT:
	case ImageFormatEnum::R8G8B8_SRGB:
	case ImageFormatEnum::B8G8R8_UNORM:
	case ImageFormatEnum::B8G8R8_SNORM:
	case ImageFormatEnum::B8G8R8_USCALED:
	case ImageFormatEnum::B8G8R8_SSCALED:
	case ImageFormatEnum::B8G8R8_UINT:
	case ImageFormatEnum::B8G8R8_SINT:
	case ImageFormatEnum::B8G8R8_SRGB:
		return sizeof(Byte) * 3;
	case ImageFormatEnum::R8G8B8A8_UNORM:
	case ImageFormatEnum::R8G8B8A8_SNORM:
	case ImageFormatEnum::R8G8B8A8_USCALED:
	case ImageFormatEnum::R8G8B8A8_SSCALED:
	case ImageFormatEnum::R8G8B8A8_UINT:
	case ImageFormatEnum::R8G8B8A8_SINT:
	case ImageFormatEnum::R8G8B8A8_SRGB:
	case ImageFormatEnum::B8G8R8A8_UNORM:
	case ImageFormatEnum::B8G8R8A8_SNORM:
	case ImageFormatEnum::B8G8R8A8_USCALED:
	case ImageFormatEnum::B8G8R8A8_SSCALED:
	case ImageFormatEnum::B8G8R8A8_UINT:
	case ImageFormatEnum::B8G8R8A8_SINT:
	case ImageFormatEnum::B8G8R8A8_SRGB:
	case ImageFormatEnum::A8B8G8R8_UNORM_PACK32:
	case ImageFormatEnum::A8B8G8R8_SNORM_PACK32:
	case ImageFormatEnum::A8B8G8R8_USCALED_PACK32:
	case ImageFormatEnum::A8B8G8R8_SSCALED_PACK32:
	case ImageFormatEnum::A8B8G8R8_UINT_PACK32:
	case ImageFormatEnum::A8B8G8R8_SINT_PACK32:
	case ImageFormatEnum::A8B8G8R8_SRGB_PACK32:
	case ImageFormatEnum::A2R10G10B10_UNORM_PACK32:
	case ImageFormatEnum::A2R10G10B10_SNORM_PACK32:
	case ImageFormatEnum::A2R10G10B10_USCALED_PACK32:
	case ImageFormatEnum::A2R10G10B10_SSCALED_PACK32:
	case ImageFormatEnum::A2R10G10B10_UINT_PACK32:
	case ImageFormatEnum::A2R10G10B10_SINT_PACK32:
	case ImageFormatEnum::A2B10G10R10_UNORM_PACK32:
	case ImageFormatEnum::A2B10G10R10_SNORM_PACK32:
	case ImageFormatEnum::A2B10G10R10_USCALED_PACK32:
	case ImageFormatEnum::A2B10G10R10_SSCALED_PACK32:
	case ImageFormatEnum::A2B10G10R10_UINT_PACK32:
	case ImageFormatEnum::A2B10G10R10_SINT_PACK32:
	case ImageFormatEnum::R16G16_UNORM:
	case ImageFormatEnum::R16G16_SNORM:
	case ImageFormatEnum::R16G16_USCALED:
	case ImageFormatEnum::R16G16_SSCALED:
	case ImageFormatEnum::R16G16_UINT:
	case ImageFormatEnum::R16G16_SINT:
	case ImageFormatEnum::R16G16_SFLOAT:
		return sizeof(Byte) * 4;
	case ImageFormatEnum::R16G16B16_UNORM:
	case ImageFormatEnum::R16G16B16_SNORM:
	case ImageFormatEnum::R16G16B16_USCALED:
	case ImageFormatEnum::R16G16B16_SSCALED:
	case ImageFormatEnum::R16G16B16_UINT:
	case ImageFormatEnum::R16G16B16_SINT:
	case ImageFormatEnum::R16G16B16_SFLOAT:
		return sizeof(Byte) * 6;
	case ImageFormatEnum::R16G16B16A16_UNORM:
	case ImageFormatEnum::R16G16B16A16_SNORM:
	case ImageFormatEnum::R16G16B16A16_USCALED:
	case ImageFormatEnum::R16G16B16A16_SSCALED:
	case ImageFormatEnum::R16G16B16A16_UINT:
	case ImageFormatEnum::R16G16B16A16_SINT:
	case ImageFormatEnum::R16G16B16A16_SFLOAT:
	case ImageFormatEnum::R32_UINT:
	case ImageFormatEnum::R32_SINT:
	case ImageFormatEnum::R32_SFLOAT:
		return sizeof(Byte) * 8;
	case ImageFormatEnum::R32G32_UINT:
	case ImageFormatEnum::R32G32_SINT:
	case ImageFormatEnum::R32G32_SFLOAT:
		return sizeof(Byte) * 16;
	case ImageFormatEnum::R32G32B32_UINT:
	case ImageFormatEnum::R32G32B32_SINT:
	case ImageFormatEnum::R32G32B32_SFLOAT:
		return sizeof(Byte) * 24;
	case ImageFormatEnum::R32G32B32A32_UINT:
	case ImageFormatEnum::R32G32B32A32_SINT:
	case ImageFormatEnum::R32G32B32A32_SFLOAT:
	case ImageFormatEnum::R64_UINT:
	case ImageFormatEnum::R64_SINT:
	case ImageFormatEnum::R64_SFLOAT:
		return sizeof(Byte) * 64;
	case ImageFormatEnum::R64G64_UINT:
	case ImageFormatEnum::R64G64_SINT:
	case ImageFormatEnum::R64G64_SFLOAT:
		return sizeof(Byte) * 128;
	case ImageFormatEnum::R64G64B64_UINT:
	case ImageFormatEnum::R64G64B64_SINT:
	case ImageFormatEnum::R64G64B64_SFLOAT:
		return sizeof(Byte) * 192;
	case ImageFormatEnum::R64G64B64A64_UINT:
	case ImageFormatEnum::R64G64B64A64_SINT:
	case ImageFormatEnum::R64G64B64A64_SFLOAT:
		return sizeof(Byte) * 256;
	default:
		return 0;
	}
}
