#pragma once
#include "Minty/Manager/Manager.h"

namespace Minty
{
	class Scene;

	/// <summary>
	/// A SubManager is a Manager that resides within a Scene, instead of a Context.
	/// </summary>
	class SubManager
		: public Manager
	{
#pragma region Variables

	private:
		Scene* mp_scene = nullptr;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new SubManager for the given Scene.
		/// </summary>
		/// <param name="scene">The Scene this SubManager belongs to.</param>
		SubManager(Scene* scene)
			: Manager()
			, mp_scene(scene)
		{
			MINTY_ASSERT(scene != nullptr, "Scene cannot be null.");
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Scene this SubManager belongs to.
		/// </summary>
		/// <returns>The Scene.</returns>
		Scene& get_scene() const { return *mp_scene; }

#pragma endregion
	};
}