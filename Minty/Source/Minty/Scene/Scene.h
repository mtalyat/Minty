#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Path.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Vector.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Event/Event.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/System/SystemManager.h"
#include "Minty/Time/Time.h"

namespace Minty
{
	/// <summary>
	/// The arguments for creating a Scene.
	/// </summary>
	struct SceneBuilder
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
		: public Asset, public Source<Scene>, public SerializableObject
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
		String m_name;

		EntityManager* mp_entityManager;
		SystemManager* mp_systemManager;
		
		// information for each registered asset
		Map<Path, AssetData> m_registeredAssets;

		// ordered list of each asset, determines loading order
		Vector<Path> m_assets;

		// set of IDs of the assets that have been loaded
		Set<UUID> m_loadedAssets;

		Entity m_activeCameraEntity;

#pragma endregion

#pragma region Constructors

	public:
		Scene(SceneBuilder const& builder);

		~Scene()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the name of this Scene.
		/// </summary>
		/// <returns>The name.</returns>
		String const& get_name() const { return m_name; }

		EntityManager& get_entity_manager() const { return *mp_entityManager; }

		SystemManager& get_system_manager() const { return *mp_systemManager; }

		void set_active_camera_entity(Entity const entity)
		{
			m_activeCameraEntity = entity;
		}

		Entity get_active_camera_entity() const
		{
			return m_activeCameraEntity;
		}

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Scene.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::Scene; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when the Asset is loaded into the AssetManager.
		/// </summary>
		void on_load() override;

		/// <summary>
		/// Called when the Asset is unloaded from the AssetManager.
		/// </summary>
		void on_unload() override;

		/// <summary>
		/// Called when the Scene is updated.
		/// </summary>
		void on_update(Time const& time);

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

		void serialize(Writer& writer) const override;

		Bool deserialize(Reader& reader) override;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Scene using the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A Scene Owner.</returns>
		static Owner<Scene> create(SceneBuilder const& builder = {});

#pragma endregion

	};
}