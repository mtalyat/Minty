#pragma once
#include "Minty/Context/Manager.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Window/Window.h"
#include "Minty/Render/Buffer.h"
#include "Minty/Render/CameraInfo.h"
#include "Minty/Render/Format.h"

namespace Minty
{
	class Shader;
	class Material;
	class Mesh;
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
#pragma region Classes

	protected:
		enum class State
		{
			Idle,
			Frame,
			Pass,
		};

#pragma endregion


#pragma region Variables

	private:
		State m_state;
		Ref<Window> m_window;

		Ref<Shader> m_boundShader;
		Ref<Material> m_boundMaterial;
		Ref<Mesh> m_boundMesh;
		Camera m_camera;
		Matrix4 m_cameraMatrix;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new RenderManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		RenderManager(RenderManagerBuilder const& builder);

		virtual ~RenderManager()
		{
			MINTY_ASSERT_ERROR(!is_initialized(), "RenderManager is not disposed before destruction.");
		}

#pragma endregion

#pragma region Get Set

	protected:
		// gets the state of the RenderManager
		State get_state() const { return m_state; }

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
		virtual Bool start_frame();

		/// <summary>
		/// Finishes rendering a frame.
		/// </summary>
		virtual void end_frame();

		/// <summary>
		/// Starts a render pass using the given Camera.
		/// </summary>
		/// <param name="cameraInfo">The CameraInfo to render the Scene from.</param>
		virtual Bool start_pass(CameraInfo const& cameraInfo);

		/// <summary>
		/// Finishes the current render pass.
		/// </summary>
		virtual void end_pass();

#pragma region Bind

	private:
		void clear_binds();

	public:
		void bind_shader(Ref<Shader> const& shader);

		void bind_material(Ref<Material> const& material);

		void bind_mesh(Ref<Mesh> const& mesh);

		void bind_vertex_buffer(Ref<Buffer> const& buffer, UInt const binding = 0);

		void bind_index_buffer(Ref<Buffer> const& buffer);

#pragma endregion

#pragma region Draw

	public:
		void draw_mesh(Ref<Mesh> const& mesh);

#pragma endregion


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