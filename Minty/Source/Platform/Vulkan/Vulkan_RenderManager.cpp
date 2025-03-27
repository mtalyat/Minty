#include "pch.h"
#include "Vulkan_RenderManager.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Vector.h"
#include "Minty/Debug/Debug.h"

using namespace Minty;

#pragma region Utility

#define VK_ASSERT_RESULT(operation, message) do { VkResult result = (operation); if (result != VK_SUCCESS) { MINTY_ABORT(message); }} while (false)
#define VK_ASSERT_RESULT_RETURN_OBJECT(objectType, functionCall, message) do { objectType object = VK_NULL_HANDLE; VK_ASSERT_RESULT((functionCall), (message)); return object; } while (false)
#define VK_ASSERT_FAIL(message) throw std::runtime_error(message)

#pragma region Extensions

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

static const Vector<const Char*> validationLayers = {
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

static VkDebugUtilsMessengerEXT s_debugMessenger;

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

static void setup_debug_messenger(VkInstance const instance)
{
	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	populate_debug_messenger_create_info(createInfo);

	VK_ASSERT_RESULT(create_debug_utils_messenger_ext(instance, &createInfo, nullptr, &s_debugMessenger), "Failed to set up debug messenger.");
}

static void cleanup_debug_messenger(VkInstance const instance)
{
	destroy_debug_utils_messenger_ext(instance, s_debugMessenger, nullptr);
}

#endif // MINTY_DEBUG

#pragma endregion

#pragma endregion

Minty::Vulkan_RenderManager::Vulkan_RenderManager(RenderManagerBuilder const& builder)
	: RenderManager(builder)
	, m_instance(nullptr)
	, m_physicalDevice(nullptr)
	, m_device(nullptr)
{
	m_instance = create_instance();
}

Minty::Vulkan_RenderManager::~Vulkan_RenderManager()
{
	destroy_instance(m_instance);
}

VkInstance Minty::Vulkan_RenderManager::create_instance()
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

	VK_ASSERT_RESULT_RETURN_OBJECT(VkInstance, vkCreateInstance(&createInfo, nullptr, &m_instance), "Failed to create instance.");
}

void Minty::Vulkan_RenderManager::destroy_instance(VkInstance const instance)
{
	vkDestroyInstance(instance, nullptr);
}
