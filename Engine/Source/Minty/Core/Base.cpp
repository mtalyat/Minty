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

void* Minty::copy(void const* const src, Size const size, Allocator const allocator)
{
	// allocate new memory
	void* const dst = allocate(size, allocator);

	// copy data
	if (src != nullptr && dst != nullptr)
	{
		memcpy(dst, src, size);
	}

	return dst;
}

void Minty::deallocate(void* const ptr, Size const size, Allocator const allocator)
{
	// ignore if nullptr
	if (ptr == nullptr)
	{
		return;
	}

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
