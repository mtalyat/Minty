#pragma once
#include "Minty/Manager/Manager.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Memory/Allocator.h"

namespace Minty
{
	struct MemoryManagerInfo;
	class MemoryPool;
	class MemoryStack;

	/// <summary>
	/// Handles allocation and deallocation of memory.
	/// </summary>
	class MemoryManager
		: public Manager
	{
#pragma region Constructors

	public:
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

#pragma region Get Set

	public:
#ifdef MINTY_DEBUG
		/**
		 * @brief Gets the size in bytes that has been allocated statically.
		 * @return The static allocated size in bytes.
		 */
		inline Size get_static_size_DEBUG() const { return m_staticSize_DEBUG; }

		/**
		 * @brief Gets the size in bytes that has been allocated dynamically.
		 * @return The dynamic allocated size in bytes.
		 */
		inline Size get_dynamic_size_DEBUG() const { return m_dynamicSize_DEBUG; }
#endif // MINTY_DEBUG

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
		Any allocate(Allocator const allocator, Size const size);
		
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
		Any allocate_temporary(Size const size);

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
		void deallocate(Allocator const allocator, Any const ptr);

		/**
		 * @brief Deallocates memory using the default system allocator.
		 * @param ptr The pointer to deallocate.
		 */
		void deallocate_default(Any const ptr);

		/**
		 * @brief Deallocates memory using the temporary memory stack.
		 * @param ptr The pointer to deallocate.
		 */
		void deallocate_temporary(Any const ptr);

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
		static Owner<MemoryManager> create(MemoryManagerInfo const& info);

		/**
		 * @brief Gets the singleton MemoryManager.
		 * @return The MemoryManager singleton.
		 */
		static MemoryManager& get_singleton();

	private:
		// gets the index to the persistent memory pool to use, given the size in bytes
		Size get_persistent_index(Size const size) const;

#pragma endregion

#pragma region Variables

	private:
		Bool m_initialized;
		MemoryStack* mp_temporaryStack;
		MemoryStack* mp_taskStacks;
		Size m_taskStackCount;
		Size m_taskIndex;
		MemoryPool* mp_persistentPools;
		Size m_persistentPoolCount;
		Size *mp_persistentPoolSizeMap;
#ifdef MINTY_DEBUG
		Size m_staticSize_DEBUG;
		Size m_dynamicSize_DEBUG;
#endif // MINTY_DEBUG

#pragma endregion
	};
}