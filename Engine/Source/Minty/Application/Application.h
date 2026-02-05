#ifndef MINTY_APPLICATION_APPLICATION_H
#define MINTY_APPLICATION_APPLICATION_H

/**
 * @file Application.h
 * @brief Defines the Application class used for managing the application lifecycle.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Lookup.h"
#include "Minty/Debug/Assert.h"
#include "Minty/System/SystemData.h"
#include "Minty/Component/ComponentData.h"
#include "Minty/Time/Timestep.h"

namespace Minty
{
	struct ApplicationInfo;
	class Window;
	class MemoryManager;
	class JobManager;
	class AudioManager;
	class LayerManager;
	class PhysicsManager;
	class AssetManager;
	class InputManager;
	class RenderManager;
	class SceneManager;
	class TimeController;
	class Event;
	class Manager;
	class Path;

	/**
	 * @brief The main Application class that manages the application lifecycle.
	 */
	class Application
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Application using the given ApplicationInfo.
		 * @param info The arguments.
		 */
		Application(ApplicationInfo const &info);

		~Application();

		Application(Application const &) = delete;
		Application(Application &&) = delete;

#pragma endregion

#pragma region Operators

	public:
		Application &operator=(Application const &) = delete;
		Application &operator=(Application &&) = delete;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Checks if the Application is currently running.
		 * @return True if running, otherwise false.
		 */
		inline Bool is_running() const { return m_running; }

		/**
		 * @brief Gets the Window of the Application.
		 * @note This will be invalid if no Window was created using the ApplicationInfo.
		 * @return The Window.
		 */
		Shared<Window> const& get_window() const { return m_window; }

		/**
		 * @note This will be invalid if no MemoryManager was created using the ApplicationInfo.
		 * @brief Gets the MemoryManager of the Application.
		 * @return The MemoryManager.
		 */
		Unique<MemoryManager> const& get_memory_manager() const
		{
			return m_memoryManager;
		}

		/**
		 * @brief Gets the JobManager of the Application.
		 * @note This will be invalid if no JobManager was created using the ApplicationInfo.
		 * @return The JobManager.
		 */
		Unique<JobManager> const& get_job_manager() const
		{
			return m_jobManager;
		}

		/**
		 * @brief Gets the AudioManager of the Application.
		 * @note This will be invalid if no AudioManager was created using the ApplicationInfo.
		 * @return The AudioManager.
		 */
		Unique<AudioManager> const& get_audio_manager() const
		{
			return m_audioManager;
		}

		/**
		 * @brief Gets the LayerManager of the Application.
		 * @note This will be invalid if no LayerManager was created using the ApplicationInfo.
		 * @return The LayerManager.
		 */
		Unique<LayerManager> const& get_layer_manager() const
		{
			return m_layerManager;
		}

		/**
		 * @brief Gets the PhysicsManager of the Application.
		 * @note This will be invalid if no PhysicsManager was created using the ApplicationInfo.
		 * @return The PhysicsManager.
		 */
		Unique<PhysicsManager> const& get_physics_manager() const
		{
			return m_physicsManager;
		}

		/**
		 * @brief Gets the AssetManager of the Application.
		 * @note This will be invalid if no AssetManager was created using the ApplicationInfo.
		 * @return The AssetManager.
		 */
		Unique<AssetManager> const& get_asset_manager() const
		{
			return m_assetManager;
		}

		/**
		 * @brief Gets the InputManager of the Application.
		 * @note This will be invalid if no InputManager was created using the ApplicationInfo.
		 * @return The InputManager.
		 */
		Unique<InputManager> const& get_input_manager() const
		{
			return m_inputManager;
		}

		/**
		 * @brief Gets the RenderManager of the Application.
		 * @note This will be invalid if no RenderManager was created using the ApplicationInfo.
		 * @return The RenderManager.
		 */
		Unique<RenderManager> const& get_render_manager() const
		{
			return m_renderManager;
		}

		/**
		 * @brief Gets the SceneManager of the Application.
		 * @note This will be invalid if no SceneManager was created using the ApplicationInfo.
		 * @return The SceneManager.
		 */
		Unique<SceneManager> const& get_scene_manager() const
		{
			return m_sceneManager;
		}

		/**
		 * @brief Gets the TimeManager of the Application.
		 * @note This will be invalid if no TimeManager was created using the ApplicationInfo.
		 * @return The TimeManager.
		 */
		Unique<TimeController> const& get_time_controller() const
		{
			return m_timeController;
		}

		/**
		 * @brief Gets the current instance of the Application.
		 * @return The current instance of the Application.
		 */
		static Application &get_singleton()
		{
			MINTY_ASSERT(s_instance, ErrorCode::Singleton_DoesNotExist);
			return *s_instance;
		}

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Quits the Application.
		 */
		void quit();

		/**
		 * @brief Performs one step in the Application's update loop.
		 */
		void step();

		/**
		 * @brief Runs the Application.
		 */
		void run();

		/**
		 * @brief Creates a new Application using the configuration file at the given path.
		 * @param path The path to the configuration file.
		 * @return An Application Owner.
		 */
		static Unique<Application> open(Path const &path);

		/**
		 * @brief Creates a new Application using the given ApplicationInfo.
		 * @param info The arguments.
		 * @return An Application Owner.
		 */
		static Unique<Application> create(ApplicationInfo const &info);

		/**
		 * @brief Creates a new Application with default settings.
		 * @return An Application Owner.
		 */
		static Unique<Application> create();

	private:
		void finalize();
		
		void render();

		void process_events();

		void advance_memory();

		void sync();

		void frame_update(Timestep const time);

		void fixed_update(Timestep const time);

		void handle_event(Event &event);

		void register_components();

		void register_systems();

		void unregister_components();

		void unregister_systems();

#pragma endregion

#pragma region Variables

	private:
		Bool m_running;
		Shared<Window> m_window;
		Unique<MemoryManager> m_memoryManager;
		Unique<JobManager> m_jobManager;
		Unique<AudioManager> m_audioManager;
		Unique<LayerManager> m_layerManager;
		Unique<PhysicsManager> m_physicsManager;
		Unique<AssetManager> m_assetManager;
		Unique<InputManager> m_inputManager;
		Unique<RenderManager> m_renderManager;
		Unique<SceneManager> m_sceneManager;
		Unique<TimeController> m_timeController;
		Vector<Manager *> m_managers;

		static Application *s_instance;

#pragma endregion
	};
}

#endif // MINTY_APPLICATION_APPLICATION_H