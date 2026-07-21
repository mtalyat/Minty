#include "Vulkan_Renderer.hpp"
#include "Vulkan_Macro.hpp"
#include "Vulkan_QueueFamilyIndices.hpp"
#include "Vulkan_SwapchainSupportDetails.hpp"
#include "Vulkan_Frame.hpp"
#include "Vulkan_Surface.hpp"
#include "Library/GLFW/GLFW.hpp"
#include "Core/Debug/DebugF.hpp"
#include "Core/Constant/Info.hpp"
#include "Core/Data/Set.hpp"
#include "Core/Data/Array.hpp"
#include <map> // for multimap, TODO: replace with our own multimap implementation

using namespace Minty;

#pragma region Utility

#pragma region Extensions

constexpr Size DEVICE_EXTENSION_COUNT = 1;
constexpr Char const *const DEVICE_EXTENSIONS[DEVICE_EXTENSION_COUNT] = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME};

static Vector<Char const *> get_required_extensions()
{
	uint32_t glfwExtensionCount = 0;
	Char const **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	uint32_t listSize = glfwExtensionCount;

#ifdef MINTY_DEBUG
	listSize++;
#endif // MINTY_DEBUG

	Vector<Char const *> extensions(listSize);
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

constexpr Size VALIDATION_LAYER_COUNT = 1;
constexpr Char const *const VALIDATION_LAYERS[VALIDATION_LAYER_COUNT] = {
	"VK_LAYER_KHRONOS_validation"};

#ifdef MINTY_DEBUG

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
	Pointer pUserData)
{
	Char const *message = pCallbackData->pMessage;

	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		Debug::log(SeverityFlagsEnum::Error, message);
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		Debug::log(SeverityFlagsEnum::Warning, message);
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
	{
		Debug::log(SeverityFlagsEnum::Info, message);
	}
	else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
	{
		Debug::log(SeverityFlagsEnum::Info, message);
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
	for (Size i = 0; i < VALIDATION_LAYER_COUNT; ++i)
	{
		Char const *const layerName = VALIDATION_LAYERS[i];
		Bool layerFound = false;

		for (auto const &layerProperties : availableLayers)
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

static void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
{
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
}

static VkResult create_debug_utils_messenger_ext(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger)
{
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

static void destroy_debug_utils_messenger_ext(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator)
{
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
	appInfo.applicationVersion = MINTY_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = MINTY_ENGINE_NAME;
	appInfo.engineVersion = MINTY_VERSION;
	appInfo.apiVersion = VK_API_VERSION_1_2;

	// instance
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	// extensions
	Vector<Char const *> extensions = get_required_extensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.get_size());
	createInfo.ppEnabledExtensionNames = extensions.get_data();

	// validation layers
#ifdef MINTY_DEBUG
	MINTY_ASSERT(check_validation_layer_support(), ErrorCodeEnum::Render_UnsupportedFeature); // "Validation layers requested, but not available."
	createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYER_COUNT);
	createInfo.ppEnabledLayerNames = VALIDATION_LAYERS;
#else
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;
#endif // MINTY_DEBUG

	VK_ASSERT_RESULT_RETURN_OBJECT(VkInstance, vkCreateInstance(&createInfo, nullptr, &object), "Failed to create instance.");
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

VkSurfaceKHR Minty::Vulkan_Renderer::create_surface(VkInstance const instance, Pointer const window)
{
	VK_ASSERT_RESULT_RETURN_OBJECT(VkSurfaceKHR, glfwCreateWindowSurface(instance, static_cast<GLFWwindow *>(window), nullptr, &object), "Failed to create window surface.");
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

	Set<String> requiredExtensions(DEVICE_EXTENSION_COUNT);
	for (Size i = 0; i < DEVICE_EXTENSION_COUNT; ++i)
	{
		requiredExtensions.add(DEVICE_EXTENSIONS[i]);
	}

	for (auto const &extension : availableExtensions)
	{
		requiredExtensions.remove(extension.extensionName);
	}

	return requiredExtensions.is_empty();
}

int Minty::Vulkan_Renderer::rate_device_suitability(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface)
{
	// check if device queues can handle what we want
	Vulkan_QueueFamilyIndices queueFamilyIndices = find_queue_families(physicalDevice, surface);
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
	Vulkan_SwapchainSupportDetails swapChainSupport = query_swapchain_support(physicalDevice, surface);
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
	if (!supportedFeatures.fillModeNonSolid)
	{
		return 0;
	}
	if (!supportedFeatures.wideLines)
	{
		return 0;
	}

	// anything works for now
	return 1;

#ifdef MINTY_KEEP

	// VkPhysicalDeviceProperties deviceProperties;
	// vkGetPhysicalDeviceProperties(device, &deviceProperties);

	// VkPhysicalDeviceFeatures deviceFeatures;
	// vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	// int score = 0;

	//// Discrete GPUs have a significant performance advantage
	// if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
	//     score += 1000;
	// }

	//// Maximum possible size of textures affects graphics quality
	// score += deviceProperties.limits.maxImageDimension2D;

	//// Application can't function without geometry shaders
	// if (!deviceFeatures.geometryShader) {
	//     return 0;
	// }

	// return score;

#endif // MINTY_KEEP
}

VkPhysicalDevice Minty::Vulkan_Renderer::select_physical_device(VkInstance const instance, VkSurfaceKHR const surface, Function<int(VkPhysicalDevice, VkSurfaceKHR)> const &ratingFunction)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		VK_ASSERT_ABORT("Failed to find_first GPUs with Vulkan support.");
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
		VK_ASSERT_ABORT("Failed to find_first a suitable GPU.");
	}
}

Vulkan_SwapchainSupportDetails Minty::Vulkan_Renderer::query_swapchain_support(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface)
{
	Vulkan_SwapchainSupportDetails details;

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

VkSurfaceFormatKHR Minty::Vulkan_Renderer::select_swap_surface_format(Vector<VkSurfaceFormatKHR> const &availableFormats, VkFormat const format, VkColorSpaceKHR const colorSpace)
{
	for (auto const &availableFormat : availableFormats)
	{
		if (availableFormat.format == format && availableFormat.colorSpace == colorSpace)
		{
			return availableFormat;
		}
	}

	return availableFormats.front();
}

VkPresentModeKHR Minty::Vulkan_Renderer::select_swap_present_mode(Vector<VkPresentModeKHR> const &availablePresentModes, VkPresentModeKHR const presentMode)
{
	for (auto const &availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == presentMode)
		{
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkFormat Minty::Vulkan_Renderer::find_supported_format(VkPhysicalDevice const physicalDevice, Vector<VkFormat> const &candidates, VkImageTiling const tiling, VkFormatFeatureFlags const features)
{
	for (VkFormat format : candidates)
	{
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features)
		{
			return format;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
		{
			return format;
		}
	}

	VK_ASSERT_ABORT("Failed to find_first supported depthFormat.");
}

VkFormat Minty::Vulkan_Renderer::find_supported_depth_stencil_format(VkPhysicalDevice const physicalDevice)
{
	return find_supported_format(physicalDevice,
								 {VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
								 VK_IMAGE_TILING_OPTIMAL,
								 VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

Vulkan_QueueFamilyIndices Minty::Vulkan_Renderer::find_queue_families(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface)
{
	Vulkan_QueueFamilyIndices queueFamilyIndices{};

	// get number of queue families
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	// get queue families
	Vector<VkQueueFamilyProperties> queueFamilies;
	queueFamilies.resize(queueFamilyCount, VkQueueFamilyProperties{});
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.get_data());

	// find queue families
	uint32_t i = 0;
	for (auto const &queueFamily : queueFamilies)
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

VkDevice Minty::Vulkan_Renderer::create_device(VkPhysicalDevice const physicalDevice, Vulkan_QueueFamilyIndices const &queueFamilyIndices)
{
	// create all the queues needed for operations, based on the families
	Vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	Set<uint32_t> uniqueQueueFamilies = {queueFamilyIndices.graphicsFamily.get_value(), queueFamilyIndices.presentFamily.get_value()};

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
	deviceFeatures.samplerAnisotropy = VK_TRUE; // enable sampler anisotropy for textures
	deviceFeatures.fillModeNonSolid = VK_TRUE;	// enable non-solid fill mode for pipelines
	deviceFeatures.wideLines = VK_TRUE;			// enable wide lines for pipelines

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.get_size());
	createInfo.pQueueCreateInfos = queueCreateInfos.get_data();
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = DEVICE_EXTENSION_COUNT;
	createInfo.ppEnabledExtensionNames = DEVICE_EXTENSIONS;

#ifdef MINTY_DEBUG
	// tie in validation layers
	createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYER_COUNT);
	createInfo.ppEnabledLayerNames = VALIDATION_LAYERS;
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

VkSwapchainKHR Minty::Vulkan_Renderer::create_swapchain(VkDevice const device, VkSurfaceKHR const surface, Vulkan_SwapchainSupportDetails const &swapchainSupport, Vulkan_QueueFamilyIndices const &queueFamilyIndices, VkSurfaceFormatKHR const surfaceFormat, VkExtent2D const extent, VkPresentModeKHR const presentMode)
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

	uint32_t queueFamilyIndicesBuffer[] = {queueFamilyIndices.graphicsFamily.get_value(), queueFamilyIndices.presentFamily.get_value()};

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

VkExtent2D Minty::Vulkan_Renderer::get_swapchain_extent(VkSurfaceCapabilitiesKHR const &capabilities, UInt2 const &framebufferSize)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		// extent has been initialized, use it
		return capabilities.currentExtent;
	}

	// create new extent from window size
	UInt2 const size = framebufferSize;

	VkExtent2D actualExtent =
		{
			static_cast<uint32_t>(size.x),
			static_cast<uint32_t>(size.y)};

	actualExtent.width = Math::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
	actualExtent.height = Math::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

	return actualExtent;
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

VkResult Minty::Vulkan_Renderer::get_next_swapchain_image_index(VkDevice const device, VkSwapchainKHR const swapchain, VkSemaphore const waitSemaphore, uint32_t &index)
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
	// also find memory with the given specific properties
	for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}

	MINTY_ABORT(ErrorCodeEnum::Render_QueryFailed); // "Failed to find suitable memory type."
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

Pointer Minty::Vulkan_Renderer::map_memory(VkDevice const device, VkDeviceMemory const memory, VkDeviceSize const offset, VkDeviceSize const size)
{
	VK_ASSERT_RESULT_RETURN_OBJECT(Pointer, vkMapMemory(device, memory, offset, size, 0, &object), "Failed to map memory.");
}

void Minty::Vulkan_Renderer::unmap_memory(VkDevice const device, VkDeviceMemory const memory)
{
	vkUnmapMemory(device, memory);
}

VkImage Minty::Vulkan_Renderer::create_image(VkDevice const device, const uint32_t width, const uint32_t height, VkImageType const type, VkFormat const format, VkImageTiling const tiling, VkImageUsageFlags const usage)
{
	// create image from info
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

VkShaderModule Minty::Vulkan_Renderer::create_shader_module(VkDevice const device, PointerConst const data, Size const size)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(data != nullptr, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(size > 0, ErrorCodeEnum::Argument_ExpectedNonZero);

	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = size;
	createInfo.pCode = reinterpret_cast<const uint32_t *>(data);

	VK_ASSERT_RESULT_RETURN_OBJECT(VkShaderModule, vkCreateShaderModule(device, &createInfo, nullptr, &object), "Failed to create shader module.");
}

void Minty::Vulkan_Renderer::destroy_shader_module(VkDevice const device, VkShaderModule const shaderModule)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(shaderModule != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroyShaderModule(device, shaderModule, nullptr);
}

VkRenderPass Minty::Vulkan_Renderer::create_render_pass(VkDevice const device, Span<VkAttachmentDescription> const colorAttachments, Span<VkAttachmentDescription> const depthAttachments)
{
	// TODO: validate

	Vector<VkAttachmentReference> colorAttachmentRefs;
	VkAttachmentReference depthAttachmentRef{};

	// create subpass and attachment references for the subpass description
	VkSubpassDescription subpass{};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	if (colorAttachments.is_empty())
	{
		subpass.colorAttachmentCount = 0;
		subpass.pColorAttachments = nullptr;
	}
	else
	{
		// create multiple attachment references, one for each color attachment
		colorAttachmentRefs.resize(colorAttachments.get_size(), VkAttachmentReference{});

		for (Size i = 0; i < colorAttachments.get_size(); ++i)
		{
			colorAttachmentRefs[i].attachment = static_cast<uint32_t>(i);
			colorAttachmentRefs[i].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		subpass.colorAttachmentCount = static_cast<uint32_t>(colorAttachmentRefs.get_size());
		subpass.pColorAttachments = colorAttachmentRefs.get_data();
	}
	if (depthAttachments.is_empty())
	{
		subpass.pDepthStencilAttachment = nullptr;
	}
	else
	{
		depthAttachmentRef.attachment = static_cast<uint32_t>(colorAttachments.get_size()); // depth attachment comes after color attachments
		depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		subpass.pDepthStencilAttachment = &depthAttachmentRef;
	}

	// render pass attachments are just the color and depth attachments combined
	Vector<VkAttachmentDescription> attachments;
	attachments.reserve(colorAttachments.get_size() + depthAttachments.get_size());
	for (const VkAttachmentDescription &colorAttachment : colorAttachments)
	{
		attachments.add(colorAttachment);
	}
	for (const VkAttachmentDescription &depthAttachment : depthAttachments)
	{
		attachments.add(depthAttachment);
	}

	// create render pass from attachments and subpass description
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
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(renderPass != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroyRenderPass(device, renderPass, nullptr);
}

VkFramebuffer Minty::Vulkan_Renderer::create_framebuffer(VkDevice const device, VkRenderPass const renderPass, VkExtent2D const extent, VkImageView const colorAttachment, VkImageView const depthAttachment)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(renderPass != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

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
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(framebuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroyFramebuffer(device, framebuffer, nullptr);
}

VkCommandPool Minty::Vulkan_Renderer::create_command_pool(VkDevice const device, const uint32_t queueFamilyIndex)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndex;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkCommandPool, vkCreateCommandPool(device, &poolInfo, nullptr, &object), "Failed to create command pool.");
}

void Minty::Vulkan_Renderer::destroy_command_pool(VkDevice const device, VkCommandPool const pool)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(pool != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroyCommandPool(device, pool, nullptr);
}

VkCommandBuffer Minty::Vulkan_Renderer::create_command_buffer(VkDevice const device, VkCommandPool const commandPool)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(commandPool != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkCommandBuffer, vkAllocateCommandBuffers(device, &allocInfo, &object), "Failed to allocate command buffers.");
}

void Minty::Vulkan_Renderer::destroy_command_buffer(VkDevice const device, VkCommandPool const commandPool, VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(commandPool != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

void Minty::Vulkan_Renderer::begin_command_buffer(VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	VK_ASSERT_RESULT(vkBeginCommandBuffer(commandBuffer, &beginInfo), "Failed to begin recording command buffer.");
}

void Minty::Vulkan_Renderer::begin_command_buffer_temp(VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	VK_ASSERT_RESULT(vkBeginCommandBuffer(commandBuffer, &beginInfo), "Failed to begin recording temp command buffer.");
}

void Minty::Vulkan_Renderer::end_command_buffer(VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VK_ASSERT_RESULT(vkEndCommandBuffer(commandBuffer), "Failed to record command buffer.");
}

VkCommandBuffer Minty::Vulkan_Renderer::start_command_buffer_single(VkDevice const device, VkCommandPool const commandPool)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(commandPool != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkCommandBuffer commandBuffer = create_command_buffer(device, commandPool);

	begin_command_buffer_temp(commandBuffer);

	return commandBuffer;
}

void Minty::Vulkan_Renderer::finish_command_buffer_single(VkDevice const device, VkCommandPool const commandPool, VkCommandBuffer const commandBuffer, VkQueue const queue)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(commandPool != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(queue != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	// end the command buffer
	end_command_buffer(commandBuffer);

	// submit the command buffer
	submit_command_buffer(commandBuffer, queue);

	// wait for the queue to finish
	VK_ASSERT_RESULT(vkQueueWaitIdle(queue), "Failed to wait for queue to finish.");

	// destroy the command buffer
	destroy_command_buffer(device, commandPool, commandBuffer);
}

void Minty::Vulkan_Renderer::reset_command_buffer(VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VK_ASSERT_RESULT(vkResetCommandBuffer(commandBuffer, 0), "Failed to reset command buffer.");
}

void Minty::Vulkan_Renderer::submit_command_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue, VkSemaphore const waitSemaphore, VkSemaphore const signalSemaphore, VkFence const inFlightFence)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(queue != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = {waitSemaphore};
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	VkSemaphore signalSemaphores[] = {signalSemaphore};
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	VK_ASSERT_RESULT(vkQueueSubmit(queue, 1, &submitInfo, inFlightFence), "Failed to submit draw command buffer.");
}

void Minty::Vulkan_Renderer::submit_command_buffer(VkCommandBuffer const commandBuffer, Vulkan_Frame const &frame, VkQueue const queue)
{
	submit_command_buffer(commandBuffer, queue, frame.imageAvailableSemaphore, frame.renderFinishedSemaphore, frame.inFlightFence);
}

void Minty::Vulkan_Renderer::submit_command_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(queue != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	VK_ASSERT_RESULT(vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE), "Failed to submit command buffer.");
}

void Minty::Vulkan_Renderer::begin_render_pass(VkCommandBuffer const commandBuffer, VkRenderPass const renderPass, VkFramebuffer const framebuffer, VkRect2D const renderArea, VkClearColorValue const clearColor)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(renderPass != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(framebuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

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
	clearValues[1].depthStencil = {1.0f, 0};
	renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.get_size());
	renderPassInfo.pClearValues = clearValues.get_data();

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void Minty::Vulkan_Renderer::end_render_pass(VkCommandBuffer const commandBuffer)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkCmdEndRenderPass(commandBuffer);
}

void Minty::Vulkan_Renderer::bind_pipeline(VkCommandBuffer const commandBuffer, VkPipeline const graphicsPipeline, VkPipelineBindPoint const bindPoint)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(graphicsPipeline != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkCmdBindPipeline(commandBuffer, bindPoint, graphicsPipeline);
}

void Minty::Vulkan_Renderer::bind_descriptor_set(VkCommandBuffer const commandBuffer, VkPipelineLayout const graphicsPipelineLayout, VkDescriptorSet const descriptorSet, uint32_t const firstSet, VkPipelineBindPoint const bindPoint)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(graphicsPipelineLayout != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(descriptorSet != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkCmdBindDescriptorSets(commandBuffer, bindPoint, graphicsPipelineLayout, firstSet, 1, &descriptorSet, 0, nullptr);
}

void Minty::Vulkan_Renderer::bind_viewport(VkCommandBuffer const commandBuffer, VkViewport const &viewport)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
}

void Minty::Vulkan_Renderer::bind_scissor(VkCommandBuffer const commandBuffer, VkRect2D const &scissor)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void Minty::Vulkan_Renderer::set_stencil_reference(VkCommandBuffer const commandBuffer, uint32_t const reference)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkCmdSetStencilReference(commandBuffer, VK_STENCIL_FACE_FRONT_AND_BACK, reference);
}

void Minty::Vulkan_Renderer::bind_vertex_buffer(VkCommandBuffer const commandBuffer, VkBuffer const buffer, uint32_t const binding)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(buffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, binding, 1, &buffer, &offset);
}

void Minty::Vulkan_Renderer::bind_index_buffer(VkCommandBuffer const commandBuffer, VkBuffer const buffer, VkIndexType const indexType)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(buffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkCmdBindIndexBuffer(commandBuffer, buffer, 0, indexType);
}

void Minty::Vulkan_Renderer::draw(VkCommandBuffer const commandBuffer, uint32_t const vertexCount, uint32_t const instanceCount)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkCmdDraw(commandBuffer, vertexCount, instanceCount, 0, 0);
}

void Minty::Vulkan_Renderer::draw_indexed(VkCommandBuffer const commandBuffer, uint32_t const indexCount, uint32_t const instanceCount)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, 0, 0, 0);
}

void Minty::Vulkan_Renderer::draw_instanced(VkCommandBuffer const commandBuffer, uint32_t const instanceCount, uint32_t const vertexCount)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkCmdDraw(commandBuffer, vertexCount, instanceCount, 0, 0);
}

