#include "pch.h"
#include "Context.h"

using namespace Minty;

Context* Context::s_instance = nullptr;

/// <summary>
/// Creates a new Context using the given ContextBuilder.
/// </summary>
/// <param name="builder">The input arguments.</param>
Minty::Context::Context(ContextBuilder const& builder)
	: mp_dualBuffer(nullptr)
	, m_memoryManager(MemoryManager::create(builder.memoryManagerBuilder))
	, m_jobManager(JobManager::create(builder.jobManagerBuilder))
	, m_assetManager(AssetManager::create(builder.assetManagerBuilder))
	, m_renderManager(RenderManager::create(builder.renderManagerBuilder))
{
	MINTY_ASSERT(!s_instance, "Context instance already exists.");
	s_instance = this;
	
	// initialize dual buffering if a debug log path was given
	if (!builder.debugLogPath.is_empty())
	{
		mp_dualBuffer = new DualBuffer(std::cout, builder.debugLogPath);
	}
}
