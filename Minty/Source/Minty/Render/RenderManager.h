#pragma once
#include "Minty/Context/Manager.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Window/Window.h"
#include "Minty/Render/Format.h"

namespace Minty
{
	class Viewport;
	class Camera;
	class Transform;
	class Surface;

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
		: public Manager
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
			MINTY_ASSERT_ERROR(!is_initialized(), "RenderManager is not disposed before destruction.");
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Window that this RenderManager is rendering to.
		/// </summary>
		/// <returns>The Window.</returns>
		Ref<Window> const& get_window() const { return m_window; }

		/// <summary>
		/// Gets the Surface that this RenderManager is rendering to.
		/// </summary>
		/// <returns>The Surface.</returns>
		virtual Ref<Surface> get_surface() const = 0;

		/// <summary>
		/// Gets the default Viewport that renders to the entire Window.
		/// </summary>
		/// <returns>The default Viewport.</returns>
		virtual Ref<Viewport> get_default_viewport() const = 0;

		virtual Format get_color_attachment_format() const = 0;

		virtual Format get_depth_attachment_format() const = 0;

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

		/// <summary>
		/// Starts a render pass using the given Camera.
		/// </summary>
		/// <param name="camera">The Camera to render the Scene from.</param>
		/// <returns>True, on success. Returns false when the frame should be skipped.</returns>
		virtual Bool start_pass(Camera const& camera, Transform const& transform) = 0;

		/// <summary>
		/// Finishes the current render pass.
		/// </summary>
		virtual void end_pass() = 0;

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