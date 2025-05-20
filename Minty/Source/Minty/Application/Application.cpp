#include "pch.h"
#include "Application.h"
#include "Minty/Time/Stopwatch.h"

using namespace Minty;

void Minty::Application::quit()
{
	// stop running
	m_running = false;
}

void Minty::Application::run()
{
	// keep track of time passed
	Time time{};
	Stopwatch totalWatch = Stopwatch::start_new();
	Stopwatch elapsedWatch = Stopwatch::start_new();

	// run the application loop
	m_running = true;
	while (m_running)
	{
		// update Time object
		time.update(totalWatch.get_elapsed_s(), elapsedWatch.get_elapsed_s());

		// reset elapsed watch
		elapsedWatch.reset();

		// update managers
		m_context->update(time);

		// finalize (late update) managers
		m_context->finalize();

		// render managers
		m_context->render();
	}

	// sync operations before moving on (threads, rendering, etc.)
	m_context->sync();
}

Owner<Application> Minty::Application::create(ApplicationBuilder const& builder)
{
	return Owner<Application>(builder);
}