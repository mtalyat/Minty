#include "pch.h"
#include "Vulkan_Viewport.h"

using namespace Minty;

Minty::Vulkan_Viewport::Vulkan_Viewport(ViewportBuilder const& builder)
	: Viewport(builder)
    , m_viewport({})
	, m_scissor({})
{
	m_viewport.x = static_cast<float>(builder.viewPosition.x);
	m_viewport.y = static_cast<float>(builder.viewPosition.y);
	m_viewport.width = static_cast<float>(builder.viewSize.x);
	m_viewport.height = static_cast<float>(builder.viewSize.y);
	m_viewport.minDepth = builder.minDepth;
	m_viewport.maxDepth = builder.maxDepth;
	m_scissor.offset.x = builder.maskPosition.x;
	m_scissor.offset.y = builder.maskPosition.y;
	m_scissor.extent.width = builder.maskSize.x;
	m_scissor.extent.height = builder.maskSize.y;
}

void Minty::Vulkan_Viewport::set_position(Int2 const& position)
{
	set_view_position(position);
	set_mask_position(position);
}

void Minty::Vulkan_Viewport::set_size(UInt2 const& size)
{
	set_view_size(size);
	set_mask_size(size);
}

Int2 Minty::Vulkan_Viewport::get_view_position() const
{
	return Int2(static_cast<Int>(m_viewport.x), static_cast<Int>(m_viewport.y));
}

void Minty::Vulkan_Viewport::set_view_position(Int2 const& position)
{
	m_viewport.x = static_cast<float>(position.x);
	m_viewport.y = static_cast<float>(position.y);
}

UInt2 Minty::Vulkan_Viewport::get_view_size() const
{
	return UInt2(static_cast<UInt>(m_viewport.width), static_cast<UInt>(m_viewport.height));
}

void Minty::Vulkan_Viewport::set_view_size(UInt2 const& size)
{
	m_viewport.width = static_cast<float>(size.x);
	m_viewport.height = static_cast<float>(size.y);
}

Int2 Minty::Vulkan_Viewport::get_mask_position() const
{
	return Int2(m_scissor.offset.x, m_scissor.offset.y);
}

void Minty::Vulkan_Viewport::set_mask_position(Int2 const& position)
{
	m_scissor.offset.x = position.x;
	m_scissor.offset.y = position.y;
}

UInt2 Minty::Vulkan_Viewport::get_mask_size() const
{
	return UInt2(m_scissor.extent.width, m_scissor.extent.height);
}

void Minty::Vulkan_Viewport::set_mask_size(UInt2 const& size)
{
	m_scissor.extent.width = size.x;
	m_scissor.extent.height = size.y;
}
