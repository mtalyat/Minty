#include "pch.h"
#include "RenderManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Render/Camera.h"
#include "Minty/Render/Image.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Render/RenderPass.h"
#include "Minty/Render/Shader.h"
#include "Minty/Render/Texture.h"
#include "Minty/Event/WindowResizeEvent.h"
#include "Minty/Render/RenderManagerInfo.h"
#include "Minty/Window/Window.h"
#include "Minty/Render/Surface.h"
#include "Minty/Render/Viewport.h"
#include "Minty/Render/MeshInfo.h"
#include "Minty/Application/Application.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Render/MaterialInfo.h"
#include "Minty/Render/CameraData.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#endif // MINTY_VULKAN

using namespace Minty;

Unique<RenderManager> Minty::RenderManager::create(RenderManagerInfo const& info)
{
#ifdef MINTY_VULKAN
	return Unique<Vulkan_RenderManager>::create(info);
#else
	return Unique<RenderManager>();
#endif // MINTY_VULKAN
}

Unique<RenderManager> Minty::RenderManager::create()
{
	RenderManagerInfo info{};
	return create(info);
}

RenderManager& Minty::RenderManager::get_singleton()
{
	return Application::get_singleton().get_render_manager();
}

void Minty::RenderManager::clear_binds()
{
	m_boundMesh = nullptr;
	m_boundMaterial = nullptr;
	m_boundShader = nullptr;
}

void Minty::RenderManager::bind_shader(Ref<Shader> const& shader)
{
	MINTY_ASSERT(shader != nullptr, ErrorCode::Argument_ExpectedNonNull);

	// do nothing if already bound
	if (m_boundShader == shader)
	{
		return;
	}

	// clear dependent binds
	m_boundMaterial = nullptr;

	// bind shader
	m_boundShader = shader;
	m_boundShader->on_bind();
}

void Minty::RenderManager::bind_material(Ref<Material> const& material)
{
	MINTY_ASSERT(material != nullptr, ErrorCode::Argument_ExpectedNonNull);

	// do nothing if already bound
	if (m_boundMaterial == material)
	{
		return;
	}

	MINTY_ASSERT(material->get_material_template()->get_shader() == m_boundShader, ErrorCode::Argument_InvalidValue);

	m_boundMaterial = material;

	// set constants
	m_boundMaterial->try_set_input("camera", &m_cameraMatrix, sizeof(Matrix4));

	// bind
	m_boundMaterial->on_bind();
}

void Minty::RenderManager::bind_mesh(Ref<Mesh> const& mesh)
{
	MINTY_ASSERT(mesh != nullptr, ErrorCode::Argument_ExpectedNonNull);

	// do nothing if already bound
	if (m_boundMesh == mesh)
	{
		return;
	}

	m_boundMesh = mesh;
	bind_vertex_buffer(m_boundMesh->get_vertex_buffer());
	bind_index_buffer(m_boundMesh->get_index_buffer());
}

void Minty::RenderManager::bind_vertex_buffer(Ref<Buffer> const& buffer, UInt const binding)
{
#ifdef MINTY_VULKAN
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	Vulkan_Renderer::bind_vertex_buffer(
		renderManager.get_current_command_buffer(),
		static_cast<VkBuffer>(buffer->get_native()),
		binding);
#endif // MINTY_VULKAN
}

void Minty::RenderManager::bind_index_buffer(Ref<Buffer> const& buffer)
{
#ifdef MINTY_VULKAN
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	Vulkan_Renderer::bind_index_buffer(
		renderManager.get_current_command_buffer(),
		static_cast<VkBuffer>(buffer->get_native()));
#endif // MINTY_VULKAN
}

void Minty::RenderManager::draw_mesh(Ref<Mesh> const& mesh)
{
	MINTY_ASSERT(mesh != nullptr, ErrorCode::Argument_ExpectedNonNull);

#if defined(MINTY_VULKAN)
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	renderManager.draw_indices(static_cast<UInt>(mesh->get_indices().get_count()));
#endif // MINTY_VULKAN
}

void Minty::RenderManager::draw_instances(UInt const instanceCount, UInt const vertexCount)
{
	MINTY_ASSERT(instanceCount > 0, ErrorCode::Argument_ExpectedNonZero);
	MINTY_ASSERT(vertexCount > 0, ErrorCode::Argument_ExpectedNonZero);

#if defined(MINTY_VULKAN)
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	renderManager.draw_instances(instanceCount, vertexCount);
#endif // MINTY_VULKAN
}

