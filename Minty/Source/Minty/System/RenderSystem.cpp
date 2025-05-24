#include "pch.h"
#include "RenderSystem.h"
#include "Minty/Component/CameraComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Component/MeshComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Component/VisibleComponent.h"
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

void Minty::RenderSystem::render_scene(CameraInfo const& cameraInfo)
{
	render_meshes(cameraInfo);
}

void Minty::RenderSystem::render_meshes(CameraInfo const& cameraInfo)
{
	RenderManager& renderManager = RenderManager::get_singleton();
	EntityManager const& entityManager = m_scene->get_entity_manager();

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
		if (!entityManager.is_in_layer(entity, cameraInfo.camera.get_layer()))
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

		// draw the mesh
		renderManager.bind_mesh(mesh);

	}
}

void Minty::RenderSystem::serialize(Writer& writer) const
{
}

Bool Minty::RenderSystem::deserialize(Reader& reader)
{
	return true;
}

void Minty::RenderSystem::on_load()
{
}

void Minty::RenderSystem::on_unload()
{
}

void Minty::RenderSystem::on_update(Time const& time)
{

}

void Minty::RenderSystem::on_finalize()
{
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
