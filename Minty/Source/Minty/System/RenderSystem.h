#pragma once
#include "Minty/Data/BufferContainerFactory.h"
#include "Minty/System/System.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	struct CameraInfo;
	class RenderManager;
	class EntityManager;

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

		// draws the UI objects
		void render_ui(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager);

		// draws the sprites in screen space
		void render_ui_sprites(CameraInfo const& cameraInfo, RenderManager& renderManager, EntityManager& entityManager);

	public:
		void on_render() override;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}