Minty::RenderManager::RenderManager(RenderManagerInfo const& info)
	: m_state(State::Idle)
	, m_window(info.window)
	, m_resizePending(false)
	, m_boundShader(nullptr)
	, m_boundMaterial(nullptr)
	, m_boundMesh(nullptr)
	, m_camera(nullptr)
	, m_cameraMatrix()
	, m_surface(nullptr)
	, m_depthStencilImage(nullptr)
	, m_defaultViewport(nullptr)
	, m_defaultMeshes()
	, m_defaultMaterials()
{
	// if no window given, use the Context's window
	if (m_window == nullptr)
	{
		m_window = Application::get_singleton().get_window_ref();
	}

	MINTY_ASSERT(m_window != nullptr, ErrorCode::Argument_ExpectedNonNull);
}

void Minty::RenderManager::set_surface(Shared<Surface> &&surface)
{
	m_surface = std::move(surface);
}

void Minty::RenderManager::set_depth_image(Shared<Image> &&image)
{
	m_depthStencilImage = std::move(image);
}

void Minty::RenderManager::set_default_viewport(Shared<Viewport> &&viewport)
{
	m_defaultViewport = std::move(viewport);
}

Format Minty::RenderManager::get_color_attachment_format() const
{
    return m_surface->get_format();
}

Format Minty::RenderManager::get_depth_attachment_format() const
{
    return m_depthStencilImage->get_format(); 
}

Ref<Mesh> Minty::RenderManager::get_default_mesh(MeshType const type)
{
	MINTY_ASSERT(type != MeshType::Custom, ErrorCode::Argument_InvalidValue);

	// find the mesh
	auto found = m_defaultMeshes.find(type);
	if (found != m_defaultMeshes.end())
	{
		// already exists
		Ref<Mesh> mesh = found->get_second();
		MINTY_ASSERT(mesh != nullptr, ErrorCode::Object_InvalidState);
		return mesh;
	}

	// if empty
	if (type == MeshType::Empty)
	{
		return nullptr;
	}

	// create the mesh
	MeshInfo info{};
	info.id = UUID::create();
	info.type = type;
	AssetManager& assetManager = AssetManager::get_singleton();
	Ref<Mesh> mesh = assetManager.create<Mesh>(info);
	m_defaultMeshes.add(type, mesh);

	return mesh;
}

Ref<MaterialTemplate> Minty::RenderManager::get_default_material_template(AssetType const assetType, Space const space, MaskMode const mask)
{
	UUID templateId;
	switch (assetType)
	{
	case AssetType::Sprite:
		switch (space)
		{
		case Space::D3:
		break;
		templateId = DEFAULT_ASSET_SPRITE_MATERIAL_TEMPLATE;
		case Space::UI:
			templateId = DEFAULT_ASSET_UI_MATERIAL_TEMPLATE;
			break;
		default:
			MINTY_NOT_IMPLEMENTED();
		}
		break;
	case AssetType::FontVariant:
		switch (space)
		{
		case Space::UI:
			templateId = DEFAULT_ASSET_TEXT_MATERIAL_TEMPLATE;
			break;
		default:
			MINTY_NOT_IMPLEMENTED();
		}
		break;
	default:
		MINTY_NOT_IMPLEMENTED();
		break;
	}
	if (mask != MaskMode::None)
	{
		if (templateId == DEFAULT_ASSET_UI_MATERIAL_TEMPLATE)
		{
			switch (mask)
			{
			case MaskMode::Write:
				templateId = DEFAULT_ASSET_UI_MASK_WRITE_MATERIAL_TEMPLATE;
				break;
			case MaskMode::Test:
				templateId = DEFAULT_ASSET_UI_MASK_TEST_MATERIAL_TEMPLATE;
				break;
			default:
				MINTY_NOT_IMPLEMENTED();
			}
		}
		else
		{
			// "Variants are only supported for UI MaterialTemplates, not for type {}."
			MINTY_ABORT_F(ErrorCode::Argument_InvalidValue, to_string(assetType));
		}
	}

	AssetManager& assetManager = AssetManager::get_singleton();
	Ref<MaterialTemplate> const& materialTemplate = assetManager.get<MaterialTemplate>(templateId);
	MINTY_ASSERT_F(materialTemplate != nullptr, ErrorCode::Asset_NotLoaded, assetType, space, templateId);
	return materialTemplate;
}

