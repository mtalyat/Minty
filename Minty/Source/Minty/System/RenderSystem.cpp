#include "pch.h"
#include "RenderSystem.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Component/CameraComponent.h"
#include "Minty/Component/CanvasComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Component/MeshComponent.h"
#include "Minty/Component/SpriteComponent.h"
#include "Minty/Component/TextComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Component/UITransformComponent.h"
#include "Minty/Component/VisibleComponent.h"
#include "Minty/Data/BatchFactory.h"
#include "Minty/Data/BufferContainer.h"
#include "Minty/Data/StaticContainer.h"
#include "Minty/Entity/EntityManager.h"
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

Minty::RenderSystem::RenderSystem(SystemBuilder const& builder)
	: System(builder)
	, m_bufferContainerFactory(BufferUsage::Vertex)
	, m_3dSpriteGroupId(m_bufferContainerFactory.create_group())
	, m_uiSpriteGroupId(m_bufferContainerFactory.create_group())
	, m_canvasEntity(INVALID_ENTITY)
	, m_canvasShader(nullptr)
	, m_canvas()
{
}

void Minty::RenderSystem::render_scene(CameraInfo const& cameraInfo)
{
	RenderManager& renderManager = RenderManager::get_singleton();
	EntityManager& entityManager = m_scene->get_entity_manager();

	render_3d(cameraInfo, renderManager, entityManager);
	render_ui(cameraInfo, renderManager, entityManager);
}

void Minty::RenderSystem::render_3d(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager)
{
	render_3d_meshes(cameraInfo, renderManager, entityManager);
	render_3d_sprites(cameraInfo, renderManager, entityManager);
}

void Minty::RenderSystem::render_3d_meshes(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager)
{
	// render enabled, visible meshes
	for (auto const& [entity, meshComp, transformComp, enabledComp, visibleComp] : entityManager.view<MeshComponent const, TransformComponent const, EnabledComponent const, VisibleComponent const>().each())
	{
		// ignore if empty
		if (meshComp.type == MeshType::Empty)
		{
			continue;
		}

		// ignore if missing mesh or material
		if (meshComp.mesh == nullptr || meshComp.material == nullptr)
		{
			continue;
		}

		// ignore if not in correct layer
		if (!entityManager.is_in_mask(entity, cameraInfo.camera->get_layer()))
		{
			continue;
		}

		// get resources
		Ref<Material> const& material = meshComp.material;
		Ref<Mesh> const& mesh = meshComp.mesh;
		Ref<MaterialTemplate> const& materialTemplate = material->get_material_template();
		Ref<Shader> const& shader = materialTemplate->get_shader();

		// bind the resources
		renderManager.bind_shader(shader);
		renderManager.bind_material(material);

		// set the transform of the object
		Matrix4 transformation = transformComp.transform.get_global_matrix();
		material->set_input("object", &transformation, sizeof(Matrix4));

		// bind the mesh
		renderManager.bind_mesh(mesh);

		// draw the mesh
		renderManager.draw_mesh(mesh);
	}
}

