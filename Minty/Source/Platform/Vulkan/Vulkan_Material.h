#pragma once
#include "Minty/Data/Array.h"
#include "Minty/Data/Vector.h"
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/ShaderInput.h"
#include "Platform/Vulkan/Vulkan_Buffer.h"

namespace Minty
{
	class Vulkan_Shader;

	class Vulkan_Material
		: public Material
	{
#pragma region Classes

	private:
		struct FrameData
		{
			Vector<Owner<Vulkan_Buffer>> buffers;
			VkDescriptorSet descriptorSet = VK_NULL_HANDLE;
		};

#pragma endregion

#pragma region Variables

	private:
		Array<FrameData, FRAMES_PER_FLIGHT> m_frames;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_Material(MaterialBuilder const& builder);

#pragma endregion

#pragma region Methods

	private:
		void initialize_frames(Ref<Vulkan_Shader> const& shader, Vector<ShaderInput> const& descriptors);

		void create_descriptor_sets(Ref<Vulkan_Shader> const& shader);

		void initialize_descriptor_sets(Vector<ShaderInput> const& descriptors, Ref<Vulkan_Shader> const& shader);

		void set_initial_values();

	public:
		void on_bind() override;

		void set_input(String const& name, void const* const data, Size const size) override;

#pragma endregion
	};
}