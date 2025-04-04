#include "pch.h"
#include "Vulkan_Renderer.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Array.h"
#include "Minty/Data/Set.h"
#include <map>

using namespace Minty;

#pragma region Utility

#ifdef MINTY_DEBUG
#define VK_ASSERT_RESULT(operation, message) do { VkResult result = (operation); if (result != VK_SUCCESS) { MINTY_ABORT(message); }} while (false)
#define VK_ASSERT_RESULT_RETURN_OBJECT(objectType, functionCall, message) do { objectType object = VK_NULL_HANDLE; VK_ASSERT_RESULT((functionCall), (message)); return object; } while (false)
#define VK_ASSERT_ABORT(message) do { MINTY_ABORT(message); } while (false)
#else // MINTY_RELEASE
#define VK_ASSERT_RESULT(operation, message) operation
#define VK_ASSERT_RESULT_RETURN_OBJECT(objectType, functionCall, message) do { objectType object = VK_NULL_HANDLE; functionCall; return object; } while (false)
#define VK_ASSERT_ABORT(message) MINTY_ABORT(message)
#endif // MINTY_DEBUG

#pragma region Extensions

static const Vector<Char const*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

static Vector<Char const*> get_required_extensions()
{
	uint32_t glfwExtensionCount = 0;
	Char const** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	uint32_t listSize = glfwExtensionCount;

#ifdef MINTY_DEBUG
	listSize++;
#endif // MINTY_DEBUG

	Vector<Char const*> extensions(listSize);
	for (Size i = 0; i < glfwExtensionCount; i++)
	{
		extensions.add(glfwExtensions[i]);
	}

#ifdef MINTY_DEBUG
	extensions.add(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif // MINTY_DEBUG

	return extensions;
}

#pragma endregion

#pragma region Validation Layers

static const Vector<Char const*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

#ifdef MINTY_DEBUG

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	Char const* message = pCallbackData->pMessage;

	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		Debug::write_error(message);
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		Debug::write_warning(message);
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
	{
		Debug::write_message(message);
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
	{
		Debug::write_info(message);
	}

	return VK_FALSE;
}

static Bool check_validation_layer_support()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	Vector<VkLayerProperties> availableLayers;
	availableLayers.resize(layerCount, VkLayerProperties{});
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.get_data());

	// validate that each layer we want exists
	for (const char* layerName : validationLayers)
	{
		Bool layerFound = false;

		for (auto const& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			return false;
		}
	}

	return true;
}

static void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
{
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
}

static VkResult create_debug_utils_messenger_ext(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr)
	{
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

static void destroy_debug_utils_messenger_ext(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr)
	{
		func(instance, debugMessenger, pAllocator);
	}
}

#endif // MINTY_DEBUG

#pragma endregion

#pragma endregion

VkInstance Minty::Vulkan_Renderer::create_instance()
{
	// application info
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Minty Application";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = MINTY_NAME;
	appInfo.engineVersion = MINTY_VERSION;
	appInfo.apiVersion = VK_API_VERSION_1_2;

	// instance
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	// extensions
	Vector<Char const*> extensions = get_required_extensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.get_size());
	createInfo.ppEnabledExtensionNames = extensions.get_data();

	// validation layers
#ifdef MINTY_DEBUG
	MINTY_ASSERT(check_validation_layer_support(), "Validation layers requested, but not available.");
	createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.get_size());
	createInfo.ppEnabledLayerNames = validationLayers.get_data();
#else
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;
#endif // MINTY_DEBUG

	VK_ASSERT_RESULT_RETURN_OBJECT(VkInstance, vkCreateInstance(&createInfo, nullptr, &object), "Failed to create get_singleton.");
}

void Minty::Vulkan_Renderer::destroy_instance(VkInstance const instance)
{
	vkDestroyInstance(instance, nullptr);
}

VkDebugUtilsMessengerEXT Minty::Vulkan_Renderer::create_debug_messenger(VkInstance const instance)
{
#ifdef MINTY_DEBUG
	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	populate_debug_messenger_create_info(createInfo);

	VK_ASSERT_RESULT_RETURN_OBJECT(VkDebugUtilsMessengerEXT, create_debug_utils_messenger_ext(instance, &createInfo, nullptr, &object), "Failed to set up debug messenger.");
#else
	return VK_NULL_HANDLE;
#endif // MINTY_DEBUG
}

void Minty::Vulkan_Renderer::destroy_debug_messenger(VkInstance const instance, VkDebugUtilsMessengerEXT const debugMessenger)
{
#ifdef MINTY_DEBUG
	destroy_debug_utils_messenger_ext(instance, debugMessenger, nullptr);
#endif // MINTY_DEBUG
}

VkSurfaceKHR Minty::Vulkan_Renderer::create_surface(VkInstance const instance, Ref<Window> const window)
{
	VK_ASSERT_RESULT_RETURN_OBJECT(VkSurfaceKHR, glfwCreateWindowSurface(instance, static_cast<GLFWwindow*>(window->get_native()), nullptr, &object), "Failed to create window surface.");
}

void Minty::Vulkan_Renderer::destroy_surface(VkInstance const instance, VkSurfaceKHR const surface)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}

static Bool check_device_extension_support(VkPhysicalDevice const physicalDevice)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

	Vector<VkExtensionProperties> availableExtensions;
	availableExtensions.resize(extensionCount, VkExtensionProperties{});
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.get_data());

	Set<String> requiredExtensions;
	requiredExtensions.add(deviceExtensions.begin(), deviceExtensions.end());

	for (auto const& extension : availableExtensions)
	{
		requiredExtensions.remove(extension.extensionName);
	}

	return requiredExtensions.is_empty();
}

