#include "pch.h"
#include "Vulkan_Shader.h"
#include "Minty/Core/Format.h"
#include "Minty/Render/ShaderModule.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Platform/Vulkan/Vulkan_Viewport.h"
#include "Platform/Vulkan/Vulkan_RenderPass.h"

using namespace Minty;

Minty::Vulkan_Shader::Vulkan_Shader(ShaderBuilder const& builder)
	: Shader(builder)
	, m_pipelineLayout(VK_NULL_HANDLE)
	, m_pipeline(VK_NULL_HANDLE)
	, m_bindings()
	, m_descriptorSetLayout(VK_NULL_HANDLE)
	, m_descriptorNameToBufferIndex()
	, m_descriptorTypeCounts()
	, m_descriptorPools()
{
	initialize_bindings(builder);
	initialize_descriptor_set_layout(builder);
	initialize_pipeline_layout(builder);
	initialize_pipeline(builder);
}

Minty::Vulkan_Shader::~Vulkan_Shader()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();

	// destroy pipeline
	if (m_pipeline != VK_NULL_HANDLE)
	{
		vkDestroyPipeline(renderManager.get_device(), m_pipeline, nullptr);
	}
	// destroy pipeline layout
	if (m_pipelineLayout != VK_NULL_HANDLE)
	{
		vkDestroyPipelineLayout(renderManager.get_device(), m_pipelineLayout, nullptr);
	}
	// destroy descriptor set layout
	if (m_descriptorSetLayout != VK_NULL_HANDLE)
	{
		vkDestroyDescriptorSetLayout(renderManager.get_device(), m_descriptorSetLayout, nullptr);
	}
	// destroy descriptor pools
	for (PoolData& poolData : m_descriptorPools)
	{
		vkDestroyDescriptorPool(renderManager.get_device(), poolData.pool, nullptr);
	}
}

void Minty::Vulkan_Shader::initialize_bindings(ShaderBuilder const& builder)
{
	// create a binding for each descriptor (not push constants)
	for (ShaderInput const& input : builder.inputs)
	{
		// ignore push constants
		if (input.type == ShaderInputType::PushConstant)
		{
			continue;
		}

		MINTY_ASSERT(input.count > 0, "Shader input count must be greater than 0.");
		MINTY_ASSERT(!input.name.is_empty(), "Shader input name must not be empty.");

		VkDescriptorType descriptorType = Vulkan_Renderer::to_vulkan(input.type);

		// find the binding to add the input to
		auto found = m_bindings.find(input.binding);
		if (found == m_bindings.end())
		{
			// create a new binding
			BindingData bindingData{};
			bindingData.descriptorType = descriptorType;
			bindingData.descriptorCount = input.count;
			bindingData.shaderStage = Vulkan_Renderer::to_vulkan(input.stage);
			m_bindings.add(input.binding, std::move(bindingData));
		}
		else
		{
			// add the input to the existing binding
			BindingData& bindingData = found->get_second();

			MINTY_ASSERT(bindingData.descriptorType == descriptorType, "Shader input type must match the binding type.");
			MINTY_ASSERT(bindingData.shaderStage == Vulkan_Renderer::to_vulkan(input.stage), "Shader input stage must match the binding stage.");

			bindingData.descriptorCount += input.count;
		}
		
		// add to type counts
		auto found2 = m_descriptorTypeCounts.find(descriptorType);
		if (found2 == m_descriptorTypeCounts.end())
		{
			// new type
			m_descriptorTypeCounts.add(descriptorType, input.count);
		}
		else
		{
			// existing type
			found2->get_second() += input.count;
		}

		// add name to lookup, if it has a buffer size
		if (input.size > 0)
		{
			m_descriptorNameToBufferIndex.add(input.name, input.binding);
		}
	}
}

void Minty::Vulkan_Shader::initialize_descriptor_set_layout(ShaderBuilder const& builder)
{
	// descriptor set layout
	Vector<VkDescriptorSetLayoutBinding> descriptorSetBindings;
	descriptorSetBindings.resize(m_bindings.get_size(), VkDescriptorSetLayoutBinding{});
	for (Size i = 0; i < m_bindings.get_size(); i++)
	{
		// create binding
		VkDescriptorSetLayoutBinding& binding = descriptorSetBindings.at(i);

		uint32_t bindingIndex = static_cast<UInt>(i);

		// find shader binding info
		MINTY_ASSERT(m_bindings.contains(bindingIndex), F("Missing ShaderBinding for binding: {}.", i));

		BindingData const& bindingInfo = m_bindings.at(bindingIndex);

		binding.binding = bindingIndex;
		binding.descriptorType = bindingInfo.descriptorType;
		binding.descriptorCount = bindingInfo.descriptorCount;
		binding.stageFlags = bindingInfo.shaderStage;
		binding.pImmutableSamplers = nullptr;
	}

	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(descriptorSetBindings.get_size());
	layoutInfo.pBindings = descriptorSetBindings.get_data();

	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VK_ASSERT_RESULT(vkCreateDescriptorSetLayout(renderManager.get_device(), &layoutInfo, nullptr, &m_descriptorSetLayout), "Failed to create descriptor set layout.");
}

