#ifndef MINTY_APPLICATION_APPLICATION_H
#define MINTY_APPLICATION_APPLICATION_H

/**
 * @file Application.h
 * @brief Defines the Application class used for managing the application lifecycle.
 * @author Mitchell Talyat
 */

#include "Minty/Context/Context.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Lookup.h"
#include "Minty/Data/Vector.h"

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
	class TimeManager;

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
		Window& get_window() const;

		/**
		 * @note This will be invalid if no MemoryManager was created using the ApplicationInfo.
		 * @brief Gets the MemoryManager of the Application.
		 * @return The MemoryManager.
		 */
		MemoryManager& get_memory_manager() const;

		/**
		 * @brief Gets the JobManager of the Application.
		 * @note This will be invalid if no JobManager was created using the ApplicationInfo.
		 * @return The JobManager.
		 */
		JobManager& get_job_manager() const;

		/**
		 * @brief Gets the AudioManager of the Application.
		 * @note This will be invalid if no AudioManager was created using the ApplicationInfo.
		 * @return The AudioManager.
		 */
		AudioManager& get_audio_manager() const;

		/**
		 * @brief Gets the LayerManager of the Application.
		 * @note This will be invalid if no LayerManager was created using the ApplicationInfo.
		 * @return The LayerManager.
		 */
		LayerManager& get_layer_manager() const;

		/**
		 * @brief Gets the PhysicsManager of the Application.
		 * @note This will be invalid if no PhysicsManager was created using the ApplicationInfo.
		 * @return The PhysicsManager.
		 */
		PhysicsManager& get_physics_manager() const;

		/**
		 * @brief Gets the AssetManager of the Application.
		 * @note This will be invalid if no AssetManager was created using the ApplicationInfo.
		 * @return The AssetManager.
		 */
		AssetManager& get_asset_manager() const;

		/**
		 * @brief Gets the InputManager of the Application.
		 * @note This will be invalid if no InputManager was created using the ApplicationInfo.
		 * @return The InputManager.
		 */
		InputManager& get_input_manager() const;

		/**
		 * @brief Gets the RenderManager of the Application.
		 * @note This will be invalid if no RenderManager was created using the ApplicationInfo.
		 * @return The RenderManager.
		 */
		RenderManager& get_render_manager() const;

		/**
		 * @brief Gets the SceneManager of the Application.
		 * @note This will be invalid if no SceneManager was created using the ApplicationInfo.
		 * @return The SceneManager.
		 */
		SceneManager& get_scene_manager() const;

		/**
		 * @brief Gets the TimeManager of the Application.
		 * @note This will be invalid if no TimeManager was created using the ApplicationInfo.
		 * @return The TimeManager.
		 */
		TimeManager& get_time_manager() const;

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
		static Owner<Application> open(Path const &path);

		/**
		 * @brief Creates a new Application using the given ApplicationInfo.
		 * @param info The arguments.
		 * @return An Application Owner.
		 */
		static Owner<Application> create(ApplicationInfo const &info);

#pragma endregion

#pragma region Variables

	private:
		Bool m_running;
		Window *mp_window;
		MemoryManager *mp_memoryManager;
		JobManager *mp_jobManager;
		AudioManager *mp_audioManager;
		LayerManager *mp_layerManager;
		PhysicsManager *mp_physicsManager;
		AssetManager *mp_assetManager;
		InputManager *mp_inputManager;
		RenderManager *mp_renderManager;
		SceneManager *mp_sceneManager;
		TimeManager *mp_timeManager;
		Vector<Manager *> m_managers;

		Lookup<TypeID, SystemData> m_registeredSystems;
		Lookup<TypeID, ComponentData> m_registeredComponents;

		static Application *s_instance;

#pragma endregion
	};
}

#endif // MINTY_APPLICATION_APPLICATION_H