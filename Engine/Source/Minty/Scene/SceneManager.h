#ifndef MINTY_SCENE_SCENEMANAGER_H
#define MINTY_SCENE_SCENEMANAGER_H

/**
 * @file SceneManager.h
 * @brief Defines the SceneManager class used for managing Scenes.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Path.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Manager/Manager.h"

namespace Minty
{
	class Scene;
	struct SceneManagerInfo;

	/**
	 * @brief Controls Scenes within the application.
	 */
	class SceneManager
	: public Manager
	{
#pragma region Types

	private:
		struct SceneData
		{
			Shared<Scene> scene;
			Path path;
		};

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates a new SceneManager using the given SceneManagerInfo.
		 * @param info The arguments.
		 */
		SceneManager(SceneManagerInfo const& info);

		~SceneManager();

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Sets the active Scene.
		 * @param scene The Scene to set as active.
		 */
		void set_active(Ref<Scene> const& scene);

		/**
		 * @brief Gets the active Scene.
		 * @returns A Ref to the active Scene.
		 */
		inline Ref<Scene> const& get_active() const { return m_activeScene; }

#pragma endregion


#pragma region Methods

	public:
		/**
		 * @brief Checks if a Scene with the given ID is managed by the SceneManager.
		 * @param id The ID of the Scene.
		 */
		inline Bool contains(UUID const id) const { return m_scenes.contains(id); }

		/**
		 * @brief Loads a scene from the given Path, optionally setting it as the active scene.
		 * @param path The Path to load the scene from.
		 * @param setAsActive If true, sets the loaded scene as the active scene. Defaults to false.
		 * @return A Ref to the loaded Scene.
		 */
		Ref<Scene> load(Path const& path, Bool const setAsActive = false);

		/**
		 * @brief Loads the given Scene, optionally setting it as the active scene.
		 * @param scene The Scene to load.
		 * @param setAsActive If true, sets the loaded scene as the active scene. Defaults to false.
		 * @return A Ref to the loaded Scene.
		 */
		Ref<Scene> load(Shared<Scene> const& scene, Bool const setAsActive = false);

		/**
		 * @brief Unloads the Scene with the given ID.
		 * @param id The ID of the Scene.
		 */
		void unload(UUID const id);

		/**
		 * @brief Reloads the Scene with the given ID.
		 * @param id The ID of the Scene.
		 */
		void reload(UUID const id);

		/**
		 * @brief Schedules the loading of a Scene from the given Path.
		 * @param path The Path to load the Scene from.
		 */
		UUID schedule_load(Path const& path, Job const& onCompletion = []() {}, Bool const setAsActive = false);

		/**
		 * @brief Schedules the unloading of the Scene with the given ID.
		 * @param id The ID of the Scene.
		 */
		void schedule_unload(UUID const id, Job const& onCompletion = []() {});

		/**
		 * @brief Called every frame to perform frame updates.
		 * @param time The time step.
		 */
		void frame_update(Timestep const& time) override;

		/**
		 * @brief Called at fixed intervals to perform fixed updates.
		 * @param time The time step.
		 */
		void fixed_update(Timestep const& time) override;

		/**
		 * @brief Finalizes the frame.
		 */
		void finalize() override;

		/**
		 * @brief Renders the active Scene.
		 */
		void render() override;

		/**
		 * @brief Handles an event sent to the SceneManager.
		 * @param event The event to handle.
		 */
		void handle_event(Event& event) override;

		/**
		 * @brief Refreshes all loaded Scenes.
		 */
		void refresh();

#pragma endregion

#pragma region Statics

	public:
		/**
		 * @brief Creates a new SceneManager using the given SceneManagerInfo.
		 * @param info The arguments.
		 * @return A Unique pointer to the created SceneManager.
		 */
		static Unique<SceneManager> create(SceneManagerInfo const& info);

		/**
		 * @brief Gets the singleton instance of the SceneManager.
		 * @return A reference to the SceneManager singleton.
		 */
		static SceneManager& get_singleton();

#pragma endregion

#pragma region Variables

	private:
		Path m_initialScene;
		Map<UUID, SceneData> m_scenes;
		Ref<Scene> m_activeScene;
		Ref<Scene> m_nextScene;

#pragma endregion
	};
}

#endif // MINTY_SCENE_SCENEMANAGER_H