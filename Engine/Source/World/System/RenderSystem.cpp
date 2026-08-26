#include "pch.hpp"
#include "RenderSystem.hpp"
#include "Render/Manager/RenderManager.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Scene/Scene/Scene.hpp"
#include "World/Entity/EntityManager.hpp"
#include "Core/Data/Factory.hpp"
#include "Core/Data/Batch.hpp"
#include "Core/Math/Matrix4x4.hpp"
#include "Core/Type/Float4.hpp"
#include "Core/Type/Float2.hpp"
#include "Render/Geometry/GeometryInfo.hpp"
#include "Render/Sprite/Sprite.hpp"
#include "Window/Window/Window.hpp"

#include "World/Component/CameraComponent.hpp"
#include "World/Component/CanvasComponent.hpp"
#include "World/Component/MeshComponent.hpp"
#include "World/Component/RelationshipComponent.hpp"
#include "World/Component/SpriteComponent.hpp"
#include "World/Component/TextComponent.hpp"
#include "World/Component/TransformComponent.hpp"
#include "World/Component/UITransformComponent.hpp"
#include "World/Tag/VisibleTag.hpp"

using namespace Minty;

using SpriteBatch = Batch<Matrix4x4, Float4, Float2, Float2, Float2, Float, UInt32, Float2>;

