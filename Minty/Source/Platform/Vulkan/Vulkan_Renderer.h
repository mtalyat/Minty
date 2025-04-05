#pragma once
#include "Minty/Core/Type.h"
#include "Minty/Data/Vector.h"
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/BufferUsage.h"
#include "Minty/Render/Filter.h"
#include "Minty/Render/Format.h"
#include "Minty/Render/ImageAddressMode.h"
#include "Minty/Render/ImageAspect.h"
#include "Minty/Render/ImageLayout.h"
#include "Minty/Render/ImageTiling.h"
#include "Minty/Render/ImageType.h"
#include "Minty/Render/ImageUsage.h"
#include "Minty/Render/RenderAttachment.h"
#include "Minty/Render/ShaderCullMode.h"
#include "Minty/Render/ShaderFrontFace.h"
#include "Minty/Render/ShaderInputRate.h"
#include "Minty/Render/ShaderInputType.h"
#include "Minty/Render/ShaderPolygonMode.h"
#include "Minty/Render/ShaderPrimitiveTopology.h"
#include "Minty/Render/ShaderStage.h"
#include "Minty/Window/Window.h"
#include "Platform/Vulkan/Vulkan_Frame.h"
#include "Platform/Vulkan/Vulkan_Swapchain.h"
#include "Platform/Vulkan/Vulkan_QueueFamilyIndices.h"
#include "Platform/Vulkan/Vulkan_SwapchainSupportDetails.h"

namespace Minty
{
	class Vulkan_Renderer
	{
#pragma region Constructors

	private:
		Vulkan_Renderer() = default;
		~Vulkan_Renderer() = default;

#pragma endregion

#pragma region Statics

#pragma region Utility

#pragma region Instance

	public:
		static VkInstance create_instance();

		static void destroy_instance(VkInstance const instance);

#pragma endregion

#pragma region Debug

	public:
		static VkDebugUtilsMessengerEXT create_debug_messenger(VkInstance const instance);

		static void destroy_debug_messenger(VkInstance const instance, VkDebugUtilsMessengerEXT const debugMessenger);

#pragma endregion

#pragma region Surface

	public:
		static VkSurfaceKHR create_surface(VkInstance const instance, Ref<Window> const window);

		static void destroy_surface(VkInstance const instance, VkSurfaceKHR const surface);

#pragma endregion

#pragma region Physical Device

	private:
		static int rate_device_suitability(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface);

	public:
		static VkPhysicalDevice select_physical_device(VkInstance const instance, VkSurfaceKHR const surface, Function<int(VkPhysicalDevice, VkSurfaceKHR)> const& ratingFunction = rate_device_suitability);

		static Vulkan_SwapchainSupportDetails query_swapchain_support(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface);

		static VkSurfaceFormatKHR select_swap_surface_format(Vector<VkSurfaceFormatKHR> const& availableFormats, VkFormat const format = VK_FORMAT_B8G8R8A8_SRGB, VkColorSpaceKHR const colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR);

		static VkPresentModeKHR select_swap_present_mode(Vector<VkPresentModeKHR> const& availablePresentModes, VkPresentModeKHR const presentMode = VK_PRESENT_MODE_MAILBOX_KHR);

		static VkFormat find_supported_format(VkPhysicalDevice const physicalDevice, Vector<VkFormat> const& candidates, VkImageTiling const tiling, VkFormatFeatureFlags const features);

		static VkFormat find_supported_depth_format(VkPhysicalDevice const physicalDevice);

#pragma endregion

#pragma region Queue Families

	public:
		static Vulkan_QueueFamilyIndices find_queue_families(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface);

#pragma endregion

#pragma region Device

	public:
		static VkDevice create_device(VkPhysicalDevice const physicalDevice, Vulkan_QueueFamilyIndices const& familyIndices);

		static void destroy_device(VkDevice const device);

		// waits until device idle
		static void sync_device(VkDevice const device);

		static VkQueue get_device_queue(VkDevice const device, const uint32_t index);

#pragma endregion

#pragma region Swapchain

	public:
		static VkSwapchainKHR create_swapchain(VkDevice const device, VkSurfaceKHR const surface, Vulkan_SwapchainSupportDetails const& swapchainSupport, Vulkan_QueueFamilyIndices const& queueFamilyIndices, VkSurfaceFormatKHR const surfaceFormat, VkExtent2D const extent, VkPresentModeKHR const presentMode);

		static void destroy_swapchain(VkDevice const device, VkSwapchainKHR const swapchain);

		static VkExtent2D get_swapchain_extent(VkSurfaceCapabilitiesKHR const& capabilities, Ref<Window> const& window);

		static Vector<VkImage> get_swapchain_images(VkDevice const device, VkSwapchainKHR const swapchain);

		static VkResult get_next_swapchain_image_index(VkDevice const device, VkSwapchainKHR const swapchain, VkSemaphore const waitSemaphore, uint32_t& index);

#pragma endregion

#pragma region Memory