Ref<Material> Minty::RenderManager::get_default_material(Ref<Texture> const& texture, Ref<MaterialTemplate> const& materialTemplate, AssetType const assetType, Space const space, MaskMode const mask)
{
	MINTY_ASSERT(texture != nullptr, ErrorCode::Argument_ExpectedNonNull);
	
	TexMatKey key = create_texmat_key(texture->get_id(), assetType, space);

	auto found = m_defaultMaterials.find(key);
	if (found != m_defaultMaterials.end())
	{
		// return existing Material
		Ref<Material> material = found->get_second();
		MINTY_ASSERT(material != nullptr, ErrorCode::Object_InvalidState);
		return material;
	}

	// create new Material
	MaterialInfo info{};
	info.id = UUID::create();

	AssetManager& assetManager = AssetManager::get_singleton();
	
	// get the material template based on the asset type and the space, if none given
	if(materialTemplate != nullptr)
	{
		info.materialTemplate = materialTemplate;
	}
	else
	{
		info.materialTemplate = get_default_material_template(assetType, space, mask);
	}

	// set the texture
	Object object{};
	object.add("texSampler", texture->get_id());
	info.values.add("texture", object);

	// create the material
	Ref<Material> material = assetManager.create<Material>(info);

	// add to default materials
	m_defaultMaterials.add(key, material);

	return material;
}

void Minty::RenderManager::refresh()
{
	MINTY_TRACE_SCOPE();

	// sync before refreshing
	sync();

	// refresh the surface
	Ref<Surface> surface = get_surface();
	if (surface != nullptr)
	{
		surface->refresh();
	}

	// recreate depth resources
	recreate_depth_resources();

	UInt2 size = surface->get_size();

	// refresh the default viewport
	Ref<Viewport> defaultViewport = get_default_viewport();
	defaultViewport->set_size(size);

	// refresh default render passes
	AssetManager& assetManager = AssetManager::get_singleton();
	for (auto const& renderPass : assetManager.get_by_type<RenderPass>())
	{
		renderPass->refresh();
	}
}

Bool Minty::RenderManager::start_frame()
{
	MINTY_TRACE_SCOPE();

	MINTY_ASSERT(m_state != State::Frame, ErrorCode::Render_AlreadyRenderingFrame);
	MINTY_ASSERT(m_state != State::Pass, ErrorCode::Render_AlreadyRenderingPass);

	// set state
	m_state = State::Frame;

	// ready to render
	return true;
}

void Minty::RenderManager::abort_frame()
{
	MINTY_ASSERT(m_state != State::Idle, ErrorCode::Render_NotRenderingFrame);
	MINTY_ASSERT(m_state != State::Pass, ErrorCode::Render_AlreadyRenderingPass);

	// reset state
	m_state = State::Idle;
}

void Minty::RenderManager::end_frame()
{
	MINTY_TRACE_SCOPE();

	MINTY_ASSERT(m_state != State::Idle, ErrorCode::Render_NotRenderingFrame);
	MINTY_ASSERT(m_state != State::Pass, ErrorCode::Render_AlreadyRenderingPass);

	// reset state
	m_state = State::Idle;
}

Bool Minty::RenderManager::start_pass(CameraData const& cameraInfo)
{
	MINTY_ASSERT(m_state != State::Idle, ErrorCode::Render_NotRenderingFrame);
	MINTY_ASSERT(m_state != State::Pass, ErrorCode::Render_AlreadyRenderingPass);

	// set state
	m_state = State::Pass;

	// clear binds
	clear_binds();

	// set camera data
	m_camera = cameraInfo.camera;
	m_cameraMatrix = cameraInfo.get_transformation_matrix();

	// bind viewport
	if (cameraInfo.viewport != nullptr)
	{
		// bind given viewport
		cameraInfo.viewport->on_bind();
	}
	else
	{
		// bind default viewport
		RenderManager::get_singleton().get_default_viewport()->on_bind();
	}

	// ready to render
	return true;
}

void Minty::RenderManager::end_pass()
{
	MINTY_ASSERT(m_state != State::Idle, ErrorCode::Render_NotRenderingFrame);
	MINTY_ASSERT(m_state != State::Frame, ErrorCode::Render_NotRenderingPass);

	// reset state
	m_state = State::Frame;
}

void Minty::RenderManager::handle_event(Event& event)
{
	if (event.get_type() == EventType::WindowResize)
	{
		// mark resize pending
		m_resizePending = true;
	}
}
