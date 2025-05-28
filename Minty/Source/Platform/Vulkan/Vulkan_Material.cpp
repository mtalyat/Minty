#include "pch.h"
#include "Vulkan_Material.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Core/Format.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Platform/Vulkan/Vulkan_Shader.h"
#include "Platform/Vulkan/Vulkan_Texture.h"
#include "Platform/Vulkan/Vulkan_Image.h"

using namespace Minty;

Minty::Vulkan_Material::Vulkan_Material(MaterialBuilder const& builder)
	: Material(builder)
	, m_frames()
	, m_pool(VK_NULL_HANDLE)
{
	Ref<MaterialTemplate> const& materialTemplate = get_material_template();
	MINTY_ASSERT(materialTemplate != nullptr, "MaterialTemplate must not be null.");
	Ref<Vulkan_Shader> shader = materialTemplate->get_shader().cast_to<Vulkan_Shader>();
	Map<String, ShaderInput> const& inputs = shader->get_inputs();

#ifdef MINTY_DEBUG

	// check for all valid inputs
	for (auto const& [name, cargo] : get_inputs())
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

	initialize_frames(shader, descriptors);
	create_descriptor_sets(shader);
	initialize_descriptor_sets(descriptors, shader);
	set_initial_values();
}

Minty::Vulkan_Material::~Vulkan_Material()
{
	// dispose all the frames
	Array<VkDescriptorSet, FRAMES_PER_FLIGHT> descriptorSets;
	for (Size i = 0; i < FRAMES_PER_FLIGHT; i++)
	{
		FrameData& frame = m_frames.at(i);
		frame.buffers.clear();
		descriptorSets.at(i) = frame.descriptorSet;
	}
	// free descriptor sets, if the shader still exists
	Ref<MaterialTemplate> const& materialTemplate = get_material_template();
	if (materialTemplate == nullptr)
	{
		return;
	}
	Ref<Shader> const& shader = materialTemplate->get_shader();
	if (shader == nullptr)
	{
		return;
	}
	Vulkan_Renderer::free_descriptor_sets(Vulkan_RenderManager::get_singleton().get_device(), m_pool, descriptorSets);
}

void Minty::Vulkan_Material::initialize_frames(Ref<Vulkan_Shader> const& shader, Vector<ShaderInput> const& descriptors)
{
	// initialize each frame data using the descriptors
	if (!descriptors.is_empty())
	{
		// calculate number of buffers per frame
		Size bufferCount = 0;
		for (ShaderInput const& descriptor : descriptors)
		{
			if (descriptor.size > 0)
			{
				bufferCount++;
			}
		}

		// create empty frame datas
		for (Size i = 0; i < FRAMES_PER_FLIGHT; i++)
		{
			FrameData& frameData = m_frames.at(i);
			frameData.buffers.resize(bufferCount, nullptr);
		}

		// populate the frame data with buffers
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
				// get the frame data
				FrameData& frameData = m_frames.at(i);

				// get the buffer index
				Size index = shader->get_buffer_index(descriptor.name);

				// create the buffer
				BufferBuilder bufferBuilder{};
				bufferBuilder.frequent = descriptor.frequent;
				bufferBuilder.size = descriptor.size * descriptor.count;
				bufferBuilder.usage = BufferUsage::Uniform;
				frameData.buffers.at(index) = Owner<Vulkan_Buffer>(bufferBuilder);
			}
		}
	}
}

void Minty::Vulkan_Material::create_descriptor_sets(Ref<Vulkan_Shader> const& shader)
{
	// create descriptor sets for each frame
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	m_pool = shader->get_descriptor_pool(1);
	Array<VkDescriptorSet, FRAMES_PER_FLIGHT> descriptorSets = Vulkan_Renderer::allocate_descriptor_sets(renderManager.get_device(), m_pool, shader->get_descriptor_set_layout());

	// distribute to frames
	for (Size i = 0; i < FRAMES_PER_FLIGHT; i++)
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
	Ref<MaterialTemplate> const& materialTemplate = get_material_template();
	Ref<Shader> const& shader = materialTemplate->get_shader();
	Set<String> setValues;

	// set all override values in the material
	ConstantContainer container;
	for (auto const& [name, cargo] : get_inputs())
	{
		// skip if input is a push constant
		ShaderInput const& input = shader->get_input(name);
		if (input.type == ShaderInputType::PushConstant) continue;

		// compile value to one array of byte data, set that value
		container = cargo.pack();
		if (container.get_size())
		{
			set_input(name, container.get_data(), container.get_size());
		}

		// mark as set
		setValues.add(name);
	}

	// set any remaining not covered values
	for (auto const& [name, cargo] : get_material_template()->get_inputs())
	{
		// skip if override value was set
		if (setValues.contains(name)) continue;

		// skip if input is a push constant
		ShaderInput const& input = shader->get_input(name);
		if (input.type == ShaderInputType::PushConstant) continue;

		// compile default values to one array of byte data, set that value
		container = cargo.pack();
		if (container.get_size())
		{
			set_input(name, container.get_data(), container.get_size());
		}
	}
}

