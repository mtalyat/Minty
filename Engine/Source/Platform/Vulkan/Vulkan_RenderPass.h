#pragma once
#include "Minty/Render/RenderPass.h"
#include "Minty/Library/Vulkan.h"

namespace Minty
{
	class Vulkan_RenderPass
		: public RenderPass
	{
#pragma region Variables

	private:
		VkRenderPass m_renderPass;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_RenderPass(RenderPassBuilder const& builder);

		~Vulkan_RenderPass() override;

#pragma endregion

#pragma region Get Set

	public:
		VkRenderPass get_render_pass() const { return m_renderPass; }

		void* get_native() const override { return m_renderPass; }

#pragma endregion


	};
}