#include "pch.h"
#include "RenderSystem.h"
#include "Minty/Component/CameraComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Component/MeshComponent.h"
#include "Minty/Component/SpriteComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Component/VisibleComponent.h"
#include "Minty/Data/BatchFactory.h"
#include "Minty/Data/BufferContainer.h"
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
{
}

void Minty::RenderSystem::render_scene(CameraInfo const& cameraInfo)
{
	RenderManager& renderManager = RenderManager::get_singleton();
	EntityManager const& entityManager = m_scene->get_entity_manager();

	render_meshes(cameraInfo, renderManager, entityManager);
	render_sprites(cameraInfo, renderManager, entityManager);
}

void Minty::RenderSystem::render_meshes(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager const& entityManager)
{
	// render enabled, visible meshes
	for (auto const& [entity, meshComp, enabledComp, visibleComp] : entityManager.view<MeshComponent const, EnabledComponent const, VisibleComponent const>().each())
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
		Matrix4 transformation;
		TransformComponent const* transformComponent = entityManager.try_get_component<TransformComponent>(entity);
		if (transformComponent)
		{
			transformation = transformComponent->transform.get_global_matrix();
		}
		else
		{
			transformation = Math::identity<Matrix4>();
		}
		material->set_input("object", &transformation, sizeof(Matrix4));

		// bind the mesh
		renderManager.bind_mesh(mesh);

		// draw the mesh
		renderManager.draw_mesh(mesh);
	}
}

void Minty::RenderSystem::render_sprites(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager const& entityManager)
{
	render_sprites_3d(cameraInfo, renderManager, entityManager);
}

void Minty::RenderSystem::render_sprites_3d(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager const& entityManager)
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

void Minty::RenderSystem::serialize(Writer& writer) const
{
}

Bool Minty::RenderSystem::deserialize(Reader& reader)
{
	return true;
}

void Minty::RenderSystem::on_render()
{
	EntityManager& entityManager = m_scene->get_entity_manager();
	RenderManager& renderManager = RenderManager::get_singleton();

	// render each camera
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
	}
}
