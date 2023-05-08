#pragma once

#pragma once

#include "M_Object.h"
#include "M_Rect.h"
#include "M_SystemManager.h"
#include "M_S_RenderSystem.h"
#include "M_S_AudioSystem.h"
#include "M_S_InputSystem.h"
#include "M_S_UserInterfaceSystem.h"
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

		// the input system
		InputSystem* const mp_inputSystem;
		// the render system
		RenderSystem* const mp_renderSystem;
		// the audio system
		AudioSystem* const mp_audioSystem;
		// the ui system
		UserInterfaceSystem* const mp_uiSystem;
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

		/// <summary>
		/// Gets the UserInterfaceSystem in this Scene.
		/// </summary>
		/// <returns></returns>
		inline UserInterfaceSystem* const userInterfaceSystem() const { return mp_uiSystem; }

		//inline UI_Canvas* mainCanvas() { return mp_mainCanvas; }

		/// <summary>
		/// Gets the Game that this Scene belongs to.
		/// </summary>
		/// <returns></returns>
		inline Game* const game() const { return mp_game; }

	private:
		/// <summary>
		/// Will delete entities and other tasks that need to be done to "clean up."
		/// </summary>
		void cleanup();
	};
}
