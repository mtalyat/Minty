#ifndef MINTY_LIBRARY_VULKAN_H
#define MINTY_LIBRARY_VULKAN_H

#include "Minty/Debug/Debug.h"

// just include GLFW, it has Vulkan in it
#include "GLFW.h"

#ifdef MINTY_DEBUG
#define VK_ASSERT_RESULT(operation, message) do { VkResult result = (operation); if (result != VK_SUCCESS) { MINTY_ABORT(ErrorCode::PlatformSpecific, message); }} while (false)
#define VK_ASSERT_RESULT_RETURN_OBJECT(objectType, functionCall, message) do { objectType object = VK_NULL_HANDLE; VK_ASSERT_RESULT((functionCall), (message)); return object; } while (false)
#else // MINTY_RELEASE
#define VK_ASSERT_RESULT(operation, message) operation
#define VK_ASSERT_RESULT_RETURN_OBJECT(objectType, functionCall, message) do { objectType object = VK_NULL_HANDLE; functionCall; return object; } while (false)
#endif // MINTY_DEBUG
#define VK_ASSERT_ABORT(message) MINTY_ABORT(ErrorCode::PlatformSpecific, message)

namespace Minty
{
	constexpr Size DESCRIPTOR_POOL_SIZE = 32;
}

#endif // MINTY_LIBRARY_VULKAN_H