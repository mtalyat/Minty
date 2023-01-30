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
		std::string m_name;

	protected:
		Engine* const mp_engine;

		entt::registry* mp_registry;

		SceneManager* const mp_sceneManager;

	public:
		Game(std::string const& name, Engine* const engine);
		virtual ~Game();

		/// <summary>
		/// Called when the Engine starts.
		/// </summary>
		/// <returns></returns>
		virtual int onCreate() = 0;

		/// <summary>
		/// Called when the Engine has started, after onCreate.
		/// </summary>
		/// <returns></returns>
		virtual int onStart() = 0;

		/// <summary>
		/// Called when the Engine stops.
		/// </summary>
		/// <returns></returns>
		virtual int onStop() = 0;

		/// <summary>
		/// Called when the Engine is stopped, after onStop.
		/// </summary>
		/// <returns></returns>
		virtual int onDestroy() = 0;

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

