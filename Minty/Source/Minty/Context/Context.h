#pragma once
#include "Minty/Core/Macro.h"
#include "Minty/Memory/MemoryManager.h"
#include "Minty/Data/Path.h"
#include "Minty/Debug/DualBuffer.h"

namespace Minty
{
	/// <summary>
	/// Holds data to initialize a Context.
	/// </summary>
	struct ContextBuilder
	{
		Path debugLogPath = "";

		MemoryManagerBuilder memoryManagerBuilder = {};
	};

	/// <summary>
	/// A context for the Minty Engine. Required to use certain features of the library.
	/// </summary>
	class Context
	{
#pragma region Variables

	private:
		static Context* s_instance;

		DualBuffer* mp_dualBuffer;
		MemoryManager* mp_memoryManager;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Context using the given ContextBuilder.
		/// </summary>
		/// <param name="builder">The input arguments.</param>
		Context(ContextBuilder const& builder);

		Context(Context const& other) = delete;

		/// <summary>
		/// Moves the given Context.
		/// </summary>
		/// <param name="other">The Context to move.</param>
		Context(Context&& other) noexcept
			: mp_dualBuffer(other.mp_dualBuffer)
			, mp_memoryManager(other.mp_memoryManager)
		{
			other.mp_dualBuffer = nullptr;
			mp_memoryManager = nullptr;
		}

		~Context()
		{
			delete mp_dualBuffer;
			delete mp_memoryManager;

			s_instance = nullptr;
		}

#pragma endregion

#pragma region Operators

	public:
		Context& operator=(Context const& other) = delete;

		Context& operator=(Context&& other) noexcept
		{
			if (this != &other)
			{
				mp_memoryManager = other.mp_memoryManager;
				other.mp_memoryManager = nullptr;
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the MemoryManager for this Context.
		/// </summary>
		/// <returns>The MemoryManager for this Context.</returns>
		MemoryManager& get_memory_manager() { return *mp_memoryManager; }

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Gets the current instance of the Context.
		/// </summary>
		/// <returns>The current instance of the Context.</returns>
		static Context& get_instance()
		{
			MINTY_ASSERT(s_instance, "Context instance is null.");
			return *s_instance;
		}

#pragma endregion

	};
}