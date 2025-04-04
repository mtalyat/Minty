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
	, m_memoryManager(builder.memoryManagerBuilder ? MemoryManager::create(*builder.memoryManagerBuilder) : nullptr)
	, m_jobManager(builder.jobManagerBuilder ? JobManager::create(*builder.jobManagerBuilder) : nullptr)
	, m_assetManager(builder.assetManagerBuilder ? AssetManager::create(*builder.assetManagerBuilder) : nullptr)
	, m_renderManager(builder.renderManagerBuilder ? RenderManager::create(*builder.renderManagerBuilder) : nullptr)
{
	MINTY_ASSERT(!s_instance, "Context get_singleton already exists.");
	s_instance = this;
	
	// initialize dual buffering if a debug log path was given
	if (!builder.debugLogPath.is_empty())
	{
		mp_dualBuffer = new DualBuffer(std::cout, builder.debugLogPath);
	}
}
