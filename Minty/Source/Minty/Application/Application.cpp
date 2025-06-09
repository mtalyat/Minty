#include "pch.h"
#include "Application.h"
#include "Minty/Time/Stopwatch.h"

using namespace Minty;

void Minty::Application::quit()
{
	// stop running
	m_running = false;
}

void Minty::Application::step(Stopwatch& totalWatch, Stopwatch& elapsedWatch)
{
	// finalize managers
	m_context->finalize();

	// render managers
	m_context->render();

	// process events
	m_context->process_events();

	// update Time object
	Time time(totalWatch.get_elapsed_s(), elapsedWatch.get_elapsed_s());
	elapsedWatch.reset();

	// update managers
	m_context->update(time);
}

void Minty::Application::run()
{
	// keep track of time passed
	Stopwatch totalWatch = Stopwatch::start_new();
	Stopwatch elapsedWatch = Stopwatch::start_new();

	// run the application loop
	Window& window = m_context->get_window();
	while (window.is_open())
	{
		step(totalWatch, elapsedWatch);
	}

	// sync operations before moving on (threads, rendering, etc.)
	m_context->sync();
}

Owner<Application> Minty::Application::open(Path const& path)
{
	ApplicationBuilder builder{};
	builder.context = Context::open(path);
	MINTY_ASSERT(builder.context, F("Failed to open context from path: {}", path));
	return create(builder);
}

Owner<Application> Minty::Application::create(ApplicationBuilder const& builder)
{
	return Owner<Application>(builder);
}