void Minty::Vulkan_Material::on_bind()
{
	// get command buffer
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VkCommandBuffer commandBuffer = renderManager.get_current_command_buffer();

	// get shader
	Ref<MaterialTemplate> const& materialTemplate = get_material_template();
	MINTY_ASSERT(materialTemplate != nullptr, "MaterialTemplate must not be null.");
	Ref<Vulkan_Shader> shader = materialTemplate->get_shader().cast_to<Vulkan_Shader>();
	MINTY_ASSERT(shader != nullptr, "Shader must not be null.");

	// get current frame data
	FrameData& frame = m_frames.at(renderManager.get_current_frame_index());

	// bind the descriptor set
	Vulkan_Renderer::bind_descriptor_set(
		commandBuffer,
		shader->get_pipeline_layout(),
		frame.descriptorSet,
		VK_PIPELINE_BIND_POINT_GRAPHICS
	);
}

void Minty::Vulkan_Material::set_input(String const& name, void const* const data, Size const size)
{
	// check if the input exists
	MINTY_ASSERT(data != nullptr, "Data must not be null.");
	MINTY_ASSERT(size > 0, "Size must be greater than 0.");

	// get material template
	Ref<MaterialTemplate> const& materialTemplate = get_material_template();
	MINTY_ASSERT(materialTemplate != nullptr, "MaterialTemplate must not be null.");
	MINTY_ASSERT(materialTemplate->has_input(name), F("Material does not have input with name: {}", name));

	// get shader
	Ref<Vulkan_Shader> shader = materialTemplate->get_shader().cast_to<Vulkan_Shader>();
	MINTY_ASSERT(shader != nullptr, "Shader must not be null.");

	// get the input
	ShaderInput const& input = shader->get_input(name);

	// set the data, based on the input type
	switch (input.type)
	{
	case ShaderInputType::UniformBuffer:
	case ShaderInputType::StorageBuffer:
	{
		// get the index of the buffer to use
		Size index = shader->get_buffer_index(name);

		// set the data in the buffers
		for (FrameData& frame : m_frames)
		{
			// get the buffer
			Ref<Vulkan_Buffer> vulkanBuffer = frame.buffers.at(index);

			MINTY_ASSERT(vulkanBuffer != nullptr, "Buffer must not be null.");
			MINTY_ASSERT(vulkanBuffer->get_size() == size, "Buffer size does not match the given size.");

			// set the data
			vulkanBuffer->set_data(data);
		}
		break;
	}
	case ShaderInputType::CombinedImageSampler:
	{
		AssetManager& assetManager = AssetManager::get_singleton();
		Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
		Vector<VkDescriptorImageInfo> imageInfos;

		// get the texture ids
		UUID const* textureIds = static_cast<UUID const*>(data);
		UUID textureId;
#ifdef MINTY_DEBUG
		for (UInt i = 0; i < input.count; i++)
		{
			textureId = textureIds[i];
			MINTY_ASSERT(textureId.is_valid(), "Texture ID must be valid.");
			MINTY_ASSERT(assetManager.contains(textureId), "Texture ID does not exist within the AssetManager.");
			Ref<Texture> texture = assetManager.get<Texture>(textureId);
			MINTY_ASSERT(texture != nullptr, "Texture must not be null.");
			Ref<Image> const& image = texture->get_image();
			MINTY_ASSERT(image != nullptr, "Image must not be null.");
		}
#endif

		for (FrameData& frame : m_frames)
		{
			// make space for image infos
			imageInfos.clear();
			imageInfos.reserve(input.count);

			// set the write info
			VkWriteDescriptorSet descriptorWrite{};
			descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrite.dstSet = frame.descriptorSet;
			descriptorWrite.dstBinding = input.binding;
			descriptorWrite.dstArrayElement = 0;
			descriptorWrite.descriptorType = Vulkan_Renderer::to_vulkan(input.type);
			descriptorWrite.descriptorCount = static_cast<uint32_t>(input.count);

			// create image info from the texture(s)
			for (UInt i = 0; i < input.count; i++)
			{
				textureId = textureIds[i];
				Ref<Vulkan_Texture> texture = assetManager.get<Texture>(textureId).cast_to<Vulkan_Texture>();
				Ref<Vulkan_Image> image = texture->get_image().cast_to<Vulkan_Image>();

				VkDescriptorImageInfo imageInfo{};
				imageInfo.sampler = static_cast<VkSampler>(texture->get_sampler());
				imageInfo.imageView = static_cast<VkImageView>(image->get_view());
				imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				imageInfos.add(imageInfo);
			}
			descriptorWrite.pImageInfo = imageInfos.get_data();

			// update the descriptor set
			Vulkan_Renderer::update_descriptor_sets(renderManager.get_device(), &descriptorWrite, 1);
		}
		break;
	}
	case ShaderInputType::PushConstant:
	{
		// get info
		Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
		VkCommandBuffer commandBuffer = renderManager.get_current_command_buffer();
		VkShaderStageFlags shaderStage = Vulkan_Renderer::to_vulkan(input.stage);
		MINTY_ASSERT(input.size == size, F("Push constant size ({}) does not match the given size ({}).", input.size, size));

		// update push constants
		Vulkan_Renderer::update_push_constants(commandBuffer, shader->get_pipeline_layout(), shaderStage, static_cast<uint32_t>(input.offset), static_cast<uint32_t>(input.size), data);

		break;
	}
	}
}
