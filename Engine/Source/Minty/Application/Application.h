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
		Window &get_window() const
		{
			MINTY_ASSERT(m_window != nullptr, ErrorCode::Object_InvalidState);
			return *m_window;
		}

		/**
		 * @brief Gets a Ref to the Window of the Application.
		 * @note This will be invalid if no Window was created using the ApplicationInfo.
		 * @return The Ref to the Window.
		 */
		Ref<Window> get_window_ref() const
		{
			MINTY_ASSERT(m_window != nullptr, ErrorCode::Object_InvalidState);
			return m_window.to_ref();
		}

		/**
		 * @note This will be invalid if no MemoryManager was created using the ApplicationInfo.
		 * @brief Gets the MemoryManager of the Application.
		 * @return The MemoryManager.
		 */
		MemoryManager &get_memory_manager() const
		{
			MINTY_ASSERT(m_memoryManager != nullptr, ErrorCode::Object_InvalidState);
			return *m_memoryManager;
		}

		/**
		 * @brief Gets the JobManager of the Application.
		 * @note This will be invalid if no JobManager was created using the ApplicationInfo.
		 * @return The JobManager.
		 */
		JobManager &get_job_manager() const
		{
			MINTY_ASSERT(m_jobManager != nullptr, ErrorCode::Object_InvalidState);
			return *m_jobManager;
		}

		/**
		 * @brief Gets the AudioManager of the Application.
		 * @note This will be invalid if no AudioManager was created using the ApplicationInfo.
		 * @return The AudioManager.
		 */
		AudioManager &get_audio_manager() const
		{
			MINTY_ASSERT(m_audioManager != nullptr, ErrorCode::Object_InvalidState);
			return *m_audioManager;
		}

		/**
		 * @brief Gets the LayerManager of the Application.
		 * @note This will be invalid if no LayerManager was created using the ApplicationInfo.
		 * @return The LayerManager.
		 */
		LayerManager &get_layer_manager() const
		{
			MINTY_ASSERT(m_layerManager != nullptr, ErrorCode::Object_InvalidState);
			return *m_layerManager;
		}

		/**
		 * @brief Gets the PhysicsManager of the Application.
		 * @note This will be invalid if no PhysicsManager was created using the ApplicationInfo.
		 * @return The PhysicsManager.
		 */
		PhysicsManager &get_physics_manager() const
		{
			MINTY_ASSERT(m_physicsManager != nullptr, ErrorCode::Object_InvalidState);
			return *m_physicsManager;
		}

		/**
		 * @brief Gets the AssetManager of the Application.
		 * @note This will be invalid if no AssetManager was created using the ApplicationInfo.
		 * @return The AssetManager.
		 */
		AssetManager &get_asset_manager() const
		{
			MINTY_ASSERT(m_assetManager != nullptr, ErrorCode::Object_InvalidState);
			return *m_assetManager;
		}

		/**
		 * @brief Gets the InputManager of the Application.
		 * @note This will be invalid if no InputManager was created using the ApplicationInfo.
		 * @return The InputManager.
		 */
		InputManager &get_input_manager() const
		{
			MINTY_ASSERT(m_inputManager != nullptr, ErrorCode::Object_InvalidState);
			return *m_inputManager;
		}

		/**
		 * @brief Gets the RenderManager of the Application.
		 * @note This will be invalid if no RenderManager was created using the ApplicationInfo.
		 * @return The RenderManager.
		 */
		RenderManager &get_render_manager() const
		{
			MINTY_ASSERT(m_renderManager != nullptr, ErrorCode::Object_InvalidState);
			return *m_renderManager;
		}

		/**
		 * @brief Gets the SceneManager of the Application.
		 * @note This will be invalid if no SceneManager was created using the ApplicationInfo.
		 * @return The SceneManager.
		 */
		SceneManager &get_scene_manager() const
		{
			MINTY_ASSERT(m_sceneManager != nullptr, ErrorCode::Object_InvalidState);
			return *m_sceneManager;
		}

		/**
		 * @brief Gets the TimeManager of the Application.
		 * @note This will be invalid if no TimeManager was created using the ApplicationInfo.
		 * @return The TimeManager.
		 */
		TimeController &get_time_manager() const
		{
			MINTY_ASSERT(m_timeController != nullptr, ErrorCode::Object_InvalidState);
			return *m_timeController;
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

		template <typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		void register_system(String const &name, Int const priority = 0)
		{
			MINTY_ASSERT(!m_registeredSystems.contains(name), ErrorCode::Argument_KeyAlreadyExists, name);
			MINTY_ASSERT(!m_registeredSystems.contains(typeid(T)), ErrorCode::Argument_KeyAlreadyExists, typeid(T).name());

			SystemData info{
				.name = name,
				.typeId = typeid(T),
				.create = [](SystemInfo const &info) -> System *
				{
					return new T(info);
				},
				.defaultPriority = priority};

			m_registeredSystems.add(name, typeid(T), info);
		}

		inline SystemData const &get_system_info(String const &name) const
		{
			MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
			MINTY_ASSERT(m_registeredSystems.contains(name), ErrorCode::System_NotRegistered, name);
			return m_registeredSystems.at(name);
		}

		inline SystemData const &get_system_info(TypeID const &typeId) const
		{
			MINTY_ASSERT(m_registeredSystems.contains(typeId), ErrorCode::System_NotRegistered, typeId.name());
			return m_registeredSystems.at(typeId);
		}

		template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
		void register_component(String const &name)
		{
			MINTY_ASSERT(!m_registeredComponents.contains(name), ErrorCode::Argument_KeyAlreadyExists, name);
			MINTY_ASSERT(!m_registeredComponents.contains(typeid(T)), ErrorCode::Argument_KeyAlreadyExists, typeid(T).name());

			ComponentData info{
				.name = name,
				.create = [](EntityManager &entityManager, Entity const entity) -> Component &
				{
					return entityManager.add_component<T>(entity);
				},
				.get = [](EntityManager &entityManager, Entity const entity) -> Component *
				{
					return entityManager.try_get_component<T>(entity);
				},
				.get_const = [](EntityManager const &entityManager, Entity const entity) -> Component const *
				{
					return entityManager.try_get_component<T>(entity);
				},
				.destroy = [](EntityManager &entityManager, Entity const entity) -> void
				{
					entityManager.remove_component<T>(entity);
				}};

			m_registeredComponents.add(name, typeid(T), info);
		}

		inline ComponentData const &get_component_info(String const &name) const
		{
			MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
			MINTY_ASSERT(m_registeredComponents.contains(name), ErrorCode::Component_NotRegistered, name);
			return m_registeredComponents.at(name);
		}

		inline ComponentData const &get_component_info(TypeID const &typeId) const
		{
			MINTY_ASSERT(m_registeredComponents.contains(typeId), ErrorCode::Component_NotRegistered, typeId.name());
			return m_registeredComponents.at(typeId);
		}

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

	private:
		/**
		 * @brief Handles an event sent to the Application.
		 * @param event The event to handle.
		 */
		void handle_event(Event &event);

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

		Lookup<TypeID, SystemData> m_registeredSystems;
		Lookup<TypeID, ComponentData> m_registeredComponents;

		static Application *s_instance;

#pragma endregion
	};
}

#endif // MINTY_APPLICATION_APPLICATION_H