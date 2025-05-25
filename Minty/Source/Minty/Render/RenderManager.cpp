#include "pch.h"
#include "RenderManager.h"
#include "Minty/Context/Context.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Render/Camera.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Render/Shader.h"
#include "Minty/Render/Texture.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#endif // MINTY_VULKAN

using namespace Minty;

Owner<RenderManager> Minty::RenderManager::create(RenderManagerBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_RenderManager>(builder);
#else
	return Owner<RenderManager>();
#endif // MINTY_VULKAN
}

RenderManager& Minty::RenderManager::get_singleton()
{
	return Context::get_singleton().get_render_manager();
}

void Minty::RenderManager::clear_binds()
{
	m_boundMesh = nullptr;
	m_boundMaterial = nullptr;
	m_boundShader = nullptr;
}

void Minty::RenderManager::bind_shader(Ref<Shader> const& shader)
{
	MINTY_ASSERT(shader != nullptr, "Cannot bind null Shader.");

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
	MINTY_ASSERT(material != nullptr, "Cannot bind null Material.");

	// do nothing if already bound
	if (m_boundMaterial == material)
	{
		return;
	}

	MINTY_ASSERT(material->get_material_template()->get_shader() == m_boundShader, "Material and Shader do not match.");

	m_boundMaterial = material;

	// set constants
	m_boundMaterial->try_set_input("camera", &m_cameraMatrix, sizeof(Matrix4));

	// bind
	m_boundMaterial->on_bind();
}

void Minty::RenderManager::bind_mesh(Ref<Mesh> const& mesh)
{
	MINTY_ASSERT(mesh != nullptr, "Cannot bind null Mesh.");

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
	MINTY_ASSERT(mesh != nullptr, "Cannot draw null Mesh.");

#if defined(MINTY_VULKAN)
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	renderManager.draw_indices(static_cast<UInt>(mesh->get_indices().get_count()));
#endif // MINTY_VULKAN
}

void Minty::RenderManager::draw_instances(UInt const instanceCount, UInt const vertexCount)
{
	MINTY_ASSERT(instanceCount > 0, "Cannot draw 0 instances.");
	MINTY_ASSERT(vertexCount > 0, "Cannot draw 0 vertices.");

#if defined(MINTY_VULKAN)
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	renderManager.draw_instances(instanceCount, vertexCount);
#endif // MINTY_VULKAN
}

Minty::RenderManager::RenderManager(RenderManagerBuilder const& builder)
	: m_state(State::Idle)
	, m_window(builder.window)
	, m_boundShader(nullptr)
	, m_boundMaterial(nullptr)
	, m_boundMesh(nullptr)
	, m_camera(nullptr)
	, m_cameraMatrix()
	, m_defaultMeshes()
{
	// if no window given, use the Context's window
	if (m_window == nullptr)
	{
		m_window = Context::get_singleton().get_window();
	}

	MINTY_ASSERT(m_window != nullptr, "RenderManager requires a Window to render to. Provide a window in the RenderManagerBuilder, or create a Context.");
}

Ref<Mesh> Minty::RenderManager::get_default_mesh(MeshType const type)
{
	MINTY_ASSERT(type != MeshType::Custom, "Cannot get default Mesh of type Custom.");

	// find the mesh
	auto found = m_defaultMeshes.find(type);
	if (found != m_defaultMeshes.end())
	{
		// already exists
		Ref<Mesh> mesh = found->get_second();
		MINTY_ASSERT(mesh != nullptr, F("Default Mesh for type {} is null.", type));
		return mesh;
	}

	// if empty
	if (type == MeshType::Empty)
	{
		return nullptr;
	}

	// create the mesh
	MeshBuilder builder{};
	builder.id = UUID::create();
	builder.type = type;
	AssetManager& assetManager = AssetManager::get_singleton();
	Ref<Mesh> mesh = assetManager.create<Mesh>(builder);
	m_defaultMeshes.add(type, mesh);

	return mesh;
}

Ref<Material> Minty::RenderManager::get_default_material(Ref<Texture> const& texture, AssetType const assetType, Space const space)
{
	MINTY_ASSERT(texture != nullptr, "Cannot get default Material with null Texture.");
	
	TexMatKey key = create_texmat_key(assetType, space);

	auto found = m_defaultMaterials.find(key);
	if (found != m_defaultMaterials.end())
	{
		// return existing Material
		Ref<Material> material = found->get_second();
		MINTY_ASSERT(material != nullptr, F("Default Material for type {} and space {} is null.", assetType, space));
		return material;
	}

	// create new Material
	MaterialBuilder builder{};
	builder.id = UUID::create();

	UUID templateId;

	// get the material template based on the asset type and the space
	switch (assetType)
	{
	case AssetType::Sprite:
		switch (space)
		{
		case Space::D3:
			templateId = DEFAULT_ASSET_SPRITE_MATERIAL_TEMPLATE;
			break;
		case Space::UI:
			templateId = DEFAULT_ASSET_UI_MATERIAL_TEMPLATE;
			break;
		default:
			MINTY_ABORT(F("Invalid Space for Sprite: {}", space));
			break;
		}
		break;
	case AssetType::FontVariant:
		switch (space)
		{
		case Space::UI:
			templateId = DEFAULT_ASSET_TEXT_MATERIAL_TEMPLATE;
			break;
		default:
			MINTY_ERROR(F("Invalid Space for AssetType FontVariant: \"{}\".", to_string(space)));
			break;
		}
		break;
	default:
		MINTY_ABORT(F("Cannot create a default Mesh for the type \"{}\".", to_string(assetType)));
		break;
	}
	AssetManager& assetManager = AssetManager::get_singleton();
	builder.materialTemplate = assetManager.get<MaterialTemplate>(templateId);
	MINTY_ASSERT(builder.materialTemplate != nullptr, F("Default MaterialTemplate for type {} and space {} is not loaded ({}).", assetType, space, templateId));

	// set the texture
	Object object{};
	object.add("texSampler", texture->get_id());
	builder.values.add("texture", object);

	// create the material
	Ref<Material> material = assetManager.create<Material>(builder);

	// add to default materials
	m_defaultMaterials.add(key, material);

	return material;
}

Bool Minty::RenderManager::start_frame()
{
	MINTY_ASSERT(m_state != State::Frame, "Attempting to start a frame while already rendering a frame.");
	MINTY_ASSERT(m_state != State::Pass, "Attempting to start a frame while rendering a pass. End the pass and frame first.");

	// set state
	m_state = State::Frame;

	// ready to render
	return true;
}

void Minty::RenderManager::end_frame()
{
	MINTY_ASSERT(m_state != State::Idle, "Attempting to end a frame while not rendering a frame.");
	MINTY_ASSERT(m_state != State::Pass, "Attempting to end a frame while rendering a pass. End the pass first.");

	// reset state
	m_state = State::Idle;
}

Bool Minty::RenderManager::start_pass(CameraInfo const& cameraInfo)
{
	MINTY_ASSERT(m_state != State::Idle, "Attempting to start a pass while not rendering a frame.");
	MINTY_ASSERT(m_state != State::Pass, "Attempting to start a pass while already rendering a pass.");

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
	MINTY_ASSERT(m_state != State::Idle, "Attempting to end a pass while not rendering a frame.");
	MINTY_ASSERT(m_state != State::Frame, "Attempting to end a pass while not rendering a pass.");

	// reset state
	m_state = State::Frame;
}
