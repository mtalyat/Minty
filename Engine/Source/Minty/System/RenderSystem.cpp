#include "pch.h"
#include "RenderSystem.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Component/CameraComponent.h"
#include "Minty/Component/CanvasComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Component/MaskComponent.h"
#include "Minty/Component/MaskedComponent.h"
#include "Minty/Component/MeshComponent.h"
#include "Minty/Component/SpriteComponent.h"
#include "Minty/Component/TextComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Component/UITransformComponent.h"
#include "Minty/Component/VisibleComponent.h"
#include "Minty/Data/BatchFactory.h"
#include "Minty/Data/BufferContainer.h"
#include "Minty/Data/Dictionary.h"
#include "Minty/Data/StaticContainer.h"
#include "Minty/Data/Vector.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Layer/LayerManager.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Render/Renderer.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Render/Shader.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

struct Minty::RenderSystem::RenderInfo
{
	Ref<Shader> shader = nullptr;
	Ref<Material> material = nullptr;
	Vector<Tuple<String, void*, Size>> inputs;
	Entity canvas = INVALID_ENTITY; // for UI rendering

	Ref<Mesh> mesh = nullptr;
	Ref<Buffer> vertexBuffer = nullptr;
	UInt instanceCount = 0;
	UInt vertexCountPerInstance = 0;
};

struct Minty::RenderSystem::RenderMap
{
	Dictionary<Int, Vector<RenderInfo>> data;

	void add(Int priority, RenderInfo&& info)
	{
		// so the highest priority is rendered first
		priority = -priority;

		// add to map
		if (!data.contains(priority))
		{
			data.add(priority, Vector<RenderInfo>());
		}
		data.at(priority).add(std::move(info));
	}
};

Minty::RenderSystem::RenderSystem(SystemInfo const& info)
	: System(info)
	, m_bufferContainerFactory(64, BufferUsage::Vertex)
	, m_canvasEntity(INVALID_ENTITY)
	, m_canvasShader(nullptr)
	, m_canvas()
{
}

void Minty::RenderSystem::render_scene(CameraData const& cameraInfo)
{
	MINTY_TRACE_SCOPE();

	RenderManager& renderManager = RenderManager::get_singleton();
	EntityManager& entityManager = m_scene->get_entity_manager();

	RenderMap renderMap;

	// add all items to the render map
	render_3d(cameraInfo, renderManager, entityManager, renderMap);
	render_ui(cameraInfo, renderManager, entityManager, renderMap);

	// render all items in the render map by priority
	for (auto const& [priority, renderInfos] : renderMap.data)
	{
		for (RenderInfo const& info : renderInfos)
		{
			// bind the resources
			renderManager.bind_shader(info.shader);
			renderManager.bind_material(info.material);

			// set the inputs
			for (auto const& [name, data, size] : info.inputs)
			{
				info.material->set_input(name, data, size);

				// free the data when done, as it was cloned when added to the render map
				deallocate(data, size, Allocator::Default);
			}

			// if there is a canvas, update it
			if(info.canvas != INVALID_ENTITY)
			{
				update_canvas(info.canvas, info.shader, entityManager);
			}

			// bind the mesh or vertex buffer
			if (info.mesh != nullptr)
			{
				renderManager.bind_mesh(info.mesh);
				renderManager.draw_mesh(info.mesh);
			}
			else if (info.vertexBuffer != nullptr && info.instanceCount > 0 && info.vertexCountPerInstance > 0)
			{
				renderManager.bind_vertex_buffer(info.vertexBuffer);
				renderManager.draw_instances(info.instanceCount, info.vertexCountPerInstance);
			}
		}
	}
}

void Minty::RenderSystem::render_3d(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap)
{
	MINTY_TRACE_SCOPE();

	render_3d_meshes(cameraInfo, renderManager, entityManager, renderMap);
	render_3d_sprites(cameraInfo, renderManager, entityManager, renderMap);
}

