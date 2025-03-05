#include "pch.h"
#include "Base.h"
#include "Minty/Application/Application.h"

using namespace Minty;

void* Minty::allocate(Size const size, Allocator const allocator)
{
	if (allocator == Allocator::Default)
	{
		return malloc(size);
	}

	// using application memory manager
	Application& app = Application::get_instance();
	MemoryManager& memoryManager = app.get_memory_manager();
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
	Application& app = Application::get_instance();
	MemoryManager& memoryManager = app.get_memory_manager();
	memoryManager.deallocate(ptr, size, allocator);
}
