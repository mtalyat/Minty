#pragma once
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/Texture.h"

namespace Minty
{
	class Vulkan_Texture
		: public Texture
	{
#pragma region Variables

	private:
		VkSampler m_sampler;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_Texture(TextureInfo const& info);

		~Vulkan_Texture();

#pragma endregion

#pragma region Accessors

	public:
		VkSampler get_sampler() const { return m_sampler; }

#pragma endregion

	};
}