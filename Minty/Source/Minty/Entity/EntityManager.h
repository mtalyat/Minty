#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Context/Manager.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Entity/EntityView.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"

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
		: public Manager
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
		EntityManager(EntityManagerBuilder const& builder)
			: Manager()
			, m_registry()
			, m_ids()
		{
		}

#pragma endregion

#pragma region Iterators

	public:

#pragma endregion

#pragma region Get Set

	public:
		UUID get_id(Entity const entity) const;

		Entity get_entity(UUID const id) const;

		void set_enabled(Entity const entity, Bool const enabled);

		Bool get_enabled(Entity const entity) const;

		void set_visible(Entity const entity, Bool const visible);

		Bool get_visible(Entity const entity) const;

		void set_layer(Entity const entity, Layer const layer);

		Layer get_layer(Entity const entity) const;

		void set_parent(Entity const entity, Entity const parent);

		Entity get_parent(Entity const entity) const;

		String get_name(Entity const entity) const;

		void set_name(Entity const entity, String const& name);

#pragma endregion

#pragma region Methods

	public:
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

		Bool is_in_layer(Entity const entity, Layer const mask);

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

		template<typename ComponentType>
		Bool has_component(Entity const entity) const
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			return m_registry.all_of<ComponentType>(entity);
		}

		template<typename ComponentType>
		void remove_component(Entity const entity)
		{
			MINTY_ASSERT(m_registry.valid(entity), "Entity is not valid.");
			m_registry.remove<ComponentType>(entity);
		}

		/// <summary>
		/// Destroys all Entities.
		/// </summary>
		void clear();

		template<typename... Get>
		EntityView<Get...> view()
		{
			return EntityView<Get...>(m_registry);
		}

		/// <summary>
		/// Sorts all of the Entities in the EntityManager.
		/// The order is based on the RelationshipComponent hierarchy.
		/// </summary>
		void sort();

		void swap_siblings(Entity const left, Entity const right);

		void move_to_next(Entity const entity);

		void move_to_previous(Entity const entity);

		void move_to_first(Entity const entity);

		void move_to_last(Entity const entity);

#pragma endregion

#pragma region Statics

	public:
		static Owner<EntityManager> create(EntityManagerBuilder const& builder = {});

		static EntityManager& get_singleton();

#pragma endregion
	};
}