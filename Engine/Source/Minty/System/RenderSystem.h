#pragma once
#include "Minty/Data/BufferContainerFactory.h"
#include "Minty/System/System.h"
#include "Minty/Entity/Entity.h"
#include "Minty/UI/Canvas.h"

namespace Minty
{
	struct CameraData;
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
#pragma region Classes

	private:
		struct RenderInfo;
		struct RenderMap;

#pragma endregion

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
		RenderSystem(SystemInfo const& info);

		~RenderSystem()
		{
		}

#pragma endregion

#pragma region Methods

	private:
		// draws everything
		void render_scene(CameraData const& cameraInfo);

		// draws the 3D objects
		void render_3d(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap);

		// draws the mesh objects
		void render_3d_meshes(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap);

		// draws the sprites
		void render_3d_sprites(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap);

		void update_canvas(Entity const entity, Ref<Shader> const& shader, EntityManager& entityManager);

		// draws the UI objects
		void render_ui(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap);

		// draws the text in screen space
		void render_ui_meshes(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap);

		// draws the sprites in screen space
		void render_ui_sprites(CameraData const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager, RenderMap& renderMap);

	public:
		void on_render() override;

#pragma endregion
	};
}