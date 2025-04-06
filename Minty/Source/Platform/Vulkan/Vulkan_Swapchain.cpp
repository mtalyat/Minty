#include "pch.h"
#include "Vulkan_Swapchain.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"

using namespace Minty;

Minty::Vulkan_Swapchain::Vulkan_Swapchain(Vulkan_RenderManager& renderManager, Format const targetFormat, Vulkan_QueueFamilyIndices const& queueFamilyIndices)
	: m_swapchain(VK_NULL_HANDLE)
	, m_extent()
	, m_targetFormat(targetFormat)
	, m_index(0)
	, m_images()
{
	// get swapchain support details
	Vulkan_SwapchainSupportDetails swapchainSupport = Vulkan_Renderer::query_swapchain_support(renderManager.get_physical_device(), renderManager.get_surface());

	// get extent
	m_extent = Vulkan_Renderer::get_swapchain_extent(swapchainSupport.capabilities, renderManager.get_window());

	// get surface format
	VkSurfaceFormatKHR surfaceFormat = Vulkan_Renderer::select_swap_surface_format(swapchainSupport.formats, Vulkan_Renderer::to_vulkan(m_targetFormat));

	// get present mode
	VkPresentModeKHR presentMode = Vulkan_Renderer::select_swap_present_mode(swapchainSupport.presentModes);

	// create swapchain
	m_swapchain = Vulkan_Renderer::create_swapchain(renderManager.get_device(), renderManager.get_surface(), swapchainSupport, queueFamilyIndices, surfaceFormat, m_extent, presentMode);
}

Minty::Vulkan_Swapchain::~Vulkan_Swapchain()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	Vulkan_Renderer::destroy_swapchain(renderManager.get_device(), m_swapchain);
}
