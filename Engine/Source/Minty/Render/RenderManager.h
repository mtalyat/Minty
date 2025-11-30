#ifndef MINTY_RENDER_RENDERMANAGER_H
#define MINTY_RENDER_RENDERMANAGER_H

/**
 * @file RenderManager.h
 * @brief Header file defining the RenderManager class.
 * @author Mitchell Talyat
 */

#include "Minty/Manager/Manager.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Window/Window.h"
#include "Minty/Render/Buffer.h"
#include "Minty/Render/CameraData.h"
#include "Minty/Render/Format.h"
#include "Minty/Render/Image.h"
#include "Minty/Render/MaskMode.h"
#include "Minty/Render/MeshType.h"
#include "Minty/Render/Space.h"
#include "Minty/Render/Surface.h"

namespace Minty
{
	class Shader;
	class MaterialTemplate;
	class Material;
	class Mesh;
	class Viewport;
	class Camera;
	class Texture;
	class Transform;
	class Surface;
	struct RenderManagerInfo;

	/**
	 * @brief Manages rendering operations.
	 */
	class RenderManager
		: public Manager
	{
#pragma region Types

	public:
        struct TexMatKey
        {
            UUID textureId;
            UInt key;

            bool operator==(const TexMatKey& other) const
            {
                return textureId == other.textureId && key == other.key;
            }
        };

	protected:
		enum class State
		{
			Idle,
			Frame,
			Pass,
		};

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new RenderManager.
		 * @param info The arguments.
		 */
		RenderManager(RenderManagerInfo const& info);

		virtual ~RenderManager() = default;

#pragma endregion

#pragma region Accessors

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

		inline void set_surface(Shared<Surface>&& surface) { m_surface = std::move(surface); }

		inline void set_depth_image(Shared<Image>&& image) { m_depthStencilImage = std::move(image); }

		inline void set_default_viewport(Shared<Viewport>&& viewport) { m_defaultViewport = std::move(viewport); }

	public:
		/**
		 * @brief Gets the Window that this RenderManager is rendering to.
		 * @return The Window.
		 */
		inline Ref<Window> const& get_window() const { return m_window; }

		/**
		 * @brief Gets the Surface that this RenderManager is rendering to.
		 * @return The Surface.
		 */
		inline Ref<Surface> get_surface() const { return m_surface.to_ref(); }

		/**
		 * @brief Gets the depth Image used for depth testing.
		 * @return The depth Image.
		 */
		inline Ref<Image> get_depth_image() const { return m_depthStencilImage.to_ref(); }

		/**
		 * @brief Gets the default Viewport that renders to the entire Surface.
		 * @return The default Viewport.
		 */
		inline Ref<Viewport> get_default_viewport() { return m_defaultViewport.to_ref(); }

		/**
		 * @brief Gets the default Viewport that renders to the entire Window.
		 * @return The default Viewport.
		 */
		inline Ref<Viewport> get_default_viewport() const { return m_defaultViewport.to_ref(); }

		/**
		 * @brief Gets the color attachment format of the current Surface.
		 * @return The attachment Format.
		 */
		inline Format get_color_attachment_format() const { return m_surface->get_format(); }

		/**
		 * @brief Gets the depth attachment format of the current depth Image.
		 * @return The attachment Format.
		 */
		inline Format get_depth_attachment_format() const { return m_depthStencilImage->get_format(); }

		/**
		 * @brief Gets the default Mesh for the given type.
		 * @param type The type of Mesh. Cannot be Custom.
		 * @return A Ref to a Mesh that corresponds with the type, or nullptr if the type is Empty.
		 */
		Ref<Mesh> get_default_mesh(MeshType const type);

		/**
		 * @brief Gets the default MaterialTemplate for the give AssetType, Space, and variant.
		 * @param assetType The AssetType.
		 * @param space The Space.
		 * @param mask The mask mode of the MaterialTemplate.
		 * @return The default MaterialTemplate.
		 */
		Ref<MaterialTemplate> get_default_material_template(AssetType const assetType, Space const space, MaskMode const mask = MaskMode::None);

		/**
		 * @brief Gets the default Material for the given Texture, AssetType, Space and variant.
		 * @param texture The Texture.
		 * @param assetType The AssetType.
		 * @param space The Space.
		 * @param mask The mask mode of the MaterialTemplate.
		 * @return The default Material.
		 */
		Ref<Material> get_default_material(Ref<Texture> const& texture, Ref<MaterialTemplate> const& materialTemplate, AssetType const assetType, Space const space, MaskMode const mask = MaskMode::None);

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Prepares to render a frame.
		 * @return True, on success. Returns false when the frame should be skipped.
		 */
		virtual Bool start_frame();

		/**
		 * @brief Aborts the current started frame.
		 */
		virtual void abort_frame();

		/**
		 * @brief Finishes rendering a frame.
		 */
		virtual void end_frame();

		/**
		 * @brief Starts a render pass using the given Camera.
		 * @param cameraInfo The CameraInfo to render the Scene from.
		 */
		virtual Bool start_pass(CameraData const& cameraInfo);

		/**
		 * @brief Finishes the current render pass.
		 */
		virtual void end_pass();

		void handle_event(Event& event) override;

		void bind_shader(Ref<Shader> const& shader);

		void bind_material(Ref<Material> const& material);

		void bind_mesh(Ref<Mesh> const& mesh);

		void bind_vertex_buffer(Ref<Buffer> const& buffer, UInt const binding = 0);

		void bind_index_buffer(Ref<Buffer> const& buffer);
		
		void draw_mesh(Ref<Mesh> const& mesh);

		void draw_instances(UInt const instanceCount, UInt const vertexCount);
		
		/**
		 * @brief Creates a new RenderManager.
		 * @param info The arguments.
		 * @return A RenderManager Owner.
		 */
		static Unique<RenderManager> create(RenderManagerInfo const& info = {});

		/**
		 * @brief Gets the active Context's RenderManager.
		 * @return The RenderManager.
		 */
		static RenderManager& get_singleton();

	protected:
		/**
		 * @brief Refreshes the Surface and related resources.
		 */
		void refresh();

		virtual	void recreate_depth_resources() = 0;

	private:
		void clear_binds();

		// creates a key for the default materials
		static TexMatKey create_texmat_key(UUID const textureId, AssetType const type, Space const space)
		{
			return TexMatKey(textureId, (static_cast<UInt>(type) << 2) | static_cast<UInt>(space));
		}

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
		
		Shared<Surface> m_surface;
		Shared<Image> m_depthStencilImage;

		// default resources

		Shared<Viewport> m_defaultViewport;
		Map<MeshType, Ref<Mesh>> m_defaultMeshes;
		Map<TexMatKey, Ref<Material>> m_defaultMaterials;

#pragma endregion
	};
}

namespace std
{
	template<>
	struct hash<Minty::RenderManager::TexMatKey>
	{
		std::size_t operator()(const Minty::RenderManager::TexMatKey& k) const noexcept
		{
			std::size_t h1 = std::hash<Minty::UUID>{}(k.textureId);
			std::size_t h2 = std::hash<Minty::UInt>{}(k.key);
			return h1 ^ (h2 << 1);
		}
	};
}

#endif // MINTY_RENDER_RENDERMANAGER_H