int Minty::Vulkan_Renderer::rate_device_suitability(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface)
{
	// check if device queues can handle what we want
	QueueFamilyIndices queueFamilyIndices = find_queue_families(physicalDevice, surface);
	if (!queueFamilyIndices.is_complete())
	{
		return 0;
	}

	// check if device supports extensions (needed for rendering to a window surface)
	Bool extensionsSupported = check_device_extension_support(physicalDevice);
	if (!extensionsSupported)
	{
		return 0;
	}

	// check if swap chains will work
	SwapChainSupportDetails swapChainSupport = query_swap_chain_support(physicalDevice, surface);
	if (swapChainSupport.formats.is_empty() || swapChainSupport.presentModes.is_empty())
	{
		return 0;
	}

	// check for sampler anisotropy
	VkPhysicalDeviceFeatures supportedFeatures;
	vkGetPhysicalDeviceFeatures(physicalDevice, &supportedFeatures);
	if (!supportedFeatures.samplerAnisotropy)
	{
		return 0;
	}

	// anything works for now
	return 1;

#ifdef MINTY_KEEP

	//VkPhysicalDeviceProperties deviceProperties;
	//vkGetPhysicalDeviceProperties(device, &deviceProperties);

	//VkPhysicalDeviceFeatures deviceFeatures;
	//vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	//int score = 0;

	//// Discrete GPUs have a significant performance advantage
	//if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
	//    score += 1000;
	//}

	//// Maximum possible size of textures affects graphics quality
	//score += deviceProperties.limits.maxImageDimension2D;

	//// Application can't function without geometry shaders
	//if (!deviceFeatures.geometryShader) {
	//    return 0;
	//}

	//return score;

#endif // MINTY_KEEP
}

VkPhysicalDevice Minty::Vulkan_Renderer::select_physical_device(VkInstance const instance, VkSurfaceKHR const surface, Function<int(VkPhysicalDevice, VkSurfaceKHR)> const& ratingFunction)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		VK_ASSERT_ABORT("Failed to find GPUs with Vulkan support.");
	}

	Vector<VkPhysicalDevice> devices;
	devices.resize(deviceCount, VK_NULL_HANDLE);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.get_data());

	// get best device
	std::multimap<int, VkPhysicalDevice> candidates;
	for (VkPhysicalDevice device : devices)
	{
		int score = rate_device_suitability(device, surface);
		candidates.insert(std::make_pair(score, device));
	}

	// get first device, if it is suitable
	if (candidates.rbegin()->first > 0)
	{
		return candidates.rbegin()->second;
	}
	else
	{
		VK_ASSERT_ABORT("Failed to find a suitable GPU.");
	}
}

Vulkan_Renderer::SwapChainSupportDetails Minty::Vulkan_Renderer::query_swap_chain_support(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface)
{
	SwapChainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

	if (formatCount != 0)
	{
		details.formats.resize(formatCount, VkSurfaceFormatKHR{});
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.get_data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0)
	{
		details.presentModes.resize(presentModeCount, VkPresentModeKHR{});
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.get_data());
	}

	return details;
}

VkSurfaceFormatKHR Minty::Vulkan_Renderer::select_swap_surface_format(Vector<VkSurfaceFormatKHR> const& availableFormats, VkFormat const format, VkColorSpaceKHR const colorSpace)
{
	for (auto const& availableFormat : availableFormats)
	{
		if (availableFormat.format == format && availableFormat.colorSpace == colorSpace)
		{
			return availableFormat;
		}
	}

	return availableFormats.front();
}

VkExtent2D Minty::Vulkan_Renderer::select_swap_extent(VkSurfaceCapabilitiesKHR const& capabilities, Ref<Window> const& window)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		// extent has been initialized, use it
		return capabilities.currentExtent;
	}

	// create new extent from window size
	int width, height;
	glfwGetFramebufferSize(static_cast<GLFWwindow*>(window->get_native()), &width, &height);

	VkExtent2D actualExtent =
	{
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height)
	};

	actualExtent.width = Math::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
	actualExtent.height = Math::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

	return actualExtent;
}

VkPresentModeKHR Minty::Vulkan_Renderer::select_swap_present_mode(Vector<VkPresentModeKHR> const& availablePresentModes, VkPresentModeKHR const presentMode)
{
	for (auto const& availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == presentMode)
		{
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkFormat Minty::Vulkan_Renderer::find_supported_format(VkPhysicalDevice const physicalDevice, Vector<VkFormat> const& candidates, VkImageTiling const tiling, VkFormatFeatureFlags const features)
{
	for (VkFormat format : candidates) {
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
			return format;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
			return format;
		}
	}

	VK_ASSERT_ABORT("Failed to find supported depthFormat.");
}

VkFormat Minty::Vulkan_Renderer::find_supported_depth_format(VkPhysicalDevice const physicalDevice)
{
	return find_supported_format(physicalDevice,
		{ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	);
}

Vulkan_Renderer::QueueFamilyIndices Minty::Vulkan_Renderer::find_queue_families(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface)
{
	QueueFamilyIndices queueFamilyIndices{};

	// get number of queue families
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	// get queue families
	Vector<VkQueueFamilyProperties> queueFamilies;
	queueFamilies.resize(queueFamilyCount, VkQueueFamilyProperties{});
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.get_data());

	// find queue families
	uint32_t i = 0;
	for (auto const& queueFamily : queueFamilies)
	{
		// check graphics family
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			queueFamilyIndices.graphicsFamily = i;
		}

		// check present family
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);
		if (presentSupport)
		{
			queueFamilyIndices.presentFamily = i;
		}

		// if all found, quit looking
		if (queueFamilyIndices.is_complete())
		{
			break;
		}

		i++;
	}

	return queueFamilyIndices;
}

VkDevice Minty::Vulkan_Renderer::create_device(VkPhysicalDevice const physicalDevice, QueueFamilyIndices const& queueFamilyIndices)
{
	// create all the queues needed for operations, based on the families
	Vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	Set<uint32_t> uniqueQueueFamilies = { queueFamilyIndices.graphicsFamily.value(), queueFamilyIndices.presentFamily.value() };

	float queuePriority = 1.0f;
	for (const uint32_t queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.add(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};
	deviceFeatures.samplerAnisotropy = VK_TRUE;

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.get_size());
	createInfo.pQueueCreateInfos = queueCreateInfos.get_data();
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.get_size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.get_data();

#ifdef MINTY_DEBUG
	// tie in validation layers
	createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.get_size());
	createInfo.ppEnabledLayerNames = validationLayers.get_data();
#else
	createInfo.enabledLayerCount = 0;
#endif // MINTY_DEBUG

	VK_ASSERT_RESULT_RETURN_OBJECT(VkDevice, vkCreateDevice(physicalDevice, &createInfo, nullptr, &object), "Failed to create logical device.");
}

void Minty::Vulkan_Renderer::destroy_device(VkDevice const device)
{
	vkDestroyDevice(device, nullptr);
}

void Minty::Vulkan_Renderer::sync_device(VkDevice const device)
{
	vkDeviceWaitIdle(device);
}

VkQueue Minty::Vulkan_Renderer::get_device_queue(VkDevice const device, const uint32_t index)
{
	VkQueue queue;
	vkGetDeviceQueue(device, index, 0, &queue);
	return queue;
}

