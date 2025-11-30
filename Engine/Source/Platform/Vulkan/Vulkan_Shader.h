#pragma once
#include "Minty/Render/Shader.h"
#include "Minty/Library/Vulkan.h"

namespace Minty
{
	class Vulkan_Shader
		: public Shader
	{
#pragma region Types

	private:
		struct BindingData
		{
			VkShaderStageFlags shaderStage;
			VkDescriptorType descriptorType;
			uint32_t descriptorCount;
		};

		struct PoolData
		{
			VkDescriptorPool pool = VK_NULL_HANDLE;
			// descriptor slots used within the pool
			UInt used = 0;
		};

#pragma endregion

#pragma region Variables

	private:
		VkPipelineLayout m_pipelineLayout;
		VkPipeline m_pipeline;

		Map<UInt, BindingData> m_bindings;

		VkDescriptorSetLayout m_descriptorSetLayout;
		Map<String, Size> m_descriptorNameToBufferIndex;
		Map<VkDescriptorType, UInt> m_descriptorTypeCounts;

		Vector<PoolData> m_descriptorPools;

#pragma endregion


#pragma region Constructors

	public:
		Vulkan_Shader(ShaderInfo const& info);

		~Vulkan_Shader() override;

#pragma endregion

#pragma region Accessors

	public:
		VkPipelineLayout get_pipeline_layout() const { return m_pipelineLayout; }

		VkPipeline get_pipeline() const { return m_pipeline; }

		VkDescriptorSetLayout get_descriptor_set_layout() const { return m_descriptorSetLayout; }

#pragma endregion


#pragma region Methods

	private:
		void initialize_bindings(ShaderInfo const& info);

		void initialize_descriptor_set_layout(ShaderInfo const& info);

		void initialize_pipeline_layout(ShaderInfo const& info);

		void initialize_pipeline(ShaderInfo const& info);

		VkDescriptorPool create_descriptor_pool(UInt const requestedSlots);

	public:
		void on_bind() override;

		// gets a descriptor pool that has sufficient space for the requested slots
		VkDescriptorPool get_descriptor_pool(UInt const requestedSlots);

		void free_descriptors(VkDescriptorPool const pool, UInt const slots);

		Size get_buffer_index(String const& name) const
		{
			MINTY_ASSERT(m_descriptorNameToBufferIndex.contains(name), ErrorCode::Argument_KeyNotFound, name);
			return m_descriptorNameToBufferIndex.at(name);
		}

#pragma endregion
	};
}