#include "pch.h"
#include "Buffer.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Buffer.h"
#endif // MINTY_VULKAN

using namespace Minty;

Owner<Buffer> Minty::Buffer::create(BufferInfo const& info)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_Buffer>(info);
#else
	return Owner<Buffer>();
#endif // MINTY_VULKAN
}