VkSwapchainKHR Minty::Vulkan_Renderer::create_swapchain(VkDevice const device, VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface, SwapChainSupportDetails const& swapchainSupport, QueueFamilyIndices const& queueFamilyIndices, VkSurfaceFormatKHR const surfaceFormat, VkExtent2D const extent, VkPresentModeKHR const presentMode)
{
	// images in the swapchain
	uint32_t imageCount = swapchainSupport.capabilities.minImageCount + 1;

	// limit image count
	if (swapchainSupport.capabilities.maxImageCount > 0 && imageCount > swapchainSupport.capabilities.maxImageCount)
	{
		imageCount = swapchainSupport.capabilities.maxImageCount;
	}

	// create the swap chain
	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;

	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	uint32_t queueFamilyIndicesBuffer[] = { queueFamilyIndices.graphicsFamily.value(), queueFamilyIndices.presentFamily.value() };

	if (queueFamilyIndices.graphicsFamily != queueFamilyIndices.presentFamily)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndicesBuffer;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
	}

	// specify if a transform is to be made (ex. 90 degree rotation)
	createInfo.preTransform = swapchainSupport.capabilities.currentTransform;

	// if this window should blend with other windows
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	// enable clipping, in case another window is in front of this one
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;

	// come back to this
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkSwapchainKHR, vkCreateSwapchainKHR(device, &createInfo, nullptr, &object), "Failed to create swap chain.");
}

void Minty::Vulkan_Renderer::destroy_swapchain(VkDevice const device, VkSwapchainKHR const swapchain)
{
	vkDestroySwapchainKHR(device, swapchain, nullptr);
}

Vector<VkImage> Minty::Vulkan_Renderer::get_swapchain_images(VkDevice const device, VkSwapchainKHR const swapchain)
{
	Vector<VkImage> images;
	uint32_t imageCount;

	vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
	images.resize(imageCount, VK_NULL_HANDLE);
	vkGetSwapchainImagesKHR(device, swapchain, &imageCount, images.get_data());

	return images;
}

VkResult Minty::Vulkan_Renderer::get_next_swapchain_image_index(VkDevice const device, VkSwapchainKHR const swapchain, VkSemaphore const waitSemaphore, uint32_t& index)
{
	VkResult result = vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, waitSemaphore, VK_NULL_HANDLE, &index);

	// if not a success and not suboptimal, error
	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		VK_ASSERT_ABORT("Failed to acquire swap chain image.");
	}

	return result;
}

uint32_t Minty::Vulkan_Renderer::find_memory_type(VkPhysicalDevice const physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	// get physical device memory properties
	VkPhysicalDeviceMemoryProperties memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

	// find memory that is suitable for a buffer
	// also find memory find memory with the given specific properties
	for (uint32_t i = 0; memoryProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}

	MINTY_ABORT("Failed to find suitable memory type.");
	return 0;
}

VkDeviceMemory Minty::Vulkan_Renderer::allocate_memory(VkDevice const device, VkDeviceSize const size, const uint32_t memoryTypeIndex)
{
	VkMemoryAllocateInfo allocateInfo{};
	allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocateInfo.allocationSize = size;
	allocateInfo.memoryTypeIndex = memoryTypeIndex;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkDeviceMemory, vkAllocateMemory(device, &allocateInfo, nullptr, &object), "Failed to allocate buffer memory.");
}

void Minty::Vulkan_Renderer::free_memory(VkDevice const device, VkDeviceMemory const memory)
{
	vkFreeMemory(device, memory, nullptr);
}

void* Minty::Vulkan_Renderer::map_memory(VkDevice const device, VkDeviceMemory const memory, VkDeviceSize const offset, VkDeviceSize const size)
{
	VK_ASSERT_RESULT_RETURN_OBJECT(void*, vkMapMemory(device, memory, offset, size, 0, &object), "Failed to map memory.");
}

void Minty::Vulkan_Renderer::unmap_memory(VkDevice const device, VkDeviceMemory const memory)
{
	vkUnmapMemory(device, memory);
}

VkImage Minty::Vulkan_Renderer::create_image(VkDevice const device, const uint32_t width, const uint32_t height, VkImageType const type, VkFormat const format, VkImageTiling const tiling, VkImageUsageFlags const usage)
{
	// create image from builder
	VkImageCreateInfo imageInfo{};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = type;
	imageInfo.extent.width = width;
	imageInfo.extent.height = height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = format;
	imageInfo.tiling = tiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	imageInfo.usage = usage;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.flags = 0;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkImage, vkCreateImage(device, &imageInfo, nullptr, &object), "Failed to create image.");
}

void Minty::Vulkan_Renderer::destroy_image(VkDevice const device, VkImage const image)
{
	vkDestroyImage(device, image, nullptr);
}

VkDeviceMemory Minty::Vulkan_Renderer::allocate_image_memory(VkDevice const device, VkPhysicalDevice const physicalDevice, VkImage const image, VkMemoryPropertyFlags const memoryProperties)
{
	// get requirements for the image
	VkMemoryRequirements memoryRequirements;
	vkGetImageMemoryRequirements(device, image, &memoryRequirements);

	// allocate the memory
	return allocate_memory(device, memoryRequirements.size, find_memory_type(physicalDevice, memoryRequirements.memoryTypeBits, memoryProperties));
}

void Minty::Vulkan_Renderer::bind_image_memory(VkDevice const device, VkImage const image, VkDeviceMemory const memory)
{
	VK_ASSERT_RESULT(vkBindImageMemory(device, image, memory, 0), "Failed to bind image memory.");
}

VkImageView Minty::Vulkan_Renderer::create_image_view(VkDevice const device, VkImage const image, VkFormat const format, VkImageAspectFlags const aspectFlags, VkImageViewType const viewType)
{
	VkImageViewCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	createInfo.image = image;
	createInfo.viewType = viewType;
	createInfo.format = format;

	// move the channels around, if needed
	createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

	createInfo.subresourceRange.aspectMask = aspectFlags;
	createInfo.subresourceRange.baseMipLevel = 0;
	createInfo.subresourceRange.levelCount = 1;
	createInfo.subresourceRange.baseArrayLayer = 0;
	createInfo.subresourceRange.layerCount = 1;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkImageView, vkCreateImageView(device, &createInfo, nullptr, &object), "Failed to create image view.");
}

void Minty::Vulkan_Renderer::destroy_image_view(VkDevice const device, VkImageView const imageView)
{
	vkDestroyImageView(device, imageView, nullptr);
}