void Minty::Vulkan_Shader::initialize_pipeline_layout(ShaderBuilder const& builder)
{
	// push constants
	Vector<VkPushConstantRange> pushConstantRanges;
	for (ShaderInput const& descriptor : builder.inputs)
	{
		// only push constants
		if (descriptor.type != ShaderInputType::PushConstant)
		{
			continue;
		}

		MINTY_ASSERT(descriptor.size > 0, "Push constant size must be greater than 0.");
		MINTY_ASSERT(descriptor.stage != ShaderStage::Undefined, "Push constant stage must not be undefined.");

		// create range for this push constant
		VkPushConstantRange pushConstantRange{};
		pushConstantRange.offset = static_cast<uint32_t>(descriptor.offset);
		pushConstantRange.size = static_cast<uint32_t>(descriptor.size);
		pushConstantRange.stageFlags = Vulkan_Renderer::to_vulkan(descriptor.stage);
		pushConstantRanges.add(pushConstantRange);
	}

	// layout
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &m_descriptorSetLayout;
	pipelineLayoutInfo.pushConstantRangeCount = static_cast<uint32_t>(pushConstantRanges.get_size());
	pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.get_data();

	// create layout
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VK_ASSERT_RESULT(vkCreatePipelineLayout(renderManager.get_device(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout), "Failed to create pipeline layout.");
}

void Minty::Vulkan_Shader::initialize_pipeline(ShaderBuilder const& builder)
{
	// vertex stage
	VkPipelineShaderStageCreateInfo vertexShaderStageInfo{};
	vertexShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertexShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertexShaderStageInfo.module = static_cast<VkShaderModule>(builder.vertexShaderModule->get_native());
	vertexShaderStageInfo.pName = builder.vertexShaderModuleEntryPoint.get_data();

	// fragment stage
	VkPipelineShaderStageCreateInfo fragmentShaderStageInfo{};
	fragmentShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragmentShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragmentShaderStageInfo.module = static_cast<VkShaderModule>(builder.fragmentShaderModule->get_native());
	fragmentShaderStageInfo.pName = builder.fragmentShaderModuleEntryPoint.get_data();

	// all stages
	VkPipelineShaderStageCreateInfo shaderStages[] = { vertexShaderStageInfo, fragmentShaderStageInfo };

	// vertex bindings and attributes
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	// vertex input bindings and attributes
	Vector<VkVertexInputBindingDescription> vertexInputBindings;
	Vector<VkVertexInputAttributeDescription> vertexInputAttributes;
	vertexInputBindings.resize(builder.vertexInput.bindings.get_size(), VkVertexInputBindingDescription{});
	for (Size i = 0; i < builder.vertexInput.bindings.get_size(); i++)
	{
		ShaderBinding const& binding = builder.vertexInput.bindings.at(i);
		VkVertexInputBindingDescription& vertexInputBinding = vertexInputBindings.at(i);
		vertexInputBinding.binding = static_cast<uint32_t>(i);
		vertexInputBinding.inputRate = Vulkan_Renderer::to_vulkan(binding.inputRate);

		uint32_t offset = 0;

		// create each attribute as well
		for (Size j = 0; j < binding.attributes.get_size(); j++)
		{
			ShaderAttribute const& attribute = binding.attributes.at(j);
			VkVertexInputAttributeDescription vertexInputAttribute{};

			// treat matrices as multiple vectors
			// all others have their own format
			switch (attribute.type)
			{
			case Type::Matrix2:
				MINTY_ASSERT(false, "Matrix2 is not supported.");
				break;
			case Type::Matrix3:
				MINTY_ASSERT(false, "Matrix3 is not supported.");
				break;
			case Type::Matrix4:
			{
				uint32_t typeSize = static_cast<uint32_t>(sizeof(Float4));
				VkFormat format = Vulkan_Renderer::to_vulkan(Type::Float4);

				for (Size k = 0; k < 4; k++)
				{
					vertexInputAttribute.location = static_cast<uint32_t>(j + k);
					vertexInputAttribute.binding = vertexInputBinding.binding;
					vertexInputAttribute.format = format;
					vertexInputAttribute.offset = offset;

					offset += typeSize;

					vertexInputAttributes.add(vertexInputAttribute);
				}

				j += 4;

				break;
			}
			default:
			{
				vertexInputAttribute.location = static_cast<uint32_t>(j);
				vertexInputAttribute.binding = vertexInputBinding.binding;
				vertexInputAttribute.format = Vulkan_Renderer::to_vulkan(attribute.type);
				vertexInputAttribute.offset = offset;

				offset += static_cast<uint32_t>(sizeof_type(attribute.type));

				vertexInputAttributes.add(vertexInputAttribute);
				break;
			}
			}
		}

		// final offset is effectively the stride
		vertexInputBinding.stride = offset;
	}

	vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexInputBindings.get_size());
	vertexInputInfo.pVertexBindingDescriptions = vertexInputBindings.get_data();
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexInputAttributes.get_size());
	vertexInputInfo.pVertexAttributeDescriptions = vertexInputAttributes.get_data();

	// topology (point, line, or triangle)
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
	inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyInfo.topology = Vulkan_Renderer::to_vulkan(builder.primitiveTopology);
	inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

	// viewport and scissor
	Ref<Vulkan_Viewport> vulkanViewport = static_cast<Ref<Vulkan_Viewport>>(builder.viewport);
	const VkViewport* viewport = &vulkanViewport->get_viewport();
	const VkRect2D* scissor = &vulkanViewport->get_scissor();

	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = scissor;

	// rasterizer
	VkPipelineRasterizationStateCreateInfo rasterizerInfo{};
	rasterizerInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizerInfo.depthClampEnable = VK_FALSE; // discard pixels outside of viewport when false, otherwise clamp
	rasterizerInfo.rasterizerDiscardEnable = VK_FALSE; // geometry will pass through rasterizer when false
	rasterizerInfo.polygonMode = Vulkan_Renderer::to_vulkan(builder.polygonMode); // how polygons are rendered (anything other than fill requires a GPU feature)
	rasterizerInfo.lineWidth = builder.lineWidth; // width of line in line/point polygon mode
	rasterizerInfo.cullMode = Vulkan_Renderer::to_vulkan(builder.cullMode); // which side to ignore
	rasterizerInfo.frontFace = Vulkan_Renderer::to_vulkan(builder.frontFace); // how to determine front side
	rasterizerInfo.depthBiasEnable = VK_FALSE;
	rasterizerInfo.depthBiasConstantFactor = 0.0f;
	rasterizerInfo.depthBiasClamp = 0.0f;
	rasterizerInfo.depthBiasSlopeFactor = 0.0f;

	// multisampling
	VkPipelineMultisampleStateCreateInfo multisampleInfo{};
	multisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampleInfo.sampleShadingEnable = VK_FALSE;
	multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampleInfo.minSampleShading = 1.0f;
	multisampleInfo.pSampleMask = nullptr;
	multisampleInfo.alphaToCoverageEnable = VK_FALSE;
	multisampleInfo.alphaToOneEnable = VK_FALSE;

	// depth stencil testing
	VkPipelineDepthStencilStateCreateInfo depthStencil{};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = VK_TRUE;
	if (builder.transparency)
	{
		// do not write if transparent, since we don't know if we can see behind the transparent object or not
		depthStencil.depthWriteEnable = VK_FALSE;
	}
	else
	{
		// write if opaque
		depthStencil.depthWriteEnable = VK_TRUE;
	}
	// replace closer pixels
	depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	// only keep within a specific range (0 to 1 is default)
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.minDepthBounds = 0.0f; // Optional
	depthStencil.maxDepthBounds = 1.0f; // Optional
	// operations
	depthStencil.stencilTestEnable = VK_FALSE;
	depthStencil.front = {}; // Optional
	depthStencil.back = {}; // Optional

	// color blending (transparency)
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	if (builder.transparency)
	{
		colorBlendAttachment.blendEnable = VK_TRUE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	}
	else
	{
		colorBlendAttachment.blendEnable = VK_FALSE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	}
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	/*
	// transparency:
	colorBlendAttachment.blendEnable = VK_TRUE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
	*/

	VkPipelineColorBlendStateCreateInfo colorBlendInfo{};
	colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendInfo.logicOpEnable = VK_FALSE;
	colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;
	colorBlendInfo.attachmentCount = 1;
	colorBlendInfo.pAttachments = &colorBlendAttachment;
	colorBlendInfo.blendConstants[0] = 0.0f;
	colorBlendInfo.blendConstants[1] = 0.0f;
	colorBlendInfo.blendConstants[2] = 0.0f;
	colorBlendInfo.blendConstants[3] = 0.0f;

	// dynamic states (viewport, scissor)
	Vector<VkDynamicState> dynamicStates = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

	VkPipelineDynamicStateCreateInfo dynamicStateInfo{};
	dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicStateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.get_size());
	dynamicStateInfo.pDynamicStates = dynamicStates.get_data();

	// create pipeline
	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;

	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssemblyInfo;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizerInfo;
	pipelineInfo.pMultisampleState = &multisampleInfo;
	pipelineInfo.pDepthStencilState = &depthStencil;
	pipelineInfo.pColorBlendState = &colorBlendInfo;
	pipelineInfo.pDynamicState = &dynamicStateInfo;

	pipelineInfo.layout = m_pipelineLayout;

	pipelineInfo.renderPass = static_cast<Ref<Vulkan_RenderPass>>(builder.renderPass)->get_render_pass();
	pipelineInfo.subpass = 0;

	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
	pipelineInfo.basePipelineIndex = -1;

	// create the pipeline
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VK_ASSERT_RESULT(vkCreateGraphicsPipelines(renderManager.get_device(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_pipeline), "Failed to create graphics pipeline.");
}