void Minty::Vulkan_Renderer::transition_image_layout(VkCommandBuffer const commandBuffer, VkImage const image, VkFormat const format, VkImageLayout const oldLayout, VkImageLayout const newLayout)
{
	if (oldLayout == newLayout)
	{
		return;
	}

	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(image != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = oldLayout;
	barrier.newLayout = newLayout;

	// set if transfering queues
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

	// affected part of image
	barrier.image = image;
	if (oldLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL || newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
	{
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
		if (has_stencil_component(format))
		{
			barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
		}
	}
	else
	{
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	}
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	// determine when the transfer can be conducted based on its layout
	VkPipelineStageFlags sourceStage;
	VkPipelineStageFlags destinationStage;

	auto configure_source = [&](VkImageLayout const layout)
	{
		switch (layout)
		{
		case VK_IMAGE_LAYOUT_UNDEFINED:
			barrier.srcAccessMask = 0;
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			break;
		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;
		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;
		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
			sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
			break;
		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			sourceStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			break;
		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			barrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			sourceStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
			break;
		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			barrier.srcAccessMask = 0;
			sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
			break;
		default:
			MINTY_ABORT_B(ErrorCodeEnum::Render_UnsupportedTransition, static_cast<Size>(oldLayout), static_cast<Size>(newLayout));
		}
	};

	auto configure_destination = [&](VkImageLayout const layout)
	{
		switch (layout)
		{
		case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;
		case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
			barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
			destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			break;
		case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
			break;
		case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
			barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			break;
		case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
			barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
			break;
		case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
			barrier.dstAccessMask = 0;
			destinationStage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
			break;
		default:
			MINTY_ABORT_B(ErrorCodeEnum::Render_UnsupportedTransition, static_cast<Size>(oldLayout), static_cast<Size>(newLayout));
		}
	};

	configure_source(oldLayout);
	configure_destination(newLayout);

	vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
}

void Minty::Vulkan_Renderer::copy_buffer_to_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue, VkBuffer const srcBuffer, VkBuffer const dstBuffer, VkDeviceSize const size)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(queue != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(srcBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(dstBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(size > 0, ErrorCodeEnum::Argument_ExpectedNonZero);

	VkBufferCopy copyRegion{};
	copyRegion.srcOffset = 0;
	copyRegion.dstOffset = 0;
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
}

void Minty::Vulkan_Renderer::copy_buffer_to_image(VkCommandBuffer const commandBuffer, VkQueue const queue, VkBuffer const srcBuffer, VkImage const dstImage, const uint32_t width, const uint32_t height)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(queue != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(srcBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(dstImage != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkBufferImageCopy region{};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;

	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;

	region.imageOffset = {0, 0, 0};
	region.imageExtent = {
		width,
		height,
		1};

	vkCmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
}

void Minty::Vulkan_Renderer::copy_image_to_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue, VkImage const srcImage, VkBuffer const dstBuffer, const uint32_t width, const uint32_t height)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(queue != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(srcImage != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(dstBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkBufferImageCopy copyRegion{};
	copyRegion.bufferOffset = 0;
	copyRegion.bufferRowLength = 0;
	copyRegion.bufferImageHeight = 0;

	copyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	copyRegion.imageSubresource.mipLevel = 0;
	copyRegion.imageSubresource.baseArrayLayer = 0;
	copyRegion.imageSubresource.layerCount = 1;

	copyRegion.imageOffset = {0, 0, 0};
	copyRegion.imageExtent = {
		width,
		height,
		1};

	vkCmdCopyImageToBuffer(commandBuffer, srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dstBuffer, 1, &copyRegion);
}

void Minty::Vulkan_Renderer::update_push_constants(VkCommandBuffer const commandBuffer, VkPipelineLayout const pipelineLayout, VkShaderStageFlags const stageFlags, uint32_t const offset, uint32_t const size, PointerConst const data)
{
	MINTY_ASSERT(commandBuffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(pipelineLayout != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(data != nullptr, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(size > 0, ErrorCodeEnum::Argument_ExpectedNonZero);

	vkCmdPushConstants(commandBuffer, pipelineLayout, stageFlags, offset, size, data);
}

VkSemaphore Minty::Vulkan_Renderer::create_semaphore(VkDevice const device)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkSemaphore, vkCreateSemaphore(device, &semaphoreInfo, nullptr, &object), "Failed to create semaphore.");
}

void Minty::Vulkan_Renderer::destroy_semaphore(VkDevice const device, VkSemaphore const semaphore)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(semaphore != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroySemaphore(device, semaphore, nullptr);
}

VkFence Minty::Vulkan_Renderer::create_fence(VkDevice const device)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkFence, vkCreateFence(device, &fenceInfo, nullptr, &object), "Failed to create fence.");
}

void Minty::Vulkan_Renderer::destroy_fence(VkDevice const device, VkFence const fence)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(fence != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroyFence(device, fence, nullptr);
}

void Minty::Vulkan_Renderer::wait_for_fence(VkDevice const device, VkFence const fence)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(fence != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);
}

void Minty::Vulkan_Renderer::reset_fence(VkDevice const device, VkFence const fence)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(fence != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkResetFences(device, 1, &fence);
}

VkResult Minty::Vulkan_Renderer::present(VkQueue const queue, VkSwapchainKHR const swapchain, uint32_t const imageIndex, VkSemaphore const signalSemaphore)
{
	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	// specify which semaphore to wait on
	VkSemaphore signalSemaphores[] = {signalSemaphore};
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	// submit swap chain
	VkSwapchainKHR swapchains[] = {swapchain};
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

VkResult Minty::Vulkan_Renderer::present_frame(VkQueue const queue, Vulkan_SurfaceData const &surface, Vulkan_Frame const &frame)
{
	return present(queue, surface.swapchain, surface.index, frame.renderFinishedSemaphore);
}
VkBuffer Minty::Vulkan_Renderer::create_buffer(VkDevice const device, VkDeviceSize const size, VkBufferUsageFlags const usage)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE; // data can be shared between queues/queue families

	VK_ASSERT_RESULT_RETURN_OBJECT(VkBuffer, vkCreateBuffer(device, &bufferInfo, nullptr, &object), "Failed to create buffer.");
}

void Minty::Vulkan_Renderer::destroy_buffer(VkDevice const device, VkBuffer const buffer)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(buffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroyBuffer(device, buffer, nullptr);
}

VkDeviceMemory Minty::Vulkan_Renderer::allocate_buffer_memory(VkDevice const device, VkPhysicalDevice const physicalDevice, VkBuffer const buffer, VkMemoryPropertyFlags const memoryProperties)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(physicalDevice != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(buffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkMemoryRequirements memoryRequirements{};
	vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);

	uint32_t memoryTypeIndex = find_memory_type(physicalDevice, memoryRequirements.memoryTypeBits, memoryProperties);
	VkDeviceMemory memory = allocate_memory(device, memoryRequirements.size, memoryTypeIndex);
	return memory;
}

void Minty::Vulkan_Renderer::bind_buffer_memory(VkDevice const device, VkBuffer const buffer, VkDeviceMemory const memory)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(buffer != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(memory != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VK_ASSERT_RESULT(vkBindBufferMemory(device, buffer, memory, 0), "Failed to bind buffer memory.");
}

Array<VkDescriptorSet, FRAMES_PER_FLIGHT> Minty::Vulkan_Renderer::allocate_descriptor_sets_for_frames(VkDevice const device, VkDescriptorPool const pool, VkDescriptorSetLayout const layout)
{
	Array<VkDescriptorSet, FRAMES_PER_FLIGHT> descriptorSets{};
	Array<VkDescriptorSetLayout, FRAMES_PER_FLIGHT> layouts(layout);

	VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
	descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	descriptorSetAllocInfo.descriptorPool = pool;
	descriptorSetAllocInfo.descriptorSetCount = FRAMES_PER_FLIGHT;
	descriptorSetAllocInfo.pSetLayouts = layouts.get_data();
	VK_ASSERT_RESULT(vkAllocateDescriptorSets(device, &descriptorSetAllocInfo, descriptorSets.get_data()), "Failed to allocate descriptor sets.");
	return descriptorSets;
}

void Minty::Vulkan_Renderer::free_descriptor_sets(VkDevice const device, VkDescriptorPool const pool, Span<VkDescriptorSet> const &descriptorSets)
{
	VK_ASSERT_RESULT(vkFreeDescriptorSets(device, pool, static_cast<uint32_t>(descriptorSets.get_size()), descriptorSets.get_data()), "Failed to free descriptor sets.");
}

void Minty::Vulkan_Renderer::update_descriptor_sets(VkDevice const device, Span<VkWriteDescriptorSet> const &descriptorWrites)
{
	vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.get_size()), descriptorWrites.get_data(), 0, nullptr);
}

VkDescriptorSetLayout Minty::Vulkan_Renderer::create_descriptor_set_layout(VkDevice const device, Span<VkDescriptorSetLayoutBinding> const bindings)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(bindings.get_size());
	layoutInfo.pBindings = bindings.get_data();

	VK_ASSERT_RESULT_RETURN_OBJECT(VkDescriptorSetLayout, vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &object), "Failed to create descriptor set layout.");
}

void Minty::Vulkan_Renderer::destroy_descriptor_set_layout(VkDevice const device, VkDescriptorSetLayout const layout)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(layout != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroyDescriptorSetLayout(device, layout, nullptr);
}

VkDescriptorPool Minty::Vulkan_Renderer::create_descriptor_pool(VkDevice const device, Span<VkDescriptorPoolSize> const poolSizes, uint32_t const maxSets)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.get_size());
	poolInfo.pPoolSizes = poolSizes.get_data();
	poolInfo.maxSets = maxSets;

	VK_ASSERT_RESULT_RETURN_OBJECT(VkDescriptorPool, vkCreateDescriptorPool(device, &poolInfo, nullptr, &object), "Failed to create descriptor pool.");
}

