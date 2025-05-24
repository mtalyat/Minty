#include "pch.h"
#include "Vulkan_Surface.h"
#include "Minty/Asset/AssetManager.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Platform/Vulkan/Vulkan_Image.h"

using namespace Minty;


// special constructor to create the initial surface
Minty::Vulkan_Surface::Vulkan_Surface(SurfaceBuilder const& builder, VkSurfaceKHR const surface, Vulkan_RenderManager& renderManager, Vulkan_QueueFamilyIndices const& queueFamilyIndices)
	: Surface(builder),
	m_surface(surface),
	m_swapchain(VK_NULL_HANDLE),
	m_extent({ 0, 0 }),
	m_format(Format::Undefined),
	m_index(0),
	m_images()
{
	initialize_swapchain(builder.targetFormat, renderManager, queueFamilyIndices);
}

Minty::Vulkan_Surface::Vulkan_Surface(SurfaceBuilder const& builder)
	: Surface(builder),
	m_surface(VK_NULL_HANDLE),
	m_swapchain(VK_NULL_HANDLE),
	m_extent({ 0, 0 }),
	m_format(Format::Undefined),
	m_index(0),
	m_images()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();

	// create the surface
	m_surface = Vulkan_Renderer::create_surface(renderManager.get_instance(), builder.window);

	// get the queue family indices
	Vulkan_QueueFamilyIndices queueFamilyIndices = Vulkan_Renderer::find_queue_families(renderManager.get_physical_device(), m_surface);

	// continue
	initialize_swapchain(builder.targetFormat, renderManager, queueFamilyIndices);
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
	ImageBuilder imageBuilder{};
	imageBuilder.aspect = ImageAspect::Color;
	imageBuilder.format = m_format;
	imageBuilder.immutable = true;
	imageBuilder.size = get_size();
	imageBuilder.tiling = ImageTiling::Optimal;
	imageBuilder.type = ImageType::D2;
	imageBuilder.usage = ImageUsage::Color;
	for (Size i = 0; i < m_images.get_size(); i++)
	{
		imageBuilder.id = UUID::create();
		Owner<Image> vulkanImage = Owner<Vulkan_Image>(imageBuilder, swapchainImages.at(i));
		m_images.at(i) = vulkanImage.create_ref();
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
	Debug::write_message("Refreshing surface...");
	// recreate the swapchain
	dispose_swapchain();
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	Vulkan_QueueFamilyIndices queueFamilyIndices = Vulkan_Renderer::find_queue_families(renderManager.get_physical_device(), m_surface);
	initialize_swapchain(m_format, renderManager, queueFamilyIndices);
}
