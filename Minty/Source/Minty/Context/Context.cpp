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
	, mp_memoryManager(new MemoryManager(builder.memoryManagerBuilder))
	, mp_assetManager(new AssetManager(builder.assetManagerBuilder))
{
	MINTY_ASSERT(!s_instance, "Context instance already exists.");
	s_instance = this;
	
	// initialize dual buffering if a debug log path was given
	if (!builder.debugLogPath.is_empty())
	{
		mp_dualBuffer = new DualBuffer(std::cout, builder.debugLogPath);
	}
}
