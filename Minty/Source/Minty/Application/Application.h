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
		/// <summary>
		/// The Context to use.
		/// </summary>
		Owner<Context> context = nullptr;
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

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Application using the given ApplicationBuilder.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Application(ApplicationBuilder const& builder)
			: m_context(builder.context)
			, m_running(false)
		{
			MINTY_ASSERT(m_context != nullptr, "Context is null.");
		}

		~Application()
		{
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
		/// <summary>
		/// Gets the Context this Application uses.
		/// </summary>
		/// <returns></returns>
		Ref<Context> get_context() const
		{
			return m_context.create_ref();
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Quits the Application.
		/// </summary>
		void quit();
		
		/// <summary>
		/// Runs the Application.
		/// </summary>
		void run();

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Application using the given ApplicationBuilder.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>An Application Owner.</returns>
		static Owner<Application> create(ApplicationBuilder const& builder = {});

#pragma endregion
	};
}