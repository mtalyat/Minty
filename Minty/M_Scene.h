#pragma once

#pragma once

#include "M_Object.h"
#include "M_Rect.h"
#include "M_SystemManager.h"
#include "M_S_RenderSystem.h"
#include "M_S_AudioSystem.h"
#include "M_S_InputSystem.h"
#include "M_C_MouseClick.h"
#include "M_Text.h"
#include "entt.hpp"

namespace minty
{
	class Engine;
	class Game;
	class Input;
	class Sprite;

	/// <summary>
	/// A scene is a collection of entities, and other resources that will run during gameplay. Only one Scene can be loaded and running at any given time.
	/// </summary>
	class MINTY_API Scene :
		public Object
	{
	private:
		// the name of the Scene
		std::string m_name;

	protected:
		// the registry of the Game
		entt::registry* mp_registry;
		// the Game this Scene belongs to
		Game* const mp_game;
		// the Engine this Scene belongs to
		Engine* const mp_engine;

		// the manager for managing systems in this Scene
		SystemManager m_systemManager;

		// the main camera in this Scene
		entt::entity m_mainCamera;
	private:
		// the input system
		InputSystem* const mp_inputSystem;
		// the render system
		RenderSystem* const mp_renderSystem;
		// the audio system
		AudioSystem* const mp_audioSystem;
	public:
		/// <summary>
		/// Creates a new Scene from the given name and Game.
		/// </summary>
		/// <param name="name">The name of the Scene.</param>
		/// <param name="game">The Game this Scene belongs to.</param>
		Scene(std::string const& name, Game* const game);
		virtual ~Scene();

		/// <summary>
		/// Performs load methods for Systems, followed by onLoad().
		/// </summary>
		/// <returns></returns>
		int load();

		/// <summary>
		/// Called when the Scene is loaded into the Game.
		/// </summary>
		/// <returns></returns>
		virtual int onLoad() { return 0; }

		/// <summary>
		/// Preforms update methods for Systems, followed by onUpdate().
		/// </summary>
		/// <returns></returns>
		int update();

		/// <summary>
		/// Called every update loop when this Scene is loaded.
		/// </summary>
		/// <returns></returns>
		virtual int onUpdate() { return 0; }

		/// <summary>
		/// Preforms fixed update methods for Systems, followed by onFixedUpdate().
		/// </summary>
		/// <returns></returns>
		int fixedUpdate();

		/// <summary>
		/// Called very fixed update loop when this Scene is loaded.
		/// </summary>
		/// <returns></returns>
		virtual int onFixedUpdate() { return 0; }

		/// <summary>
		/// Performs unload methods for Systems, followed by onUnload().
		/// </summary>
		/// <returns></returns>
		int unload();

		/// <summary>
		/// Called when the Scene is unloaded from the Game.
		/// </summary>
		/// <returns></returns>
		virtual int onUnload() { return 0; }

		/// <summary>
		/// Gets the name of this Scene.
		/// </summary>
		/// <returns></returns>
		inline std::string const& name() const { return m_name; }

		/// <summary>
		/// Gets the main Camera entity in this Scene.
		/// </summary>
		/// <returns></returns>
		inline entt::entity& mainCamera() { return m_mainCamera; }

		/// <summary>
		/// Gets the SystemManager in this Scene.
		/// </summary>
		/// <returns></returns>
		inline SystemManager* const systemManager() { return &m_systemManager; }

		/// <summary>
		/// Gets the InputSystem for this Scene.
		/// </summary>
		/// <returns></returns>
		inline InputSystem* const inputSystem() const { return mp_inputSystem; }

		/// <summary>
		/// Gets the RenderSystem in this Scene.
		/// </summary>
		/// <returns></returns>
		inline RenderSystem* const renderSystem() const { return mp_renderSystem; }

		/// <summary>
		/// Gets the AudioSystem in this Scene.
		/// </summary>
		/// <returns></returns>
		inline AudioSystem* const audioSystem() const { return mp_audioSystem; }

		//inline UI_Canvas* mainCanvas() { return mp_mainCanvas; }

		/// <summary>
		/// Gets the Game that this Scene belongs to.
		/// </summary>
		/// <returns></returns>
		inline Game* const game() const { return mp_game; }

	protected:

		/*
				The following methods are helper methods for creating generic entities that may commonly be created within the scene.
				This helps with development of projects, and should help reduce the code that is written. For example, almost every
				scene will need an entity with a Camera component.
		*/

		/// <summary>
		/// Creates and returns an entity with the following components: Position, Size, Camera, Renderable.
		/// </summary>
		/// <returns></returns>
		entt::entity createEntity_camera(float const pivotX = 0.5f, float const pivotY = 0.5f);

		/// <summary>
		/// Creates and returns an entity with the following components: Position, Renderer, Renderable.
		/// </summary>
		/// <param name="path"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		/// <returns></returns>
		entt::entity createEntity_sprite(std::string const& path, float const x, float const y, int const layer = 0, int const order = 0, float const pivotX = 0.0f, float const pivotY = 0.0f);

		/// <summary>
		/// Creates and returns an entity with the following components: Position, Renderer, Renderable.
		/// </summary>
		/// <param name="path"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		/// <param name="pivotX"></param>
		/// <param name="pivotY"></param>
		/// <returns></returns>
		entt::entity createEntity_sprite(Sprite* const sprite, float const x, float const y, int const layer = 0, int const order = 0);

		/// <summary>
		/// Creates and returns an entity with the following components: Position, Renderer, Renderable, Collider.
		/// </summary>
		/// <param name="path"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="bounds"></param>
		/// <param name="z"></param>
		/// <returns></returns>
		entt::entity createEntity_spriteWithCollider(std::string const& path, float const x, float const y, int const layer = 0, int const order = 0, float const pivotX = 0.0f, float const pivotY = 0.0f, bool const isTrigger = false, bool const isStatic = false, bool const isDynamic = true, Rect const* const rect = nullptr);

		/// <summary>
		/// Creates and returns an entity with the following components: UI, Renderer, Renderable.
		/// </summary>
		/// <param name="path"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		/// <param name="anchorX"></param>
		/// <param name="anchorY"></param>
		/// <param name="pivotX"></param>
		/// <param name="pivotY"></param>
		/// <returns></returns>
		entt::entity createEntity_ui(std::string const& path, float const x, float const y, int const layer = 0, int const order = 0, float const pivotX = 0.0f, float const pivotY = 0.0f, float const anchorX = 0.0f, float const anchorY = 0.0f);

		/// <summary>
		/// Creates and returns an entity with the following components: UI, SpriteRenderer, Renderable.
		/// </summary>
		/// <param name="sprite"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		/// <param name="anchorX"></param>
		/// <param name="anchorY"></param>
		/// <param name="pivotX"></param>
		/// <param name="pivotY"></param>
		/// <returns></returns>
		entt::entity createEntity_ui(Sprite* const sprite, float const x, float const y, int const layer = 0, int const order = 0, float const pivotX = 0.0f, float const pivotY = 0.0f, float const anchorX = 0.0f, float const anchorY = 0.0f);

		/// <summary>
		/// Creates and returns an entity with the following components: UI, SpriteRenderer, Renderable, MouseClick, Clickable.
		/// </summary>
		/// <param name="path"></param>
		/// <param name="func"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="layer"></param>
		/// <param name="order"></param>
		/// <param name="pivotX"></param>
		/// <param name="pivotY"></param>
		/// <param name="anchorX"></param>
		/// <param name="anchorY"></param>
		/// <returns></returns>
		entt::entity createEntity_ui_button(std::string const& path, mouseclick_t::func const& func, float const x, float const y, int const layer = 0, int const order = 0, float const pivotX = 0.0f, float const pivotY = 0.0f, float const anchorX = 0.0f, float const anchorY = 0.0f);

		/// <summary>
		/// Creates and returns an entity with the following components: Renderable, TextRenderer.
		/// </summary>
		/// <param name="text"></param>
		/// <param name="font"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="layer"></param>
		/// <param name="order"></param>
		/// <returns></returns>
		entt::entity createEntity_ui_text(Text* const text, float const x, float const y, int const layer = 0, int const order = 0, float const anchorX = 0.0f, float const anchorY = 0.0f);

	private:
		/// <summary>
		/// Will delete entities and other tasks that need to be done to "clean up."
		/// </summary>
		void cleanup();
	};
}
