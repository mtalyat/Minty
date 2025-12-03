#include "pch.h"
#include "Image.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Render/ImageInfo.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Image.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::Image::Image(ImageInfo const &info)
	: Asset(info.id), m_format(info.format), m_type(info.type), m_tiling(info.tiling), m_aspect(info.aspect), m_usage(info.usage), m_size(info.size), m_immutable(info.immutable)
{
	MINTY_ASSERT(info.format != Format::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.type != ImageType::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.tiling != ImageTiling::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.aspect != ImageAspect::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.usage != ImageUsage::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.size.x > 0 && info.size.y > 0, ErrorCode::Argument_ExpectedAboveZero);
}

Shared<Image> Minty::Image::create(ImageInfo const &info)
{
#ifdef MINTY_VULKAN
	return Shared<Vulkan_Image>::create(info);
#else
	return Shared<Image>();
#endif // MINTY_VULKAN
}

Shared<Image> Minty::Image::create()
{
	ImageInfo info{};
	return create(info);
}