VkDescriptorPool Minty::Vulkan_Shader::create_descriptor_pool(UInt const requestedSlots)
{
	// get total number of sets, for each flight
	UInt totalCount = static_cast<UInt>(FRAMES_PER_FLIGHT * DESCRIPTOR_POOL_SIZE);

	// create pool sizes
	Vector<VkDescriptorPoolSize> poolSizes(m_descriptorTypeCounts.get_size());
	for (auto const& [type, count] : m_descriptorTypeCounts)
	{
		VkDescriptorPoolSize poolSize{};
		poolSize.type = type;
		poolSize.descriptorCount = count * totalCount;
		poolSizes.add(poolSize);
	}

	// create pool
	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.get_size());
	poolInfo.pPoolSizes = poolSizes.get_data();
	poolInfo.maxSets = totalCount;
	poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VkDescriptorPool descriptorPool;
	VK_ASSERT_RESULT(vkCreateDescriptorPool(renderManager.get_device(), &poolInfo, nullptr, &descriptorPool), "Failed to create descriptor pool.");

	// add to pools
	PoolData poolData{};
	poolData.pool = descriptorPool;
	poolData.used = requestedSlots;
	m_descriptorPools.add(std::move(poolData));

	// done
	return descriptorPool;
}

void Minty::Vulkan_Shader::on_bind()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VkCommandBuffer commandBuffer = renderManager.get_current_command_buffer();

	// bind pipeline
	Vulkan_Renderer::bind_pipeline(commandBuffer, m_pipeline, VK_PIPELINE_BIND_POINT_GRAPHICS);
}

