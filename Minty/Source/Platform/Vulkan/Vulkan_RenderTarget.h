#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/RenderTarget.h"

namespace Minty
{
	class Vulkan_RenderTarget
		: public RenderTarget
	{
#pragma region Variables

	private:
		Vector<VkFramebuffer> m_framebuffers;
		UInt2 m_size;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_RenderTarget(RenderTargetBuilder const& builder);

		~Vulkan_RenderTarget() override;

#pragma endregion

#pragma region Get Set

	public:
		UInt2 get_size() const override { return m_size; }

		inline VkFramebuffer get_framebuffer(Size const index) const { return m_framebuffers[index]; }

#pragma endregion

#pragma region Methods

	private:
		void initialize(RenderTargetBuilder const& builder);

		void dispose();

	public:
		void refresh(RenderTargetBuilder const& builder) override;

#pragma endregion
	};
}