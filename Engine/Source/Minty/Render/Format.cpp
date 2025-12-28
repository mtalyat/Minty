#include "pch.h"
#include "Format.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size FORMAT_COUNT = 96;
static constexpr Char const* FORMAT_STRINGS[FORMAT_COUNT] = {
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

Size Minty::format_get_size(Format const format)
{
	switch (format)
	{
	case Format::R4G4_UNORM_PACK8:
	case Format::R8_UNORM:
	case Format::R8_SNORM:
	case Format::R8_USCALED:
	case Format::R8_SSCALED:
	case Format::R8_UINT:
	case Format::R8_SINT:
	case Format::R8_SRGB:
		return sizeof(Byte) * 1;
	case Format::R4G4B4A4_UNORM_PACK16:
	case Format::B4G4R4A4_UNORM_PACK16:
	case Format::R5G6B5_UNORM_PACK16:
	case Format::B5G6R5_UNORM_PACK16:
	case Format::R5G5B5A1_UNORM_PACK16:
	case Format::B5G5R5A1_UNORM_PACK16:
	case Format::A1R5G5B5_UNORM_PACK16:
	case Format::R8G8_UNORM:
	case Format::R8G8_SNORM:
	case Format::R8G8_USCALED:
	case Format::R8G8_SSCALED:
	case Format::R8G8_UINT:
	case Format::R8G8_SINT:
	case Format::R8G8_SRGB:
	case Format::R16_UNORM:
	case Format::R16_SNORM:
	case Format::R16_USCALED:
	case Format::R16_SSCALED:
	case Format::R16_UINT:
	case Format::R16_SINT:
	case Format::R16_SFLOAT:
		return sizeof(Byte) * 2;
	case Format::R8G8B8_UNORM:
	case Format::R8G8B8_SNORM:
	case Format::R8G8B8_USCALED:
	case Format::R8G8B8_SSCALED:
	case Format::R8G8B8_UINT:
	case Format::R8G8B8_SINT:
	case Format::R8G8B8_SRGB:
	case Format::B8G8R8_UNORM:
	case Format::B8G8R8_SNORM:
	case Format::B8G8R8_USCALED:
	case Format::B8G8R8_SSCALED:
	case Format::B8G8R8_UINT:
	case Format::B8G8R8_SINT:
	case Format::B8G8R8_SRGB:
		return sizeof(Byte) * 3;
	case Format::R8G8B8A8_UNORM:
	case Format::R8G8B8A8_SNORM:
	case Format::R8G8B8A8_USCALED:
	case Format::R8G8B8A8_SSCALED:
	case Format::R8G8B8A8_UINT:
	case Format::R8G8B8A8_SINT:
	case Format::R8G8B8A8_SRGB:
	case Format::B8G8R8A8_UNORM:
	case Format::B8G8R8A8_SNORM:
	case Format::B8G8R8A8_USCALED:
	case Format::B8G8R8A8_SSCALED:
	case Format::B8G8R8A8_UINT:
	case Format::B8G8R8A8_SINT:
	case Format::B8G8R8A8_SRGB:
	case Format::A8B8G8R8_UNORM_PACK32:
	case Format::A8B8G8R8_SNORM_PACK32:
	case Format::A8B8G8R8_USCALED_PACK32:
	case Format::A8B8G8R8_SSCALED_PACK32:
	case Format::A8B8G8R8_UINT_PACK32:
	case Format::A8B8G8R8_SINT_PACK32:
	case Format::A8B8G8R8_SRGB_PACK32:
	case Format::A2R10G10B10_UNORM_PACK32:
	case Format::A2R10G10B10_SNORM_PACK32:
	case Format::A2R10G10B10_USCALED_PACK32:
	case Format::A2R10G10B10_SSCALED_PACK32:
	case Format::A2R10G10B10_UINT_PACK32:
	case Format::A2R10G10B10_SINT_PACK32:
	case Format::A2B10G10R10_UNORM_PACK32:
	case Format::A2B10G10R10_SNORM_PACK32:
	case Format::A2B10G10R10_USCALED_PACK32:
	case Format::A2B10G10R10_SSCALED_PACK32:
	case Format::A2B10G10R10_UINT_PACK32:
	case Format::A2B10G10R10_SINT_PACK32:
	case Format::R16G16_UNORM:
	case Format::R16G16_SNORM:
	case Format::R16G16_USCALED:
	case Format::R16G16_SSCALED:
	case Format::R16G16_UINT:
	case Format::R16G16_SINT:
	case Format::R16G16_SFLOAT:
		return sizeof(Byte) * 4;
	case Format::R16G16B16_UNORM:
	case Format::R16G16B16_SNORM:
	case Format::R16G16B16_USCALED:
	case Format::R16G16B16_SSCALED:
	case Format::R16G16B16_UINT:
	case Format::R16G16B16_SINT:
	case Format::R16G16B16_SFLOAT:
		return sizeof(Byte) * 6;
	case Format::R16G16B16A16_UNORM:
	case Format::R16G16B16A16_SNORM:
	case Format::R16G16B16A16_USCALED:
	case Format::R16G16B16A16_SSCALED:
	case Format::R16G16B16A16_UINT:
	case Format::R16G16B16A16_SINT:
	case Format::R16G16B16A16_SFLOAT:
	case Format::R32_UINT:
	case Format::R32_SINT:
	case Format::R32_SFLOAT:
		return sizeof(Byte) * 8;
	case Format::R32G32_UINT:
	case Format::R32G32_SINT:
	case Format::R32G32_SFLOAT:
		return sizeof(Byte) * 16;
	case Format::R32G32B32_UINT:
	case Format::R32G32B32_SINT:
	case Format::R32G32B32_SFLOAT:
		return sizeof(Byte) * 24;
	case Format::R32G32B32A32_UINT:
	case Format::R32G32B32A32_SINT:
	case Format::R32G32B32A32_SFLOAT:
	case Format::R64_UINT:
	case Format::R64_SINT:
	case Format::R64_SFLOAT:
		return sizeof(Byte) * 64;
	case Format::R64G64_UINT:
	case Format::R64G64_SINT:
	case Format::R64G64_SFLOAT:
		return sizeof(Byte) * 128;
	case Format::R64G64B64_UINT:
	case Format::R64G64B64_SINT:
	case Format::R64G64B64_SFLOAT:
		return sizeof(Byte) * 192;
	case Format::R64G64B64A64_UINT:
	case Format::R64G64B64A64_SINT:
	case Format::R64G64B64A64_SFLOAT:
		return sizeof(Byte) * 256;
	default:
		return 0;
	}
}

Bool Minty::Parser<Format>::parse(StringView const str, Format &value)
{
	if(str == "Default")
	{
		value = Format::Default;
		return true;
	}

    return Tool::parse_string_to_enum(str, reinterpret_cast<Size&>(value), FORMAT_STRINGS, FORMAT_COUNT);
}

String Minty::Parser<Format>::to_string(Format const &obj)
{
	if (obj == Format::Default)
	{
		return "Default";
	}

    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), FORMAT_STRINGS, FORMAT_COUNT);
}
