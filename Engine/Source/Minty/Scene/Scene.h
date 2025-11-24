#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Vector.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Event/Event.h"
#include "Minty/Physics/PhysicsSimulation.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/System/SystemManager.h"
#include "Minty/Time/Timestep.h"

namespace Minty
{
	/// <summary>
	/// The arguments for creating a Scene.
	/// </summary>
	struct SceneInfo
	{
		/// <summary>
		/// The UUID of the Scene.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The name of the Scene.
		/// </summary>
		String name = "Scene";
	};

	/// <summary>
	/// A Scene is a collection of entities, components, and systems.
	/// </summary>
	class Scene
		: public SerializableObject, public Source<Scene>
	{
#pragma region Classes

	private:
		struct AssetData
		{
			Size index;
			UUID id;
		};

#pragma endregion

#pragma region Variables

	private:
		UUID m_id;
		String m_name;

		Owner<EntityManager> m_entityManager;
		Owner<SystemManager> m_systemManager;
		
		// information for each loaded asset
		Map<Path, AssetData> m_loadedAssets;

		// ordered list of each asset, determines loading order
		Vector<Path> m_assets;

		// set of IDs of the assets that have been registered
		Set<UUID> m_registeredAssets;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Scene using the given arguments.
		/// </summary>
		/// <param name="info">The arguments.</param>
		Scene(SceneInfo const& info);

		Scene(Scene&& other) noexcept;

		~Scene() override;

#pragma endregion
		
#pragma region Operators

	public:
		Scene& operator=(Scene&& other) noexcept;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the ID of this Scene.
		/// </summary>
		/// <returns>The ID.</returns>
		UUID get_id() const { return m_id; }

		/// <summary>
		/// Gets the name of this Scene.
		/// </summary>
		/// <returns>The name.</returns>
		String const& get_name() const { return m_name; }

		/// <summary>
		/// Gets the EntityManager of this Scene.
		/// </summary>
		/// <returns></returns>
		EntityManager& get_entity_manager() const { return *m_entityManager; }

		/// <summary>
		/// Gets the SystemManager of this Scene.
		/// </summary>
		/// <returns></returns>
		SystemManager& get_system_manager() const { return *m_systemManager; }

		/// <summary>
		/// Gets the set of loaded Asset IDs in this Scene.
		/// </summary>
		/// <returns>The set of IDs.</returns>
		Set<UUID> const& get_loaded_assets() const { return m_registeredAssets; }

#pragma endregion

#pragma region Methods

	private:
		// loads the assets controlled by this Scene
		void load_assets(Vector<Path> const& newAssets);

		// unloads the assets controlled by this Scene
		void unload_assets();

	public:
		/// <summary>
		/// Called when the Asset is loaded into the AssetManager.
		/// </summary>
		void on_load();

		/// <summary>
		/// Called when the Asset is unloaded from the AssetManager.
		/// </summary>
		void on_unload();

		/// <summary>
		/// Called when the Scene is updated.
		/// </summary>
		void on_frame_update(Timestep const& time);

		void on_fixed_update(Timestep const& time);

		/// <summary>
		/// Called when the Scene is finalized.
		/// </summary>
		void on_finalize();

		/// <summary>
		/// Called when the Scene is rendered.
		/// </summary>
		void on_render();

		/// <summary>
		/// Called when an Event is received.
		/// </summary>
		/// <param name="event">The Event.</param>
		void on_event(Event& event);

		/// <summary>
		/// Register an Asset to the Scene. The Scene takes ownership of the Asset.
		/// </summary>
		/// <param name="asset">The ID of the Asset to take ownership of.</param>
		void register_asset(UUID const assetId);

		/// <summary>
		/// Registers an asset by extracting its id and forwarding it to the overload that accepts an asset id.
		/// </summary>
		/// <param name="asset">Const reference to a Ref<Asset> that identifies the asset to register. The function extracts the asset's id and calls register_asset(id).</param>
		inline void register_asset(Ref<Asset> const& asset)
		{
			register_asset(asset->get_id());
		}

		/// <summary>
		/// Unregisters an Asset from the Scene. The Scene releases ownership of the Asset.
		/// </summary>
		/// <param name="assetId">The ID of the Asset to release ownership of.</param>
		void unregister_asset(UUID const assetId);
		
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Scene using the given arguments.
		/// </summary>
		/// <param name="info">The arguments.</param>
		/// <returns>A Scene Owner.</returns>
		static Owner<Scene> create(SceneInfo const& info = {});

#pragma endregion

	};
}