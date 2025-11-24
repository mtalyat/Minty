#pragma once
#include "Minty/Context/Context.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Time/TimeManagerBuilder.h"

namespace Minty
{
	class Stopwatch;
	class TimeManager;

	/// <summary>
	/// The arguments for creating an Application.
	/// </summary>
	struct ApplicationBuilder
	{
		/// <summary>
		/// The Context to use.
		/// </summary>
		Owner<Context> context = nullptr;

		/// <summary>
		/// The arguments for the application's TimeManager.
		/// </summary>
		TimeManagerBuilder timeManagerBuilder = {};
	};

	/// <summary>
	/// Handles the update loop of an application.
	/// </summary>
	class Application
	{
#pragma region Variables

	private:
		Owner<Context> m_context;
		TimeManager* mp_timeManager;
		Bool m_running;
		static Application* s_instance;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Application using the given ApplicationBuilder.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Application(ApplicationBuilder const& builder);

		~Application();

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
		/// Performs one step in the Application's update loop.
		/// </summary>
		/// <param name="timeManager">The TimeManager to use for this step.</param>
		void step(TimeManager const& timeManager);
		
		/// <summary>
		/// Runs the Application.
		/// </summary>
		void run();

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Application using the configuration file at the given path.
		/// </summary>
		/// <param name="path">The path to the configuration file.</param>
		/// <returns>An Application Owner.</returns>
		static Owner<Application> open(Path const& path);

		/// <summary>
		/// Creates a new Application using the given ApplicationBuilder.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>An Application Owner.</returns>
		static Owner<Application> create(ApplicationBuilder const& builder = {});

		/// <summary>
		/// Gets the current instance of the Application.
		/// </summary>
		/// <returns>The current instance of the Application.</returns>
		static Application& get_singleton()
		{
			MINTY_ASSERT(s_instance, "Application singleton is null.");
			return *s_instance;
		}

#pragma endregion
	};
}