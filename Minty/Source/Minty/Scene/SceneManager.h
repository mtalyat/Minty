#pragma once
#include "Minty/Data/Path.h"
#include "Minty/Manager/Manager.h"
#include "Minty/Scene/Scene.h"

namespace Minty
{
	/// <summary>
	/// The arguments for creating a SceneManager.
	/// </summary>
	struct SceneManagerBuilder
	{
		/// <summary>
		/// The path to the first scene to load.
		/// </summary>
		Path initialScene;
	};

	/// <summary>
	/// Manages and controls all Scenes in the game.
	/// </summary>
	class SceneManager
		: public Manager
	{
#pragma region Classes

	private:
		struct SceneData
		{
			Owner<Scene> scene;
			Path path;
		};

#pragma endregion

#pragma region Variables

	private:
		Path m_initialScene;

		// loaded scenes
		Map<UUID, SceneData> m_scenes;

		// current scene receiving updates
		Ref<Scene> m_activeScene;

		// the next scene to become active
		Ref<Scene> m_nextScene;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new SceneManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		SceneManager(SceneManagerBuilder const& builder)
			: Manager()
			, m_initialScene(builder.initialScene)
			, m_scenes()
			, m_activeScene(nullptr)
			, m_nextScene(nullptr)
		{
			MINTY_ASSERT(m_initialScene.is_empty() || Path::exists(m_initialScene), "The initial scene path does not exist.");
		}

		~SceneManager()
		{
			MINTY_ASSERT_ERROR(!is_initialized(), "SceneManager is not disposed before destruction.");
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Sets the given Scene as the active Scene.
		/// </summary>
		/// <param name="scene">The next active Scene.</param>
		void set_active(Ref<Scene> const& scene);

		/// <summary>
		/// Gets the active Scene.
		/// </summary>
		/// <returns>The active Scene.</returns>
		Ref<Scene> const& get_active() const
		{
			return m_activeScene;
		}

#pragma endregion


#pragma region Methods

	public:
		/// <summary>
		/// Checks if this SceneManager contains a Scene with the given ID.
		/// </summary>
		/// <param name="id">The ID.</param>
		/// <returns>True if the Scene exists.</returns>
		inline Bool contains(UUID const id) const
		{
			return m_scenes.contains(id);
		}

		/// <summary>
		/// Loads the Scene from the given Path, and adds it to the SceneManager.
		/// </summary>
		/// <param name="path">The Path to the Scene.</param>
		Ref<Scene> load(Path const& path, Bool const setAsActive = false);

		/// <summary>
		/// Removes the Scene with the given ID from the SceneManager, and unloads it.
		/// </summary>
		/// <param name="id"></param>
		void unload(UUID const id);

		/// <summary>
		/// Reloads the Scene with the given ID.
		/// </summary>
		/// <param name="id">The ID of the Scene.</param>
		void reload(UUID const id);

		/// <summary>
		/// Schedules the Scene to be loaded from the given Path, and adds it to the SceneManager upon completion.
		/// </summary>
		/// <param name="path"></param>
		/// <param name="onCompletion">The Job to run upon completion of the loading.</param>
		UUID schedule_load(Path const& path, Job const& onCompletion = []() {}, Bool const setAsActive = false);

		/// <summary>
		/// Removes the Scene from the SceneManager, and Schedules the Scene with the given ID to be unloaded.
		/// </summary>
		/// <param name="id">The ID of the Scene.</param>
		/// <param name="onCompletion">The Job to run upon completion of the unloading.</param>
		void schedule_unload(UUID const id, Job const& onCompletion = []() {});

		/// <summary>
		/// Called when the Manager is created.
		/// </summary>
		void initialize() override;

		/// <summary>
		/// Called when the Manager is destroyed.
		/// </summary>
		void dispose() override;

		/// <summary>
		/// Called every frame.
		/// </summary>
		void update(Time const& time) override;

		/// <summary>
		/// Called after every update operation.
		/// </summary>
		void finalize() override;

		/// <summary>
		/// Called every frame to perform rendering.
		/// </summary>
		void render() override;

		/// <summary>
		/// Called when the Manager needs to synchronize operations.
		/// </summary>
		void sync() override;

		/// <summary>
		/// Handles the given Event.
		/// </summary>
		/// <param name="event">The Event to handle.</param>
		void handle_event(Event& event) override;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new SceneManager.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A SceneManager Owner.</returns>
		static Owner<SceneManager> create(SceneManagerBuilder const& builder = {});

		/// <summary>
		/// Gets the active Context's SceneManager.
		/// </summary>
		/// <returns>The SceneManager.</returns>
		static SceneManager& get_singleton();

#pragma endregion

	};
}