	public:
		static uint32_t find_memory_type(VkPhysicalDevice const physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

		static VkDeviceMemory allocate_memory(VkDevice const device, VkDeviceSize const size, const uint32_t memoryTypeIndex);

		static void free_memory(VkDevice const device, VkDeviceMemory const memory);

		static void* map_memory(VkDevice const device, VkDeviceMemory const memory, VkDeviceSize const offset, VkDeviceSize const size);

		static void unmap_memory(VkDevice const device, VkDeviceMemory const memory);

#pragma endregion

#pragma region Image

	public:
		static VkImage create_image(VkDevice const device, const uint32_t width, const uint32_t height, VkImageType const type, VkFormat const format, VkImageTiling const tiling, VkImageUsageFlags const usage);

		static void destroy_image(VkDevice const device, VkImage const image);

		static VkDeviceMemory allocate_image_memory(VkDevice const device, VkPhysicalDevice const physicalDevice, VkImage const image, VkMemoryPropertyFlags const memoryProperties);

		static void bind_image_memory(VkDevice const device, VkImage const image, VkDeviceMemory const memory);

#pragma endregion

#pragma region Image View

	public:
		static VkImageView create_image_view(VkDevice const device, VkImage const image, VkFormat const format, VkImageAspectFlags const aspectFlags, VkImageViewType const viewType = VK_IMAGE_VIEW_TYPE_2D);

		static void destroy_image_view(VkDevice const device, VkImageView const imageView);

#pragma endregion

#pragma region Sampler

	public:
		static VkSampler create_sampler(VkDevice const device, VkFilter const magFilter = VK_FILTER_NEAREST, VkFilter const minFilter = VK_FILTER_NEAREST, VkSamplerAddressMode const addressMode = VK_SAMPLER_ADDRESS_MODE_REPEAT, VkBorderColor const borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK, Bool const normalizedCoordinates = true);

		static void destroy_sampler(VkDevice const device, VkSampler const sampler);

#pragma endregion

#pragma region Depth

	public:
		// checks if the given format has a stencil component
		static Bool has_stencil_component(VkFormat const format);

#pragma endregion

#pragma region Shader Module

	public:
		static VkShaderModule create_shader_module(VkDevice const device, void const* const data, Size const size);

		static void destroy_shader_module(VkDevice const device, VkShaderModule const shaderModule);

#pragma endregion

#pragma region Render Pass

	public:
		static VkRenderPass create_render_pass(VkDevice const device, VkAttachmentDescription const* const colorAttachment, VkAttachmentDescription const* const depthAttachment);

		static void destroy_render_pass(VkDevice const device, VkRenderPass const renderPass);

#pragma endregion

#pragma region Frame Buffer

	public:
		static VkFramebuffer create_framebuffer(VkDevice const device, VkRenderPass const renderPass, VkExtent2D const extent, VkImageView const colorAttachment = VK_NULL_HANDLE, VkImageView const depthAttachment = VK_NULL_HANDLE);

		static void destroy_framebuffer(VkDevice const device, VkFramebuffer const framebuffer);

#pragma endregion

#pragma region Command Pool

	public:
		static VkCommandPool create_command_pool(VkDevice const device, const uint32_t queueFamilyIndex);

		static void destroy_command_pool(VkDevice const device, VkCommandPool const pool);

#pragma endregion

#pragma region Command Buffer

	public:
		static VkCommandBuffer create_command_buffer(VkDevice const device, VkCommandPool const commandPool);

		static void destroy_command_buffer(VkDevice const device, VkCommandPool const commandPool, VkCommandBuffer const commandBuffer);

		static void begin_command_buffer(VkCommandBuffer const commandBuffer);

		static void begin_command_buffer_temp(VkCommandBuffer const commandBuffer);

		static void end_command_buffer(VkCommandBuffer const commandBuffer);

		static VkCommandBuffer start_command_buffer_single(VkDevice const device, VkCommandPool const commandPool);

		static void finish_command_buffer_single(VkDevice const device, VkCommandPool const commandPool, VkCommandBuffer const commandBuffer, VkQueue const queue);

		static void reset_command_buffer(VkCommandBuffer const commandBuffer);

		// submit and presentation
		static void submit_command_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue, VkSemaphore const waitSemaphore, VkSemaphore const signalSemaphore, VkFence const inFlightFence);

		static void submit_command_buffer(VkCommandBuffer const commandBuffer, Frame const& frame, VkQueue const queue);

		static void submit_command_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue);

#pragma endregion

#pragma region Commands

	public:
		static void begin_render_pass(VkCommandBuffer const commandBuffer, VkRenderPass const renderPass, VkFramebuffer const framebuffer, VkRect2D const renderArea, VkClearColorValue const clearColor);

		static void end_render_pass(VkCommandBuffer const commandBuffer);

		static void bind_pipeline(VkCommandBuffer const commandBuffer, VkPipeline const graphicsPipeline, VkPipelineBindPoint const bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS);

