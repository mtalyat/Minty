#include "pch.h"
#include "RenderManager.h"
#include "Minty/Context/Context.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"

using namespace Minty;

Owner<RenderManager> Minty::RenderManager::create(RenderManagerBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_RenderManager>(builder);
#else
	return Owner<RenderManager>();
#endif // MINTY_VULKAN
}

RenderManager& Minty::RenderManager::get_singleton()
{
	return Context::get_singleton().get_render_manager();
}
