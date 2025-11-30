#pragma once
#include "Minty/Render/ShaderModule.h"
#include "Minty/Library/Vulkan.h"

namespace Minty
{
	class Vulkan_ShaderModule
		: public ShaderModule
	{
#pragma region Variables

	private:
		VkShaderModule m_shaderModule;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_ShaderModule(ShaderModuleInfo const& info);

		~Vulkan_ShaderModule() override;

#pragma endregion

#pragma region Methods

	public:
		Any get_native() const { return m_shaderModule; }

#pragma endregion
	};
}