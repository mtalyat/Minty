#pragma once
#include "Minty/Asset/AssetManager.h"
#include "Minty/Audio/AudioManager.h"
#include "Minty/Component/Component.h"
#include "Minty/Core/Macro.h"
#include "Minty/Debug/DualBuffer.h"
#include "Minty/Data/Lookup.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Vector.h"
#include "Minty/Input/InputManager.h"
#include "Minty/Job/JobManager.h"
#include "Minty/Manager/Manager.h"
#include "Minty/Memory/MemoryManager.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Scene/SceneManager.h"

namespace Minty
{
	/// <summary>
	/// Holds data to initialize a Context.
	/// </summary>
	struct ContextBuilder
	{
		Path debugLogPath = "";

		WindowBuilder windowBuilder = {};
		MemoryManagerBuilder memoryManagerBuilder = {};
		JobManagerBuilder jobManagerBuilder = {};
		AudioManagerBuilder audioManagerBuilder = {};
		PhysicsManagerBuilder physicsManagerBuilder = {};
		AssetManagerBuilder assetManagerBuilder = {};
		InputManagerBuilder inputManagerBuilder = {};
		RenderManagerBuilder renderManagerBuilder = {};
		SceneManagerBuilder sceneManagerBuilder = {};
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
		Owner<Window> m_window;
		Owner<MemoryManager> m_memoryManager;
		Owner<JobManager> m_jobManager;
		Owner<AudioManager> m_audioManager;
		Owner<PhysicsManager> m_physicsManager;
		Owner<AssetManager> m_assetManager;
		Owner<InputManager> m_inputManager;
		Owner<RenderManager> m_renderManager;
		Owner<SceneManager> m_sceneManager;
		Vector<Manager*> m_managers;

		Lookup<TypeID, SystemInfo> m_registeredSystems;
		Lookup<TypeID, ComponentInfo> m_registeredComponents;

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
		Context(Context&& other) noexcept;

		~Context();

#pragma endregion

#pragma region Operators

	public:
		Context& operator=(Context const& other) = delete;

		Context& operator=(Context&& other) noexcept;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the MemoryManager in this Context.
		/// </summary>
		/// <returns>The MemoryManager.</returns>
		MemoryManager& get_memory_manager() { return *m_memoryManager; }

		/// <summary>
		/// Gets the MemoryManager in this Context.
		/// </summary>
		/// <returns>The MemoryManager.</returns>
		Ref<MemoryManager> get_memory_manager_ref() const { return m_memoryManager.create_ref(); }

		/// <summary>
		/// Gets the JobManager in this Context.
		/// </summary>
		/// <returns>The JobManager.</returns>
		JobManager& get_job_manager() { return *m_jobManager; }

		/// <summary>
		/// Gets the JobManager in this Context.
		/// </summary>
		/// <returns>The JobManager.</returns>
		Ref<JobManager> get_job_manager_ref() const { return m_jobManager.create_ref(); }

		/// <summary>
		/// Gets the AudioManager in this Context.
		/// </summary>
		/// <returns>The AudioManager.</returns>
		AudioManager& get_audio_manager() { return *m_audioManager; }

		/// <summary>
		/// Gets the AudioManager in this Context.
		/// </summary>
		/// <returns>The AudioManager.</returns>
		Ref<AudioManager> get_audio_manager_ref() const { return m_audioManager.create_ref(); }

		/// <summary>
		/// Gets the PhysicsManager in this Context.
		/// </summary>
		/// <returns>The PhysicsManager.</returns>
		PhysicsManager& get_physics_manager() { return *m_physicsManager; }

		/// <summary>
		/// Gets the PhysicsManager in this Context.
		/// </summary>
		/// <returns>The PhysicsManager.</returns>
		Ref<PhysicsManager> get_physics_manager_ref() const { return m_physicsManager.create_ref(); }

		/// <summary>
		/// Gets the AssetManager in this Context.
		/// </summary>
		/// <returns>The AssetManager.</returns>
		AssetManager& get_asset_manager() { return *m_assetManager; }

		/// <summary>
		/// Gets the AssetManager in this Context.
		/// </summary>
		/// <returns>The AssetManager.</returns>
		Ref<AssetManager> get_asset_manager_ref() const { return m_assetManager.create_ref(); }

		/// <summary>
		/// Gets the InputManager in this Context.
		/// </summary>
		/// <returns>The InputManager.</returns>
		InputManager& get_input_manager() { return *m_inputManager; }

