#include "pch.h"
#include "RenderManager.h"
#include "Minty/Context/Context.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Render/Camera.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Render/Shader.h"
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
	m_boundMaterial->set_input("camera", &m_cameraMatrix, sizeof(Matrix4));

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

Minty::RenderManager::RenderManager(RenderManagerBuilder const& builder)
	: m_state(State::Idle)
	, m_window(builder.window)
	, m_boundShader(nullptr)
	, m_boundMaterial(nullptr)
	, m_boundMesh(nullptr)
	, m_camera({})
	, m_cameraMatrix()
{
	// if no window given, use the Context's window
	if (m_window == nullptr)
	{
		m_window = Context::get_singleton().get_window();
	}

	MINTY_ASSERT(m_window != nullptr, "RenderManager requires a Window to render to. Provide a window in the RenderManagerBuilder, or create a Context.");
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
