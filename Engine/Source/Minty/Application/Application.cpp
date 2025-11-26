#include "pch.h"
#include "Application.h"
#include "Minty/Time/Stopwatch.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Time/TimeManager.h"
#include "Minty/Time/Timestep.h"

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
	MINTY_ASSERT(!s_instance, ErrorCode::Singleton_AlreadyExists);
	MINTY_ASSERT(info.context != nullptr, ErrorCode::Argument_ExpectedNonNull);

	s_instance = this;
	mp_timeManager = new TimeManager(info.timeManagerInfo);
}

Minty::Application::~Application()
{
	delete mp_timeManager;

	MINTY_ASSERT(s_instance != nullptr, ErrorCode::Singleton_DoesNotExist);
	MINTY_ASSERT(s_instance == this, ErrorCode::Singleton_DifferentObject);
	s_instance = nullptr;
}

void Minty::Application::quit()
{
	// stop running
	m_running = false;
}

void Minty::Application::step()
{
	MINTY_TRACE_SCOPE();

	// finalize managers
	m_context->finalize();

	// render managers
	m_context->render();

	// process events
	m_context->process_events();

	// perform updates for frame and fixed updates
	Int const fixedUpdates = mp_timeManager->update();

	Timestep const time = mp_timeManager->get_frame_timestep();
	m_context->frame_update(time);

	for (Int i = 0; i < fixedUpdates; i++)
	{
		Timestep const fixedTime = mp_timeManager->get_fixed_timestep();
		m_context->fixed_update(fixedTime);
	}
}

void Minty::Application::run()
{
	// initialize
	m_context->initialize();

	// get the window and start running
	Window& window = m_context->get_window();

	mp_timeManager->start();

	// run the application loop
	m_running = true;
	while (m_running && window.is_open())
	{
		step();
	}
	m_running = false;

	mp_timeManager->stop();

	// if window is still open, close it
	if (window.is_open())
	{
		window.close();
	}

	// sync operations before moving on (threads, rendering, etc.)
	m_context->sync();

	// dispose the context
	m_context->dispose();
}

Owner<Application> Minty::Application::open(Path const& path)
{
	ApplicationInfo info{};
	info.context = Context::open(path);
	MINTY_ASSERT(info.context != nullptr, ErrorCode::File_NotFound, path);
	return create(info);
}

Owner<Application> Minty::Application::create(ApplicationInfo const& info)
{
	return Owner<Application>(info);
}