GeometryHandle Minty::RenderSystem::create_sprite_quad_geometry(RenderManager &renderManager)
	{
		struct SpriteQuadVertex
		{
			Float2 position;
			Float2 texCoord;
		};

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

EntityHandle Minty::RenderSystem::resolve_canvas(EntityHandle const entity, EntityManager const &entityManager)
	{
		EntityHandle current = entity;
		while (current != INVALID_ENTITY)
		{
			if (entityManager.has<CanvasComponent>(current))
			{
				return current;
			}

			RelationshipComponent const *relationship = entityManager.try_get<RelationshipComponent const>(current);
			if (!relationship)
			{
				break;
			}

			current = relationship->parent;
		}

		return INVALID_ENTITY;
	}

Rect Minty::RenderSystem::compute_ui_rect(UITransform const &transform, Rect const &parentRect)
	{
		Float x = 0.0f;
		Float y = 0.0f;
		Float width = transform.get_width();
		Float height = transform.get_height();

		Anchor const horizontal = transform.get_anchor() & AnchorEnumFlags::Horizontal;
		Bool const hasLeft = horizontal.has_flag(AnchorEnumFlags::Left);
		Bool const hasCenter = horizontal.has_flag(AnchorEnumFlags::Center);
		Bool const hasRight = horizontal.has_flag(AnchorEnumFlags::Right);
		if (hasLeft && hasRight)
		{
			x = parentRect.x + transform.get_x();
			width = parentRect.width - transform.get_x() - transform.get_width();
		}
		else if (hasCenter && !hasLeft && !hasRight)
		{
			x = parentRect.x + transform.get_x() + (parentRect.width - width) * 0.5f;
		}
		else if (hasRight && !hasLeft)
		{
			x = parentRect.x + parentRect.width + transform.get_x() - width;
		}
		else
		{
			x = parentRect.x + transform.get_x();
		}

		Anchor const vertical = transform.get_anchor() & AnchorEnumFlags::Vertical;
		Bool const hasTop = vertical.has_flag(AnchorEnumFlags::Top);
		Bool const hasMiddle = vertical.has_flag(AnchorEnumFlags::Middle);
		Bool const hasBottom = vertical.has_flag(AnchorEnumFlags::Bottom);
		if (hasTop && hasBottom)
		{
			y = parentRect.y + transform.get_y();
			height = parentRect.height - transform.get_y() - transform.get_height();
		}
		else if (hasMiddle && !hasTop && !hasBottom)
		{
			y = parentRect.y + transform.get_y() + (parentRect.height - height) * 0.5f;
		}
		else if (hasBottom && !hasTop)
		{
			y = parentRect.y + transform.get_y();
		}
		else
		{
			y = parentRect.y + parentRect.height + transform.get_y() - height;
		}

		return Rect(x, y, width, height);
	}

void Minty::RenderSystem::update_dynamic_canvas_resolution(EntityManager &entityManager)
	{
		Int2 const framebufferSize = Window::get_main().get_framebuffer_size();
		UInt2 const resolution(
			static_cast<UInt>(Math::max(framebufferSize.x, 1)),
			static_cast<UInt>(Math::max(framebufferSize.y, 1)));

		auto const canvasView = entityManager.view<CanvasComponent>();
		for (auto &&[entity, canvasComp] : canvasView.each())
		{
			EntityHandle const entityHandle = static_cast<EntityHandle>(entity);

			if (canvasComp.resizeMode != CanvasResizeModeEnum::Dynamic)
			{
				continue;
			}

			if (canvasComp.resolution != resolution)
			{
				canvasComp.resolution = resolution;
			}

			UITransformComponent *canvasTransformComp = entityManager.try_get<UITransformComponent>(entityHandle);
			if (canvasTransformComp)
			{
				canvasTransformComp->transform.set_size(
					static_cast<Float>(resolution.x),
					static_cast<Float>(resolution.y));
			}
		}
	}

Matrix4 Minty::RenderSystem::create_ui_matrix(Rect const &rect, Float const rotation, CanvasComponent const &canvas, Float2 const spriteSize, Float2 const spritePivot)
	{
		Float2 const safeSpriteSize = {
			Math::max(spriteSize.x, 1.0f),
			Math::max(spriteSize.y, 1.0f)};

		Float const canvasWidth = Math::max(static_cast<Float>(canvas.resolution.x), 1.0f);
		Float const canvasHeight = Math::max(static_cast<Float>(canvas.resolution.y), 1.0f);

		Float const sx = rect.width / safeSpriteSize.x;
		Float const sy = rect.height / safeSpriteSize.y;

		Float const pivotX = spritePivot.x * sx;
		Float const pivotY = spritePivot.y * sy;

		Float const pivotPixelX = rect.x + pivotX;
		Float const pivotPixelY = rect.y + pivotY;

		Float const x = (pivotPixelX / canvasWidth) * 2.0f - 1.0f;
		Float const y = 1.0f - (pivotPixelY / canvasHeight) * 2.0f;
		Float const z = 0.0f;

		Float3 const position = {
			x,
			y,
			z};

		Matrix4 matrix = Math::translate(Math::identity<Matrix4>(), position);
		matrix = Math::rotate(matrix, rotation, Math::FORWARD);
		matrix = Math::scale(matrix, Float3((2.0f / canvasWidth) * sx, (2.0f / canvasHeight) * sy, 1.0f));

		return matrix;
	}

Matrix4 Minty::RenderSystem::create_ui_matrix(Rect const &rect, Float const rotation, CanvasComponent const &canvas, Sprite const &sprite)
	{
		return create_ui_matrix(
			rect,
			rotation,
			canvas,
			Float2(
				static_cast<Float>(Math::max(sprite.get_size().x, 1)),
				static_cast<Float>(Math::max(sprite.get_size().y, 1))),
			Float2(
				static_cast<Float>(sprite.get_pivot().x),
				static_cast<Float>(sprite.get_pivot().y)));
	}

Minty::RenderSystem::RenderSystem(Scene &scene)
	: mp_scene(&scene)
{
	MINTY_ASSERT(mp_scene != nullptr, ErrorCodeEnum::Argument_ExpectedNonNull);
}

void Minty::RenderSystem::on_render()
{
	RenderManager &renderManager = RenderManager::get_instance();
	ResourceManager &resourceManager = ResourceManager::get_instance();

	EntityManager &entityManager = mp_scene->get_entity_manager();
	update_dynamic_canvas_resolution(entityManager);

	struct UIRenderData
	{
		Rect rect;
		Float depth = 0.0f;
		Float rotation = 0.0f;
		EntityHandle canvas = INVALID_ENTITY;
	};

	// Render each camera/view within the scene.
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

		// Render all entities with UITransform + SpriteComponent once per pass, independent of cameras.
		Factory<MaterialHandle, SpriteBatch> uiBatchFactory;
		Map<EntityHandle, UIRenderData> uiRenderData;

		auto const uiLooseView = entityManager.view<UITransformComponent, SpriteComponent, VisibleTag>();
		for (auto &&[entity, uiTransformComp, spriteComp] : uiLooseView.each())
		{
			EntityHandle const entityHandle = static_cast<EntityHandle>(entity);

			if (entityManager.has<RelationshipComponent>(entityHandle))
			{
				continue;
			}

			EntityHandle const canvasEntity = resolve_canvas(entityHandle, entityManager);
			if (canvasEntity == INVALID_ENTITY)
			{
				continue;
			}

			CanvasComponent const *canvasComp = entityManager.try_get<CanvasComponent const>(canvasEntity);
			if (!canvasComp)
			{
				continue;
			}

			Sprite const &sprite = renderManager.get(spriteComp.spriteHandle);
			UInt2 const textureSize = renderManager.get_size(sprite.get_texture_handle());

			Rect const canvasRect(0.0f, 0.0f, static_cast<Float>(canvasComp->resolution.x), static_cast<Float>(canvasComp->resolution.y));
			Rect const globalRect = compute_ui_rect(uiTransformComp.transform, canvasRect);
			Matrix4 const transform = create_ui_matrix(globalRect, uiTransformComp.transform.get_rotation(), *canvasComp, sprite);

			UIRenderData data{};
			data.rect = globalRect;
			data.depth = uiTransformComp.transform.get_depth();
			data.rotation = uiTransformComp.transform.get_rotation();
			data.canvas = canvasEntity;
			uiRenderData.add(entityHandle, data);

			MaterialHandle const materialHandle = spriteComp.materialHandle;
			SpriteBatch &uiBatch = uiBatchFactory.get_or_create(materialHandle);
			uiBatch.add_group(
				transform,
				spriteComp.color.to_float4(),
				sprite.get_offset(),
				sprite.get_size(),
				sprite.get_pivot(),
				1.0f,
				static_cast<UInt32>(spriteComp.flipState),
				Float2(static_cast<Float>(textureSize.x), static_cast<Float>(textureSize.y)));
		}

		auto const uiHierarchyView = entityManager.view<RelationshipComponent, UITransformComponent, SpriteComponent, VisibleTag>();
		for (auto &&[entity, relationshipComp, uiTransformComp, spriteComp] : uiHierarchyView.each())
		{
			EntityHandle const entityHandle = static_cast<EntityHandle>(entity);

			EntityHandle const canvasEntity = resolve_canvas(entityHandle, entityManager);
			if (canvasEntity == INVALID_ENTITY)
			{
				continue;
			}

			CanvasComponent const *canvasComp = entityManager.try_get<CanvasComponent const>(canvasEntity);
			if (!canvasComp)
			{
				continue;
			}

			Rect parentRect(0.0f, 0.0f, static_cast<Float>(canvasComp->resolution.x), static_cast<Float>(canvasComp->resolution.y));
			Float parentDepth = 0.0f;
			Float parentRotation = 0.0f;

			if (relationshipComp.parent != INVALID_ENTITY && uiRenderData.contains(relationshipComp.parent))
			{
				UIRenderData const &parentData = uiRenderData.at(relationshipComp.parent);
				parentRect = parentData.rect;
				parentDepth = parentData.depth;
				parentRotation = parentData.rotation;
			}

			Rect const globalRect = compute_ui_rect(uiTransformComp.transform, parentRect);
			Float const globalDepth = parentDepth + uiTransformComp.transform.get_depth();
			Float const globalRotation = parentRotation + uiTransformComp.transform.get_rotation();

			UIRenderData data{};
			data.rect = globalRect;
			data.depth = globalDepth;
			data.rotation = globalRotation;
			data.canvas = canvasEntity;
			if (uiRenderData.contains(entityHandle))
			{
				uiRenderData.at(entityHandle) = data;
			}
			else
			{
				uiRenderData.add(entityHandle, data);
			}

			Sprite const &sprite = renderManager.get(spriteComp.spriteHandle);
			UInt2 const textureSize = renderManager.get_size(sprite.get_texture_handle());
			Matrix4 const transform = create_ui_matrix(globalRect, globalRotation, *canvasComp, sprite);

			MaterialHandle const materialHandle = spriteComp.materialHandle;
			SpriteBatch &uiBatch = uiBatchFactory.get_or_create(materialHandle);
			uiBatch.add_group(
				transform,
				spriteComp.color.to_float4(),
				sprite.get_offset(),
				sprite.get_size(),
				sprite.get_pivot(),
				1.0f,
				static_cast<UInt32>(spriteComp.flipState),
				Float2(static_cast<Float>(textureSize.x), static_cast<Float>(textureSize.y)));
		}

		GeometryHandle const uiGeometryHandle = create_sprite_quad_geometry(renderManager);
		renderManager.bind(uiGeometryHandle);

		for (auto &&[materialHandle, uiBatch] : uiBatchFactory)
		{
			PipelineHandle const pipelineHandle = renderManager.get_pipeline(materialHandle);
			renderManager.bind(pipelineHandle);
			renderManager.bind(materialHandle);
			renderManager.draw_batch(
				uiBatch.get_group_count(),
				View(uiBatch.get_data(), uiBatch.get_size()));
		}

		Factory<MaterialHandle, SpriteBatch> uiTextBatchFactory;

		auto const enqueue_text = [&](EntityHandle const entityHandle, UITransformComponent const &uiTransformComp, TextComponent const &textComp, Rect const &parentRect, Float const parentRotation, EntityHandle const canvasEntity)
		{
			if (textComp.fontResourceHandle == INVALID_HANDLE || textComp.materialHandle == INVALID_HANDLE)
			{
				return;
			}

			CanvasComponent const *canvasComp = entityManager.try_get<CanvasComponent const>(canvasEntity);
			if (!canvasComp)
			{
				return;
			}

			if (!resourceManager.contains<FontResource>(textComp.fontResourceHandle))
			{
				return;
			}

			FontResource const &font = resourceManager.at<FontResource>(textComp.fontResourceHandle);
			if (font.variants.is_empty())
			{
				return;
			}

			FontVariant const &variant = font.variants.begin()->get_second();
			if (variant.pages.is_empty())
			{
				return;
			}

			Rect const globalRect = compute_ui_rect(uiTransformComp.transform, parentRect);
			Float const globalRotation = parentRotation + uiTransformComp.transform.get_rotation();

			UIRenderData data{};
			data.rect = globalRect;
			data.depth = 0.0f;
			data.rotation = globalRotation;
			data.canvas = canvasEntity;
			if (uiRenderData.contains(entityHandle))
			{
				uiRenderData.at(entityHandle) = data;
			}
			else
			{
				uiRenderData.add(entityHandle, data);
			}

			Float const lineHeight = Math::max(variant.lineHeight, 1.0f);
			Float const glyphScale = Math::max(globalRect.height, 1.0f) / lineHeight;

			Float cursorX = 0.0f;
			Float cursorY = 0.0f;
			Bool hasPrevious = false;
			Char previous = '\0';

			TextureHandle const textTextureHandle = renderManager.create(variant.pages[0]);
			UInt2 const textTextureSize = renderManager.get_size(textTextureHandle);

			for (Size i = 0; i < textComp.text.get_size(); ++i)
			{
				Char const c = textComp.text[i];

				if (c == '\n')
				{
					cursorX = 0.0f;
					cursorY += lineHeight * glyphScale;
					hasPrevious = false;
					continue;
				}

				auto const glyphIt = variant.characters.find(c);
				if (glyphIt == variant.characters.end())
				{
					hasPrevious = false;
					continue;
				}

				if (hasPrevious)
				{
					Int const kerningKey = FontVariant::make_kerning_key(previous, c);
					if (variant.kernings.contains(kerningKey))
					{
						cursorX += variant.kernings.at(kerningKey) * glyphScale;
					}
				}

				FontGlyph const &glyph = glyphIt->get_second();
				if (c == ' ')
				{
					cursorX += glyph.advance * glyphScale;
					hasPrevious = true;
					previous = c;
					continue;
				}

				if (glyph.page != 0)
				{
					hasPrevious = true;
					previous = c;
					continue;
				}

				Float const glyphWidth = Math::max(glyph.size.x * glyphScale, 1.0f);
				Float const glyphHeight = Math::max(glyph.size.y * glyphScale, 1.0f);
				Float const glyphX = globalRect.x + cursorX + glyph.offset.x * glyphScale;
				Float const glyphTop = globalRect.y + globalRect.height - cursorY - glyph.offset.y * glyphScale;
				Float const glyphY = glyphTop - glyphHeight;

				Rect const glyphRect(glyphX, glyphY, glyphWidth, glyphHeight);
				Matrix4 const glyphTransform = create_ui_matrix(
					glyphRect,
					globalRotation,
					*canvasComp,
					Float2(Math::max(glyph.size.x, 1.0f), Math::max(glyph.size.y, 1.0f)),
					Float2(0.0f, 0.0f));

				SpriteBatch &batch = uiTextBatchFactory.get_or_create(textComp.materialHandle);
				batch.add_group(
					glyphTransform,
					textComp.color.to_float4(),
					glyph.position,
					glyph.size,
					Float2(0.0f, 0.0f),
					1.0f,
					0x2u,
					Float2(static_cast<Float>(textTextureSize.x), static_cast<Float>(textTextureSize.y)));

				cursorX += glyph.advance * glyphScale;
				hasPrevious = true;
				previous = c;
			}
		};

		auto const uiLooseTextView = entityManager.view<UITransformComponent, TextComponent, VisibleTag>();
		for (auto &&[entity, uiTransformComp, textComp] : uiLooseTextView.each())
		{
			EntityHandle const entityHandle = static_cast<EntityHandle>(entity);
			if (entityManager.has<RelationshipComponent>(entityHandle))
			{
				continue;
			}

			EntityHandle const canvasEntity = resolve_canvas(entityHandle, entityManager);
			if (canvasEntity == INVALID_ENTITY)
			{
				continue;
			}

			CanvasComponent const *canvasComp = entityManager.try_get<CanvasComponent const>(canvasEntity);
			if (!canvasComp)
			{
				continue;
			}

			Rect const canvasRect(0.0f, 0.0f, static_cast<Float>(canvasComp->resolution.x), static_cast<Float>(canvasComp->resolution.y));
			enqueue_text(entityHandle, uiTransformComp, textComp, canvasRect, 0.0f, canvasEntity);
		}

		auto const uiHierarchyTextView = entityManager.view<RelationshipComponent, UITransformComponent, TextComponent, VisibleTag>();
		for (auto &&[entity, relationshipComp, uiTransformComp, textComp] : uiHierarchyTextView.each())
		{
			EntityHandle const entityHandle = static_cast<EntityHandle>(entity);

			EntityHandle const canvasEntity = resolve_canvas(entityHandle, entityManager);
			if (canvasEntity == INVALID_ENTITY)
			{
				continue;
			}

			CanvasComponent const *canvasComp = entityManager.try_get<CanvasComponent const>(canvasEntity);
			if (!canvasComp)
			{
				continue;
			}

			Rect parentRect(0.0f, 0.0f, static_cast<Float>(canvasComp->resolution.x), static_cast<Float>(canvasComp->resolution.y));
			Float parentRotation = 0.0f;

			if (relationshipComp.parent != INVALID_ENTITY && uiRenderData.contains(relationshipComp.parent))
			{
				UIRenderData const &parentData = uiRenderData.at(relationshipComp.parent);
				parentRect = parentData.rect;
				parentRotation = parentData.rotation;
			}

			enqueue_text(entityHandle, uiTransformComp, textComp, parentRect, parentRotation, canvasEntity);
		}

		for (auto &&[materialHandle, batch] : uiTextBatchFactory)
		{
			PipelineHandle const pipelineHandle = renderManager.get_pipeline(materialHandle);
			renderManager.bind(pipelineHandle);
			renderManager.bind(materialHandle);
			renderManager.draw_batch(batch.get_group_count(), View(batch.get_data(), batch.get_size()));
		}

}
