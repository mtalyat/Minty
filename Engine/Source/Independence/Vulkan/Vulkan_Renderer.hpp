#pragma once

/**
 * @file Vulkan_Renderer.hpp
 * @brief Vulkan_Renderer class definition.
 * @author Mitchell Talyat
 */

#include "Vulkan_QueueFamilyIndices.hpp"
#include "Vulkan_SwapchainSupportDetails.hpp"
#include "Vulkan_Frame.hpp"
#include "Core/Data/Array.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Type/Function.hpp"
#include "Library/Vulkan/Vulkan.hpp"
#include "Render/Constant/Render.hpp"

namespace Minty
{
	struct Vulkan_SurfaceData;
	class Window;

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
		static VkSurfaceKHR create_surface(VkInstance const instance, Pointer const window);

		static void destroy_surface(VkInstance const instance, VkSurfaceKHR const surface);

#pragma endregion

#pragma region Physical Device

	private:
		static int rate_device_suitability(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface);

	public:
		static VkPhysicalDevice select_physical_device(VkInstance const instance, VkSurfaceKHR const surface, Function<int(VkPhysicalDevice, VkSurfaceKHR)> const &ratingFunction = rate_device_suitability);

		static Vulkan_SwapchainSupportDetails query_swapchain_support(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface);

		static VkSurfaceFormatKHR select_swap_surface_format(Vector<VkSurfaceFormatKHR> const &availableFormats, VkFormat const format = VK_FORMAT_B8G8R8A8_SRGB, VkColorSpaceKHR const colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR);

		static VkPresentModeKHR select_swap_present_mode(Vector<VkPresentModeKHR> const &availablePresentModes, VkPresentModeKHR const presentMode = VK_PRESENT_MODE_MAILBOX_KHR);

		static VkFormat find_supported_format(VkPhysicalDevice const physicalDevice, Vector<VkFormat> const &candidates, VkImageTiling const tiling, VkFormatFeatureFlags const features);

		static VkFormat find_supported_depth_stencil_format(VkPhysicalDevice const physicalDevice);

#pragma endregion

#pragma region Queue Families

	public:
		static Vulkan_QueueFamilyIndices find_queue_families(VkPhysicalDevice const physicalDevice, VkSurfaceKHR const surface);

#pragma endregion

#pragma region Device

	public:
		static VkDevice create_device(VkPhysicalDevice const physicalDevice, Vulkan_QueueFamilyIndices const &familyIndices);

		static void destroy_device(VkDevice const device);

		// waits until device idle
		static void sync_device(VkDevice const device);

		static VkQueue get_device_queue(VkDevice const device, const uint32_t index);

#pragma endregion

#pragma region Swapchain

	public:
		static VkSwapchainKHR create_swapchain(VkDevice const device, VkSurfaceKHR const surface, Vulkan_SwapchainSupportDetails const &swapchainSupport, Vulkan_QueueFamilyIndices const &queueFamilyIndices, VkSurfaceFormatKHR const surfaceFormat, VkExtent2D const extent, VkPresentModeKHR const presentMode);

		static void destroy_swapchain(VkDevice const device, VkSwapchainKHR const swapchain);

		static VkExtent2D get_swapchain_extent(VkSurfaceCapabilitiesKHR const &capabilities, UInt2 const &framebufferSize);

		static Vector<VkImage> get_swapchain_images(VkDevice const device, VkSwapchainKHR const swapchain);

		static VkResult get_next_swapchain_image_index(VkDevice const device, VkSwapchainKHR const swapchain, VkSemaphore const waitSemaphore, uint32_t &index);

#pragma endregion

#pragma region Memory

	public:
		static uint32_t find_memory_type(VkPhysicalDevice const physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

		static VkDeviceMemory allocate_memory(VkDevice const device, VkDeviceSize const size, const uint32_t memoryTypeIndex);

		static void free_memory(VkDevice const device, VkDeviceMemory const memory);

		static Pointer map_memory(VkDevice const device, VkDeviceMemory const memory, VkDeviceSize const offset, VkDeviceSize const size);

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
		static VkShaderModule create_shader_module(VkDevice const device, PointerConst const data, Size const size);

		static void destroy_shader_module(VkDevice const device, VkShaderModule const shaderModule);

#pragma endregion

#pragma region Render Pass

	public:
		static VkRenderPass create_render_pass(VkDevice const device, Span<VkAttachmentDescription> const colorAttachments, Span<VkAttachmentDescription> const depthAttachments);

		static void destroy_render_pass(VkDevice const device, VkRenderPass const renderPass);

#pragma endregion

#pragma region Vulkan_Frame Buffer

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

		static void submit_command_buffer(VkCommandBuffer const commandBuffer, Vulkan_Frame const &frame, VkQueue const queue);

		static void submit_command_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue);

#pragma endregion

#pragma region Commands

