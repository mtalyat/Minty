#include "pch.h"
#include "Application.h"
#include "Minty/Time/Stopwatch.h"
#include "Minty/Debug/Trace.h"

using namespace Minty;

Application* Minty::Application::s_instance = nullptr;

void Minty::Application::quit()
{
	// stop running
	m_running = false;
}

void Minty::Application::step(Stopwatch& totalWatch, Stopwatch& elapsedWatch)
{
	MINTY_TRACE_SCOPE();

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
	// initialize
	m_context->initialize();

	// keep track of time passed
	Stopwatch totalWatch = Stopwatch::start_new();
	Stopwatch elapsedWatch = Stopwatch::start_new();

	// get the window and start running
	Window& window = m_context->get_window();
	m_running = true;

	// run the application loop
	while (m_running && window.is_open())
	{
		step(totalWatch, elapsedWatch);
	}

	// if window is still open, close it
	if (window.is_open())
	{
		window.close();
	}
	m_running = false;

	// sync operations before moving on (threads, rendering, etc.)
	m_context->sync();

	// dispose the context
	m_context->dispose();
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