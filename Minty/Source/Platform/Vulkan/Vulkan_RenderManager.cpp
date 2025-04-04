#include "pch.h"
#include "Vulkan_RenderManager.h"
#include "Vulkan_Renderer.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Vector.h"
#include "Minty/Debug/Debug.h"

using namespace Minty;

Minty::Vulkan_RenderManager::Vulkan_RenderManager(RenderManagerBuilder const& builder)
	: RenderManager(builder)
	, m_instance(VK_NULL_HANDLE)
#ifdef MINTY_DEBUG
	, m_debugMessenger(VK_NULL_HANDLE)
#endif // MINTY_DEBUG
	, m_surface(VK_NULL_HANDLE)
	, m_physicalDevice(VK_NULL_HANDLE)
	, m_device(VK_NULL_HANDLE)
	, m_graphicsQueue(VK_NULL_HANDLE)
	, m_presentQueue(VK_NULL_HANDLE)
	, m_commandPool(VK_NULL_HANDLE)
{
	// create instance
	m_instance = Vulkan_Renderer::create_instance();

	// set up debugging
#ifdef MINTY_DEBUG
	m_debugMessenger = Vulkan_Renderer::create_debug_messenger(m_instance);
#endif // MINTY_DEBUG

	// create surface
	m_surface = Vulkan_Renderer::create_surface(m_instance, builder.window);

	// get physical device
	m_physicalDevice = Vulkan_Renderer::select_physical_device(m_instance, m_surface);

	// get queue families
	Vulkan_Renderer::QueueFamilyIndices queueFamilyIndices = Vulkan_Renderer::find_queue_families(m_physicalDevice, m_surface);

	// create device
	m_device = Vulkan_Renderer::create_device(m_physicalDevice, queueFamilyIndices);

	// get queues
	m_graphicsQueue = Vulkan_Renderer::get_device_queue(m_device, queueFamilyIndices.graphicsFamily.value());
	m_presentQueue = Vulkan_Renderer::get_device_queue(m_device, queueFamilyIndices.presentFamily.value());

	// create command pool
	m_commandPool = Vulkan_Renderer::create_command_pool(m_device, queueFamilyIndices.graphicsFamily.value());

	// TODO: finish initialization
}

Minty::Vulkan_RenderManager::~Vulkan_RenderManager()
{
	Vulkan_Renderer::destroy_instance(m_instance);
}

Bool Minty::Vulkan_RenderManager::start_frame()
{
	MINTY_ASSERT(false, "Not implemented.");
	return Bool();
}

void Minty::Vulkan_RenderManager::end_frame()
{
	MINTY_ASSERT(false, "Not implemented.");
}
