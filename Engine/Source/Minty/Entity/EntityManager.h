#ifndef MINTY_ENTITY_ENTITYMANAGER_H
#define MINTY_ENTITY_ENTITYMANAGER_H

/**
 * @file EntityManager.h
 * @brief Defines the EntityManager class responsible for managing Entities.
 * @author Mitchell Talyat
 */

#include "Minty/Component/RelationshipComponent.h"
#include "Minty/Core/Types.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Entity/EntityView.h"
#include "Minty/Data/Lookup.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Manager/SubManager.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/Component/ComponentData.h"

namespace Minty
{
	class EntityPath;
	class Prefab;
	class Scene;
	struct EntityManagerInfo;
	struct TransformComponent;
	struct UITransformComponent;

	/**
	 * @brief The EntityManager is responsible for creating, managing, and destroying Entities within a Scene.
	 */
	class EntityManager
		: public SubManager,
		  public SerializableObject
	{
#pragma region Constructors

	public:
		/**
		 * @brief Constructs an EntityManager for the given Scene with the specified info.
		 * @param scene The Scene this EntityManager belongs to.
		 * @param info The EntityManagerInfo containing initialization parameters.
		 */
		EntityManager(Ref<Scene> const& scene, EntityManagerInfo const &info);

		/**
		 * @brief Move constructor.
		 * @param other The EntityManager to move from.
		 */
		EntityManager(EntityManager &&other) noexcept;

		~EntityManager() override = default;

		EntityManager(EntityManager const &) = delete;

#pragma endregion

#pragma region Operators

	public:
		EntityManager &operator=(EntityManager &&other) noexcept
		{
			if (this != &other)
			{
				m_registry = std::move(other.m_registry);
				m_ids = std::move(other.m_ids);
			}
			return *this;
		}

		EntityManager &operator=(EntityManager const &) = delete;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the unique ID of the given Entity.
		 * @param entity The Entity.
		 */
		UUID get_id(Entity const entity) const;

		/**
		 * @brief Sets the unique ID of the given Entity.
		 * @param entity The Entity.
		 * @param id The unique ID to set.
		 */
		void set_id(Entity const entity, UUID const id);

		/**
		 * @brief Gets the Entity with the given unique ID.
		 * @param id The unique ID.
		 */
		Entity get_entity(UUID const id) const;

		/**
		 * @brief Gets the Entity at the given EntityPath, starting from the source Entity.
		 * @param source The source Entity.
		 * @param path The EntityPath.
		 */
		Entity get_entity(Entity const source, EntityPath const &path) const;

		/**
		 * @brief Gets a string representation of the given Entity.
		 * @param entity The Entity.
		 * @returns The string representation, in the format "Name (ID)".
		 */
		String to_string(Entity const entity) const;

		/**
		 * @brief Enables or disables the given Entity.
		 * @param entity The Entity.
		 * @param enabled True to enable, false to disable.
		 */
		void set_enabled(Entity const entity, Bool const enabled);

		/**
		 * @brief Checks if the given Entity is enabled.
		 * @param entity The Entity.
		 */
		Bool get_enabled(Entity const entity) const;

		/**
		 * @brief Sets the visibility of the given Entity.
		 * @param entity The Entity.
		 * @param visible True to make visible, false to make invisible.
		 */
		void set_visible(Entity const entity, Bool const visible);

		/**
		 * @brief Checks if the given Entity is visible.
		 * @param entity The Entity.
		 */
		Bool get_visible(Entity const entity) const;

		/**
		 * @brief Sets the layer of the given Entity.
		 * @param entity The Entity.
		 * @param layer The Layer to set.
		 */
		void set_layer(Entity const entity, Layer const layer);

		/**
		 * @brief Gets the layer of the given Entity.
		 * @param entity The Entity.
		 */
		Layer get_layer(Entity const entity) const;

		/**
		 * @brief Sets the parent of the given Entity.
		 * @param entity The Entity.
		 * @param parent The parent Entity.
		 */
		void set_parent(Entity const entity, Entity const parent);

		/**
		 * @brief Gets the parent of the given Entity.
		 * @param entity The Entity.
		 */
		Entity get_parent(Entity const entity) const;

		/**
		 * @brief Gets the child of the given Entity at the specified index.
		 * @param entity The Entity.
		 * @param index The index of the child.
		 */
		Entity get_child(Entity const entity, Size const index) const;

		/**
		 * @brief Gets the number of children the given Entity has.
		 * @param entity The Entity.
		 */
		Size get_child_count(Entity const entity) const;

		/**
		 * @brief Gets the name of the given Entity.
		 * @param entity The Entity.
		 */
		String get_name(Entity const entity) const;

		/**
		 * @brief Sets the name of the given Entity.
		 * @param entity The Entity.
		 * @param name The name to set.
		 */
		void set_name(Entity const entity, String const &name);

		/**
		 * @brief Gets the total number of Entities managed.
		 * @returns The number of Entities.
		 */
		inline Size get_size() const { return m_registry.storage<Entity>()->in_use(); }

	private:
		void remove_from_parent(RelationshipComponent &relationshipComp, RelationshipComponent &parentRelationshipComp);

		void add_to_parent(Entity const entity, RelationshipComponent &relationshipComp, RelationshipComponent &parentRelationshipComp);

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when the Scene is loaded.
		 */
		void on_scene_load() override;

		/**
		 * @brief Called every frame to update Entities.
		 * @param time The Timestep since the last frame.
		 */
		void frame_update(Timestep const time) override;

		/**
		 * @brief Called at a fixed interval to update Entities.
		 * @param time The Timestep since the last fixed update.
		 */
		void fixed_update(Timestep const time) override;

		/**
		 * @brief Finalizes the EntityManager, cleaning up resources.
		 */
		void finalize() override;

		/**
		 * @brief Checks if this manager contains an Entity with the given ID.
		 * @param id The Entity ID.
		 * @returns True if the Entity exists.
		 */
		inline Bool contains(UUID const id) const { return m_ids.contains(id); }

		/**
		 * @brief Checks if this manager contains the given Entity.
		 * @param entity The Entity.
		 */
		inline Bool contains(Entity const entity) const { return m_registry.valid(entity); }

		/**
		 * @brief Checks if the given Entity is in the specified Layer.
		 * @param entity The Entity.
		 * @param layer The Layer.
		 * @returns True if the Entity is in the Layer.
		 */
		Bool is_in_layer(Entity const entity, Layer const layer) const;

		/**
		 * @brief Checks if the given Entity is in the specified Layer mask.
		 * @param entity The Entity.
		 * @param mask The Layer mask.
		 * @returns True if the Entity is in the Layer mask.
		 */
		Bool is_in_mask(Entity const entity, Layer const mask) const;

		/**
		 * @brief Marks the given Entity as dirty. Dirty components need to be refreshed.
		 * @param entity The Entity.
		 */
		void dirty(Entity const entity);

		/**
		 * @brief Forcefully refreshes the given Entity. This will update all Components of the Entity, even if they are not dirty.
		 * @param entity The Entity.
		 */
		void refresh(Entity const entity);

		/**
		 * @brief Creates an empty Entity.
		 * @returns The Entity.
		 */
		Entity create_entity();

		/**
		 * @brief Creates an Entity with the given ID.
		 * @param id The Entity ID.
		 * @returns The Entity.
		 */
		Entity create_entity(UUID const id);

		/**
		 * @brief Creates a new entity with the specified name.
		 * @param name The name to assign to the newly created entity.
		 * @returns The Entity.
		 */
		Entity create_entity(String const &name);

		/**
		 * @brief Creates a new entity with the specified parent entity.
		 * @param parent The parent entity to associate with the newly created entity.
		 * @returns The Entity.
		 */
		Entity create_entity(Entity const parent);

		/**
		 * @brief Creates a new Entity with the specified name and unique identifier.
		 * @param name The name to assign to the new Entity.
		 * @param id The unique identifier (UUID) for the new Entity.
		 * @returns The Entity.
		 */
		Entity create_entity(String const &name, UUID const id);

		/**
		 * @brief Creates a new entity with the specified name, unique identifier, and parent entity.
		 * @param name The name to assign to the new entity.
		 * @param id The unique identifier for the new entity.
		 * @param parent The parent entity to associate with the new entity.
		 * @returns The Entity.
		 */
		Entity create_entity(String const &name, UUID const id, Entity const parent);

		/**
		 * @brief Spawns a new entity from the specified prefab.
		 * @param prefab A constant reference to the prefab used to create the entity.
		 * @returns The spawned Entity.
		 */
		Entity spawn_entity(Ref<Prefab> const &prefab);

		/**
		 * @brief Creates and returns a new entity instance from the specified prefab with the given name.
		 * @param prefab A reference to the prefab used to instantiate the entity.
		 * @param name The name to assign to the newly spawned entity.
		 * @returns The newly created entity instance.
		 */
		Entity spawn_entity(Ref<Prefab> const &prefab, String const &name);

		/**
		 * @brief Spawns a new entity from the given prefab with the specified unique identifier.
		 * @param prefab A reference to the prefab used to create the entity.
		 * @param id The unique identifier to assign to the spawned entity.
		 * @returns The newly spawned entity.
		 */
		Entity spawn_entity(Ref<Prefab> const &prefab, UUID const id);

		/**
		 * @brief Spawns a new entity from the given prefab, optionally attaching it to a parent entity.
		 * @param prefab A reference to the prefab to instantiate.
		 * @param parent The parent entity to which the new entity will be attached.
		 * @returns The newly spawned entity.
		 */
		Entity spawn_entity(Ref<Prefab> const &prefab, Entity const parent);

		/**
		 * @brief Creates and returns a new entity instance from the specified prefab.
		 * @param prefab A reference to the prefab to instantiate.
		 * @param name The name to assign to the spawned entity.
		 * @param id The unique identifier to assign to the entity.
		 * @returns The newly spawned entity.
		 */
		Entity spawn_entity(Ref<Prefab> const &prefab, String const &name, UUID const id);

		/**
		 * @brief Creates and returns a new entity instance from a prefab.
		 * @param prefab A reference to the prefab to instantiate.
		 * @param name The name to assign to the spawned entity.
		 * @param id The unique identifier to assign to the entity.
		 * @param parent The parent entity to which the new entity will be attached.
		 * @returns The newly spawned entity.
		 */
		Entity spawn_entity(Ref<Prefab> const &prefab, String const &name, UUID const id, Entity const parent);

		/**
		 * @brief Adds a Component to the given Entity.
		 * @tparam ComponentType The type of Component.
		 * @tparam Args Variadic template arguments.
		 * @param entity The Entity.
		 * @param args Arguments to forward to the Component constructor.
		 * @returns A reference to the newly added Component.
		 */
		template <typename ComponentType, typename... Args>
		ComponentType &add_component(Entity const entity, Args &&...args)
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			MINTY_ASSERT(!m_registry.all_of<ComponentType>(entity), ErrorCode::Entity_DuplicateComponent);
			return m_registry.emplace<ComponentType>(entity, std::forward<Args>(args)...);
		}