void Minty::RenderSystem::render_3d_meshes(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap)
{
	MINTY_TRACE_SCOPE();

	// render visible meshes
	for (auto const& [entity, meshComp, transformComp, visibleComp] : entityManager.view<MeshComponent const, TransformComponent const, VisibleComponent const>().each())
	{
		// ignore if empty
		if (meshComp.type == MeshType::Empty)
		{
			continue;
		}

		// ignore if not in correct layer
		if (!entityManager.is_in_mask(entity, cameraInfo.camera->get_layer_mask()))
		{
			MINTY_LOG(F("Entity {} (priority = {}) is not in camera priority mask ({}), skipping.", entityManager.get_entity_string(entity), entityManager.get_layer(entity), cameraInfo.camera->get_layer_mask()));
			continue;
		}

		// ignore if missing mesh or material
		if (meshComp.mesh == nullptr || meshComp.material == nullptr)
		{
			MINTY_WARNING(F("Skipping {} due to missing mesh or material.", entityManager.get_entity_string(entity)));
			continue;
		}

		// get resources
		Ref<Material> const& material = meshComp.material;
		Ref<Mesh> const& mesh = meshComp.mesh;
		Ref<MaterialTemplate> const& materialTemplate = material->get_material_template();
		Ref<Shader> const& shader = materialTemplate->get_shader();
		Matrix4 transformation = transformComp.transform.get_global_matrix();

		// add to render map
		RenderInfo info = {
			.shader = shader,
			.material = material,
			.mesh = mesh
		};
		info.inputs.add({ "object", clone(transformation, Allocator::Default), sizeof(Matrix4) });
		renderMap.add(shader->get_priority(), std::move(info));
	}
}

void Minty::RenderSystem::render_3d_sprites(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap)
{
	MINTY_TRACE_SCOPE();

	// get the number of world sprites
	auto spriteView = entityManager.view<SpriteComponent const, TransformComponent const, VisibleComponent const>();
	Size count = spriteView.get_size();

	// skip if no sprites
	if (count == 0)
	{
		return;
	}

	// calculate the size of the batch
	Size const dataSize = sizeof(Float4) + sizeof(Float2) * 3 + sizeof(Float) + sizeof(UInt) + sizeof(Matrix4);
	Size const maxDataSize = count * dataSize;

	// create each batch of sprites
	Ref<Sprite> sprite;
	Ref<Material> material;
	BatchFactory<1, Ref<Material>> batchFactory(maxDataSize);
	for (auto const& [entity, spriteComp, transformComp, visibleComp] : spriteView.each())
	{
		sprite = spriteComp.sprite;

		// skip if no sprite
		if (sprite == nullptr)
		{
			continue;
		}

		// skip if not in correct layer
		if (!entityManager.is_in_mask(entity, cameraInfo.camera->get_layer_mask()))
		{
			continue;
		}

		// get the batch based on the material
		Ref<Texture> const& texture = sprite->get_texture();
		MINTY_ASSERT(texture != nullptr, "Sprite has no texture.");
		Ref<MaterialTemplate> const& materialTemplate = spriteComp.materialTemplate;
		material = renderManager.get_default_material(texture, materialTemplate, AssetType::Sprite, Space::D3);
		Batch<1, Ref<Material>>& batch = batchFactory.get_or_create_batch({ material });

		// get the values for this instance
		Float4 instColor
		{
			spriteComp.color.rf(),
			spriteComp.color.gf(),
			spriteComp.color.bf(),
			spriteComp.color.af()
		};
		Float2 instOffset = sprite->get_render_offset();
		Float2 instSize = sprite->get_render_size();
		Float2 instPivot = sprite->get_render_pivot();
		Float2 instScale = sprite->get_render_scale();
		UInt instFlags = 0;
		if (spriteComp.flipX) instFlags |= 0x1;
		if (spriteComp.flipY) instFlags |= 0x2;
		Transform const& transform = transformComp.transform;
		Matrix4 transformGlobalMatrix = transform.get_global_matrix();
		Float4 instTransform0 = transformGlobalMatrix[0];
		Float4 instTransform1 = transformGlobalMatrix[1];
		Float4 instTransform2 = transformGlobalMatrix[2];
		Float4 instTransform3 = transformGlobalMatrix[3];

		// pack all of the data into the batch
		DynamicContainer& batchContainer = batch.get_data_container();
		batchContainer.append(&instColor, sizeof(Float4));
		batchContainer.append(&instOffset, sizeof(Float2));
		batchContainer.append(&instSize, sizeof(Float2));
		batchContainer.append(&instPivot, sizeof(Float2));
		batchContainer.append(&instScale, sizeof(Float2));
		batchContainer.append(&instFlags, sizeof(UInt));
		batchContainer.append(&instTransform0, sizeof(Float4));
		batchContainer.append(&instTransform1, sizeof(Float4));
		batchContainer.append(&instTransform2, sizeof(Float4));
		batchContainer.append(&instTransform3, sizeof(Float4));

		// one more item stored inside the batch
		batch.increment();
	}

	// render the batches
	for (auto const& batch : batchFactory)
	{
		// get resources
		Ref<Material> material = batch.get_object<Ref<Material>>(0);
		Ref<MaterialTemplate> materialTemplate = material->get_material_template();
		Ref<Shader> shader = materialTemplate->get_shader();

		// update the instanced container with the data
		BufferContainer& container = m_bufferContainerFactory.get_container(batch.get_data_size());
		container.set(batch.get_data(), batch.get_data_size());

		// add to render map
		RenderInfo info = {
			.shader = shader,
			.material = material,
			.vertexBuffer = container.get_buffer(),
			.instanceCount = static_cast<UInt>(batch.get_count()),
			.vertexCountPerInstance = 6 // 6 vertices per sprite, generated in the shader
		};
		renderMap.add(shader->get_priority(), std::move(info));
	}
}

