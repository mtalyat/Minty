#pragma once

#include "M_Object.h"
#include "entt.hpp"

namespace minty
{
	class Engine;
	class SceneManager;
	class Scene;

	/// <summary>
	/// Controls a gameplay session.
	/// </summary>
	class MINTY_API Game :
		public Object
	{
	private:
		// the name of the game
		std::string m_name;

	protected:
		// the engine that this Game belngs to
		Engine* const mp_engine;

		// the registry that this Game will use
		entt::registry* mp_registry;
		
		// the scene manager this game will use to load and manage scenes
		SceneManager* const mp_sceneManager;

	public:
		/// <summary>
		/// Creates a new Game.
		/// </summary>
		/// <param name="name">The name of the Game.</param>
		/// <param name="engine">The Engine this Game belongs to.</param>
		Game(std::string const& name, Engine* const engine);
		virtual ~Game();

		/// <summary>
		/// Called when the Engine has started.
		/// </summary>
		/// <returns></returns>
		virtual int onStart() = 0;

		/// <summary>
		/// Called when the Engine stops.
		/// </summary>
		/// <returns></returns>
		virtual int onStop() = 0;

		/// <summary>
		/// Gets the name of this Game.
		/// </summary>
		/// <returns></returns>
		std::string const& name() const { return m_name; }

		/// <summary>
		/// Gets the entity registry for this Game.
		/// </summary>
		/// <returns></returns>
		entt::registry* const registry() const { return mp_registry; }
		
		/// <summary>
		/// Gets the SceneManager for this Game.
		/// </summary>
		/// <returns></returns>
		SceneManager* const sceneManager() const { return mp_sceneManager; }

		/// <summary>
		/// Gets the Engine that this Game belongs to.
		/// </summary>
		/// <returns></returns>
		inline Engine* const engine() const { return mp_engine; }
	};
}

