#pragma once
#include "Minty/System/System.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	struct CameraInfo;

	/// <summary>
	/// Handles rendering the Scene.
	/// </summary>
	class RenderSystem
		: public System
	{
#pragma region Variables

	private:

#pragma endregion

#pragma region Constructors

	public:
		RenderSystem(SystemBuilder const& builder)
			: System(builder)
		{
		}

#pragma endregion

#pragma region Methods

	private:
		// draws everything
		void render_scene(CameraInfo const& cameraInfo);

		// draws the mesh objects
		void render_meshes(CameraInfo const& cameraInfo);

	public:
		void on_render() override;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}