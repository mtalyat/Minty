#include "pch.h"
#include "Vulkan_Surface.h"
#include "Minty/Asset/AssetManager.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Platform/Vulkan/Vulkan_Image.h"
#include "Minty/Render/SurfaceInfo.h"
#include "Minty/Render/ImageInfo.h"

using namespace Minty;


// special constructor to create the initial surface
Minty::Vulkan_Surface::Vulkan_Surface(SurfaceInfo const& info, VkSurfaceKHR const surface, Vulkan_RenderManager& renderManager, Vulkan_QueueFamilyIndices const& queueFamilyIndices)
	: Surface(info),
	m_surface(surface),
	m_swapchain(VK_NULL_HANDLE),
	m_extent({ 0, 0 }),
	m_format(Format::Undefined),
	m_index(0),
	m_images()
{
	initialize_swapchain(info.targetFormat, renderManager, queueFamilyIndices);
}

Minty::Vulkan_Surface::Vulkan_Surface(SurfaceInfo const& info)
	: Surface(info),
	m_surface(VK_NULL_HANDLE),
	m_swapchain(VK_NULL_HANDLE),
	m_extent({ 0, 0 }),
	m_format(Format::Undefined),
	m_index(0),
	m_images()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();

	// create the surface
	m_surface = Vulkan_Renderer::create_surface(renderManager.get_instance(), info.window);

	// get the queue family indices
	Vulkan_QueueFamilyIndices queueFamilyIndices = Vulkan_Renderer::find_queue_families(renderManager.get_physical_device(), m_surface);

	// continue
	initialize_swapchain(info.targetFormat, renderManager, queueFamilyIndices);
}

Minty::Vulkan_Surface::~Vulkan_Surface()
{
	dispose_swapchain();

	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();

	// destroy surface
	Vulkan_Renderer::destroy_surface(renderManager.get_instance(), m_surface);
}

void Minty::Vulkan_Surface::initialize_swapchain(Format const targetFormat, Vulkan_RenderManager& renderManager, Vulkan_QueueFamilyIndices const& queueFamilyIndices)
{
	// get swapchain support details
	Vulkan_SwapchainSupportDetails swapchainSupport = Vulkan_Renderer::query_swapchain_support(renderManager.get_physical_device(), m_surface);

	// get extent
	m_extent = Vulkan_Renderer::get_swapchain_extent(swapchainSupport.capabilities, renderManager.get_window());

	// get surface format
	VkSurfaceFormatKHR surfaceFormat = Vulkan_Renderer::select_swap_surface_format(swapchainSupport.formats, Vulkan_Renderer::to_vulkan(targetFormat));
	m_format = static_cast<Format>(surfaceFormat.format);

	// get present mode
	VkPresentModeKHR presentMode = Vulkan_Renderer::select_swap_present_mode(swapchainSupport.presentModes);

	// create swapchain
	m_swapchain = Vulkan_Renderer::create_swapchain(renderManager.get_device(), m_surface, swapchainSupport, queueFamilyIndices, surfaceFormat, m_extent, presentMode);

	// get the swapchain images
	Vector<VkImage> swapchainImages = Vulkan_Renderer::get_swapchain_images(renderManager.get_device(), m_swapchain);

	// create the images
	AssetManager& assetManager = AssetManager::get_singleton();
	m_images.resize(swapchainImages.get_size(), Ref<Image>());
	ImageInfo imageInfo{};
	imageInfo.aspect = ImageAspect::Color;
	imageInfo.format = m_format;
	imageInfo.immutable = true;
	imageInfo.size = get_size();
	imageInfo.tiling = ImageTiling::Optimal;
	imageInfo.type = ImageType::D2;
	imageInfo.usage = ImageUsage::Color;
	for (Size i = 0; i < m_images.get_size(); i++)
	{
		imageInfo.id = UUID::create();
		Shared<Image> vulkanImage = Shared<Vulkan_Image>::create(imageInfo, swapchainImages.at(i));
		m_images.at(i) = vulkanImage.to_ref();
		assetManager.add(vulkanImage);
		vulkanImage.release();
	}
}

void Minty::Vulkan_Surface::dispose_swapchain()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	AssetManager& assetManager = AssetManager::get_singleton();

	// unload swapchain images
	for (auto const& image : m_images)
	{
		if (image != nullptr)
		{
			assetManager.unload(image->get_id());
		}
	}
	m_images.clear();

	// destroy swapchain
	Vulkan_Renderer::destroy_swapchain(renderManager.get_device(), m_swapchain);
}

void Minty::Vulkan_Surface::refresh()
{
	MINTY_LOG_MESSAGE("Refreshing surface...");
	// recreate the swapchain
	dispose_swapchain();
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	Vulkan_QueueFamilyIndices queueFamilyIndices = Vulkan_Renderer::find_queue_families(renderManager.get_physical_device(), m_surface);
	initialize_swapchain(m_format, renderManager, queueFamilyIndices);
	MINTY_LOG_MESSAGE_F("Surface refreshed with new size: {}.", get_size());
}
