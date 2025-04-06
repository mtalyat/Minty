#pragma once
#include "Minty/Memory/MemoryManager.h"

namespace Minty
{
	struct ApplicationBuilder
	{
		MemoryManagerBuilder memoryManagerBuilder;
	};

	class Application
	{
#pragma region Variables

	private:
		static Application* s_instance;

		MemoryManager m_memoryManager;

#pragma endregion

#pragma region Constructors

	public:
		Application(ApplicationBuilder const& builder)
			: m_memoryManager(builder.memoryManagerBuilder)
		{
			MINTY_ASSERT(!s_instance, "Application singleton already exists.");
			s_instance = this;
		}

		~Application()
		{
			s_instance = nullptr;
		}

#pragma endregion
		
#pragma region Operators

	public:

#pragma endregion

#pragma region Get Set

	public:
		MemoryManager& get_memory_manager() { return m_memoryManager; }

		static Application& instance()
		{
			MINTY_ASSERT(s_instance, "Application singleton is null.");
			return *s_instance;
		}

#pragma endregion

#pragma region Methods

	public:


#pragma endregion
	};
}