VkDescriptorPool Minty::Vulkan_Shader::get_descriptor_pool(UInt const requestedSlots)
{
	MINTY_ASSERT(requestedSlots > 0, "Requested slots must be greater than 0.");
	MINTY_ASSERT(requestedSlots <= DESCRIPTOR_POOL_SIZE, "Requested slots must be less than or equal to the max pool size.");

	// find a pool with enough slots, use that if able
	for (PoolData& pool : m_descriptorPools)
	{
		if (pool.used + requestedSlots <= DESCRIPTOR_POOL_SIZE)
		{
			// increment used count
			pool.used += requestedSlots;

			// return for usage
			return pool.pool;
		}
	}

	// none found, create a new one
	return create_descriptor_pool(requestedSlots);
}

void Minty::Vulkan_Shader::free_descriptors(VkDescriptorPool const pool, UInt const slots)
{
	MINTY_ASSERT(slots > 0, "Slots must be greater than 0.");
	MINTY_ASSERT(pool != VK_NULL_HANDLE, "Pool is null.");

	// find the pool
	for (PoolData& poolData : m_descriptorPools)
	{
		if (poolData.pool == pool)
		{
			// decrement used count
			MINTY_ASSERT(slots <= poolData.used, "Cannot free more slots than used.");
			poolData.used -= slots;

			return;
		}
	}
	MINTY_ABORT("Failed to free descriptors: Pool not found.");
}
