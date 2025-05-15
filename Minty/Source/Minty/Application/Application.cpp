#include "pch.h"
#include "Application.h"

using namespace Minty;

Application* Application::s_instance = nullptr;

Owner<Application> Minty::Application::create(ApplicationBuilder const& builder)
{
	return Owner<Application>(builder);
}

Application& Minty::Application::get_singleton()
{
	MINTY_ASSERT(s_instance, "Application singleton is null.");
	return *s_instance;
}
