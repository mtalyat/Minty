#include "pch.h"
#include "Base.h"
#include "Minty/Context/Context.h"

using namespace Minty;

void* Minty::allocate(Size const size, Allocator const allocator)
{
	if (allocator == Allocator::Default)
	{
		return malloc(size);
	}

	// using application memory manager
	Context& context = Context::get_singleton();
	MemoryManager& memoryManager = context.get_memory_manager();
	return memoryManager.allocate(size, allocator);
}

void Minty::deallocate(void* const ptr, Size const size, Allocator const allocator)
{
	if (allocator == Allocator::Default)
	{
		free(ptr);
		return;
	}

	// using application memory manager
	Context& context = Context::get_singleton();
	MemoryManager& memoryManager = context.get_memory_manager();
	memoryManager.deallocate(ptr, size, allocator);
}
