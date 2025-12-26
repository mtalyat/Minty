#pragma once
#include "Minty/Manager/Manager.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"

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
		void frame_update(Timestep const time) override;

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

#pragma endregion
	};
}