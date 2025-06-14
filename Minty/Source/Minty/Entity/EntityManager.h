#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Core/Types.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Entity/EntityPath.h"
#include "Minty/Entity/EntityView.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Manager/SubManager.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
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
			, m_ids()
		{
		}

		EntityManager(EntityManager&& other) noexcept
			: SubManager(std::move(other))
			, m_registry(std::move(other.m_registry))
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
				m_ids = std::move(other.m_ids);
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		UUID get_id(Entity const entity) const;

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

		Component& add_component(Entity const entity, String const& name);

		template<typename ComponentType>
		ComponentType& get_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.get<ComponentType>(entity);
		}

		template<typename ComponentType>
		ComponentType const& get_component(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.get<ComponentType>(entity);
		}

		Component& get_component(Entity const entity, String const& name);

		Component const& get_component(Entity const entity, String const& name) const;

		template<typename ComponentType>
		ComponentType* try_get_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.try_get<ComponentType>(entity);
		}

		template<typename ComponentType>
		ComponentType const* try_get_component(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.try_get<ComponentType>(entity);
		}

		Component* try_get_component(Entity const entity, String const& name);

		Component const* try_get_component(Entity const entity, String const& name) const;

		template<typename ComponentType>
		Bool has_component(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.all_of<ComponentType>(entity);
		}

		Bool has_component(Entity const entity, String const& name) const;

		template<typename ComponentType>
		void remove_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			m_registry.remove<ComponentType>(entity);
		}

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
		/// Adds or replaces the component on the given Entity.
		/// </summary>
		/// <typeparam name="ComponentType">The type of Component.</typeparam>
		/// <param name="entity">The Entity to add the Component to.</param>
		template<typename ComponentType>
		void mark_entity(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			m_registry.emplace_or_replace<ComponentType>(entity);
		}

		/// <summary>
		/// Adds or replaces the component on all Entities.
		/// </summary>
		/// <typeparam name="ComponentType">The type of Component.</typeparam>
		template<typename ComponentType>
		void mark_all_entities()
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

		void swap_siblings(Entity const left, Entity const right);

		void move_to_next(Entity const entity);

		void move_to_previous(Entity const entity);

		void move_to_first(Entity const entity);

		void move_to_last(Entity const entity);

		void destroy(Entity const entity);

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
		Bool deserialize_components(Reader& reader, Entity const entity, Size const index);

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

#pragma endregion
};
}