		static void bind_descriptor_set(VkCommandBuffer const commandBuffer, VkPipelineLayout const graphicsPipelineLayout, VkDescriptorSet const descriptorSet, VkPipelineBindPoint const bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS);

		static void bind_viewport(VkCommandBuffer const commandBuffer, VkViewport const& viewport);

		static void bind_scissor(VkCommandBuffer const commandBuffer, VkRect2D const& scissor);

		static void bind_vertex_buffer(VkCommandBuffer const commandBuffer, VkBuffer const buffer, uint32_t const binding = 0);

		static void bind_index_buffer(VkCommandBuffer const commandBuffer, VkBuffer const buffer, VkIndexType const indexType = VK_INDEX_TYPE_UINT16);

		static void draw(VkCommandBuffer const commandBuffer, uint32_t const vertexCount, uint32_t const instanceCount = 1);

		static void draw_indexed(VkCommandBuffer const commandBuffer, uint32_t const indexCount, uint32_t const instanceCount = 1);

		static void transition_image_layout(VkCommandBuffer const commandBuffer, VkImage const image, VkFormat const format, VkImageLayout const oldLayout, VkImageLayout const newLayout);

		static void copy_buffer_to_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue, VkBuffer const srcBuffer, VkBuffer const dstBuffer, VkDeviceSize const size);

		static void copy_buffer_to_image(VkCommandBuffer const commandBuffer, VkQueue const queue, VkBuffer const srcBuffer, VkImage const dstImage, const uint32_t width, const uint32_t height);

#pragma endregion

#pragma region Multithreading

	public:
		static VkSemaphore create_semaphore(VkDevice const device);

		static void destroy_semaphore(VkDevice const device, VkSemaphore const semaphore);

		static VkFence create_fence(VkDevice const device);

		static void destroy_fence(VkDevice const device, VkFence const fence);

		static void wait_for_fence(VkDevice const device, VkFence const fence);

		static void reset_fence(VkDevice const device, VkFence const fence);

#pragma endregion

#pragma region Presentation

	public:
		static VkResult present(VkQueue const queue, VkSwapchainKHR const swapchain, uint32_t const imageIndex, VkSemaphore const signalSemaphore);

		static VkResult present_frame(VkQueue const queue, Vulkan_Swapchain const& swapchain, Frame const& frame)
		{
			return present(queue, swapchain.get_swapchain(), swapchain.get_index(), frame.renderFinishedSemaphore);
		}

#pragma endregion

#pragma region Buffer

	public:
		static VkBuffer create_buffer(VkDevice const device, VkDeviceSize const size, VkBufferUsageFlags const usage);

		static void destroy_buffer(VkDevice const device, VkBuffer const buffer);

		static VkDeviceMemory allocate_buffer_memory(VkDevice const device, VkPhysicalDevice const physicalDevice, VkBuffer const buffer, VkMemoryPropertyFlags const memoryProperties);

		static void bind_buffer_memory(VkDevice const device, VkBuffer const buffer, VkDeviceMemory const memory);

#pragma endregion

#pragma region Descriptor Set

	public:
		static void update_descriptor_sets(VkDevice const device, VkWriteDescriptorSet* const write, uint32_t const count);

#pragma endregion

#pragma region Conversions

	public:
		static VkFormat to_vulkan(const Minty::Format format);

		static VkBufferUsageFlags to_vulkan(const Minty::BufferUsage bufferUsage);

		static VkShaderStageFlags to_vulkan(const Minty::ShaderStage shaderStage);

		static VkDescriptorType to_vulkan(const Minty::ShaderInputType type);

		static VkFormat to_vulkan(const Minty::Type type);

		static VkImageType to_vulkan(const Minty::ImageType type);

		static VkImageTiling to_vulkan(const Minty::ImageTiling tiling);

		static VkSamplerAddressMode to_vulkan(const Minty::ImageAddressMode addressMode);

		static VkImageAspectFlags to_vulkan(const Minty::ImageAspect aspect);

		static VkImageUsageFlags to_vulkan(const Minty::ImageUsage usage);

		static VkPrimitiveTopology to_vulkan(const Minty::ShaderPrimitiveTopology topology);

		static VkCullModeFlags to_vulkan(const Minty::ShaderCullMode mode);

		static VkFrontFace to_vulkan(const Minty::ShaderFrontFace frontFace);

		static VkPolygonMode to_vulkan(const Minty::ShaderPolygonMode mode);

		static VkVertexInputRate to_vulkan(const Minty::ShaderInputRate rate);

		static VkAttachmentLoadOp to_vulkan(Minty::RenderAttachment::LoadOperation const operation);

		static VkAttachmentStoreOp to_vulkan(Minty::RenderAttachment::StoreOperation const operation);

		static VkAttachmentDescription to_vulkan(Minty::RenderAttachment const& attachment);

		static VkImageLayout to_vulkan(Minty::ImageLayout const layout);

		static VkFilter to_vulkan(Minty::Filter const filter);

#pragma endregion

#pragma endregion

#pragma endregion
	};
}