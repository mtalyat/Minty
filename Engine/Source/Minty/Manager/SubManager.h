#ifndef MINTY_MANAGER_SUBMANAGER_H
#define MINTY_MANAGER_SUBMANAGER_H

/**
 * @file SubManager.h
 * @brief Defines the SubManager class representing a Manager within a Scene.
 * @author Mitchell Talyat
 */

#include "Minty/Manager/Manager.h"

namespace Minty
{
	class Scene;

	/**
	 * @brief A SubManager is a Manager that belongs to a specific Scene.
	 */
	class SubManager
		: public Manager
	{
#pragma region Constructors

	public:
		/**
		 * @brief Constructs a SubManager belonging to the given Scene.
		 * @param scene The Scene this SubManager belongs to.
		 */
		SubManager(Scene* scene)
			: Manager()
			, mp_scene(scene)
		{
			MINTY_ASSERT(scene != nullptr, ErrorCode::Argument_ExpectedNonNull);
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the Scene this SubManager belongs to.
		 * @returns The Scene.
		 */
		Scene& get_scene() const { return *mp_scene; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when the Scene is loaded.
		 */
		virtual void on_scene_load() {}

		/**
		 * @brief Called when the Scene is unloaded.
		 */
		virtual void on_scene_unload() {}

#pragma endregion

#pragma region Variables

	private:
		Scene* mp_scene = nullptr;

#pragma endregion
	};
}

#endif // MINTY_MANAGER_SUBMANAGER_H