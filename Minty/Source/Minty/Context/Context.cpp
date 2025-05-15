#include "pch.h"
#include "Context.h"
#include "Minty/System/RenderSystem.h"

using namespace Minty;

Context* Context::s_instance = nullptr;

/// <summary>
/// Creates a new Context using the given ContextBuilder.
/// </summary>
/// <param name="builder">The input arguments.</param>
Minty::Context::Context(ContextBuilder const& builder)
	: mp_dualBuffer(nullptr)
	, m_memoryManager(nullptr)
	, m_jobManager(nullptr)
	, m_assetManager(nullptr)
	, m_renderManager(nullptr)
	, m_sceneManager(nullptr)
	, m_managers()
	, m_registeredSystems()
	, m_registeredComponents()
{
	MINTY_ASSERT(!s_instance, "Context singleton already exists.");
	s_instance = this;
	
	// initialize dual buffering if a debug log path was given
	if (!builder.debugLogPath.is_empty())
	{
		mp_dualBuffer = new DualBuffer(std::cout, builder.debugLogPath);
	}

	// create managers
	m_memoryManager = MemoryManager::create(builder.memoryManagerBuilder);
	m_jobManager = JobManager::create(builder.jobManagerBuilder);
	m_assetManager = AssetManager::create(builder.assetManagerBuilder);
	m_renderManager = RenderManager::create(builder.renderManagerBuilder);
	m_sceneManager = SceneManager::create(builder.sceneManagerBuilder);
	m_managers.add(m_memoryManager.get());
	m_managers.add(m_jobManager.get());
	m_managers.add(m_renderManager.get());
	m_managers.add(m_assetManager.get());
	m_managers.add(m_sceneManager.get());

	// initialize managers
	initialize();
}

Minty::Context::~Context()
{
	// sync managers
	sync();

	// dispose managers
	dispose();

	// clean up
	delete mp_dualBuffer;
	m_memoryManager.release();
	m_jobManager.release();
	m_assetManager.release();
	m_renderManager.release();
	m_sceneManager.release();
	m_managers.clear();

	s_instance = nullptr;
}

void Minty::Context::initialize()
{
	// initialize the managers
	for (Manager* manager : m_managers)
	{
		manager->initialize();
	}

	// register systems
	register_system<RenderSystem>("Render");

	// register components
	
}

void Minty::Context::dispose()
{
	// dispose managers
	for (auto it = m_managers.rbegin(); it != m_managers.rend(); ++it)
	{
		(*it)->dispose();
	}
	m_managers.clear();

	// unregister systems
	m_registeredSystems.clear();
}

void Minty::Context::update(Time const& time)
{
	// update managers
	for (Manager* manager : m_managers)
	{
		manager->update(time);
	}
}

void Minty::Context::finalize()
{
	// finalize managers
	for (Manager* manager : m_managers)
	{
		manager->finalize();
	}
}

void Minty::Context::render()
{
	// render managers
	for (Manager* manager : m_managers)
	{
		manager->render();
	}
}

void Minty::Context::sync()
{
	// sync managers
	for (Manager* manager : m_managers)
	{
		manager->sync();
	}
}
