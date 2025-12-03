#ifndef MINTY_SCENE_SCENE_H
#define MINTY_SCENE_SCENE_H

/**
 * @file Scene.h
 * @brief Defines the Scene class representing a collection of entities and systems.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Vector.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/Time/Timestep.h"

namespace Minty
{
	class EntityManager;
	class SystemManager;
	class PhysicsSimulation;
	class Event;
	class Manager;
	struct SceneInfo;

	/**
	 * @brief A Scene represents a collection of entities and systems that define a particular state or level in the application.
	 */
	class Scene
		: public SerializableObject, public Source<Scene>
	{
#pragma region Types

	private:
		struct AssetData
		{
			Size index;
			UUID id;
		};

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Constructs a Scene with the given SceneInfo.
		 * @param info The SceneInfo containing initialization parameters.
		 */
		Scene(SceneInfo const& info);

		/**
		 * @brief Move constructor.
		 * @param other The Scene to move from.
		 */
		Scene(Scene&& other) noexcept;

		~Scene() override;
		
		Scene(Scene const&) = delete;

#pragma endregion
		
#pragma region Operators

	public:
		Scene& operator=(Scene&& other) noexcept;

		Scene& operator=(Scene const&) = delete;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the UUID of this Scene.
		 * @returns The UUID.
		 */
		UUID get_id() const { return m_id; }

		/**
		 * @brief Gets the name of this Scene.
		 * @returns The name.
		 */
		String const& get_name() const { return m_name; }

		/**
		 * @brief Gets the EntityManager of this Scene.
		 * @returns The EntityManager.
		 */
		EntityManager& get_entity_manager() const { return *m_entityManager; }

		/**
		 * @brief Gets the SystemManager of this Scene.
		 * @returns The SystemManager.
		 */
		SystemManager& get_system_manager() const { return *m_systemManager; }

		/**
		 * @brief Gets the set of loaded asset IDs registered to this Scene.
		 * @returns The set of loaded asset IDs.
		 */
		Set<UUID> const& get_loaded_assets() const { return m_registeredAssets; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when the Asset is loaded by the AssetManager.
		 */
		void on_load();

		/**
		 * @brief Called when the Asset is unloaded by the AssetManager.
		 */
		void on_unload();

		/**
		 * @brief Called once per frame to update the Scene.
		 * @param time The Timestep representing the time since the last frame.
		 */
		void on_frame_update(Timestep const& time);

		/**
		 * @brief Called at a fixed interval to update the Scene.
		 * @param time The Timestep representing the fixed time step.
		 */
		void on_fixed_update(Timestep const& time);

		/**
		 * @brief Called when the Scene is being finalized.
		 */
		void on_finalize();

		/**
		 * @brief Called when the Scene should render its contents.
		 */
		void on_render();

		/**
		 * @brief Called when an Event is dispatched to the Scene.
		 * @param event The Event to handle.
		 */
		void on_event(Event& event);

		/**
		 * @brief Registers an Asset to the Scene by its UUID. The Scene takes ownership of the Asset.
		 * @param assetId The UUID of the Asset to register.
		 */
		void register_asset(UUID const assetId);

		/**
		 * @brief Registers an Asset to the Scene. The Scene takes ownership of the Asset.
		 * @param asset The Asset to register.
		 */
		inline void register_asset(Ref<Asset> const& asset) { register_asset(asset->get_id()); }

		/**
		 * @brief Unregisters an Asset from the Scene by its UUID. The Scene releases ownership of the Asset.
		 * @param assetId The UUID of the Asset to unregister.
		 */
		void unregister_asset(UUID const assetId);
		
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

		/**
		 * @brief Creates a new Scene with the given SceneInfo.
		 * @param info The SceneInfo containing initialization parameters.
		 * @returns The newly created Scene.
		 */
		static Shared<Scene> create(SceneInfo const& info);

		/**
		 * @brief Creates a new default Scene.
		 * @returns The newly created Scene.
		 */
		static Shared<Scene> create();

	private:
		// loads the assets controlled by this Scene
		void load_assets(Vector<Path> const& newAssets);

		// unloads the assets controlled by this Scene
		void unload_assets();

#pragma endregion

#pragma region Variables

	private:
		UUID m_id;
		String m_name;

		Shared<EntityManager> m_entityManager;
		Shared<SystemManager> m_systemManager;
		Vector<Manager*> m_subManagers;
		
		// information for each loaded asset
		Map<Path, AssetData> m_loadedAssets;

		// ordered list of each asset, determines loading order
		Vector<Path> m_assets;

		// set of IDs of the assets that have been registered
		Set<UUID> m_registeredAssets;

#pragma endregion
	};
}

#endif // MINTY_SCENE_SCENE_H