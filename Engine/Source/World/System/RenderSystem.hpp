#pragma once

/**
 * @file RenderSystem.hpp
 * @brief Header file defining the RenderSystem class.
 * @author Mitchell Talyat
 */

#include "World/Entity/Entity.hpp"
#include "Render/Type/Handle.hpp"
#include "Core/Type/Rect.hpp"
#include "Core/Type/Float2.hpp"
#include "Core/Math/Matrix4x4.hpp"

namespace Minty
{
	class Scene;
	class RenderManager;
	class EntityManager;
	class UITransform;
	struct CanvasComponent;
	struct Sprite;

	/**
	 * @brief Handles rendering the Scene.
	 */
	class RenderSystem
	{
#pragma region Type

	private:
		struct RenderInfo;
		struct RenderMap;

#pragma endregion

#pragma region Constructor

	public:
		/**
		 * @brief Creates a RenderSystem using the given Scene.
		 */
		RenderSystem(Scene& scene);

#pragma endregion

#pragma region Methods

	public:
		void on_render();

	private:
		static GeometryHandle create_sprite_quad_geometry(RenderManager &renderManager);
		static EntityHandle resolve_canvas(EntityHandle const entity, EntityManager const &entityManager);
		static Rect compute_ui_rect(UITransform const &transform, Rect const &parentRect);
		static void update_dynamic_canvas_resolution(EntityManager &entityManager);
		static Matrix4 create_ui_matrix(Rect const &rect, Float const rotation, CanvasComponent const &canvas, Float2 const spriteSize, Float2 const spritePivot);
		static Matrix4 create_ui_matrix(Rect const &rect, Float const rotation, CanvasComponent const &canvas, Sprite const &sprite);

#pragma endregion

#pragma region Variables

	private:
		Scene* mp_scene;

#pragma endregion
	};
}
