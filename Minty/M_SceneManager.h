#pragma once

#include "M_Object.h"
#include <map>

namespace minty
{
	class Scene;

	/// <summary>
	/// Manages loading, unloading, and transitioning to different Scenes.
	/// </summary>
	class MINTY_API SceneManager :
		public Object
	{
	private:
		std::map<std::string, Scene*>* mp_scenes;
		Scene* mp_active;

	public:
		SceneManager()
			: mp_scenes(new std::map<std::string, Scene*>())
			, mp_active(nullptr)
		{}

		~SceneManager();

		/// <summary>
		/// Checks if this SceneManager contains a Scene with the given name.
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		bool contains(std::string const& name);

		/// <summary>
		/// Adds a Scene to the SceneManager.
		/// </summary>
		/// <param name="scene"></param>
		/// <returns></returns>
		bool add(Scene* const scene);

		/// <summary>
		/// Loads the Scene with the given name.
		/// </summary>
		/// <param name="name"></param>
		void load(std::string const& name);

		/// <summary>
		/// Unloads and loads the active Scene.
		/// </summary>
		void reload();

		/// <summary>
		/// Gets the active Scene.
		/// </summary>
		/// <returns></returns>
		inline Scene* const active() { return mp_active; }
	};
}