VkSampler Minty::Vulkan_Renderer::create_sampler(VkDevice const device, VkFilter const magFilter, VkFilter const minFilter, VkSamplerAddressMode const addressMode, VkBorderColor const borderColor, Bool const normalizedCoordinates)
{
	VkSamplerCreateInfo samplerInfo{};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;

	// what to do when image is too close
	samplerInfo.magFilter = magFilter;

	// what to do when image is too far
	samplerInfo.minFilter = minFilter;

	// what to do when sampling outside of image
	samplerInfo.addressModeU = addressMode;
	samplerInfo.addressModeV = addressMode;
	samplerInfo.addressModeW = addressMode;

#ifdef MINTY_KEEP
	// limit the number of samples that can be used
	VkPhysicalDeviceProperties properties{};
	vkGetPhysicalDeviceProperties(s_physicalDevice, &properties);
	samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
#endif // MINTY_KEEP

	samplerInfo.anisotropyEnable = VK_FALSE;
	samplerInfo.maxAnisotropy = 1.0f;

	// set border color, if clamping
	samplerInfo.borderColor = borderColor;

	// use pixel coordinates instead of normalized?
	samplerInfo.unnormalizedCoordinates = !normalizedCoordinates;

	// when true, it samples an area instead of a pixel
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

	// mipmapping
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 0.0f;

	// create sampler
	VK_ASSERT_RESULT_RETURN_OBJECT(VkSampler, vkCreateSampler(device, &samplerInfo, nullptr, &object), "Failed to create image sampler.");
}

void Minty::Vulkan_Renderer::destroy_sampler(VkDevice const device, VkSampler const sampler)
{
	vkDestroySampler(device, sampler, nullptr);
}

Bool Minty::Vulkan_Renderer::has_stencil_component(VkFormat const format)
{
	return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}

VkShaderModule Minty::Vulkan_Renderer::create_shader_module(VkDevice const device, void const* const data, Size const size)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(data != nullptr, "Data is null.");
	MINTY_ASSERT(size > 0, "Size is zero.");

	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = size;
	createInfo.pCode = reinterpret_cast<const uint32_t*>(data);

	VK_ASSERT_RESULT_RETURN_OBJECT(VkShaderModule, vkCreateShaderModule(device, &createInfo, nullptr, &object), "Failed to create shader module.");
}

void Minty::Vulkan_Renderer::destroy_shader_module(VkDevice const device, VkShaderModule const shaderModule)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(shaderModule != VK_NULL_HANDLE, "Shader module is null.");

	vkDestroyShaderModule(device, shaderModule, nullptr);
}

VkRenderPass Minty::Vulkan_Renderer::create_render_pass(VkDevice const device, VkAttachmentDescription const* const colorAttachment, VkAttachmentDescription const* const depthAttachment)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");

	Vector<VkAttachmentDescription> attachments;
	attachments.reserve(2);
	Array<VkAttachmentReference, 2> attachmentRefs = {};

	if (colorAttachment)
	{
		attachmentRefs[0].attachment = static_cast<uint32_t>(attachments.get_size());
		attachmentRefs[0].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		attachments.add(*colorAttachment);
	}

	if (depthAttachment)
	{
		attachmentRefs[1].attachment = static_cast<uint32_t>(attachments.get_size());
		attachmentRefs[1].layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		attachments.add(*depthAttachment);
	}

	// subpass
	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 0;
	subpass.pColorAttachments = nullptr;
	subpass.pDepthStencilAttachment = nullptr;

	// behave differently based on attachments
	if (colorAttachment)
	{
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &attachmentRefs[0];
	}

	if (depthAttachment)
	{
		subpass.pDepthStencilAttachment = &attachmentRefs[1];
	}

	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.get_size());
	renderPassInfo.pAttachments = attachments.get_data();
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 0;
	renderPassInfo.pDependencies = nullptr;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkRenderPass, vkCreateRenderPass(device, &renderPassInfo, nullptr, &object), "Failed to create render pass.");
}

void Minty::Vulkan_Renderer::destroy_render_pass(VkDevice const device, VkRenderPass const renderPass)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(renderPass != VK_NULL_HANDLE, "Render pass is null.");

	vkDestroyRenderPass(device, renderPass, nullptr);
}

VkFramebuffer Minty::Vulkan_Renderer::create_framebuffer(VkDevice const device, VkRenderPass const renderPass, VkExtent2D const extent, VkImageView const colorAttachment, VkImageView const depthAttachment)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(renderPass != VK_NULL_HANDLE, "Render pass is null.");

	Vector<VkImageView> attachments;
	attachments.reserve(2);

	if (colorAttachment != VK_NULL_HANDLE)
	{
		attachments.add(colorAttachment);
	}
	if (depthAttachment != VK_NULL_HANDLE)
	{
		attachments.add(depthAttachment);
	}

	VkFramebufferCreateInfo framebufferInfo{};
	framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferInfo.renderPass = renderPass;
	framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.get_size());
	framebufferInfo.pAttachments = attachments.get_data();
	framebufferInfo.width = extent.width;
	framebufferInfo.height = extent.height;
	framebufferInfo.layers = 1;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkFramebuffer, vkCreateFramebuffer(device, &framebufferInfo, nullptr, &object), "Failed to create framebuffer.");
}

void Minty::Vulkan_Renderer::destroy_framebuffer(VkDevice const device, VkFramebuffer const framebuffer)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(framebuffer != VK_NULL_HANDLE, "Framebuffer is null.");

	vkDestroyFramebuffer(device, framebuffer, nullptr);
}

VkCommandPool Minty::Vulkan_Renderer::create_command_pool(VkDevice const device, const uint32_t queueFamilyIndex)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndex;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkCommandPool, vkCreateCommandPool(device, &poolInfo, nullptr, &object), "Failed to create command pool.");
}

void Minty::Vulkan_Renderer::destroy_command_pool(VkDevice const device, VkCommandPool const pool)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(pool != VK_NULL_HANDLE, "Command pool is null.");

	vkDestroyCommandPool(device, pool, nullptr);
}

VkCommandBuffer Minty::Vulkan_Renderer::create_command_buffer(VkDevice const device, VkCommandPool const commandPool)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(commandPool != VK_NULL_HANDLE, "Command pool is null.");

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkCommandBuffer, vkAllocateCommandBuffers(device, &allocInfo, &object), "Failed to allocate command buffers.");
}