void Minty::RenderSystem::update_canvas(Entity const entity, Ref<Shader> const& shader, EntityManager& entityManager)
{
	// skip if enitity matches the canvas entity
	if (entity == m_canvasEntity)
	{
		return;
	}

	// get canvas
	CanvasComponent* canvasComp = entityManager.try_get_component<CanvasComponent>(entity);
	MINTY_ASSERT(canvasComp != nullptr, "Failed to get Canvas component for UITransform.");
	Canvas const& canvas = canvasComp->canvas;

	// if same shader and same size, do nothing
	if (shader == m_canvasShader &&
		canvas.get_resolution() == m_canvas.get_resolution())
	{
		return;
	}

	// update Canvas global constant
	DynamicContainer canvasContainer(sizeof(Int) * 2);
	Int2 resolution = canvasComp->canvas.get_resolution();
	canvasContainer.append(&resolution.x, sizeof(Int));
	canvasContainer.append(&resolution.y, sizeof(Int));

	// update shader
	shader->set_global_input("canvas", canvasContainer.get_data(), canvasContainer.get_size());
}

void Minty::RenderSystem::render_ui(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap)
{
	MINTY_TRACE_SCOPE();

	// sort the UITransform components by depth
	entityManager.sort<UITransformComponent>([](UITransformComponent const& a, UITransformComponent const& b) -> Bool
		{
			return a.transform.get_depth() < b.transform.get_depth();
		});

	// reset canvas
	m_canvas.set_resolution(UInt2());

	// render UI
	render_ui_sprites(cameraInfo, renderManager, entityManager, renderMap);
	render_ui_meshes(cameraInfo, renderManager, entityManager, renderMap);
}

void Minty::RenderSystem::render_ui_meshes(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap)
{
	MINTY_TRACE_SCOPE();

	BatchFactory<2, Ref<Material>, Entity> batchFactory(256);
	StaticContainer pushData(sizeof(Float) * 9);
	for (auto&& [entity, enabledComp, visibleComp, uiTransformComp, textComp, meshComp] : entityManager.view<EnabledComponent const, VisibleComponent const, UITransformComponent const, TextComponent const, MeshComponent const>().each())
	{
		// skip if no mesh
		if (meshComp.mesh == nullptr || meshComp.material == nullptr)
		{
			continue;
		}

		// skip if not in correct layer
		if (!entityManager.is_in_mask(entity, cameraInfo.camera->get_layer_mask()))
		{
			continue;
		}

		// get resources
		Ref<Mesh> const& mesh = meshComp.mesh;
		Ref<Material> const& material = meshComp.material;
		Ref<MaterialTemplate> const& materialTemplate = material->get_material_template();
		MINTY_ASSERT(materialTemplate != nullptr, "Failed to get MaterialTemplate for UI Mesh.");
		Ref<Shader> const& shader = materialTemplate->get_shader();
		MINTY_ASSERT(shader != nullptr, "Failed to get Shader for UI Mesh.");

		// update push constant info
		pushData.clear();
		pushData.append_object(uiTransformComp.transform.get_global_rect().rect);
		pushData.append_object(textComp.color.to_float4());
		pushData.append_object(uiTransformComp.transform.get_depth());
		//material->set_input("push", pushData.get_data(), pushData.get_size());

		// add to render map
		RenderInfo info = {
			.shader = shader,
			.material = material,
			.canvas = uiTransformComp.canvas,
			.mesh = mesh
		};
		info.inputs.add({ "push", copy(pushData.get_data(), pushData.get_size(), Allocator::Default), pushData.get_size() });
		renderMap.add(shader->get_priority(), std::move(info));
	}
}

