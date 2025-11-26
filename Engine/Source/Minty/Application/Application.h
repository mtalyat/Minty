#pragma once
#include "Minty/Context/Context.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Time/TimeManagerInfo.h"

namespace Minty
{
	class Stopwatch;
	class TimeManager;

	/// <summary>
	/// The arguments for creating an Application.
	/// </summary>
	struct ApplicationInfo
	{
		/// <summary>
		/// The Context to use.
		/// </summary>
		Owner<Context> context = nullptr;

		/// <summary>
		/// The arguments for the application's TimeManager.
		/// </summary>
		TimeManagerInfo timeManagerInfo = {};
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
		/// Creates a new Application using the given ApplicationInfo.
		/// </summary>
		/// <param name="info">The arguments.</param>
		Application(ApplicationInfo const& info);

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
		void step();
		
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
		/// Creates a new Application using the given ApplicationInfo.
		/// </summary>
		/// <param name="info">The arguments.</param>
		/// <returns>An Application Owner.</returns>
		static Owner<Application> create(ApplicationInfo const& info = {});

		/// <summary>
		/// Gets the current instance of the Application.
		/// </summary>
		/// <returns>The current instance of the Application.</returns>
		static Application& get_singleton()
		{
			MINTY_ASSERT(s_instance, ErrorCode::Singleton_DoesNotExist);
			return *s_instance;
		}

#pragma endregion
	};
}