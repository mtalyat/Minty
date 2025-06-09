#pragma once
#include "Minty/Manager/Manager.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Format.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Dictionary.h"
#include "Minty/Data/Pointer.h"
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
		MemoryStackBuilder temporary = {};

		/// <summary>
		/// The MemoryStacks for tasks (multiple frames) memory.
		/// </summary>
		MemoryStackBuilder task = {};

		/// <summary>
		/// The number of task MemoryStacks to create.
		/// </summary>
		Size taskCount = 0;

		/// <summary>
		/// The MemoryPools for persistent memory.
		/// </summary>
		Vector<MemoryPoolBuilder> persistents;
	};

	/// <summary>
	/// Handles allocation and deallocation of memory.
	/// </summary>
	class MemoryManager
		: public Manager
	{
#pragma region Variables

	private:
		// temporary, one frame only
		MemoryStack m_temporary;
		// task, variable number of frames
		Vector<MemoryStack> m_tasks;
		// the index of the current task
		Size m_taskIndex;
		// persistent: 64b, 256b, 1kb, 4kb, 16kb, 64kb, 256kb, 1mb, etc.
		Vector<MemoryPool> m_persistents;
		// ordered list of persistent sizes and indices to the pools
		Dictionary<Size, Size> m_persistentSizes;

		// number of bytes allocated using the MemoryManager
		Size m_staticSize;
		// number of bytes allocated using new instead of the MemoryManager
		Size m_dynamicSize;

#pragma endregion

#pragma region Constructors

	public:
		MemoryManager(MemoryManagerBuilder const& builder);

		MemoryManager(MemoryManager const& other) = delete;

		MemoryManager(MemoryManager&& other) noexcept
			: Manager()
			, m_temporary(std::move(other.m_temporary))
			, m_tasks(std::move(other.m_tasks))
			, m_taskIndex(std::move(other.m_taskIndex))
			, m_persistents(std::move(other.m_persistents))
			, m_persistentSizes(std::move(other.m_persistentSizes))
			, m_staticSize(std::move(other.m_staticSize))
			, m_dynamicSize(std::move(other.m_dynamicSize))
		{
		}

		~MemoryManager()
		{
			MINTY_ASSERT_ERROR(!is_initialized(), "MemoryManager is not disposed before destruction.");
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
				m_tasks = std::move(other.m_tasks);
				m_persistents = std::move(other.m_persistents);
				m_taskIndex = std::move(other.m_taskIndex);
				m_staticSize = std::move(other.m_staticSize);
				m_dynamicSize = std::move(other.m_dynamicSize);
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

	private:
		// gets the index to the persistent memory pool to use, given the size in bytes
		Size get_persistent_index(Size const size) const;

	public:
		/// <summary>
		/// Shuts down this MemoryManager.
		/// </summary>
		void dispose() override;

		/// <summary>
		/// Called once a frame.
		/// </summary>
		void update(Time const& time) override;

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

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new MemoryManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A MemoryManager Owner.</returns>
		static Owner<MemoryManager> create(MemoryManagerBuilder const& builder = {});

		/// <summary>
		/// Gets the active Context's MemoryManager.
		/// </summary>
		/// <returns>The MemoryManager.</returns>
		static MemoryManager& get_singleton();

#pragma endregion
	};
}