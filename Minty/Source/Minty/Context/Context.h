#pragma once
#include "Minty/Asset/AssetManager.h"
#include "Minty/Core/Macro.h"
#include "Minty/Context/Manager.h"
#include "Minty/Debug/DualBuffer.h"
#include "Minty/Data/Lookup.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Vector.h"
#include "Minty/Job/JobManager.h"
#include "Minty/Memory/MemoryManager.h"
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

		MemoryManagerBuilder memoryManagerBuilder = {};
		JobManagerBuilder jobManagerBuilder = {};
		AssetManagerBuilder assetManagerBuilder = {};
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
		Owner<MemoryManager> m_memoryManager;
		Owner<JobManager> m_jobManager;
		Owner<AssetManager> m_assetManager;
		Owner<RenderManager> m_renderManager;
		Owner<SceneManager> m_sceneManager;
		Vector<Manager*> m_managers;

		Lookup<TypeID, SystemInfo> m_registeredSystems;
		//Lookup<TypeID, ComponentInfo> m_registeredComponents;

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
		Context(Context&& other) noexcept
			: mp_dualBuffer(other.mp_dualBuffer)
			, m_memoryManager(std::move(other.m_memoryManager))
			, m_jobManager(std::move(other.m_jobManager))
			, m_assetManager(std::move(other.m_assetManager))
			, m_renderManager(std::move(other.m_renderManager))
			, m_sceneManager(std::move(other.m_sceneManager))
			, m_managers(std::move(other.m_managers))
		{
			other.mp_dualBuffer = nullptr;
		}

		~Context();

#pragma endregion

#pragma region Operators

	public:
		Context& operator=(Context const& other) = delete;

		Context& operator=(Context&& other) noexcept
		{
			if (this != &other)
			{
				mp_dualBuffer = other.mp_dualBuffer;
				other.mp_dualBuffer = nullptr;
				m_memoryManager = std::move(other.m_memoryManager);
				m_jobManager = std::move(other.m_jobManager);
				m_assetManager = std::move(other.m_assetManager);
				m_renderManager = std::move(other.m_renderManager);
				m_sceneManager = std::move(other.m_sceneManager);
				m_managers = std::move(other.m_managers);
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the MemoryManager in this Context.
		/// </summary>
		/// <returns>The MemoryManager.</returns>
		MemoryManager& get_memory_manager() { return *m_memoryManager; }

		/// <summary>
		/// Gets the JobManager in this Context.
		/// </summary>
		/// <returns>The JobManager.</returns>
		JobManager& get_job_manager() { return *m_jobManager; }

		/// <summary>
		/// Gets the AssetManager in this Context.
		/// </summary>
		/// <returns>The AssetManager.</returns>
		AssetManager& get_asset_manager() { return *m_assetManager; }

		/// <summary>
		/// Gets the RenderManager in this Context.
		/// </summary>
		/// <returns>The RenderManager.</returns>
		RenderManager& get_render_manager() { return *m_renderManager; }

		/// <summary>
		/// Gets the SceneManager in this Context.
		/// </summary>
		/// <returns>The SceneManager.</returns>
		SceneManager& get_scene_manager() { return *m_sceneManager; }

#pragma endregion

#pragma region Methods

	private:
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

#pragma region Systems

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		void register_system(String const& name)
		{
			MINTY_ASSERT(!m_registeredSystems.contains(name), F("System already exists with the name: {}", name));
			MINTY_ASSERT(!m_registeredSystems.contains(typeid(T)), F("System already exists with the TypeID: {}", typeid(T)));

			SystemInfo info{};
			info.name = name;
			info.typeId = typeid(T);
			info.create = [](SystemBuilder const& builder) -> System*
				{
					return new T(builder);
				};

			m_registeredSystems.add(name, typeid(T), info);
		}

		SystemInfo const* get_system_info(String const& name) const
		{
			auto it = m_registeredSystems.find(name);
			if (it == m_registeredSystems.end())
			{
				return nullptr;
			}
			return &it->get_third();
		}

		template<typename T, typename = std::enable_if_t<std::is_base_of_v<System, T>>>
		SystemInfo const* get_system_info() const
		{
			auto it = m_registeredSystems.find(typeid(T));
			if (it == m_registeredSystems.end())
			{
				return nullptr;
			}
			return &it->get_third();
		}

#pragma endregion

#pragma endregion

#pragma region Statics

	public:
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