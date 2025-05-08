#include "pch.h"
#include "Vulkan_Texture.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"

using namespace Minty;

/// <summary>
/// Creates a new Vulkan_Texture.
/// </summary>
/// <param name="builder">The arguments.</param>
Minty::Vulkan_Texture::Vulkan_Texture(TextureBuilder const& builder)
	: Texture(builder)
	, m_sampler(VK_NULL_HANDLE)
{
	MINTY_ASSERT(builder.filter != Filter::Undefined, "Filter must not be undefined.");
	MINTY_ASSERT(builder.addressMode != AddressMode::Undefined, "Address mode must not be undefined.");

	// create the sampler
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VkFilter filter = Vulkan_Renderer::to_vulkan(builder.filter);
	VkSamplerAddressMode addressMode = Vulkan_Renderer::to_vulkan(builder.addressMode);
	m_sampler = Vulkan_Renderer::create_sampler(
		renderManager.get_device(),
		filter,
		filter,
		addressMode,
		VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		builder.normalizeCoordinates
	);
}

Minty::Vulkan_Texture::~Vulkan_Texture()
{
	// destroy the sampler
	Vulkan_Renderer::destroy_sampler(Vulkan_RenderManager::get_singleton().get_device(), m_sampler);
}