void Minty::RenderSystem::render_3d_sprites(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager)
{
	// get the number of world sprites
	auto spriteView = entityManager.view<EnabledComponent const, VisibleComponent const, SpriteComponent const, TransformComponent const>();
	Size count = spriteView.get_size();

	// skip if no sprites
	if (count == 0)
	{
		return;
	}

	// calculate the size of the batch
	Size const dataSize = sizeof(Float4) + sizeof(Float2) * 3 + sizeof(Float) + sizeof(Matrix4);
	Size const maxDataSize = count * dataSize;

	// create each batch of sprites
	Ref<Sprite> sprite;
	Ref<Material> material;
	BatchFactory<1, Ref<Material>> batchFactory(maxDataSize);
	for (auto const& [entity, enabledComp, visibleComp, spriteComp, transformComp] : spriteView.each())
	{
		sprite = spriteComp.sprite;

		// skip if no sprite
		if (sprite == nullptr)
		{
			continue;
		}

		// skip if not in correct layer
		if (!entityManager.is_in_mask(entity, cameraInfo.camera->get_layer()))
		{
			continue;
		}

		// get the batch based on the material
		Ref<Texture> texture = sprite->get_texture();
		MINTY_ASSERT(texture != nullptr, "Sprite has no texture.");
		material = renderManager.get_default_material(texture, AssetType::Sprite, Space::D3);
		Batch<1, Ref<Material>>& batch = batchFactory.get_or_create_batch({ material });

		// get the values for this instance
		Float4 instColor
		{
			spriteComp.color.rf(),
			spriteComp.color.gf(),
			spriteComp.color.bf(),
			spriteComp.color.af()
		};
		Float2 instOffset = sprite->get_offset();
		Float2 instSize = sprite->get_size();
		Float2 instPivot = sprite->get_pivot();
		Float instScale = sprite->get_scale();
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
		batchContainer.append(&instScale, sizeof(Float));
		batchContainer.append(&instTransform0, sizeof(Float4));
		batchContainer.append(&instTransform1, sizeof(Float4));
		batchContainer.append(&instTransform2, sizeof(Float4));
		batchContainer.append(&instTransform3, sizeof(Float4));

		// one more item stored inside the batch
		batch.increment();
	}

	// render the batches
	Size index = 0;
	for (auto const& batch : batchFactory)
	{
		// bind batch
		Ref<Material> material = batch.get_object<Ref<Material>>(0);
		Ref<MaterialTemplate> materialTemplate = material->get_material_template();
		Ref<Shader> shader = materialTemplate->get_shader();
		renderManager.bind_shader(shader);
		renderManager.bind_material(material);

		// update the instanced container with the data
		BufferContainer& container = m_bufferContainerFactory.get_container(m_3dSpriteGroupId, index);
		container.set(batch.get_data(), batch.get_data_size());
		renderManager.bind_vertex_buffer(container.get_buffer());

		// draw the sprites
		renderManager.draw_instances(static_cast<UInt>(batch.get_count()), 6); // 6 vertices per sprite, generated in the shader

		index++;
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

void Minty::RenderSystem::render_ui(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager)
{
	// sort the UITransform components by depth
	entityManager.sort<UITransformComponent>([](UITransformComponent const& a, UITransformComponent const& b) -> Bool
		{
			return a.transform.get_depth() < b.transform.get_depth();
		});

	// reset canvas
	m_canvas.set_resolution(UInt2());

	// render UI
	render_ui_sprites(cameraInfo, renderManager, entityManager);
	render_ui_meshes(cameraInfo, renderManager, entityManager);
}

void Minty::RenderSystem::render_ui_meshes(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager)
{
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
		if (!entityManager.is_in_mask(entity, cameraInfo.camera->get_layer()))
		{
			continue;
		}

		Ref<Mesh> const& mesh = meshComp.mesh;
		Ref<Material> const& material = meshComp.material;
		Ref<MaterialTemplate> const& materialTemplate = material->get_material_template();
		MINTY_ASSERT(materialTemplate != nullptr, "Failed to get MaterialTemplate for UI Mesh.");
		Ref<Shader> const& shader = materialTemplate->get_shader();
		MINTY_ASSERT(shader != nullptr, "Failed to get Shader for UI Mesh.");

		// update canvas info
		update_canvas(uiTransformComp.canvas, shader, entityManager);

		// update push constant info
		pushData.clear();
		pushData.append_object(uiTransformComp.transform.get_global_rect().rect);
		pushData.append_object(textComp.color.to_float4());
		pushData.append_object(uiTransformComp.transform.get_depth());
		material->set_input("push", pushData.get_data(), pushData.get_size());

		// bind shader and material
		renderManager.bind_shader(shader);
		renderManager.bind_material(material);

		// bind mesh
		renderManager.bind_mesh(mesh);

		// draw the mesh
		renderManager.draw_mesh(mesh);
	}
}

void Minty::RenderSystem::render_ui_sprites(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager)
{
	// batch the UI sprites
	Ref<Material> material;
	BatchFactory<2, Ref<Material>, Entity> batchFactory(256);
	for (auto const& [entity, enabledComp, visibleComp, spriteComp, uiTransformComp] : entityManager.view<EnabledComponent const, VisibleComponent const, SpriteComponent const, UITransformComponent const>().each())
	{
		// skip if no sprite
		Ref<Sprite> const& sprite = spriteComp.sprite;
		if (sprite == nullptr)
		{
			continue;
		}

		// skip if not in correct layer
		if (!entityManager.is_in_mask(entity, cameraInfo.camera->get_layer()))
		{
			continue;
		}

		// get the texture
		Ref<Texture> const& texture = sprite->get_texture();
		MINTY_ASSERT(texture != nullptr, "Sprite has no Texture.");

		// get the material to use
		material = renderManager.get_default_material(texture, AssetType::Sprite, Space::UI);
		MINTY_ASSERT(material != nullptr, "Failed to get default Material for UI Sprite.");

		// get batch based on material and canvas
		auto& batch = batchFactory.get_or_create_batch({ material, uiTransformComp.canvas });
		DynamicContainer& batchContainer = batch.get_data_container();

		// get instance data
		Float4 instRect = uiTransformComp.transform.get_global_rect().rect;
		Float4 instSprite = sprite->get_rect().rect;
		Float4 instColor = spriteComp.color.to_float4();
		Float instDepth = uiTransformComp.transform.get_depth();

		// add data to batch
		batchContainer.append_object(instRect);
		batchContainer.append_object(instSprite);
		batchContainer.append_object(instColor);
		batchContainer.append_object(instDepth);

		batch.increment();
	}

	// render each batch
	Size index = 0;
	for (auto const& batch : batchFactory)
	{
		// get assets
		Ref<Material> material = batch.get_object<Ref<Material>>(0);
		Ref<MaterialTemplate> const& materialTemplate = material->get_material_template();
		MINTY_ASSERT(materialTemplate != nullptr, "Failed to get material template for UI Sprite.");
		Ref<Shader> const& shader = materialTemplate->get_shader();
		MINTY_ASSERT(shader != nullptr, "Failed to get shader for UI Sprite.");

		// update canvas info
		Entity const canvasEntity = batch.get_object<Entity>(1);
		update_canvas(canvasEntity, shader, entityManager);

		// bind assets
		renderManager.bind_shader(shader);
		renderManager.bind_material(material);

		// update the instanced container with the data
		BufferContainer& container = m_bufferContainerFactory.get_container(m_uiSpriteGroupId, index);
		container.set(batch.get_data(), batch.get_data_size());
		renderManager.bind_vertex_buffer(container.get_buffer());

		// draw the sprites
		renderManager.draw_instances(static_cast<UInt>(batch.get_count()), 6); // 6 vertices per sprite, generated in the shader

		index++;
	}
}

void Minty::RenderSystem::on_render()
{
	EntityManager& entityManager = m_scene->get_entity_manager();
	RenderManager& renderManager = RenderManager::get_singleton();

	// render each camera
	Int count = 0;
	for (auto const& [cameraEntity, cameraComp] : entityManager.view<CameraComponent>().each())
	{
		// create the camera info
		TransformComponent* transformComponent = entityManager.try_get_component<TransformComponent>(cameraEntity);
		CameraInfo cameraInfo
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
