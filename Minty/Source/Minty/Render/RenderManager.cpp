#include "pch.h"
#include "RenderManager.h"
#include "Minty/Context/Context.h"

using namespace Minty;

Owner<RenderManager> Minty::RenderManager::create(RenderManagerBuilder const& builder)
{
    return Owner<RenderManager>();
}

RenderManager& Minty::RenderManager::instance()
{
	return Context::instance().get_render_manager();
}