void Minty::Vulkan_Renderer::destroy_command_buffer(VkDevice const device, VkCommandPool const commandPool, VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(commandPool != VK_NULL_HANDLE, "Command pool is null.");
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");

	vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

void Minty::Vulkan_Renderer::begin_command_buffer(VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	VK_ASSERT_RESULT(vkBeginCommandBuffer(commandBuffer, &beginInfo), "Failed to begin recording command buffer.");
}

void Minty::Vulkan_Renderer::begin_command_buffer_temp(VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	VK_ASSERT_RESULT(vkBeginCommandBuffer(commandBuffer, &beginInfo), "Failed to begin recording temp command buffer.");
}

void Minty::Vulkan_Renderer::end_command_buffer(VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");

	VK_ASSERT_RESULT(vkEndCommandBuffer(commandBuffer), "Failed to record command buffer.");
}

VkCommandBuffer Minty::Vulkan_Renderer::start_command_buffer_single(VkDevice const device, VkCommandPool const commandPool)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(commandPool != VK_NULL_HANDLE, "Command pool is null.");

	VkCommandBuffer commandBuffer = create_command_buffer(device, commandPool);

	begin_command_buffer_temp(commandBuffer);

	return commandBuffer;
}

void Minty::Vulkan_Renderer::finish_command_buffer_single(VkDevice const device, VkCommandPool const commandPool, VkCommandBuffer const commandBuffer, VkQueue const queue)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(commandPool != VK_NULL_HANDLE, "Command pool is null.");
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(queue != VK_NULL_HANDLE, "Queue is null.");

	end_command_buffer(commandBuffer);
}

void Minty::Vulkan_Renderer::reset_command_buffer(VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");

	VK_ASSERT_RESULT(vkResetCommandBuffer(commandBuffer, 0), "Failed to reset command buffer.");
}

void Minty::Vulkan_Renderer::submit_command_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue, VkSemaphore const waitSemaphore, VkSemaphore const signalSemaphore, VkFence const inFlightFence)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(queue != VK_NULL_HANDLE, "Queue is null.");

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { waitSemaphore };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	VkSemaphore signalSemaphores[] = { signalSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	VK_ASSERT_RESULT(vkQueueSubmit(queue, 1, &submitInfo, inFlightFence), "Failed to submit draw command buffer.");
}

void Minty::Vulkan_Renderer::submit_command_buffer(VkCommandBuffer const commandBuffer, Frame const& frame, VkQueue const queue)
{
	submit_command_buffer(commandBuffer, queue, frame.imageAvailableSemaphore, frame.renderFinishedSemaphore, frame.inFlightFence);
}

void Minty::Vulkan_Renderer::submit_command_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(queue != VK_NULL_HANDLE, "Queue is null.");

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	VK_ASSERT_RESULT(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE), "Failed to submit command buffer.");
}

void Minty::Vulkan_Renderer::begin_render_pass(VkCommandBuffer const commandBuffer, VkRenderPass const renderPass, VkFramebuffer const framebuffer, VkRect2D const renderArea, VkClearColorValue const clearColor)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(renderPass != VK_NULL_HANDLE, "Render pass is null.");
	MINTY_ASSERT(framebuffer != VK_NULL_HANDLE, "Framebuffer is null.");

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass;
	renderPassInfo.framebuffer = framebuffer;

	// determine where to draw_vertices
	// keep same as viewport for efficiency
	renderPassInfo.renderArea = renderArea;

	// clear color to cover last frame
	Array<VkClearValue, 2> clearValues{};
	clearValues[0].color = clearColor;
	clearValues[1].depthStencil = { 1.0f, 0 };
	renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.get_size());
	renderPassInfo.pClearValues = clearValues.get_data();

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void Minty::Vulkan_Renderer::end_render_pass(VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");

	vkCmdEndRenderPass(commandBuffer);
}

void Minty::Vulkan_Renderer::bind_pipeline(VkCommandBuffer const commandBuffer, VkPipeline const graphicsPipeline, VkPipelineBindPoint const bindPoint)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(graphicsPipeline != VK_NULL_HANDLE, "Graphics pipeline is null.");

	vkCmdBindPipeline(commandBuffer, bindPoint, graphicsPipeline);
}

void Minty::Vulkan_Renderer::bind_descriptor_set(VkCommandBuffer const commandBuffer, VkPipelineLayout const graphicsPipelineLayout, VkDescriptorSet const descriptorSet, VkPipelineBindPoint const bindPoint)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(graphicsPipelineLayout != VK_NULL_HANDLE, "Graphics pipeline layout is null.");
	MINTY_ASSERT(descriptorSet != VK_NULL_HANDLE, "Descriptor set is null.");

	vkCmdBindDescriptorSets(commandBuffer, bindPoint, graphicsPipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
}

void Minty::Vulkan_Renderer::bind_viewport(VkCommandBuffer const commandBuffer, VkViewport const& viewport)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");

	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
}

void Minty::Vulkan_Renderer::bind_scissor(VkCommandBuffer const commandBuffer, VkRect2D const& scissor)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");

	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void Minty::Vulkan_Renderer::bind_vertex_buffer(VkCommandBuffer const commandBuffer, VkBuffer const buffer, uint32_t const binding)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(buffer != VK_NULL_HANDLE, "Buffer is null.");

	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, binding, 1, &buffer, &offset);
}

void Minty::Vulkan_Renderer::bind_index_buffer(VkCommandBuffer const commandBuffer, VkBuffer const buffer, VkIndexType const indexType)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(buffer != VK_NULL_HANDLE, "Buffer is null.");

	vkCmdBindIndexBuffer(commandBuffer, buffer, 0, indexType);
}

void Minty::Vulkan_Renderer::draw(VkCommandBuffer const commandBuffer, uint32_t const vertexCount, uint32_t const instanceCount)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");

	vkCmdDraw(commandBuffer, vertexCount, instanceCount, 0, 0);
}

void Minty::Vulkan_Renderer::draw_indexed(VkCommandBuffer const commandBuffer, uint32_t const indexCount, uint32_t const instanceCount)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");

	vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, 0, 0, 0);
}

void Minty::Vulkan_Renderer::transition_image_layout(VkCommandBuffer const commandBuffer, VkImage const image, VkFormat const format, VkImageLayout const oldLayout, VkImageLayout const newLayout)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(image != VK_NULL_HANDLE, "Image is null.");

	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = oldLayout;
	barrier.newLayout = newLayout;

	// set if transfering queues
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

	// affected part of image
	barrier.image = image;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	// determine when the transfer can be conducted based on its layout
	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;
	if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
	{
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

		sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
	{
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	}
	else
	{
		MINTY_ABORT("Unsupported layout transition.");
	}

	vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
}

