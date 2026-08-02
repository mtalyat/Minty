#include "pch.hpp"
#include "RenderSystem.hpp"
#include "Render/Manager/RenderManager.hpp"
#include "Scene/Scene/Scene.hpp"
#include "World/Entity/EntityManager.hpp"
#include "Core/Data/Factory.hpp"
#include "Core/Data/Batch.hpp"
#include "Core/Math/Matrix4x4.hpp"
#include "Core/Type/Float4.hpp"
#include "Core/Type/Float2.hpp"
#include "Render/Geometry/GeometryInfo.hpp"
#include "Render/Sprite/Sprite.hpp"

#include "World/Component/CameraComponent.hpp"
#include "World/Component/MeshComponent.hpp"
#include "World/Component/SpriteComponent.hpp"
#include "World/Component/TransformComponent.hpp"
#include "World/Component/UITransformComponent.hpp"
#include "World/Tag/VisibleTag.hpp"

using namespace Minty;

namespace
{
	struct SpriteQuadVertex
	{
		Float2 position;
		Float2 texCoord;
	};

	GeometryHandle create_sprite_quad_geometry(RenderManager &renderManager)
	{
		static GeometryHandle s_spriteQuadGeometry = INVALID_HANDLE;
		if (s_spriteQuadGeometry != INVALID_HANDLE)
		{
			return s_spriteQuadGeometry;
		}

		static constexpr SpriteQuadVertex quadVertices[] = {
			{{0.0f, 0.0f}, {0.0f, 0.0f}},
			{{0.0f, 1.0f}, {0.0f, 1.0f}},
			{{1.0f, 0.0f}, {1.0f, 0.0f}},
			{{1.0f, 1.0f}, {1.0f, 1.0f}}
		};
		static constexpr UInt16 quadIndices[] = {0, 1, 2, 1, 3, 2};

		GeometryInfo geometryInfo{};
		geometryInfo.vertexData = View(quadVertices, sizeof(quadVertices));
		geometryInfo.vertexStride = sizeof(SpriteQuadVertex);
		geometryInfo.indexData = View(quadIndices, sizeof(quadIndices));
		geometryInfo.indexType = GeometryIndexType{GeometryIndexTypeEnum::UInt16};

		s_spriteQuadGeometry = renderManager.create(geometryInfo);
		return s_spriteQuadGeometry;
	}
}

Minty::RenderSystem::RenderSystem(Scene &scene)
	: mp_scene(&scene)
{
	MINTY_ASSERT(mp_scene != nullptr, ErrorCodeEnum::Argument_ExpectedNonNull);
}

void Minty::RenderSystem::on_render()
{
	RenderManager &renderManager = RenderManager::get_instance();

	using SpriteBatch = Batch<Matrix4x4, Float4, Float2, Float2, Float2, Float, UInt32, Float2>;

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
		auto const cameraView = entityManager.view<CameraComponent, TransformComponent>();
		for (auto &&[entity, cameraComp, transformComp] : cameraView.each())
		{
			// Update the RenderView orientation
			renderManager.update(cameraComp.renderViewHandle, transformComp.transform.get_position(), transformComp.transform.get_forward());

			// Bind the RenderView for rendering
			renderManager.bind(cameraComp.renderViewHandle);

			// Render all entities with a MeshComponent
			auto const meshView = entityManager.view<TransformComponent, MeshComponent, VisibleTag>();
			for (auto &&[entity, transformComp, meshComp] : meshView.each())
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

			// Render all entities with a SpriteComponent
			Factory<MaterialHandle, SpriteBatch> spriteBatchFactory;
			auto const spriteView = entityManager.view<TransformComponent, SpriteComponent, VisibleTag>();
			for (auto &&[entity, transformComp, spriteComp] : spriteView.each())
			{
				// Get the handles from the SpriteComponent
				SpriteHandle const spriteHandle = spriteComp.spriteHandle;
				MaterialHandle const materialHandle = spriteComp.materialHandle;

				// Get the sprite information
				Sprite const &sprite = renderManager.get(spriteHandle);
				UInt2 const textureSize = renderManager.get_size(sprite.get_texture_handle());

				// Get the batch for this material, or create a new one if it doesn't exist
				SpriteBatch &spriteBatch = spriteBatchFactory.get_or_create(materialHandle);

				// Add the sprite to the batch
				spriteBatch.add_group(
					transformComp.transform.get_global_matrix(),
					spriteComp.color.to_float4(),
					sprite.get_offset(),
					sprite.get_size(),
					sprite.get_pivot(),
					sprite.get_scale(),
					static_cast<UInt32>(spriteComp.flipState),
					Float2(static_cast<Float>(textureSize.x), static_cast<Float>(textureSize.y)));
			}

			// Bind the shared quad geometry for sprite instancing
			GeometryHandle const spriteGeometryHandle = create_sprite_quad_geometry(renderManager);
			renderManager.bind(spriteGeometryHandle);

			// Render all sprite batches
			for (auto &&[materialHandle, spriteBatch] : spriteBatchFactory)
			{
				// Get the pipeline for this material
				PipelineHandle const pipelineHandle = renderManager.get_pipeline(materialHandle);

				// Bind the pipeline and material
				renderManager.bind(pipelineHandle);
				renderManager.bind(materialHandle);

				// Draw the batch
				renderManager.draw_batch(
					spriteBatch.get_group_count(),
					View(spriteBatch.get_data(), spriteBatch.get_size()));
			}
		}

		// End the pass
		renderManager.end_pass();
	}

	// End the frame
	renderManager.end_frame();
}
