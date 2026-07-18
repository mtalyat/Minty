#pragma once

/**
 * @file Vulkan_Macro.h
 * @brief Header file defining macros for Vulkan error handling and assertions.
 * @author Mitchell Talyat
 */

#include "Core/Debug/DebugF.hpp"

#ifdef MINTY_DEBUG
#define VK_ASSERT_RESULT(operation, message) do { VkResult result = (operation); if (result != VK_SUCCESS) { MINTY_ABORT_F(ErrorCodeEnum::PlatformSpecific, message); }} while (false)
#define VK_ASSERT_RESULT_RETURN_OBJECT(objectType, functionCall, message) do { objectType object = VK_NULL_HANDLE; VK_ASSERT_RESULT((functionCall), (message)); return object; } while (false)
#else // MINTY_RELEASE
#define VK_ASSERT_RESULT(operation, message) operation
#define VK_ASSERT_RESULT_RETURN_OBJECT(objectType, functionCall, message) do { objectType object = VK_NULL_HANDLE; functionCall; return object; } while (false)
#endif // MINTY_DEBUG
#define VK_ASSERT_ABORT(message) MINTY_ABORT_F(ErrorCodeEnum::PlatformSpecific, message)