void Minty::Vulkan_Renderer::copy_buffer_to_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue, VkBuffer const srcBuffer, VkBuffer const dstBuffer, VkDeviceSize const size)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(queue != VK_NULL_HANDLE, "Queue is null.");
	MINTY_ASSERT(srcBuffer != VK_NULL_HANDLE, "Source buffer is null.");
	MINTY_ASSERT(dstBuffer != VK_NULL_HANDLE, "Destination buffer is null.");
	MINTY_ASSERT(size > 0, "Size is zero.");

	VkBufferCopy copyRegion{};
	copyRegion.srcOffset = 0;
	copyRegion.dstOffset = 0;
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
}

void Minty::Vulkan_Renderer::copy_buffer_to_image(VkCommandBuffer const commandBuffer, VkQueue const queue, VkBuffer const srcBuffer, VkImage const dstImage, const uint32_t width, const uint32_t height)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, "Command buffer is null.");
	MINTY_ASSERT(queue != VK_NULL_HANDLE, "Queue is null.");
	MINTY_ASSERT(srcBuffer != VK_NULL_HANDLE, "Source buffer is null.");
	MINTY_ASSERT(dstImage != VK_NULL_HANDLE, "Destination image is null.");

	VkBufferImageCopy region{};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;

	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;

	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = {
		width,
		height,
		1
	};

	vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
}

VkSemaphore Minty::Vulkan_Renderer::create_semaphore(VkDevice const device)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkSemaphore, vkCreateSemaphore(device, &semaphoreInfo, nullptr, &object), "Failed to create semaphore.");
}

void Minty::Vulkan_Renderer::destroy_semaphore(VkDevice const device, VkSemaphore const semaphore)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(semaphore != VK_NULL_HANDLE, "Semaphore is null.");

	vkDestroySemaphore(device, semaphore, nullptr);
}

VkFence Minty::Vulkan_Renderer::create_fence(VkDevice const device)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkFence, vkCreateFence(device, &fenceInfo, nullptr, &object), "Failed to create fence.");
}

void Minty::Vulkan_Renderer::destroy_fence(VkDevice const device, VkFence const fence)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(fence != VK_NULL_HANDLE, "Fence is null.");

	vkDestroyFence(device, fence, nullptr);
}

void Minty::Vulkan_Renderer::wait_for_fence(VkDevice const device, VkFence const fence)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(fence != VK_NULL_HANDLE, "Fence is null.");

	vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);
}

void Minty::Vulkan_Renderer::reset_fence(VkDevice const device, VkFence const fence)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(fence != VK_NULL_HANDLE, "Fence is null.");

	vkResetFences(device, 1, &fence);
}

VkResult Minty::Vulkan_Renderer::present_frame(VkQueue const queue, VkSwapchainKHR const swapchain, uint32_t const imageIndex, VkSemaphore const signalSemaphore)
{
	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	// specify which semaphore to wait on
	VkSemaphore signalSemaphores[] = { signalSemaphore };
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	// submit swap chain
	VkSwapchainKHR swapchains[] = { swapchain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapchains;

	// specify which image to use
	presentInfo.pImageIndices = &imageIndex;

	// check results of swap chain?
	presentInfo.pResults = nullptr;

	// present it
	VkResult result = vkQueuePresentKHR(queue, &presentInfo);

	if (result != VK_SUCCESS && result != VK_ERROR_OUT_OF_DATE_KHR && result != VK_SUBOPTIMAL_KHR)
	{
		VK_ASSERT_ABORT("Failed to present the frame.");
	}

	return result;
}

VkBuffer Minty::Vulkan_Renderer::create_buffer(VkDevice const device, VkDeviceSize const size, VkBufferUsageFlags const usage)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");

	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; // data can be shared between queues/queue families

	VK_ASSERT_RESULT_RETURN_OBJECT(VkBuffer, vkCreateBuffer(device, &bufferInfo, nullptr, &object), "Failed to create buffer.");
}

void Minty::Vulkan_Renderer::destroy_buffer(VkDevice const device, VkBuffer const buffer)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(buffer != VK_NULL_HANDLE, "Buffer is null.");

	vkDestroyBuffer(device, buffer, nullptr);
}

VkDeviceMemory Minty::Vulkan_Renderer::allocate_buffer_memory(VkDevice const device, VkPhysicalDevice const physicalDevice, VkBuffer const buffer, VkMemoryPropertyFlags const memoryProperties)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(physicalDevice != VK_NULL_HANDLE, "Physical device is null.");
	MINTY_ASSERT(buffer != VK_NULL_HANDLE, "Buffer is null.");

	VkMemoryRequirements memoryRequirements{};
	vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);

	uint32_t memoryTypeIndex = find_memory_type(physicalDevice, memoryRequirements.memoryTypeBits, memoryProperties);
	VkDeviceMemory memory = allocate_memory(device, memoryRequirements.size, memoryTypeIndex);
	bind_buffer_memory(device, buffer, memory);
	return memory;
}

void Minty::Vulkan_Renderer::bind_buffer_memory(VkDevice const device, VkBuffer const buffer, VkDeviceMemory const memory)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, "Device is null.");
	MINTY_ASSERT(buffer != VK_NULL_HANDLE, "Buffer is null.");
	MINTY_ASSERT(memory != VK_NULL_HANDLE, "Memory is null.");

	VK_ASSERT_RESULT(vkBindBufferMemory(device, buffer, memory, 0), "Failed to bind buffer memory.");
}

VkFormat Minty::Vulkan_Renderer::to_vulkan(const Minty::Format format)
{
	// 1:1 with Vulkan
	return static_cast<VkFormat>(format);
}

VkBufferUsageFlags Minty::Vulkan_Renderer::to_vulkan(const Minty::BufferUsage bufferUsage)
{
	switch (bufferUsage)
	{
	case BufferUsage::Undefined:
		MINTY_ABORT("Buffer usage is undefined.");
		break;
	case BufferUsage::Transfer:
		return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	case BufferUsage::Vertex:
		return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	case BufferUsage::Index:
		return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
	case BufferUsage::Uniform:
		return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	default:
		MINTY_ABORT("Unsupported buffer usage.");
		break;
	}

	return VK_BUFFER_USAGE_FLAG_BITS_MAX_ENUM;
}

