#pragma once
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/RenderManager.h"

namespace Minty
{
	class Vulkan_RenderManager
		: public RenderManager
	{
#pragma region Variables

	private:
		VkInstance m_instance;
		VkDebugUtilsMessengerEXT m_debugMessenger;
		VkSurfaceKHR m_surface;
		VkPhysicalDevice m_physicalDevice;
		VkDevice m_device;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;
		VkCommandPool m_commandPool;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_RenderManager(RenderManagerBuilder const& builder);

		~Vulkan_RenderManager();

#pragma endregion

#pragma region Get Set

	public:
		inline VkInstance get_instance() const { return m_instance; }

		inline VkSurfaceKHR get_surface() const { return m_surface; }

		inline VkPhysicalDevice get_physical_device() const { return m_physicalDevice; }

		inline VkDevice get_device() const { return m_device; }

		inline VkQueue get_graphics_queue() const { return m_graphicsQueue; }

		inline VkQueue get_present_queue() const { return m_presentQueue; }

		inline VkCommandPool get_command_pool() const { return m_commandPool; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Prepares to render a frame.
		/// </summary>
		/// <returns>True, on success. Returns false when the frame should be skipped.</returns>
		Bool start_frame();

		/// <summary>
		/// Finishes rendering a frame.
		/// </summary>
		void end_frame();

#pragma endregion


#pragma region Statics

		/// <summary>
		/// Gets the active Context's Vulkan RenderManager.
		/// </summary>
		/// <returns>The Vulkan_RenderManager.</returns>
		inline static Vulkan_RenderManager& get_singleton()
		{
			return static_cast<Vulkan_RenderManager&>(RenderManager::get_singleton());
		}

#pragma endregion

	};
}