#pragma once
#include "Minty/Asset/AssetManager.h"
#include "Minty/Core/Macro.h"
#include "Minty/Debug/DualBuffer.h"
#include "Minty/Data/Path.h"
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

		MemoryManagerBuilder* memoryManagerBuilder = nullptr;
		JobManagerBuilder* jobManagerBuilder = nullptr;
		AssetManagerBuilder* assetManagerBuilder = nullptr;
		RenderManagerBuilder* renderManagerBuilder = nullptr;
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
		{
			other.mp_dualBuffer = nullptr;
		}

		~Context()
		{
			delete mp_dualBuffer;
			m_memoryManager.release();
			m_jobManager.release();
			m_assetManager.release();
			m_renderManager.release();

			s_instance = nullptr;
		}

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

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Gets the current instance of the Context.
		/// </summary>
		/// <returns>The current instance of the Context.</returns>
		static Context& get_singleton()
		{
			MINTY_ASSERT(s_instance, "Context get_singleton is null.");
			return *s_instance;
		}

#pragma endregion

	};
}