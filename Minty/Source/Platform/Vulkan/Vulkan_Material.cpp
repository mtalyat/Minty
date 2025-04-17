#include "pch.h"
#include "Vulkan_Material.h"
#include "Minty/Core/Format.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Platform/Vulkan/Vulkan_Shader.h"

using namespace Minty;

Minty::Vulkan_Material::Vulkan_Material(MaterialBuilder const& builder)
	: Material(builder)
	, m_frames()
{
	Ref<MaterialTemplate> const& materialTemplate = get_material_template();
	MINTY_ASSERT(materialTemplate != nullptr, "MaterialTemplate must not be null.");
	Ref<Vulkan_Shader> shader = materialTemplate->get_shader().cast_to<Vulkan_Shader>();
	Map<String, ShaderInput> const& inputs = shader->get_inputs();

#ifdef MINTY_DEBUG

	// check for all valid inputs
	for (auto const& [name, cargo] : get_values())
	{
		MINTY_ASSERT(shader->contains_input(name), F("Shader does not contain input with name: {}", name));
	}

#endif // MINTY_DEBUG

	// get just descriptors
	Vector<ShaderInput> descriptors(inputs.get_size());
	for (auto const& [name, input] : inputs)
	{
		if (input.type != ShaderInputType::PushConstant)
		{
			descriptors.add(input);
		}
	}

	initialize_frames(descriptors);
	create_descriptor_sets(shader);
	initialize_descriptor_sets(descriptors, shader);
	set_initial_values();
}

void Minty::Vulkan_Material::initialize_frames(Vector<ShaderInput> const& descriptors)
{
	// initialize each frame data using the descriptors
	if (!descriptors.is_empty())
	{
		for (ShaderInput const& descriptor : descriptors)
		{
			// ignore if no size for uniform buffer
			if (descriptor.size == 0)
			{
				continue;
			}

			// create uniform data buffers for each frame
			for (Size i = 0; i < FRAMES_PER_FLIGHT; i++)
			{
				FrameData& frameData = m_frames.at(i);

				BufferBuilder bufferBuilder{};
				bufferBuilder.frequent = descriptor.frequent;
				bufferBuilder.size = descriptor.size * descriptor.count;
				bufferBuilder.usage = BufferUsage::Uniform;
				frameData.buffers.add(Owner<Vulkan_Buffer>(bufferBuilder));
			}
		}
	}
}

void Minty::Vulkan_Material::create_descriptor_sets(Ref<Vulkan_Shader> const& shader)
{
	// create descriptor sets for each frame
	Vector<VkDescriptorSetLayout> descriptorSetLayouts(FRAMES_PER_FLIGHT, shader->get_descriptor_set_layout());
	VkDescriptorSetAllocateInfo descriptorSetAllocInfo{};
	descriptorSetAllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	descriptorSetAllocInfo.descriptorPool = shader->get_descriptor_pool(1);
	descriptorSetAllocInfo.descriptorSetCount = static_cast<uint32_t>(descriptorSetLayouts.get_size());
	descriptorSetAllocInfo.pSetLayouts = descriptorSetLayouts.get_data();
	Vector<VkDescriptorSet> descriptorSets(FRAMES_PER_FLIGHT, VK_NULL_HANDLE);
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VK_ASSERT_RESULT(vkAllocateDescriptorSets(renderManager.get_device(), &descriptorSetAllocInfo, descriptorSets.get_data()), "Failed to allocate descriptor sets.");

	// distribute to frames
	for (Size i = 0; i < m_frames.get_size(); i++)
	{
		FrameData& frameData = m_frames.at(i);
		frameData.descriptorSet = descriptorSets.at(i);
	}
}

void Minty::Vulkan_Material::initialize_descriptor_sets(Vector<ShaderInput> const& descriptors, Ref<Vulkan_Shader> const& shader)
{
	// write all of the initial input values to the descriptor sets
	for (FrameData& frame : m_frames)
	{
		Vector<VkDescriptorBufferInfo> bufferInfos(descriptors.get_size());
		Vector<VkDescriptorImageInfo> imageInfos(descriptors.get_size());
		Vector<VkWriteDescriptorSet> descriptorWrites(descriptors.get_size());

		// create buffers
		for (ShaderInput const& descriptor : descriptors)
		{
			switch (descriptor.type)
			{
			case ShaderInputType::UniformBuffer:
			case ShaderInputType::StorageBuffer:
			{
				VkWriteDescriptorSet descriptorWrite{};
				descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				descriptorWrite.dstSet = frame.descriptorSet;
				descriptorWrite.dstBinding = descriptor.binding;
				descriptorWrite.dstArrayElement = 0; // if an array

				descriptorWrite.descriptorType = Vulkan_Renderer::to_vulkan(descriptor.type);
				descriptorWrite.descriptorCount = 1; // how many to update

				// buffer
				Ref<Vulkan_Buffer> vulkanBuffer = frame.buffers.at(shader->get_buffer_index(descriptor.name));

				VkDescriptorBufferInfo bufferInfo{};
				bufferInfo.buffer = static_cast<VkBuffer>(vulkanBuffer->get_native());
				bufferInfo.offset = 0;
				bufferInfo.range = VK_WHOLE_SIZE;

				bufferInfos.add(bufferInfo);
				descriptorWrite.pBufferInfo = &bufferInfos.back();

				descriptorWrites.add(descriptorWrite);
			}
			break;
			}
		}

		// update descriptor sets
		Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
		Vulkan_Renderer::update_descriptor_sets(renderManager.get_device(), descriptorWrites.get_data(), static_cast<uint32_t>(descriptorWrites.get_size()));
	}
}

void Minty::Vulkan_Material::set_initial_values()
{
	// set initial values
	Set<String> setValues;

	// set all override values in the material
	DynamicContainer container;
	for (auto const& [name, cargo] : get_values())
	{
		// compile value to one array of byte data, set that value
		collect_cargo(cargo, container);
		set_input(name, container.get_data(), container.get_size());

		// mark as set
		setValues.add(name);
	}

	// set any remaining not covered values
	for (auto const& [name, cargo] : get_material_template()->get_values())
	{
		// skip if override value was set
		if (setValues.contains(name)) continue;

		// compile default values to one array of byte data, set that value
		collect_cargo(cargo, container);
		set_input(name, container.get_data(), container.get_size());
	}
}

void Minty::Vulkan_Material::collect_cargo(Map<String, Variable> const& values, Container& container)
{
	container.clear();
	for (auto const& [name, variable] : values)
	{
		// add variable data to container
		Container const& variableContainer = variable.get_data();
		container.append(variableContainer.get_data(), variableContainer.get_size());
	}
}

void Minty::Vulkan_Material::on_bind()
{

}

void Minty::Vulkan_Material::set_input(String const& name, void const* const data, Size const size)
{
}