VkShaderStageFlags Minty::Vulkan_Renderer::to_vulkan(const Minty::ShaderStage shaderStage)
{
	switch (shaderStage)
	{
	case ShaderStage::Undefined:
		MINTY_ABORT("Shader stage is undefined.");
		break;
	case ShaderStage::Vertex:
		return VK_SHADER_STAGE_VERTEX_BIT;
	case ShaderStage::Fragment:
		return VK_SHADER_STAGE_FRAGMENT_BIT;
	default:
		MINTY_ABORT("Unsupported shader stage.");
		break;
	}

	return VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
}

VkDescriptorType Minty::Vulkan_Renderer::to_vulkan(const Minty::ShaderInputType type)
{
	switch (type)
	{
	case ShaderInputType::Undefined:
		MINTY_ABORT("Shader input type is undefined.");
		break;
	case ShaderInputType::Sample:
		return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
	case ShaderInputType::CombinedImageSampler:
		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	case ShaderInputType::SampledImage:
		return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
	case ShaderInputType::StorageImage:
		return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
	case ShaderInputType::UniformTexelBuffer:
		return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
	case ShaderInputType::StorageTexelBuffer:
		return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
	case ShaderInputType::UniformBuffer:
		return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	case ShaderInputType::StorageBuffer:
		return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	case ShaderInputType::UniformBufferDynamic:
		return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
	case ShaderInputType::StorageBufferDynamic:
		return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
	case ShaderInputType::PushConstant:
		return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
	default:
		MINTY_ABORT("Unsupported shader input type.");
		break;
	}
	return VK_DESCRIPTOR_TYPE_MAX_ENUM;
}

VkFormat Minty::Vulkan_Renderer::to_vulkan(const Minty::Type type)
{
	switch (type)
	{
	case Type::Float:
		return VkFormat::VK_FORMAT_R32_SFLOAT;
	case Type::Float2:
		return VkFormat::VK_FORMAT_R32G32_SFLOAT;
	case Type::Float3:
		return VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
	case Type::Float4:
		return VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT;
	case Type::Int:
		return VkFormat::VK_FORMAT_R32_SINT;
	case Type::Int2:
		return VkFormat::VK_FORMAT_R32G32_SINT;
	case Type::Int3:
		return VkFormat::VK_FORMAT_R32G32B32_SINT;
	case Type::Int4:
		return VkFormat::VK_FORMAT_R32G32B32A32_SINT;
	case Type::UInt:
		return VkFormat::VK_FORMAT_R32_UINT;
	case Type::UInt2:
		return VkFormat::VK_FORMAT_R32G32_UINT;
	case Type::UInt3:
		return VkFormat::VK_FORMAT_R32G32B32_UINT;
	case Type::UInt4:
		return VkFormat::VK_FORMAT_R32G32B32A32_UINT;
	default:
		MINTY_ABORT("Unsupported type.");
		break;
	}

	return VK_FORMAT_UNDEFINED;
}

VkImageType Minty::Vulkan_Renderer::to_vulkan(const Minty::ImageType type)
{
	switch (type)
	{
	case Minty::ImageType::D1:
		return VK_IMAGE_TYPE_1D;
	case Minty::ImageType::D2:
		return VK_IMAGE_TYPE_2D;
	case Minty::ImageType::D3:
		return VK_IMAGE_TYPE_3D;
	default:
		MINTY_ABORT("Unsupported image type.");
		break;
	}

	return VK_IMAGE_TYPE_MAX_ENUM;
}

VkImageTiling Minty::Vulkan_Renderer::to_vulkan(const Minty::ImageTiling tiling)
{
	switch (tiling)
	{
	case ImageTiling::Undefined:
		MINTY_ABORT("Image tiling is undefined.");
		break;
	case ImageTiling::Optimal:
		return VK_IMAGE_TILING_OPTIMAL;
	case ImageTiling::Linear:
		return VK_IMAGE_TILING_LINEAR;
	default:
		MINTY_ABORT("Unsupported image tiling.");
		break;
	};

	return VK_IMAGE_TILING_MAX_ENUM;
}

VkSamplerAddressMode Minty::Vulkan_Renderer::to_vulkan(const Minty::ImageAddressMode addressMode)
{
	switch (addressMode)
	{
	case ImageAddressMode::Undefined:
		MINTY_ABORT("Image address mode is undefined.");
		break;
	case ImageAddressMode::Repeat:
		return VK_SAMPLER_ADDRESS_MODE_REPEAT;
	case ImageAddressMode::MirroredRepeat:
		return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
	case ImageAddressMode::ClampToEdge:
		return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	case ImageAddressMode::ClampToBorder:
		return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	case ImageAddressMode::MirroredClampToEdge:
		return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
	default:
		MINTY_ABORT("Unsupported image address mode.");
		break;
	};

	return VK_SAMPLER_ADDRESS_MODE_MAX_ENUM;
}

VkImageAspectFlags Minty::Vulkan_Renderer::to_vulkan(const Minty::ImageAspect aspect)
{
	switch (aspect)
	{
	case ImageAspect::Undefined:
		MINTY_ABORT("Image aspect is undefined.");
		break;
	case ImageAspect::Color:
		return VK_IMAGE_ASPECT_COLOR_BIT;
	case ImageAspect::Depth:
		return VK_IMAGE_ASPECT_DEPTH_BIT;
	default:
		MINTY_ABORT("Unsupported image aspect.");
		break;
	}

	return VK_IMAGE_ASPECT_FLAG_BITS_MAX_ENUM;
}

VkImageUsageFlags Minty::Vulkan_Renderer::to_vulkan(const Minty::ImageUsage usage)
{
	switch (usage)
	{
	case ImageUsage::Undefined:
		MINTY_ABORT("Image usage is undefined.");
		break;
	case ImageUsage::Sampled:
		return VK_IMAGE_USAGE_SAMPLED_BIT;
	case ImageUsage::Storage:
		return VK_IMAGE_USAGE_STORAGE_BIT;
	case ImageUsage::Color:
		return VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	case ImageUsage::DepthStencil:
		return VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	default:
		MINTY_ABORT("Unsupported image usage.");
		break;
	}

	return VK_IMAGE_USAGE_FLAG_BITS_MAX_ENUM;
}

