#pragma once
#include "Minty/Asset/AssetManager.h"
#include "Minty/Core/Macro.h"
#include "Minty/Context/Manager.h"
#include "Minty/Debug/DualBuffer.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Vector.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Job/JobManager.h"
#include "Minty/Memory/MemoryManager.h"
#include "Minty/Render/RenderManager.h"

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
		EntityManagerBuilder entityManagerBuilder = {};
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
		Owner<EntityManager> m_entityManager;
		Vector<Manager*> m_managers;

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
			, m_entityManager(std::move(other.m_entityManager))
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
				m_entityManager = std::move(other.m_entityManager);
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
		/// Gets the EntityManager in this Context.
		/// </summary>
		/// <returns>The EntityManager.</returns>
		EntityManager& get_entity_manager() { return *m_entityManager; }

#pragma endregion

#pragma region Methods

	private:
		void initialize();

		void dispose();

	public:
		/// <summary>
		/// Updates all Managers in this Context.
		/// </summary>
		void update();

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