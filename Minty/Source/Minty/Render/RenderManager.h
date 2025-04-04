#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Window/Window.h"
#include "Minty/Render/Format.h"

namespace Minty
{
	/// <summary>
	/// The arguments for creating a RenderManager.
	/// </summary>
	struct RenderManagerBuilder
	{
		/// <summary>
		/// The Window to render to.
		/// </summary>
		Ref<Window> window = nullptr;

		/// <summary>
		/// The format of the target surface.
		/// </summary>
		Format targetSurfaceFormat = Format::Default;
	};

	/// <summary>
	/// Handles rendering to a Window.
	/// </summary>
	class RenderManager
	{
#pragma region Variables

	private:
		Ref<Window> m_window;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new RenderManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		RenderManager(RenderManagerBuilder const& builder)
			: m_window(builder.window)
		{
		}

		virtual ~RenderManager()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Window that this RenderManager is rendering to.
		/// </summary>
		/// <returns>The Window.</returns>
		Ref<Window> get_window() const { return m_window; }

#pragma endregion


#pragma region Methods

	public:
		/// <summary>
		/// Prepares to render a frame.
		/// </summary>
		/// <returns>True, on success. Returns false when the frame should be skipped.</returns>
		virtual Bool start_frame() = 0;

		/// <summary>
		/// Finishes rendering a frame.
		/// </summary>
		virtual void end_frame() = 0;

#pragma endregion


#pragma region Statics

	public:
		/// <summary>
		/// Creates a new RenderManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A RenderManager Owner.</returns>
		static Owner<RenderManager> create(RenderManagerBuilder const& builder = {});

		/// <summary>
		/// Gets the active Context's RenderManager.
		/// </summary>
		/// <returns>The RenderManager.</returns>
		static RenderManager& get_singleton();

#pragma endregion

	};
}