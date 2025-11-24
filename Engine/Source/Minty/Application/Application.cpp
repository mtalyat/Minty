#include "pch.h"
#include "Application.h"
#include "Minty/Time/Stopwatch.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Time/TimeManager.h"

using namespace Minty;

Application* Minty::Application::s_instance = nullptr;

/// <summary>
/// Creates a new Application using the given ApplicationInfo.
/// </summary>
/// <param name="info">The arguments.</param>
inline Minty::Application::Application(ApplicationInfo const& info)
	: m_context(info.context)
	, mp_timeManager(nullptr)
	, m_running(false)
{
	MINTY_ASSERT(!s_instance, "Application singleton already exists.");
	MINTY_ASSERT(m_context != nullptr, "Context is null.");

	s_instance = this;
	mp_timeManager = new TimeManager(info.timeManagerInfo);
}

Minty::Application::~Application()
{
	delete mp_timeManager;

	MINTY_ASSERT_ERROR(s_instance == this, "Application singleton is not this instance.");
	s_instance = nullptr;
}

void Minty::Application::quit()
{
	// stop running
	m_running = false;
}

void Minty::Application::step(TimeManager const& timeManager)
{
	MINTY_TRACE_SCOPE();

	// finalize managers
	m_context->finalize();

	// render managers
	m_context->render();

	// process events
	m_context->process_events();

	// update managers
	Time const time = timeManager.get_frame_time();
	m_context->frame_update(time);

	Time const fixedTime = timeManager.get_fixed_time();
	m_context->fixed_update(fixedTime);
}

void Minty::Application::run()
{
	// initialize
	m_context->initialize();

	// keep track of time passed
	Stopwatch totalWatch = Stopwatch::start_new();
	Stopwatch elapsedWatch = Stopwatch::start_new();
	TimeManagerInfo tmInfo;
	TimeManager timeManager(tmInfo);

	// get the window and start running
	Window& window = m_context->get_window();
	m_running = true;

	// run the application loop
	while (m_running && window.is_open())
	{
		step(timeManager);
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
	ApplicationInfo info{};
	info.context = Context::open(path);
	MINTY_ASSERT(info.context, F("Failed to open context from path: {}", path));
	return create(info);
}

Owner<Application> Minty::Application::create(ApplicationInfo const& info)
{
	return Owner<Application>(info);
}