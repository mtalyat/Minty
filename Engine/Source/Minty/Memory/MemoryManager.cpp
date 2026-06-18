#include "pch.h"
#include "MemoryManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Core/Format.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Memory/MemoryManagerInfo.h"
#include "Minty/Memory/MemoryStack.h"
#include "Minty/Memory/MemoryPool.h"
#include "Minty/Memory/MemoryPoolInfo.h"
#include "Minty/Memory/FrameAllocator.h"
#include "Minty/Memory/PersistentAllocator.h"
#ifdef MINTY_DEBUG
#include <unordered_map>
#endif // MINTY_DEBUG

using namespace Minty;

Minty::MemoryManager::MemoryManager(MemoryManagerInfo const &info)
	: Manager()
{
	MINTY_ASSERT(info.persistentPoolInfos == nullptr || info.persistentPoolInfoCount > 0, ErrorCode::Argument_ExpectedAboveZero);
	MINTY_ASSERT(info.persistentPoolInfos == nullptr || info.persistentPoolInfoCount <= MAX_PERSISTENT_POOLS, ErrorCode::Argument_OutOfRange);

	if (info.frameStackInfo != nullptr)
	{
		FrameAllocator::initialize(*info.frameStackInfo);
	}

	if (info.persistentPoolInfos != nullptr && info.persistentPoolInfoCount > 0)
	{
		PersistentAllocator::initialize(info.persistentPoolInfos, info.persistentPoolInfoCount);
	}
}

Minty::MemoryManager::~MemoryManager()
{
	PersistentAllocator::dispose();
	FrameAllocator::dispose();
}

void Minty::MemoryManager::frame_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	FrameAllocator::reset();
}

Unique<MemoryManager> Minty::MemoryManager::create(MemoryManagerInfo const &info)
{
	return Unique<MemoryManager>::create(info);
}

Unique<MemoryManager> Minty::MemoryManager::create()
{
	MemoryManagerInfo info{};
	return create(info);
}

Unique<MemoryManager> const &Minty::MemoryManager::get_instance()
{
	return Application::get_singleton().get_memory_manager();
}

MemoryManager &Minty::MemoryManager::get_singleton()
{
	Unique<MemoryManager> const &instance = Application::get_singleton().get_memory_manager();
	MINTY_ASSERT(instance, ErrorCode::Application_MemoryManagerNotInitialized);
	return *instance;
}
