#pragma once
#include "Minty/Manager/Manager.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Window/Window.h"
#include "Minty/Render/Buffer.h"
#include "Minty/Render/CameraInfo.h"
#include "Minty/Render/Format.h"
#include "Minty/Render/Image.h"
#include "Minty/Render/MeshType.h"
#include "Minty/Render/Space.h"
#include "Minty/Render/Surface.h"

namespace Minty
{
	class Shader;
	class Material;
	class Mesh;
	class Viewport;
	class Camera;
	class Texture;
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

	private:
		using TexMatKey = UInt;

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

		Bool m_resizePending;

		// current binds

		Ref<Shader> m_boundShader;
		Ref<Material> m_boundMaterial;
		Ref<Mesh> m_boundMesh;
		Ref<Camera> m_camera;
		Matrix4 m_cameraMatrix;

		// global resources
		
		Owner<Surface> m_surface;
		Owner<Image> m_depthImage;

		// default resources

		Owner<Viewport> m_defaultViewport;
		Map<MeshType, Ref<Mesh>> m_defaultMeshes;
		Map<TexMatKey, Ref<Material>> m_defaultMaterials;

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

		Bool check_resize_pending()
		{
			if (m_resizePending)
			{
				m_resizePending = false;
				return true;
			}
			return false;
		}

		inline void set_surface(Owner<Surface>&& surface) { m_surface = std::move(surface); }

		inline void set_depth_image(Owner<Image>&& image) { m_depthImage = std::move(image); }

		inline void set_default_viewport(Owner<Viewport>&& viewport) { m_defaultViewport = std::move(viewport); }

	public:
		/// <summary>
		/// Gets the Window that this RenderManager is rendering to.
		/// </summary>
		/// <returns>The Window.</returns>
		inline Ref<Window> const& get_window() const { return m_window; }

		/// <summary>
		/// Gets the Surface that this RenderManager is rendering to.
		/// </summary>
		/// <returns>The Surface.</returns>
		inline Ref<Surface> get_surface() const { return m_surface.create_ref(); }

		/// <summary>
		/// Gets the depth Image used for depth testing.
		/// </summary>
		/// <returns>The depth Image.</returns>
		inline Ref<Image> get_depth_image() const { return m_depthImage.create_ref(); }

		/// <summary>
		/// Gets the default Viewport that renders to the entire Surface.
		/// </summary>
		/// <returns>The default Viewport.</returns>
		inline Ref<Viewport> get_default_viewport() { return m_defaultViewport.create_ref(); }

		/// <summary>
		/// Gets the default Viewport that renders to the entire Window.
		/// </summary>
		/// <returns>The default Viewport.</returns>
		inline Ref<Viewport> get_default_viewport() const { return m_defaultViewport.create_ref(); }

		/// <summary>
		/// Gets the color attachment format of the current Surface.
		/// </summary>
		/// <returns>The attachment Format.</returns>
		inline Format get_color_attachment_format() const { return m_surface->get_format(); }

		/// <summary>
		/// Gets the depth attachment format of the current depth Image.
		/// </summary>
		/// <returns>The attachment Format.</returns>
		inline Format get_depth_attachment_format() const { return m_depthImage->get_format(); }

		/// <summary>
		/// Gets the default Mesh for the given type.
		/// </summary>
		/// <param name="type">The type of Mesh. Cannot be Custom.</param>
		/// <returns>A Ref to a Mesh that corresponds with the type, or nullptr if the type is Empty.</returns>
		Ref<Mesh> get_default_mesh(MeshType const type);

		/// <summary>
		/// Gets the default Material for the given Texture, AssetType, and Space.
		/// </summary>
		/// <param name="texture">The Texture.</param>
		/// <param name="assetType">The AssetType.</param>
		/// <param name="space">The Space.</param>
		/// <returns>The default Material.</returns>
		Ref<Material> get_default_material(Ref<Texture> const& texture, AssetType const assetType, Space const space);

#pragma endregion

#pragma region Methods

	protected:
		/// <summary>
		/// Refreshes the Surface and related resources.
		/// </summary>
		void refresh();

		virtual	void recreate_depth_resources() = 0;

	public:
		void initialize() override;

		void dispose() override;

		/// <summary>
		/// Prepares to render a frame.
		/// </summary>
		/// <returns>True, on success. Returns false when the frame should be skipped.</returns>
		virtual Bool start_frame();

		/// <summary>
		/// Aborts the current started frame.
		/// </summary>
		virtual void abort_frame();

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

		void handle_event(Event& event) override;

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

		void draw_instances(UInt const instanceCount, UInt const vertexCount);

#pragma endregion


#pragma endregion

#pragma region Statics

	private:
		// creates a key for the default materials
		static TexMatKey create_texmat_key(AssetType const type, Space const space)
		{
			return (static_cast<UShort>(type) << (sizeof(UShort) << 3)) | static_cast<UShort>(space);
		}

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