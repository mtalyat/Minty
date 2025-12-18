#include "pch.h"
#include "Vulkan_Texture.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Minty/Render/TextureInfo.h"

using namespace Minty;

/// <summary>
/// Creates a new Vulkan_Texture.
/// </summary>
/// <param name="info">The arguments.</param>
Minty::Vulkan_Texture::Vulkan_Texture(TextureInfo const& info)
	: Texture(info)
	, m_sampler(VK_NULL_HANDLE)
{
	MINTY_ASSERT(info.filter != Filter::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.addressMode != AddressMode::Undefined, ErrorCode::Argument_ExpectedNonDefault);

	// create the sampler
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VkFilter filter = Vulkan_Renderer::to_vulkan(info.filter);
	VkSamplerAddressMode addressMode = Vulkan_Renderer::to_vulkan(info.addressMode);
	m_sampler = Vulkan_Renderer::create_sampler(
		renderManager.get_device(),
		filter,
		filter,
		addressMode,
		VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		info.normalizeCoordinates
	);
}

Minty::Vulkan_Texture::~Vulkan_Texture()
{
	// destroy the sampler
	Vulkan_Renderer::destroy_sampler(Vulkan_RenderManager::get_singleton().get_device(), m_sampler);
}
