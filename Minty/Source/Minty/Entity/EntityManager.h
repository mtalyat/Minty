#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Component/RelationshipComponent.h"
#include "Minty/Core/Types.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Entity/EntityPath.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Entity/EntityView.h"
#include "Minty/Entity/Prefab.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Manager/SubManager.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	struct TransformComponent;
	struct UITransformComponent;

	/// <summary>
	/// The arguments for an EntityManager.
	/// </summary>
	struct EntityManagerBuilder
	{

	};

	/// <summary>
	/// Manages all Entities in the game.
	/// </summary>
	class EntityManager
		: public SubManager, public SerializableObject
	{
#pragma region Variables

	private:
		entt::registry m_registry;
		RelationshipComponent m_root;
		Map<UUID, Entity> m_ids;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new EntityManager using the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		EntityManager(Scene* scene, EntityManagerBuilder const& builder)
			: SubManager(scene)
			, m_registry()
			, m_root()
			, m_ids()
		{
		}

		EntityManager(EntityManager&& other) noexcept
			: SubManager(std::move(other))
			, m_registry(std::move(other.m_registry))
			, m_root(std::move(other.m_root))
			, m_ids(std::move(other.m_ids))
		{
		}

		~EntityManager()
		{
			MINTY_ASSERT_ERROR(!is_initialized(), "EntityManager is not disposed before destruction.");
		}

#pragma endregion

#pragma region Operators

	public:
		EntityManager& operator=(EntityManager&& other) noexcept
		{
			if (this != &other)
			{
				m_registry = std::move(other.m_registry);
				m_root = std::move(other.m_root);
				m_ids = std::move(other.m_ids);
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	private:
		void remove_from_parent(RelationshipComponent& relationshipComp, RelationshipComponent& parentRelationshipComp);

		void add_to_parent(Entity const entity, RelationshipComponent& relationshipComp, RelationshipComponent& parentRelationshipComp);

	public:
		UUID get_id(Entity const entity) const;

		void set_id(Entity const entity, UUID const id);

		Entity get_entity(UUID const id) const;

		Entity get_entity(Entity const source, EntityPath const& path) const;

		// name (UUID)
		String get_entity_string(Entity const entity) const;

		void set_enabled(Entity const entity, Bool const enabled);

		Bool get_enabled(Entity const entity) const;

		void set_visible(Entity const entity, Bool const visible);

		Bool get_visible(Entity const entity) const;

		void set_layer(Entity const entity, Layer const layer);

		Layer get_layer(Entity const entity) const;

		void set_parent(Entity const entity, Entity const parent);

		Entity get_parent(Entity const entity) const;

		Entity get_child(Entity const entity, Size const index) const;

		String get_name(Entity const entity) const;

		void set_name(Entity const entity, String const& name);

		Size get_size() const { return m_registry.storage<Entity>()->in_use(); }

#pragma endregion

#pragma region Methods

	private:
		// finalizes dirty components
		void finalize_dirties();

		Entity create_entity_smart(String const& name, UUID const id);

		void update_transform(Entity const entity, Entity const parent, TransformComponent& transformComp);

		void update_uiTransform(Entity const entity, Entity const parent, UITransformComponent& uiTransformComp);

	public:
		/// <summary>
		/// Called when the Manager is created.
		/// </summary>
		void initialize() override;
		/// <summary>
		/// Called every frame.
		/// </summary>
		void update(Time const& time) override;
		/// <summary>
		/// Called after every update operation.
		/// </summary>
		void finalize() override;

		/// <summary>
		/// Checks if this manager contains an Entity with the given ID.
		/// </summary>
		/// <param name="id">The ID of the Entity.</param>
		/// <returns>True if an Entity with the ID exists.</returns>
		Bool contains(UUID const id) const
		{
			return m_ids.contains(id);
		}

		/// <summary>
		/// Checks if this manager contains the given Entity.
		/// </summary>
		/// <param name="entity">The Entity.</param>
		/// <returns>True if the given Entity exists.</returns>
		Bool contains(Entity const entity) const
		{
			return m_registry.valid(entity);
		}

		/// <summary>
		/// Checks if the given Entity's layer mask contains the given Layer.
		/// </summary>
		/// <param name="entity">The Entity.</param>
		/// <param name="layer">The Layer(s).</param>
		/// <returns>True if the layer is within the Entity's layers.</returns>
		Bool is_in_layer(Entity const entity, Layer const layer) const;

		/// <summary>
		/// Checks if the given mask contains the given Entity's layer.
		/// </summary>
		/// <param name="entity">The Entity.</param>
		/// <param name="mask">The Layer(s).</param>
		/// <returns>True if the Entity's layers are within the layer mask.</returns>
		Bool is_in_mask(Entity const entity, Layer const mask) const;

		/// <summary>
		/// Marks the given Entity as dirty. Dirty components need to be refreshed.
		/// </summary>
		/// <param name="entity">The Entity.</param>
		void dirty(Entity const entity);

		/// <summary>
		/// Forcefully refreshes the given Entity. This will update all Components of the Entity, even if they are not dirty.
		/// </summary>
		/// <param name="entity">The Entity.</param>
		void refresh(Entity const entity);

		/// <summary>
		/// Creates an empty Entity.
		/// </summary>
		/// <returns>The Entity.</returns>
		Entity create_entity();

		/// <summary>
		/// Creates an Entity with the given ID.
		/// </summary>
		/// <param name="id">The ID of the Entity.</param>
		/// <returns>The Entity.</returns>
		Entity create_entity(UUID const id);

		/// <summary>
		/// Creates an Entity with the given name.
		/// </summary>
		/// <param name="name">The name of the Entity.</param>
		/// <returns>The Entity.</returns>
		Entity create_entity(String const& name);

		/// <summary>
		/// Creates an Entity with the given name and ID.
		/// </summary>
		/// <param name="name">The name of the Entity.</param>
		/// <param name="id">The ID of the Entity.</param>
		/// <returns>The Entity.</returns>
		Entity create_entity(String const& name, UUID const id);

		/// <summary>
		/// Creates an Entity based on the given Prefab.
		/// </summary>
		/// <param name="id">The new ID to use.</param>
		/// <param name="prefab">The Prefab.</param>
		/// <returns>The first Entity created by the Prefab.</returns>
		Entity create_entity(UUID const id, Ref<Prefab> const& prefab);

		/// <summary>
		/// Adds a Component to the given Entity.
		/// </summary>
		/// <typeparam name="ComponentType"></typeparam>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="entity"></param>
		/// <param name="...args"></param>
		/// <returns></returns>
		template<typename ComponentType, typename... Args>
		ComponentType& add_component(Entity const entity, Args&&... args)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.emplace<ComponentType>(entity, std::forward<Args>(args)...);
		}

		/// <summary>
		/// Adds a component with the specified name to the given entity and returns a reference to the newly added component.
		/// </summary>
		/// <param name="entity">The entity to which the component will be added.</param>
		/// <param name="name">The name of the component to add.</param>
		/// <returns>A reference to the newly added component.</returns>
		Component& add_component(Entity const entity, String const& name);

		/// <summary>
		/// Retrieves a reference to a component of the specified type from the given entity.
		/// </summary>
		/// <typeparam name="ComponentType">The type of the component to retrieve.</typeparam>
		/// <param name="entity">The entity from which to retrieve the component.</param>
		/// <returns>A reference to the component of the specified type associated with the entity.</returns>
		template<typename ComponentType>
		ComponentType& get_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.get<ComponentType>(entity);
		}

		/// <summary>
		/// Retrieves a reference to a component of the specified type from the given entity.
		/// </summary>
		/// <typeparam name="ComponentType">The type of the component to retrieve.</typeparam>
		/// <param name="entity">The entity from which to retrieve the component.</param>
		/// <returns>A constant reference to the component of the specified type associated with the entity.</returns>
		template<typename ComponentType>
		ComponentType const& get_component(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.get<ComponentType>(entity);
		}

		/// <summary>
		/// Retrieves a reference to a component of the specified entity by name.
		/// </summary>
		/// <param name="entity">The entity from which to retrieve the component.</param>
		/// <param name="name">The name of the component to retrieve.</param>
		/// <returns>A reference to the requested component.</returns>
		Component& get_component(Entity const entity, String const& name);

		/// <summary>
		/// Retrieves a constant reference to a component of the specified entity by name.
		/// </summary>
		/// <param name="entity">The entity from which to retrieve the component.</param>
		/// <param name="name">The name of the component to retrieve.</param>
		/// <returns>A constant reference to the requested component.</returns>
		Component const& get_component(Entity const entity, String const& name) const;

		/// <summary>
		/// Retrieves a component of the specified type from the given entity, or adds it if it does not exist.
		/// </summary>
		/// <typeparam name="ComponentType">The type of the component to retrieve or add.</typeparam>
		/// <param name="entity">The entity from which to get or add the component.</param>
		/// <returns>A reference to the component of the specified type associated with the entity.</returns>
		template<typename ComponentType>
		ComponentType& get_or_add_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.emplace_or_replace<ComponentType>(entity);
		}

		/// <summary>
		/// Retrieves a component by name from the specified entity, or adds it if it does not exist.
		/// </summary>
		/// <param name="entity">The entity from which to retrieve or add the component.</param>
		/// <param name="name">The name of the component to retrieve or add.</param>
		/// <returns>A reference to the retrieved or newly added component.</returns>
		Component& get_or_add_component(Entity const entity, String const& name);

		/// <summary>
		/// Attempts to retrieve a pointer to a component of the specified type from the given entity.
		/// </summary>
		/// <typeparam name="ComponentType">The type of the component to retrieve.</typeparam>
		/// <param name="entity">The entity from which to retrieve the component.</param>
		/// <returns>A pointer to the component of the specified type if it exists; otherwise, nullptr.</returns>
		template<typename ComponentType>
		ComponentType* try_get_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.try_get<ComponentType>(entity);
		}

		/// <summary>
		/// Attempts to retrieve a pointer to a component of the specified type from the given entity.
		/// </summary>
		/// <typeparam name="ComponentType">The type of the component to retrieve.</typeparam>
		/// <param name="entity">The entity from which to retrieve the component.</param>
		/// <returns>A pointer to the component of the specified type if it exists; otherwise, nullptr.</returns>
		template<typename ComponentType>
		ComponentType const* try_get_component(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.try_get<ComponentType>(entity);
		}

		/// <summary>
		/// Attempts to retrieve a component from the specified entity by name.
		/// </summary>
		/// <param name="entity">The entity from which to retrieve the component.</param>
		/// <param name="name">The name of the component to retrieve.</param>
		/// <returns>A pointer to the component if found; otherwise, nullptr.</returns>
		Component* try_get_component(Entity const entity, String const& name);

		/// <summary>
		/// Attempts to retrieve a component from the specified entity by name.
		/// </summary>
		/// <param name="entity">The entity from which to retrieve the component.</param>
		/// <param name="name">The name of the component to retrieve.</param>
		/// <returns>A pointer to the component if found; otherwise, nullptr.</returns>
		Component const* try_get_component(Entity const entity, String const& name) const;

		/// <summary>
		/// Checks if the specified entity has a component of the given type.
		/// </summary>
		/// <typeparam name="ComponentType">The type of the component to check for.</typeparam>
		/// <param name="entity">The entity to check for the component.</param>
		/// <returns>True if the entity has the specified component; otherwise, false.</returns>
		template<typename ComponentType>
		Bool has_component(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.all_of<ComponentType>(entity);
		}

		/// <summary>
		/// Checks whether the specified entity has a component with the given name.
		/// </summary>
		/// <param name="entity">The entity to check for the component.</param>
		/// <param name="name">The name of the component to look for.</param>
		/// <returns>True if the entity has a component with the specified name; otherwise, false.</returns>
		Bool has_component(Entity const entity, String const& name) const;

		/// <summary>
		/// Removes a component of the specified type from an entity.
		/// </summary>
		/// <typeparam name="ComponentType">The type of the component to remove from the entity.</typeparam>
		/// <param name="entity">The entity from which the component will be removed.</param>
		template<typename ComponentType>
		void remove_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			m_registry.remove<ComponentType>(entity);
		}

		/// <summary>
		/// Removes a component with the specified name from the given entity.
		/// </summary>
		/// <param name="entity">The entity from which the component will be removed.</param>
		/// <param name="name">The name of the component to remove.</param>
		void remove_component(Entity const entity, String const& name);

		/// <summary>
		/// Destroys all Entities.
		/// </summary>
		void clear();

		/// <summary>
		/// Destroys all Components of the given type.
		/// If any Entity has this Component, it will be removed.
		/// </summary>
		/// <typeparam name="ComponentType">The type of Component.</typeparam>
		template<typename ComponentType>
		void clear()
		{
			m_registry.clear<ComponentType>();
		}

		/// <summary>
		/// Clears the Component from the given Entity.
		/// </summary>
		/// <typeparam name="ComponentType">The type of Component.</typeparam>
		/// <param name="entity">The Entity.</param>
		template<typename ComponentType>
		void clear(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			if(m_registry.all_of<ComponentType>(entity))
			{
				m_registry.remove<ComponentType>(entity);
			}
		}

		/// <summary>
		/// Adds or replaces the component on the given Entity.
		/// </summary>
		/// <typeparam name="ComponentType">The type of Component.</typeparam>
		/// <param name="entity">The Entity to add the Component to.</param>
		template<typename ComponentType>
		void mark(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			m_registry.emplace_or_replace<ComponentType>(entity);
		}

		/// <summary>
		/// Adds or replaces the component on all Entities.
		/// </summary>
		/// <typeparam name="ComponentType">The type of Component.</typeparam>
		template<typename ComponentType>
		void mark_all()
		{
			for (auto const [entity] : m_registry.storage<Entity>().each())
			{
				m_registry.emplace_or_replace<ComponentType>(entity);
			}
		}

        /// <summary>
        /// Gets an EntityView with the given Components.
        /// </summary>
        /// <typeparam name="...Include">The Component types to include.</typeparam>
        /// <typeparam name="...Exclude">The Component types to exclude.</typeparam>
        /// <returns>A view containing all of the Entities with the given Component types.</returns>
        template<typename... Include, typename... Exclude>
        auto view(entt::exclude_t<Exclude...> exclude = entt::exclude_t{})
        {
			return EntityView(m_registry.view<Include...>(exclude));
        }

		/// <summary>
		/// Sorts all of the Entities.
		/// The order is based on the RelationshipComponent hierarchy.
		/// </summary>
		void sort();

		/// <summary>
		/// Sorts the Entities with the given Component type.
		/// </summary>
		/// <typeparam name="T">The Component type.</typeparam>
		/// <param name="compare">The compare function.</param>
		template<typename T>
		void sort(Function<Bool(T const&, T const&)> const& compare)
		{
			m_registry.sort<T>(compare);
		}

		/// <summary>
		/// Sorts the Entities with the given Component type.
		/// </summary>
		/// <typeparam name="T">The Component type.</typeparam>
		/// <param name="compare">The compare function.</param>
		template<typename T>
		void sort(Function<Bool(Entity const, Entity const)> const& compare)
		{
			m_registry.sort<T>(compare);
		}

		/// <summary>
		/// Swaps the positions of two sibling entities.
		/// </summary>
		/// <param name="left">The first sibling entity to swap.</param>
		/// <param name="right">The second sibling entity to swap.</param>
		void swap_siblings(Entity const left, Entity const right);

		/// <summary>
		/// Advances the specified entity to its next state or position.
		/// </summary>
		/// <param name="entity">The entity to be moved to the next state or position.</param>
		void move_to_next(Entity const entity);

		/// <summary>
		/// Moves the specified entity to its previous position or state.
		/// </summary>
		/// <param name="entity">The entity to be moved to the previous position or state.</param>
		void move_to_previous(Entity const entity);

		/// <summary>
		/// Moves the specified entity to the first position.
		/// </summary>
		/// <param name="entity">The entity to move to the first position.</param>
		void move_to_first(Entity const entity);

		/// <summary>
		/// Moves the specified entity to the last position.
		/// </summary>
		/// <param name="entity">The entity to move to the last position.</param>
		void move_to_last(Entity const entity);

		/// <summary>
		/// Destroys the given Entity.
		/// </summary>
		/// <param name="entity"></param>
		void destroy(Entity const entity);

		/// <summary>
		/// Destroys all Entities with the given Component type.
		/// </summary>
		/// <typeparam name="ComponentType"></typeparam>
		template<typename ComponentType>
		void destroy_with()
		{
			auto view = m_registry.view<ComponentType>();
			m_registry.destroy(view.begin(), view.end());
		}

		/// <summary>
		/// Destroys all Entities with a DestroyComponent.
		/// </summary>
		void cleanup();

#pragma region Serialization

	private:
		// deserializes just the entity at the index
		Entity deserialize_entity(Reader& reader, Size const index);
		// deserializes the components of the entity at the index
		Bool deserialize_components(Reader& reader, Size const index, EntitySerializationData data);
		// deserialize the entities from the prefab
		Bool deserialize_prefab(Reader& reader, Map<UUID, UUID>& idMap);
		// deserialize the override values for a prefab
		Bool deserialize_prefab_entity(Reader& reader, Ref<Prefab> const& prefab);
	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new EntityManager with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>An EntityManager Owner.</returns>
		static Owner<EntityManager> create(Scene* scene, EntityManagerBuilder const& builder = {});

		/// <summary>
		/// Gets the singleton EntityManager for the active Scene.
		/// </summary>
		/// <returns>The EntityManager.</returns>
		static EntityManager& get_singleton();

#pragma region Entity Serialization Utility

		public:
			static void deserialize_entity(Reader& reader, Size const index, String& name, UUID& id, UUID& prefabId);

#pragma endregion

#pragma endregion
};
}