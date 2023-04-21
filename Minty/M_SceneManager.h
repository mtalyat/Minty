#pragma once

#include "M_Object.h"
#include <map>
#include <vector>

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
		// the scenes being managed
		std::map<std::string, Scene*>* mp_scenes;
		// the scene actively loaded
		Scene* mp_active;

	public:
		/// <summary>
		/// Creates a new SceneManager.
		/// </summary>
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
		/// Loads the Scene with the given name, and emplaces it on the top of the Stack.
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