		/// <summary>
		/// Gets the InputManager in this Context.
		/// </summary>
		/// <returns>The InputManager.</returns>
		Ref<InputManager> get_input_manager_ref() const { return m_inputManager.create_ref(); }

		/// <summary>
		/// Gets the RenderManager in this Context.
		/// </summary>
		/// <returns>The RenderManager.</returns>
		RenderManager& get_render_manager() { return *m_renderManager; }

		/// <summary>
		/// Gets the RenderManager in this Context.
		/// </summary>
		/// <returns>The RenderManager.</returns>
		Ref<RenderManager> get_render_manager_ref() const { return m_renderManager.create_ref(); }

		/// <summary>
		/// Gets the Window in this Context.
		/// </summary>
		/// <returns></returns>
		Window& get_window() const { return *m_window; }

		/// <summary>
		/// Gets the Window in this Context.
		/// </summary>
		/// <returns></returns>
		Ref<Window> get_window_ref() const { return m_window.create_ref(); }

		/// <summary>
		/// Gets the SceneManager in this Context.
		/// </summary>
		/// <returns>The SceneManager.</returns>
		SceneManager& get_scene_manager() { return *m_sceneManager; }

		/// <summary>
		/// Gets the SceneManager in this Context.
		/// </summary>
		/// <returns>The SceneManager.</returns>
		Ref<SceneManager> get_scene_manager_ref() const { return m_sceneManager.create_ref(); }

#pragma endregion

#pragma region Methods

	private:
		void register_components();
		void register_systems();

		void initialize();

		void dispose();

	public:
		/// <summary>
		/// Updates all Managers in this Context.
		/// </summary>
		void update(Time const& time);

		/// <summary>
		/// Finalizes all Managers in this Context.
		/// </summary>
		void finalize();

		/// <summary>
		/// Renders all Managers in this Context.
		/// </summary>
		void render();

		/// <summary>
		/// Syncs all Managers in this Context.
		/// </summary>
		void sync();

		/// <summary>
		/// Processes all pending events in this Context.
		/// </summary>
		void process_events();

		/// <summary>
		/// Handles the given Event.
		/// </summary>
		/// <param name="event">The Event that has occured.</param>
		void handle_event(Event& event);
#pragma region Systems

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		void register_system(String const& name, Int const priority)
		{
			MINTY_ASSERT(!m_registeredSystems.contains(name), F("System already exists with the name: {}", name));
			MINTY_ASSERT(!m_registeredSystems.contains(typeid(T)), F("System already exists with the TypeID: {}", typeid(T).name()));

			SystemInfo info
			{
				.name = name,
				.typeId = typeid(T),
				.create = [](SystemBuilder const& builder) -> System*
				{
					return new T(builder);
				},
				.defaultPriority = priority
			};

			m_registeredSystems.add(name, typeid(T), info);
		}

		SystemInfo const* get_system_info(String const& name) const;

		SystemInfo const* get_system_info(TypeID const& typeId) const;

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
		void register_component(String const& name)
		{
			MINTY_ASSERT(!m_registeredComponents.contains(name), F("Component already exists with the name: {}", name));
			MINTY_ASSERT(!m_registeredComponents.contains(typeid(T)), F("Component already exists with the TypeID: {}", typeid(T).name()));

			ComponentInfo info
			{
				.name = name,
				.create = [](EntityManager& entityManager, Entity const entity) -> Component&
				{
					return entityManager.add_component<T>(entity);
				},
				.get = [](EntityManager& entityManager, Entity const entity) -> Component*
				{
					return entityManager.try_get_component<T>(entity);
				},
				.get_const = [](EntityManager const& entityManager, Entity const entity) -> Component const*
				{
					return entityManager.try_get_component<T>(entity);
				},
				.destroy = [](EntityManager& entityManager, Entity const entity) -> void
				{
					entityManager.remove_component<T>(entity);
				}
			};

			m_registeredComponents.add(name, typeid(T), info);
		}

		ComponentInfo const* get_component_info(String const& name) const;

		ComponentInfo const* get_component_info(TypeID const& typeId) const;

#pragma endregion

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Context using the given ContextBuilder.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A Context Owner.</returns>
		static Owner<Context> create(ContextBuilder const& builder = {});

		/// <summary>
		/// Gets the current instance of the Context.
		/// </summary>
		/// <returns>The current instance of the Context.</returns>
		static Context& get_singleton()
		{
			MINTY_ASSERT(s_instance, "Context singleton is null.");
			return *s_instance;
		}

#pragma endregion
	};
}