void Minty::Vulkan_Renderer::destroy_descriptor_pool(VkDevice const device, VkDescriptorPool const pool)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(pool != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroyDescriptorPool(device, pool, nullptr);
}

VkPipelineLayout Minty::Vulkan_Renderer::create_pipeline_layout(VkDevice const device, Span<VkDescriptorSetLayout> const setLayouts, Span<VkPushConstantRange> const pushConstantRanges)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(setLayouts.get_size());
	pipelineLayoutInfo.pSetLayouts = setLayouts.get_data();
	pipelineLayoutInfo.pushConstantRangeCount = static_cast<uint32_t>(pushConstantRanges.get_size());
	pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.get_data();

	VK_ASSERT_RESULT_RETURN_OBJECT(VkPipelineLayout, vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &object), "Failed to create pipeline layout.");
}

void Minty::Vulkan_Renderer::destroy_pipeline_layout(VkDevice const device, VkPipelineLayout const layout)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(layout != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroyPipelineLayout(device, layout, nullptr);
}

VkPipeline Minty::Vulkan_Renderer::create_graphics_pipeline(VkDevice const device, VkGraphicsPipelineCreateInfo const &pipelineInfo)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	VK_ASSERT_RESULT_RETURN_OBJECT(VkPipeline, vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &object), "Failed to create graphics pipeline.");
}

void Minty::Vulkan_Renderer::destroy_pipeline(VkDevice const device, VkPipeline const pipeline)
{
	MINTY_ASSERT(device != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT(pipeline != VK_NULL_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

	vkDestroyPipeline(device, pipeline, nullptr);
}
