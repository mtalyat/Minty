#include "pch.h"
#include "RenderTarget.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_RenderTarget.h"
#endif // MINTY_VULKAN

using namespace Minty;

Owner<RenderTarget> Minty::RenderTarget::create(RenderTargetBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_RenderTarget>(builder);
#else
	return Owner<RenderTarget>();
#endif // MINTY_VULKAN
}
