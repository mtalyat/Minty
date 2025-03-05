#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"
#include "Minty/Memory/Allocator.h"
#include "Minty/Memory/MemoryPool.h"
#include "Minty/Memory/MemoryStack.h"

namespace Minty
{
	/// <summary>
	/// Arguments for creating a MemoryManager.
	/// </summary>
	struct MemoryManagerBuilder
	{
		/// <summary>
		/// The MemoryStack for temporary (one frame) memory.
		/// </summary>
		MemoryStackBuilder temporary = { MB * 4 };

		/// <summary>
		/// The MemoryStacks for tasks (multiple frames) memory.
		/// </summary>
		MemoryStackBuilder task = { MB * 4 };
		
		/// <summary>
		/// The MemoryPools for persistent memory.
		/// </summary>
		MemoryPoolBuilder persistent[8] = 
		{
			{64, MB / 64}, {256, MB / 256}, {KB, MB / KB}, {4 * KB, MB / (4 * KB)}, {16 * KB, MB / (16 * KB)}, {64 * KB, MB / (64 * KB)}, {256 * KB, MB / (256 * KB)}, {MB, 16}
		};
	};

	/// <summary>
	/// Handles allocation and deallocation of memory.
	/// </summary>
	class MemoryManager
	{
#pragma region Variables

	public:
		static constexpr Size TASK_MEMORY_COUNT = 4;
		static constexpr Size PERSISTENT_MEMORY_COUNT = 8;

	private:
		// temporary, one frame only
		MemoryStack m_temporary;
		// task, 4 frames or less
		MemoryStack m_task[TASK_MEMORY_COUNT];
		// the index of the current task
		Size m_taskIndex;
		// persistent: 64b, 256b, 1kb, 4kb, 16kb, 64kb, 256kb, 1mb
		MemoryPool m_persistent[PERSISTENT_MEMORY_COUNT];

		// number of bytes allocated using the MemoryManager
		Size m_staticSize;
		// number of bytes allocated using new instead of the MemoryManager
		Size m_dynamicSize;

#pragma endregion

#pragma region Constructors

	public:
		MemoryManager(MemoryManagerBuilder const& builder)
			: m_temporary(builder.temporary)
			, m_task{ MemoryStack(builder.task), MemoryStack(builder.task), MemoryStack(builder.task), MemoryStack(builder.task) }
			, m_taskIndex(0)
			, m_persistent{ MemoryPool(builder.persistent[0]), MemoryPool(builder.persistent[1]), MemoryPool(builder.persistent[2]), MemoryPool(builder.persistent[3]), MemoryPool(builder.persistent[4]), MemoryPool(builder.persistent[5]), MemoryPool(builder.persistent[6]), MemoryPool(builder.persistent[7])}
			, m_staticSize(0)
			, m_dynamicSize(0)
		{}

		MemoryManager(MemoryManager const& other) = delete;

		MemoryManager(MemoryManager&& other) noexcept
			: m_temporary(std::move(other.m_temporary))
			, m_task{ std::move(other.m_task[0]), std::move(other.m_task[1]), std::move(other.m_task[2]), std::move(other.m_task[3]) }
			, m_taskIndex(other.m_taskIndex)
			, m_persistent{ std::move(other.m_persistent[0]), std::move(other.m_persistent[1]), std::move(other.m_persistent[2]), std::move(other.m_persistent[3]), std::move(other.m_persistent[4]), std::move(other.m_persistent[5]), std::move(other.m_persistent[6]), std::move(other.m_persistent[7] )}
			, m_staticSize(other.m_staticSize)
			, m_dynamicSize(other.m_dynamicSize)
		{
			other.m_taskIndex = 0;
			other.m_staticSize = 0;
			other.m_dynamicSize = 0;
		}

		~MemoryManager()
		{
			// ensure nothing left
			MINTY_ASSERT(m_dynamicSize == 0, F("MemoryManager has dynamic memory leaks. {} bytes of data leaked.", m_dynamicSize));
		}

#pragma endregion

#pragma region Operators

	public:
		MemoryManager& operator=(MemoryManager const& other) = delete;

		MemoryManager& operator=(MemoryManager&& other) noexcept
		{
			if (this != &other)
			{
				m_temporary = std::move(other.m_temporary);
				for (Size i = 0; i < TASK_MEMORY_COUNT; ++i)
				{
					m_task[i] = std::move(other.m_task[i]);
				}
				for (Size i = 0; i < PERSISTENT_MEMORY_COUNT; i++)
				{
					m_persistent[i] = std::move(other.m_persistent[i]);
				}
				m_staticSize = other.m_staticSize;
				m_dynamicSize = other.m_dynamicSize;
				other.m_staticSize = 0;
				other.m_dynamicSize = 0;
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the total number of bytes allocated using the MemoryManager.
		/// </summary>
		/// <returns></returns>
		Size get_size() const { return m_staticSize + m_dynamicSize; }
		
		/// <summary>
		/// Gets the size in bytes that has been allocated using the pre-allocated data in the MemoryManager.
		/// </summary>
		/// <returns></returns>
		Size get_static_size() const { return m_staticSize; }

		/// <summary>
		/// Gets the size in bytes that has been allocated dynamically.
		/// </summary>
		/// <returns></returns>
		Size get_dynamic_size() const { return m_dynamicSize; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called once a frame.
		/// </summary>
		void update();

		/// <summary>
		/// Allocates the given number of bytes using the appropriate allocation method.
		/// </summary>
		/// <param name="size">The number of bytes to allocate.</param>
		/// <param name="allocator">The allocation method to use.</param>
		/// <returns>The pointer to the newly allocated data.</returns>
		void* allocate(Size const size, Allocator const allocator);

		/// <summary>
		/// Deallocates the given number of bytes using the appropriate deallocation method.
		/// </summary>
		/// <param name="ptr">The pointer to the allocated data.</param>
		/// <param name="size">The number of bytes that have been allocated.</param>
		/// <param name="allocator">The allocation method used.</param>
		void deallocate(void* const ptr, Size const size, Allocator const allocator);

	private:
		// gets the index to the persistent memory pool to use, given the size in bytes
		Size get_persistent_index(Size const size) const;

#pragma endregion
	};
}