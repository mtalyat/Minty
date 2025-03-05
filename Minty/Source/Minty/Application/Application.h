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
			MINTY_ASSERT(!s_instance, "Application instance already exists.");
			s_instance = this;
		}

		constexpr ~Application()
		{
			s_instance = nullptr;
		}

#pragma endregion
		
#pragma region Operators

	public:

#pragma endregion

#pragma region Get Set

	public:
		static Application& get_instance()
		{
			MINTY_ASSERT(s_instance, "Application instance is null.");
			return *s_instance;
		}

#pragma endregion

#pragma region Methods

	public:


#pragma endregion
	};
}