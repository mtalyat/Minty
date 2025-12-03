#include "pch.h"
#include "Buffer.h"
#include "Minty/Render/BufferInfo.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Buffer.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::Buffer::Buffer(BufferInfo const &info)
	: m_usage(info.usage), m_frequent(info.frequent)
{
}

Shared<Buffer> Minty::Buffer::create(BufferInfo const &info)
{
#ifdef MINTY_VULKAN
	return Shared<Vulkan_Buffer>::create(info);
#else
	return Shared<Buffer>();
#endif // MINTY_VULKAN
}

Shared<Buffer> Minty::Buffer::create()
{
	BufferInfo info{};
	return create(info);
}