		/**
		 * @brief Adds a component with the specified name to the given entity and returns a reference to the newly added component.
		 * @param entity The entity to which the component will be added.
		 * @param name The name of the component to add.
		 * @returns A reference to the newly added component.
		 */
		Component &add_component(Entity const entity, String const &name);

		/**
		 * @brief Retrieves a reference to a component of the specified type from the given entity.
		 * @tparam ComponentType The type of the component to retrieve.
		 * @param entity The entity from which to retrieve the component.
		 * @returns A reference to the component of the specified type associated with the entity.
		 */
		template <typename ComponentType>
		ComponentType &get_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			MINTY_ASSERT(m_registry.all_of<ComponentType>(entity), ErrorCode::Entity_MissingComponent);
			return m_registry.get<ComponentType>(entity);
		}

		/**
		 * @brief Retrieves a reference to a component of the specified type from the given entity.
		 * @tparam ComponentType The type of the component to retrieve.
		 * @param entity The entity from which to retrieve the component.
		 * @returns A constant reference to the component of the specified type associated with the entity.
		 */
		template <typename ComponentType>
		ComponentType const &get_component(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			MINTY_ASSERT(m_registry.all_of<ComponentType>(entity), ErrorCode::Entity_MissingComponent);
			return m_registry.get<ComponentType>(entity);
		}

		/**
		 * @brief Retrieves a reference to a component of the specified entity by name.
		 * @param entity The entity from which to retrieve the component.
		 * @param name The name of the component to retrieve.
		 * @returns A reference to the requested component.
		 */
		Component &get_component(Entity const entity, String const &name);

		/**
		 * @brief Retrieves a constant reference to a component of the specified entity by name.
		 * @param entity The entity from which to retrieve the component.
		 * @param name The name of the component to retrieve.
		 * @returns A constant reference to the requested component.
		 */
		Component const &get_component(Entity const entity, String const &name) const;

		/**
		 * @brief Retrieves a component of the specified type from the given entity, or adds it if it does not exist.
		 * @tparam ComponentType The type of the component to retrieve or add.
		 * @param entity The entity from which to get or add the component.
		 * @returns A reference to the component of the specified type associated with the entity.
		 */
		template <typename ComponentType>
		ComponentType &get_or_add_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			return m_registry.get_or_emplace<ComponentType>(entity);
		}

		/**
		 * @brief Retrieves a component by name from the specified entity, or adds it if it does not exist.
		 * @param entity The entity from which to retrieve or add the component.
		 * @param name The name of the component to retrieve or add.
		 * @returns A reference to the retrieved or newly added component.
		 */
		Component &get_or_add_component(Entity const entity, String const &name);

		/**
		 * @brief Attempts to retrieve a pointer to a component of the specified type from the given entity.
		 * @tparam ComponentType The type of the component to retrieve.
		 * @param entity The entity from which to retrieve the component.
		 * @returns A pointer to the component of the specified type if it exists; otherwise, nullptr.
		 */
		template <typename ComponentType>
		ComponentType *try_get_component(Entity const entity)
		{
			if(!m_registry.valid(entity))
			{
				return nullptr;
			}
			return m_registry.try_get<ComponentType>(entity);
		}

		/**
		 * @brief Attempts to retrieve a pointer to a component of the specified type from the given entity.
		 * @tparam ComponentType The type of the component to retrieve.
		 * @param entity The entity from which to retrieve the component.
		 * @returns A pointer to the component of the specified type if it exists; otherwise, nullptr.
		 */
		template <typename ComponentType>
		ComponentType const *try_get_component(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			return m_registry.try_get<ComponentType>(entity);
		}

		/**
		 * @brief Attempts to retrieve a component from the specified entity by name.
		 * @param entity The entity from which to retrieve the component.
		 * @param name The name of the component to retrieve.
		 * @returns A pointer to the component if found; otherwise, nullptr.
		 */
		Component *try_get_component(Entity const entity, String const &name);

		/**
		 * @brief Attempts to retrieve a component from the specified entity by name.
		 * @param entity The entity from which to retrieve the component.
		 * @param name The name of the component to retrieve.
		 * @returns A pointer to the component if found; otherwise, nullptr.
		 */
		Component const *try_get_component(Entity const entity, String const &name) const;

		/**
		 * @brief Checks if the specified entity has a component of the given type.
		 * @tparam ComponentType The type of the component to check for.
		 * @param entity The entity to check for the component.
		 * @returns True if the entity has the specified component; otherwise, false.
		 */
		template <typename ComponentType>
		Bool has_component(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			return m_registry.all_of<ComponentType>(entity);
		}

		/**
		 * @brief Checks whether the specified entity has a component with the given name.
		 * @param entity The entity to check for the component.
		 * @param name The name of the component to look for.
		 * @returns True if the entity has a component with the specified name; otherwise, false.
		 */
		Bool has_component(Entity const entity, String const &name) const;

		/**
		 * @brief Checks if the specified entity has all components of the given types.
		 * @tparam ComponentTypes The types of the components to check for.
		 * @param entity The entity to check for the components.
		 * @returns True if the entity has all the specified components; otherwise, false.
		 */
		template <typename... ComponentTypes>
		Bool has_all_components(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			return m_registry.all_of<ComponentTypes...>(entity);
		}

		/**
		 * @brief Checks if the specified entity has any components of the given types.
		 * @tparam ComponentTypes The types of the components to check for.
		 * @param entity The entity to check for the components.
		 * @returns True if the entity has any of the specified components; otherwise, false.
		 */
		template <typename... ComponentTypes>
		Bool has_any_components(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			return m_registry.any_of<ComponentTypes...>(entity);
		}

		/**
		 * @brief Removes a component of the specified type from an entity.
		 * @tparam ComponentType The type of the component to remove from the entity.
		 * @param entity The entity from which the component will be removed.
		 */
		template <typename ComponentType>
		void remove_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			m_registry.remove<ComponentType>(entity);
		}

		/**
		 * @brief Removes a component with the specified name from the given entity.
		 * @param entity The entity from which the component will be removed.
		 * @param name The name of the component to remove.
		 */
		void remove_component(Entity const entity, String const &name);

		/**
		 * @brief Destroys all Entities.
		 */
		void clear();

		/**
		 * @brief Destroys all Components of the given type. If any Entity has this Component, it will be removed.
		 * @tparam ComponentType The type of Component.
		 */
		template <typename ComponentType>
		void clear()
		{
			m_registry.clear<ComponentType>();
		}

		/**
		 * @brief Clears the Component from the given Entity.
		 * @tparam ComponentType The type of Component.
		 * @param entity The Entity.
		 */
		template <typename ComponentType>
		void clear(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			if (m_registry.all_of<ComponentType>(entity))
			{
				m_registry.remove<ComponentType>(entity);
			}
		}

		/**
		 * @brief Adds or replaces the component on the given Entity.
		 * @tparam ComponentType The type of Component.
		 * @param entity The Entity to add the Component to.
		 */
		template <typename ComponentType>
		void mark(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), ErrorCode::Entity_NotValid);
			m_registry.emplace_or_replace<ComponentType>(entity);

			// mark children as well
			RelationshipComponent const *const relationshipComp = m_registry.try_get<RelationshipComponent>(entity);
			if (relationshipComp && relationshipComp->children > 0)
			{
				Entity child = relationshipComp->first;
				while (child != INVALID_ENTITY)
				{
					mark<ComponentType>(child);
					child = m_registry.get<RelationshipComponent>(child).next;
				}
			}
		}

		/**
		 * @brief Adds or replaces the component on all Entities.
		 * @tparam ComponentType The type of Component.
		 */
		template <typename ComponentType>
		void mark_all()
		{
			for (auto const [entity] : m_registry.storage<Entity>().each())
			{
				m_registry.emplace_or_replace<ComponentType>(entity);
			}
		}

		/**
		 * @brief Gets an EntityView with the given Components.
		 * @tparam Include The Component types to include.
		 * @tparam Exclude The Component types to exclude.
		 * @param exclude The exclude parameter.
		 * @returns A view containing all of the Entities with the given Component types.
		 */
		template <typename... Include, typename... Exclude>
		auto view(entt::exclude_t<Exclude...> exclude = entt::exclude_t{})
		{
			return EntityView(m_registry.view<Include...>(exclude));
		}

		/**
		 * @brief Sorts all of the Entities. The order is based on the RelationshipComponent hierarchy.
		 */
		void sort();

		/**
		 * @brief Sorts the Entities with the given Component type.
		 * @tparam T The Component type.
		 * @param compare The compare function.
		 */
		template <typename T>
		void sort(Function<Bool(T const &, T const &)> const &compare)
		{
			m_registry.sort<T>(compare);
		}

		/**
		 * @brief Sorts the Entities with the given Component type.
		 * @tparam T The Component type.
		 * @param compare The compare function.
		 */
		template <typename T>
		void sort(Function<Bool(Entity const, Entity const)> const &compare)
		{
			m_registry.sort<T>(compare);
		}

		/**
		 * @brief Swaps the positions of two sibling entities.
		 * @param left The first sibling entity to swap.
		 * @param right The second sibling entity to swap.
		 */
		void swap_siblings(Entity const left, Entity const right);

		/**
		 * @brief Advances the specified entity to its next state or position.
		 * @param entity The entity to be moved to the next state or position.
		 */
		void move_to_next(Entity const entity);

		/**
		 * @brief Moves the specified entity to its previous position or state.
		 * @param entity The entity to be moved to the previous position or state.
		 */
		void move_to_previous(Entity const entity);

		/**
		 * @brief Moves the specified entity to the first position.
		 * @param entity The entity to move to the first position.
		 */
		void move_to_first(Entity const entity);

		/**
		 * @brief Moves the specified entity to the last position.
		 * @param entity The entity to move to the last position.
		 */
		void move_to_last(Entity const entity);

		/**
		 * @brief Destroys the given Entity.
		 * @param entity The Entity.
		 */
		void destroy(Entity const entity);

		/**
		 * @brief Destroys all Entities with the given Component type.
		 * @tparam ComponentType The type of Component.
		 */
		template <typename ComponentType>
		void destroy_with()
		{
			for (auto &&[entity, comp] : m_registry.view<ComponentType>().each())
			{
				destroy(entity);
			}
		}

		/**
		 * @brief Destroys the given Entity immediately.
		 * @param entity The Entity to destroy.
		 */
		void destroy_immediately(Entity const entity);

		/**
		 * @brief Destroys all Entities with a DestroyComponent.
		 */
		void cleanup();
		
		void serialize(Writer &writer) const override;
		Bool deserialize(Reader &reader) override;

		/**
		 * @brief Registers a Component type with the EntityManager.
		 * @tparam T The Component type.
		 * @param name The name of the Component.
		 */
		template <typename T, typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
		static void register_component(String const &name)
		{
			MINTY_ASSERT_F(!s_registeredComponents.contains(name), ErrorCode::Argument_KeyAlreadyExists, name);
			MINTY_ASSERT_F(!s_registeredComponents.contains(typeid(T)), ErrorCode::Argument_KeyAlreadyExists, typeid(T).name());

			ComponentData info{
				.name = name,
				.create = [](EntityManager &entityManager, Entity const entity) -> Component &
				{
					return entityManager.add_component<T>(entity);
				},
				.get = [](EntityManager &entityManager, Entity const entity) -> Component *
				{
					return entityManager.try_get_component<T>(entity);
				},
				.get_const = [](EntityManager const &entityManager, Entity const entity) -> Component const *
				{
					return entityManager.try_get_component<T>(entity);
				},
				.destroy = [](EntityManager &entityManager, Entity const entity) -> void
				{
					entityManager.remove_component<T>(entity);
				}};

			s_registeredComponents.add(name, typeid(T), info);
		}

		/**
		 * @brief Gets the ComponentData for the Component with the given name.
		 * @param name The name of the Component.
		 */
		inline static ComponentData const &get_component_info(String const &name)
		{
			MINTY_ASSERT(!name.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
			MINTY_ASSERT_F(s_registeredComponents.contains(name), ErrorCode::Component_NotRegistered, name);
			return s_registeredComponents.at(name);
		}

		/**
		 * @brief Gets the ComponentData for the Component with the given TypeID.
		 * @param typeId The TypeID of the Component.
		 */
		inline static ComponentData const &get_component_info(TypeID const &typeId)
		{
			MINTY_ASSERT_F(s_registeredComponents.contains(typeId), ErrorCode::Component_NotRegistered, typeId.name());
			return s_registeredComponents.at(typeId);
		}

		/**
		 * @brief Clears all registered components.
		 */
		inline static void clear_registered_components()
		{
			s_registeredComponents.clear();
		}
		
		/**
		 * @brief Creates a new EntityManager with the given arguments.
		 * @param scene The Scene this EntityManager belongs to.
		 * @param info The arguments.
		 * @returns An EntityManager Owner.
		 */
		static Shared<EntityManager> create(Ref<Scene> const& scene, EntityManagerInfo const &info);

		/**
		 * @brief Creates a default EntityManager.
		 * @param scene The Scene this EntityManager belongs to.
		 * @returns An EntityManager Owner.
		 */
		static Shared<EntityManager> create(Ref<Scene> const& scene);

		/**
		 * @brief Gets the singleton EntityManager for the active Scene.
		 * @returns The EntityManager.
		 */
		static EntityManager &get_singleton();

	private:
		// finalizes dirty components
		void finalize_dirties();

		Entity create_entity_smart(String const &name, UUID const id);

		// preps the entity for destruction
		void strip_entity(Entity const entity);

		void update_transform(Entity const entity, Entity const parent, TransformComponent &transformComp);

		void update_uiTransform(Entity const entity, Entity const parent, UITransformComponent &uiTransformComp);

		Bool deserialize_entities(Reader &reader, Map<UUID, Entity> *idMap = nullptr, Entity const baseEntity = INVALID_ENTITY);

		Bool deserialize_components(Reader &reader, Entity const entity, Map<UUID, Entity> *idMap = nullptr);
		
		static void deserialize_entity_header(Reader &reader, Size const index, String &name, UUID &id, UUID &prefabId);

#pragma endregion

#pragma region Variables

	private:
		entt::registry m_registry;

		Map<UUID, Entity> m_ids;
		Bool m_needsSorted;
		
		static Lookup<TypeID, ComponentData> s_registeredComponents;

#pragma endregion
	};
}

#endif // MINTY_ENTITY_ENTITYMANAGER_H