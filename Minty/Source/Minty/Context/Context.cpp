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
{
	MINTY_ASSERT(!s_instance, "Context instance already exists.");
	s_instance = this;

	if (!builder.debugLogPath.is_empty())
	{
		mp_dualBuffer = new DualBuffer(std::cout, builder.debugLogPath);
	}
}
