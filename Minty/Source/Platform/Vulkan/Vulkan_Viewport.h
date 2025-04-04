#pragma once
#include "Minty/Render/Viewport.h"
#include "Minty/Library/Vulkan.h"

namespace Minty
{
	class Vulkan_Viewport
		: public Viewport
	{
#pragma region Variables

	private:
		VkViewport m_viewport;
		VkRect2D m_scissor;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_Viewport(ViewportBuilder const& builder);

		~Vulkan_Viewport() override
		{
		}

#pragma endregion

#pragma region Get Set

#pragma endregion

		void set_position(Int2 const& position) override;
		void set_size(UInt2 const& size) override;
		Int2 get_view_position() const override;
		void set_view_position(Int2 const& position) override;
		UInt2 get_view_size() const override;
		void set_view_size(UInt2 const& size) override;
		Int2 get_mask_position() const override;
		void set_mask_position(Int2 const& position) override;
		UInt2 get_mask_size() const override;
		void set_mask_size(UInt2 const& size) override;

		VkViewport const& get_viewport() const { return m_viewport; }

		VkRect2D const& get_scissor() const { return m_scissor; }
	};
}