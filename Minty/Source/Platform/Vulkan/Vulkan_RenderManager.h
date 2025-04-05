#pragma once
#include "Minty/Data/Array.h"
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/Image.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Render/Viewport.h"
#include "Platform/Vulkan/Vulkan_Frame.h"
#include "Platform/Vulkan/Vulkan_Swapchain.h"

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

		Owner<Vulkan_Swapchain> m_swapchain;

		Ref<Viewport> m_defaultViewport;
		Ref<Image> m_depthImage;

		Array<Frame, FRAMES_PER_FLIGHT> m_frames;
		Size m_currentFrame = 0;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_RenderManager(RenderManagerBuilder const& builder);

		~Vulkan_RenderManager();

#pragma endregion

#pragma region Get Set

	private:
		inline void advance_frame() { m_currentFrame = (m_currentFrame + 1) % FRAMES_PER_FLIGHT; }

	public:
		inline VkInstance get_instance() const { return m_instance; }

		inline VkSurfaceKHR get_surface() const { return m_surface; }

		inline VkPhysicalDevice get_physical_device() const { return m_physicalDevice; }

		inline VkDevice get_device() const { return m_device; }

		inline VkQueue get_graphics_queue() const { return m_graphicsQueue; }

		inline VkQueue get_present_queue() const { return m_presentQueue; }

		inline VkCommandPool get_command_pool() const { return m_commandPool; }

		inline Frame& get_current_frame() { return m_frames[m_currentFrame]; }

		inline Frame const& get_current_frame() const { return m_frames[m_currentFrame]; }

		// gets the current frame's command buffer
		inline VkCommandBuffer get_current_command_buffer() const { return m_frames[m_currentFrame].commandBuffer; }

		inline Vulkan_Swapchain& get_swapchain() { return *m_swapchain; }
		inline Vulkan_Swapchain const& get_swapchain() const { return *m_swapchain; }

		inline Ref<Image> const& get_depth_image() const { return m_depthImage; }

		inline Ref<Viewport> const& get_default_viewport() const override { return m_defaultViewport; }

#pragma endregion

#pragma region Methods

	private:
		void initialize_frame(Frame& frame);

		void dispose_frame(Frame& frame);

		void create_depth_resources();

		void destroy_depth_resources();

		void recreate_depth_resources();

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

		/// <summary>
		/// Creates and begins a temporary command buffer.
		/// </summary>
		/// <returns>The command buffer.</returns>
		VkCommandBuffer start_command_buffer_single();

		/// <summary>
		/// Ends, submits and destroys a temporary command buffer.
		/// </summary>
		/// <param name="commandBuffer">The command buffer.</param>
		/// <param name="queue">The queue to submit the commands to.</param>
		void finish_command_buffer_single(VkCommandBuffer const commandBuffer, VkQueue const queue);

		// recreates the swapchain (useful for resize events)
		void recreate_swapchain();

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