VkPrimitiveTopology Minty::Vulkan_Renderer::to_vulkan(const Minty::ShaderPrimitiveTopology topology)
{
	switch (topology)
	{
	case ShaderPrimitiveTopology::Undefined:
		MINTY_ABORT("Shader primitive topology is undefined.");
		break;
	case ShaderPrimitiveTopology::PointList:
		return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
	case ShaderPrimitiveTopology::LineList:
		return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
	case ShaderPrimitiveTopology::LineStrip:
		return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
	case ShaderPrimitiveTopology::TriangleList:
		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	case ShaderPrimitiveTopology::TriangleStrip:
		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
	case ShaderPrimitiveTopology::TriangleFan:
		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
	default:
		MINTY_ABORT("Unsupported shader primitive topology.");
		break;
	}

	return VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
}

VkCullModeFlags Minty::Vulkan_Renderer::to_vulkan(const Minty::ShaderCullMode mode)
{
	switch (mode)
	{
	case ShaderCullMode::Undefined:
		MINTY_ABORT("Shader cull mode is undefined.");
		break;
	case ShaderCullMode::None:
		return VK_CULL_MODE_NONE;
	case ShaderCullMode::Front:
		return VK_CULL_MODE_FRONT_BIT;
	case ShaderCullMode::Back:
		return VK_CULL_MODE_BACK_BIT;
	case ShaderCullMode::Both:
		return VK_CULL_MODE_FRONT_AND_BACK;
	default:
		MINTY_ABORT("Unsupported shader cull mode.");
		break;
	}

	return VK_CULL_MODE_FLAG_BITS_MAX_ENUM;
}

VkFrontFace Minty::Vulkan_Renderer::to_vulkan(const Minty::ShaderFrontFace frontFace)
{
	switch (frontFace)
	{
	case ShaderFrontFace::Undefined:
		MINTY_ABORT("Shader front face is undefined.");
		break;
	case ShaderFrontFace::Clockwise:
		return VK_FRONT_FACE_CLOCKWISE;
	case ShaderFrontFace::CounterClockwise:
		return VK_FRONT_FACE_COUNTER_CLOCKWISE;
	default:
		MINTY_ABORT("Unsupported shader front face.");
		break;
	}

	return VK_FRONT_FACE_MAX_ENUM;
}

VkPolygonMode Minty::Vulkan_Renderer::to_vulkan(const Minty::ShaderPolygonMode mode)
{
	switch (mode)
	{
	case ShaderPolygonMode::Undefined:
		MINTY_ABORT("Shader polygon mode is undefined.");
		break;
	case ShaderPolygonMode::Fill:
		return VK_POLYGON_MODE_FILL;
	case ShaderPolygonMode::Line:
		return VK_POLYGON_MODE_LINE;
	case ShaderPolygonMode::Point:
		return VK_POLYGON_MODE_POINT;
	default:
		MINTY_ABORT("Unsupported shader polygon mode.");
		break;
	}

	return VK_POLYGON_MODE_MAX_ENUM;
}

VkVertexInputRate Minty::Vulkan_Renderer::to_vulkan(const Minty::ShaderInputRate rate)
{
	switch (rate)
	{
	case ShaderInputRate::Undefined:
		MINTY_ABORT("Shader input rate is undefined.");
		break;
	case ShaderInputRate::Vertex:
		return VK_VERTEX_INPUT_RATE_VERTEX;
	case ShaderInputRate::Instance:
		return VK_VERTEX_INPUT_RATE_INSTANCE;
	default:
		MINTY_ABORT("Unsupported shader input rate.");
		break;
	}

	return VK_VERTEX_INPUT_RATE_MAX_ENUM;
}

VkAttachmentLoadOp Minty::Vulkan_Renderer::to_vulkan(Minty::RenderAttachment::LoadOperation const operation)
{
	switch (operation)
	{
	case RenderAttachment::LoadOperation::DontCare:
		return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	case RenderAttachment::LoadOperation::Load:
		return VK_ATTACHMENT_LOAD_OP_LOAD;
	case RenderAttachment::LoadOperation::Clear:
		return VK_ATTACHMENT_LOAD_OP_CLEAR;
	default:
		MINTY_ABORT("Unsupported load operation.");
		break;
	}

	return VK_ATTACHMENT_LOAD_OP_MAX_ENUM;
}

VkAttachmentStoreOp Minty::Vulkan_Renderer::to_vulkan(Minty::RenderAttachment::StoreOperation const operation)
{
	switch (operation)
	{
	case RenderAttachment::StoreOperation::DontCare:
		return VK_ATTACHMENT_STORE_OP_DONT_CARE;
	case RenderAttachment::StoreOperation::Store:
		return VK_ATTACHMENT_STORE_OP_STORE;
	default:
		MINTY_ABORT("Unsupported store operation.");
		break;
	}

	return VK_ATTACHMENT_STORE_OP_MAX_ENUM;
}

VkAttachmentDescription Minty::Vulkan_Renderer::to_vulkan(Minty::RenderAttachment const& attachment)
{
	VkAttachmentDescription description{};

	description.format = to_vulkan(attachment.format);
	description.samples = VK_SAMPLE_COUNT_1_BIT;
	description.loadOp = to_vulkan(attachment.loadOperation);
	description.storeOp = to_vulkan(attachment.storeOperation);
	description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	description.initialLayout = to_vulkan(attachment.initialLayout);
	description.finalLayout = to_vulkan(attachment.finalLayout);

	return description;
}

VkImageLayout Minty::Vulkan_Renderer::to_vulkan(Minty::ImageLayout const layout)
{
	switch (layout)
	{
	case ImageLayout::Undefined:
		MINTY_ABORT("Image layout is undefined.");
		break;
	case ImageLayout::General:
		return VK_IMAGE_LAYOUT_GENERAL;
	case ImageLayout::ColorAttachment:
		return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	case ImageLayout::DepthStencilAttachment:
		return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	case ImageLayout::DepthStencilReadOnly:
		return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
	case ImageLayout::ShaderReadOnly:
		return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	case ImageLayout::TransferSource:
		return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
	case ImageLayout::TransferDestination:
		return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	case ImageLayout::Preinitialized:
		return VK_IMAGE_LAYOUT_PREINITIALIZED;
	default:
		MINTY_ABORT("Unsupported image layout.");
		break;
	}

	return VK_IMAGE_LAYOUT_MAX_ENUM;
}

VkFilter Minty::Vulkan_Renderer::to_vulkan(Minty::Filter const filter)
{
	switch (filter)
	{
	case Filter::Undefined:
		MINTY_ABORT("Filter is undefined.");
		break;
	case Filter::Nearest:
		return VK_FILTER_NEAREST;
	case Filter::Linear:
		return VK_FILTER_LINEAR;
	default:
		MINTY_ABORT("Unsupported filter.");
		break;
	}

	return VK_FILTER_MAX_ENUM;
}