void Minty::RenderSystem::render_ui_sprites(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap)
{
	MINTY_TRACE_SCOPE();

	// sort by depth
	entityManager.sort<UITransformComponent>([&](UITransformComponent const& left, UITransformComponent const& right)
		{
			// sort by canvas first
			if (left.canvas != right.canvas)
			{
				return left.canvas < right.canvas;
			}

			// then by depth
			return left.transform.get_global_depth() < right.transform.get_global_depth();
		});

	// batch the UI sprites
	Ref<Material> material;
	BatchFactory<2, Ref<Material>, Entity> batchFactory(256);
	auto view = entityManager.view<UITransformComponent const, VisibleComponent const, SpriteComponent const>();
	view.use<UITransformComponent>();
	for (auto const& [entity, uiTransformComp, visibleComp, spriteComp] : view.each())
	{
		// skip if no sprite
		Ref<Sprite> const& sprite = spriteComp.sprite;
		if (sprite == nullptr)
		{
			continue;
		}

		// skip if not in correct layer
		if (!entityManager.is_in_mask(entity, cameraInfo.camera->get_layer_mask()))
		{
			continue;
		}

		// get the texture
		Ref<Texture> const& texture = sprite->get_texture();
		MINTY_ASSERT(texture != nullptr, "Sprite has no Texture.");
		Ref<MaterialTemplate> const& materialTemplate = spriteComp.materialTemplate;

		// get the material to use
		MaskMode mask = MaskMode::None;
		UInt stencil = 0;
		if (entityManager.has_component<MaskComponent>(entity))
		{
			mask = MaskMode::Write;
			stencil = entityManager.get_component<MaskComponent>(entity).value;
		} else if (entityManager.has_component<MaskedComponent>(entity))
		{
			mask = MaskMode::Test;
			stencil = entityManager.get_component<MaskedComponent>(entity).value;
		}
		material = renderManager.get_default_material(texture, materialTemplate, AssetType::Sprite, Space::UI, mask);
		MINTY_ASSERT(material != nullptr, "Failed to get default Material for UI Sprite.");
		if (mask != MaskMode::None)
		{
			material->set_stencil(stencil);
		}
		// get batch based on material and canvas
		auto& batch = batchFactory.get_or_create_batch({ material, uiTransformComp.canvas });
		DynamicContainer& batchContainer = batch.get_data_container();

		// get instance data
		Float4 instRect = uiTransformComp.transform.get_global_rect().rect;
		Float4 instSprite = sprite->get_render_rect().rect;
		Float4 instColor = spriteComp.color.to_float4();
		Float2 instPivot = sprite->get_render_pivot();
		Float instDepth = 0.0f; // the UITransformComponent::depth is used for sorting only
		Float instRotation = uiTransformComp.transform.get_global_rotation();

		// add data to batch
		batchContainer.append_object(instRect);
		batchContainer.append_object(instSprite);
		batchContainer.append_object(instColor);
		batchContainer.append_object(instPivot);
		batchContainer.append_object(instDepth);
		batchContainer.append_object(instRotation);

		batch.increment();
	}

	// render each batch
	for (auto const& batch : batchFactory)
	{
		// get resources
		Ref<Material> material = batch.get_object<Ref<Material>>(0);
		Ref<MaterialTemplate> const& materialTemplate = material->get_material_template();
		MINTY_ASSERT(materialTemplate != nullptr, "Failed to get material template for UI Sprite.");
		Ref<Shader> const& shader = materialTemplate->get_shader();
		MINTY_ASSERT(shader != nullptr, "Failed to get shader for UI Sprite.");
		Entity const canvasEntity = batch.get_object<Entity>(1);

		// update the instanced container with the data
		BufferContainer& container = m_bufferContainerFactory.get_container(batch.get_data_size());
		container.set(batch.get_data(), batch.get_data_size());

		RenderInfo info = {
			.shader = shader,
			.material = material,
			.canvas = canvasEntity,
			.vertexBuffer = container.get_buffer(),
			.instanceCount = static_cast<UInt>(batch.get_count()),
			.vertexCountPerInstance = 6 // 6 vertices per sprite, generated in the shader
		};
		renderMap.add(shader->get_priority(), std::move(info));
	}
}

void Minty::RenderSystem::on_render()
{
	MINTY_TRACE_SCOPE();

	// reset all buffers so they can be reused this frame
	m_bufferContainerFactory.reset();

	EntityManager& entityManager = m_scene->get_entity_manager();
	RenderManager& renderManager = RenderManager::get_singleton();

	// render each camera
	Int count = 0;
	for (auto const& [cameraEntity, cameraComp, enabledComp] : entityManager.view<CameraComponent, EnabledComponent const>().each())
	{
		// create the camera info
		TransformComponent* transformComponent = entityManager.try_get_component<TransformComponent>(cameraEntity);
		CameraData cameraInfo
		{
			.position = transformComponent ? transformComponent->transform.get_global_position() : Math::identity<Float3>(),
			.rotation = transformComponent ? transformComponent->transform.get_global_rotation() : Math::identity<Quaternion>(),
			.camera = cameraComp.camera,
			.viewport = nullptr
		};

		// start the pass
		if (!renderManager.start_pass(cameraInfo))
		{
			continue;
		}

		// draw the scene
		render_scene(cameraInfo);

		// end the pass
		renderManager.end_pass();

		count++;
	}

	MINTY_ASSERT(count > 0, "No cameras found to render from.");
}
