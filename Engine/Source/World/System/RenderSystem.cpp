#include "pch.hpp"
#include "RenderSystem.hpp"
#include "Render/Manager/RenderManager.hpp"
#include "Scene/Scene/Scene.hpp"
#include "World/Entity/EntityManager.hpp"

#include "World/Component/CameraComponent.hpp"
#include "World/Component/MeshComponent.hpp"
#include "World/Component/TransformComponent.hpp"
#include "World/Tag/VisibleTag.hpp"

using namespace Minty;

Minty::RenderSystem::RenderSystem(Scene& scene)
	: mp_scene(&scene)
{
	MINTY_ASSERT(mp_scene != nullptr, ErrorCodeEnum::Argument_ExpectedNonNull);
}

void Minty::RenderSystem::on_render()
{
	RenderManager &renderManager = RenderManager::get_instance();

	// Start the frame
	if (!renderManager.begin_frame())
	{
		return;
	}

	EntityManager &entityManager = mp_scene->get_entity_manager();

	// Render all passes
	Vector<RenderPassHandle> const &passes = renderManager.get_passes();
	for (RenderPassHandle const handle : passes)
	{
		// Start the pass
		if (!renderManager.begin_pass(handle))
		{
			continue;
		}

		// Render each camera/view within the scene
		auto const cameraView = entityManager.view<CameraComponent>();
		for (auto &&[entity, cameraComp] : cameraView.each())
		{
			// Update the RenderView associated with this CameraComponent
			renderManager.update(cameraComp.renderViewHandle, cameraComp.camera->get_position(), cameraComp.camera->get_direction());

			// Bind the RenderView for rendering
			renderManager.bind(cameraComp.renderViewHandle);

			// Render all entities with a MeshComponent
			auto const view = entityManager.view<TransformComponent, MeshComponent, VisibleTag>();
			for (auto &&[entity, transformComp, meshComp] : view.each())
			{
				// Get the handles from the MeshComponent
				GeometryHandle const geometryHandle = meshComp.geometry;
				MaterialHandle const materialHandle = meshComp.material;
				PipelineHandle const pipelineHandle = renderManager.get_pipeline(materialHandle);

				// Bind the pipeline and material
				renderManager.bind(pipelineHandle);
				renderManager.bind(materialHandle);

				// Bind the geometry
				renderManager.bind(geometryHandle);

				// Draw the object using the transform
				renderManager.draw(transformComp.transform);
			}
		}

		// End the pass
		renderManager.end_pass();
	}

	// End the frame
	renderManager.end_frame();
}

void Minty::RenderSystem::on_load()
{
}

void Minty::RenderSystem::on_unload()
{
}