	public:
		static void begin_render_pass(VkCommandBuffer const commandBuffer, VkRenderPass const renderPass, VkFramebuffer const framebuffer, VkRect2D const renderArea, VkClearColorValue const clearColor);

		static void end_render_pass(VkCommandBuffer const commandBuffer);

		static void bind_pipeline(VkCommandBuffer const commandBuffer, VkPipeline const graphicsPipeline, VkPipelineBindPoint const bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS);

		static void bind_descriptor_set(VkCommandBuffer const commandBuffer, VkPipelineLayout const graphicsPipelineLayout, VkDescriptorSet const descriptorSet, uint32_t const firstSet = 0, VkPipelineBindPoint const bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS);

		static void bind_viewport(VkCommandBuffer const commandBuffer, VkViewport const &viewport);

		static void bind_scissor(VkCommandBuffer const commandBuffer, VkRect2D const &scissor);

		static void set_stencil_reference(VkCommandBuffer const commandBuffer, uint32_t const reference);

		static void bind_vertex_buffer(VkCommandBuffer const commandBuffer, VkBuffer const buffer, uint32_t const binding = 0);

		static void bind_index_buffer(VkCommandBuffer const commandBuffer, VkBuffer const buffer, VkIndexType const indexType = VK_INDEX_TYPE_UINT16);

		static void draw(VkCommandBuffer const commandBuffer, uint32_t const vertexCount, uint32_t const instanceCount = 1);

		static void draw_indexed(VkCommandBuffer const commandBuffer, uint32_t const indexCount, uint32_t const instanceCount = 1);

		static void draw_instanced(VkCommandBuffer const commandBuffer, uint32_t const instanceCount, uint32_t const vertexCount);

		static void transition_image_layout(VkCommandBuffer const commandBuffer, VkImage const image, VkFormat const format, VkImageLayout const oldLayout, VkImageLayout const newLayout);

		static void copy_buffer_to_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue, VkBuffer const srcBuffer, VkBuffer const dstBuffer, VkDeviceSize const size);

		static void copy_buffer_to_image(VkCommandBuffer const commandBuffer, VkQueue const queue, VkBuffer const srcBuffer, VkImage const dstImage, const uint32_t width, const uint32_t height);

		static void copy_image_to_buffer(VkCommandBuffer const commandBuffer, VkQueue const queue, VkImage const srcImage, VkBuffer const dstBuffer, const uint32_t width, const uint32_t height);

		static void update_push_constants(VkCommandBuffer const commandBuffer, VkPipelineLayout const pipelineLayout, VkShaderStageFlags const stageFlags, uint32_t const offset, uint32_t const size, PointerConst const data);

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

		static VkResult present_frame(VkQueue const queue, Vulkan_SurfaceData const &surface, Vulkan_Frame const &frame);

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
		static Array<VkDescriptorSet, FRAMES_PER_FLIGHT> allocate_descriptor_sets_for_frames(VkDevice const device, VkDescriptorPool const pool, VkDescriptorSetLayout const layout);

		static void free_descriptor_sets(VkDevice const device, VkDescriptorPool const pool, Span<VkDescriptorSet> const &descriptorSets);

		static void update_descriptor_sets(VkDevice const device, Span<VkWriteDescriptorSet> const &descriptorWrites);

#pragma endregion

#pragma region Descriptor Set Layout

	public:
		static VkDescriptorSetLayout create_descriptor_set_layout(VkDevice const device, Span<VkDescriptorSetLayoutBinding> const bindings);

		static void destroy_descriptor_set_layout(VkDevice const device, VkDescriptorSetLayout const layout);

#pragma endregion

#pragma region Descriptor Pool

	public:
		static VkDescriptorPool create_descriptor_pool(VkDevice const device, Span<VkDescriptorPoolSize> const poolSizes, uint32_t const maxSets);

		static void destroy_descriptor_pool(VkDevice const device, VkDescriptorPool const pool);

#pragma endregion

#pragma region Pipeline Layout

	public:
		static VkPipelineLayout create_pipeline_layout(VkDevice const device, Span<VkDescriptorSetLayout> const setLayouts, Span<VkPushConstantRange> const pushConstantRanges);

		static void destroy_pipeline_layout(VkDevice const device, VkPipelineLayout const layout);

#pragma endregion

#pragma region Pipeline

	public:
		static VkPipeline create_graphics_pipeline(VkDevice const device, VkGraphicsPipelineCreateInfo const &pipelineInfo);

		static void destroy_pipeline(VkDevice const device, VkPipeline const pipeline);

#pragma endregion

#pragma endregion

#pragma endregion
	};
}