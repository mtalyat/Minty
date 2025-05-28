#pragma once
#include "Minty/Data/BufferContainerFactory.h"
#include "Minty/System/System.h"
#include "Minty/Entity/Entity.h"
#include "Minty/UI/Canvas.h"

namespace Minty
{
	struct CameraInfo;
	class EntityManager;
	class Material;
	class RenderManager;
	class Shader;

	/// <summary>
	/// Handles rendering the Scene.
	/// </summary>
	class RenderSystem
		: public System
	{
#pragma region Variables

	private:
		BufferContainerFactory m_bufferContainerFactory;
		UUID m_3dSpriteGroupId;
		UUID m_uiSpriteGroupId;
		Entity m_canvasEntity;
		Ref<Shader> m_canvasShader;
		Canvas m_canvas;

#pragma endregion

#pragma region Constructors

	public:
		RenderSystem(SystemBuilder const& builder);

		~RenderSystem()
		{
		}

#pragma endregion

#pragma region Methods

	private:
		// draws everything
		void render_scene(CameraInfo const& cameraInfo);

		// draws the 3D objects
		void render_3d(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager);

		// draws the mesh objects
		void render_3d_meshes(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager);

		// draws the sprites
		void render_3d_sprites(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager);

		void update_canvas(Entity const entity, Ref<Shader> const& shader, EntityManager& entityManager);

		// draws the UI objects
		void render_ui(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager);

		// draws the text in screen space
		void render_ui_meshes(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager);

		// draws the sprites in screen space
		void render_ui_sprites(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager);

	public:
		void on_render() override;

#pragma endregion
	};
}