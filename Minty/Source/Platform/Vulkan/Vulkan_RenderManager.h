#pragma once
#include "Minty/Data/Array.h"
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/Image.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Render/RenderAttachment.h"
#include "Minty/Render/Viewport.h"
#include "Platform/Vulkan/Vulkan_Frame.h"
#include "Platform/Vulkan/Vulkan_Surface.h"

namespace Minty
{
	class Vulkan_RenderManager
		: public RenderManager
	{
#pragma region Variables

	private:
		VkInstance m_instance;
		VkDebugUtilsMessengerEXT m_debugMessenger;
		Format m_targetSurfaceFormat;
		Owner<Vulkan_Surface> m_surface;
		VkPhysicalDevice m_physicalDevice;
		VkDevice m_device;
		VkQueue m_graphicsQueue;
		VkQueue m_presentQueue;
		VkCommandPool m_commandPool;

		Owner<Viewport> m_defaultViewport;
		Owner<Image> m_depthImage;

		Array<Vulkan_Frame, FRAMES_PER_FLIGHT> m_frames;
		Size m_currentFrameIndex = 0;

		// number of passes done in the current frame
		Size m_passesMade;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_RenderManager(RenderManagerBuilder const& builder);

		~Vulkan_RenderManager()
		{
		}

#pragma endregion

#pragma region Get Set

	private:
		inline void advance_frame() { m_currentFrameIndex = (m_currentFrameIndex + 1) % FRAMES_PER_FLIGHT; }

	public:
		inline VkInstance get_instance() const { return m_instance; }

		inline VkPhysicalDevice get_physical_device() const { return m_physicalDevice; }

		inline VkDevice get_device() const { return m_device; }

		inline VkQueue get_graphics_queue() const { return m_graphicsQueue; }

		inline VkQueue get_present_queue() const { return m_presentQueue; }

		inline VkCommandPool get_command_pool() const { return m_commandPool; }

		inline Size get_current_frame_index() const { return m_currentFrameIndex; }

		inline Vulkan_Frame& get_current_frame() { return m_frames[m_currentFrameIndex]; }

		inline Vulkan_Frame const& get_current_frame() const { return m_frames[m_currentFrameIndex]; }

		// gets the current frame's command buffer
		VkCommandBuffer get_current_command_buffer() const;

		inline Ref<Image> get_depth_image() const { return m_depthImage.create_ref(); }

		inline Ref<Surface> get_surface() const override { return m_surface.create_ref().cast_to<Surface>(); }

		inline Ref<Viewport> get_default_viewport() const override { return m_defaultViewport.create_ref(); }

		Format get_color_attachment_format() const override;

		Format get_depth_attachment_format() const override;

#pragma endregion

#pragma region Methods

	private:
		void initialize_frame(Vulkan_Frame& frame);

		void dispose_frame(Vulkan_Frame& frame);

		void create_depth_resources();

		void destroy_depth_resources();

		void recreate_depth_resources();

	public:
		void initialize() override;

		void dispose() override;

		void sync() override;

		Bool start_frame() override;
		void end_frame() override;

		Bool start_pass(CameraInfo const& cameraInfo) override;
		void end_pass() override;

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

		// creates a Vulkan render attachment from the RenderAttachment
		VkAttachmentDescription create_attachment_description(RenderAttachment const& attachment) const;

#pragma region Draw

	public:
		void draw_vertices(UInt const vertexCount) const;
		void draw_indices(UInt const indexCount) const;
		void draw_instances(UInt const instanceCount, UInt const vertexCount) const;

#pragma endregion


#pragma endregion

#pragma region Statics

	public:
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