#pragma once
#include "Minty/Manager/Manager.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Memory/AllocatorType.h"

namespace Minty
{
	struct MemoryManagerInfo;
	class MemoryPool;
	class MemoryStack;

	/**
	 * @class MemoryManager
	 * @brief Manages memory allocation and deallocation using various allocators.
	 */
	class MemoryManager
		: public Manager
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a MemoryManager using the given information.
		 * @param info The information for creating the MemoryManager.
		 */
		MemoryManager(MemoryManagerInfo const& info);

		~MemoryManager() override;

		MemoryManager(MemoryManager const& other) = delete;
		MemoryManager(MemoryManager&& other) = delete;

#pragma endregion

#pragma region Operators

	public:
		MemoryManager& operator=(MemoryManager const& other) = delete;
		MemoryManager& operator=(MemoryManager&& other) = delete;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called once a frame. Advances to the next task memory stack, then frees temporary and task memory.
		 * @param time The time information for the frame.
		 */
		void frame_update(Timestep const& time) override;

		/**
		 * @brief Allocates memory using the given allocator.
		 * @param allocator The allocator to use.
		 * @param size The size of memory to allocate in bytes.
		 * @return A pointer to the allocated memory.
		 */
		Any allocate(AllocatorType const allocator, Size const size);
		
		/**
		 * @brief Allocates memory using the default system allocator.
		 * @param size The size of memory to allocate in bytes.
		 * @return A pointer to the allocated memory.
		 */
		Any allocate_default(Size const size);

		/**
		 * @brief Allocates memory using the temporary memory stack.
		 * @param size The size of memory to allocate in bytes.
		 * @return A pointer to the allocated memory.
		 */
		Any allocate_frame(Size const size);

		/**
		 * @brief Allocates memory using the task memory stack.
		 * @param size The size of memory to allocate in bytes.
		 * @return A pointer to the allocated memory.
		 */
		Any allocate_task(Size const size);

		/**
		 * @brief Allocates memory using the persistent memory pools.
		 * @param size The size of memory to allocate in bytes.
		 * @return A pointer to the allocated memory.
		 */
		Any allocate_persistent(Size const size);

		/**
		 * @brief Deallocates memory using the given allocator.
		 * @param allocator The allocator to use.
		 * @param ptr The pointer to deallocate.
		 */
		void deallocate(AllocatorType const allocator, Any const ptr);

		/**
		 * @brief Deallocates memory using the default system allocator.
		 * @param ptr The pointer to deallocate.
		 */
		void deallocate_default(Any const ptr);

		/**
		 * @brief Deallocates memory using the temporary memory stack.
		 * @param ptr The pointer to deallocate.
		 */
		void deallocate_frame(Any const ptr);

		/**
		 * @brief Deallocates memory using the task memory stack.
		 * @param ptr The pointer to deallocate.
		 */
		void deallocate_task(Any const ptr);

		/**
		 * @brief Deallocates memory using the persistent memory pools.
		 * @param ptr The pointer to deallocate.
		 */
		void deallocate_persistent(Any const ptr);

		/**
		 * @brief Creates the singleton MemoryManager.
		 * @param info The arguments for creating the MemoryManager.
		 */
		static Unique<MemoryManager> create(MemoryManagerInfo const& info);

		/**
		 * @brief Creates a new MemoryManager with default settings.
		 * @return A MemoryManager Owner.
		 */
		static Unique<MemoryManager> create();

		/**
		 * @brief Gets the singleton MemoryManager.
		 * @return The MemoryManager singleton.
		 */
		static Unique<MemoryManager> const& get_instance();

		/**
		 * @brief Gets the singleton MemoryManager.
		 * @return A reference to the MemoryManager.
		 */
		static MemoryManager& get_singleton();

	private:
		// gets the index to the persistent memory pool to use, given the size in bytes
		Size get_persistent_index(Size const size) const;

#pragma endregion

#pragma region Variables

	private:
		Bool m_initialized;
		Bool m_frameInitialized;
		Bool m_taskInitialized;
		Bool m_persistentInitialized;
		Size m_persistentSizes[MAX_PERSISTENT_POOLS];
		Size m_persistentMap[MAX_PERSISTENT_POOL_SIZE + 1];

#pragma endregion
	};
}