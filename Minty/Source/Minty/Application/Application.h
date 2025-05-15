#pragma once
#include "Minty/Context/Context.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Debug/Debug.h"

namespace Minty
{
	/// <summary>
	/// The arguments for creating an Application.
	/// </summary>
	struct ApplicationBuilder
	{
		Owner<Context> context;
	};

	/// <summary>
	/// Handles the update loop of an application.
	/// </summary>
	class Application
	{
#pragma region Variables

	private:
		Owner<Context> m_context;
		Bool m_running;

		static Application* s_instance;

#pragma endregion

#pragma region Constructors

	public:
		Application(ApplicationBuilder const& builder)
			: m_context(builder.context)
			, m_running(false)
		{
			MINTY_ASSERT(!s_instance, "Application singleton already exists.");
			s_instance = this;

			MINTY_ASSERT(m_context != nullptr, "Context is null.");
		}

		~Application()
		{
			s_instance = nullptr;
		}

		Application(Application const&) = delete;
		Application(Application&&) = delete;

#pragma endregion
		
#pragma region Operators

	public:
		Application& operator=(Application const&) = delete;
		Application& operator=(Application&&) = delete;

#pragma endregion

#pragma region Get Set

	public:
		Ref<Context> get_context() const
		{
			return m_context.create_ref();
		}

#pragma endregion

#pragma region Methods

	public:
		void quit()
		{
			m_running = false;
		}

		void run()
		{
			m_running = true;
			while (m_running)
			{
				break;
			}
		}

#pragma endregion

#pragma region Statics

	public:
		static Owner<Application> create(ApplicationBuilder const& builder = {});

		static Application& get_singleton();

#pragma endregion

	};
}