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

		bool contains(std::string const& name);

		bool add(Scene* const scene);

		void load(std::string const& name);

		inline Scene* const active() { return mp_active; }
	};
}
