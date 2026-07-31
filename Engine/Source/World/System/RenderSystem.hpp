#pragma once

/**
 * @file RenderSystem.hpp
 * @brief Header file defining the RenderSystem class.
 * @author Mitchell Talyat
 */



namespace Minty
{
	class Scene;

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

		void on_load();

		void on_unload();

	private:

#pragma endregion

#pragma region Variables

	private:
		Scene* mp_scene;

#pragma endregion
	};
}
