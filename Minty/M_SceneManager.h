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
		std::map<std::string, Scene*>* mp_scenes;
		std::vector<Scene*>* mp_activeScenes;
		Scene* mp_active;

	public:
		SceneManager()
			: mp_scenes(new std::map<std::string, Scene*>())
			, mp_activeScenes(new std::vector<Scene*>())
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
		void load(std::string const& name, bool const unloadActive = true);

		/// <summary>
		/// Unloads the current active Scene, and returns to the topmost Scene in the Stack.
		/// </summary>
		void unload();

		/// <summary>
		/// Unloads and loads the active Scene.
		/// </summary>
		void reload();

		/// <summary>
		/// Gets the active Scene.
		/// </summary>
		/// <returns></returns>
		inline Scene* const active() { return mp_active; }

	private:
		// adds scene to stack, sets as active
		void push(Scene* const scene);

		// removes scene from stack, sets active as top of stack or null if empty
		void pop();
	};
}
