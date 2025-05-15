#include "pch.h"
#include "EntityManager.h"
#include "Minty/Component/DirtyComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Component/LayerComponent.h"
#include "Minty/Component/NameComponent.h"
#include "Minty/Component/RelationshipComponent.h"
#include "Minty/Component/UUIDComponent.h"
#include "Minty/Component/VisibleComponent.h"
#include "Minty/Context/Context.h"

using namespace Minty;

UUID Minty::EntityManager::get_id(Entity const entity) const
{
	if (entity == INVALID_ENTITY)
	{
		return INVALID_ID;
	}

	UUIDComponent const* uuidComponent = m_registry.try_get<UUIDComponent>(entity);
	if (uuidComponent)
	{
		return uuidComponent->id;
	}
	// no related ID
	return INVALID_ID;
}

Entity Minty::EntityManager::get_entity(UUID const id) const
{
	if (!id.is_valid())
	{
		return INVALID_ENTITY;
	}

	auto it = m_ids.find(id);
	if (it != m_ids.end())
	{
		return it->get_second();
	}

	// no related entity
	return INVALID_ENTITY;
}

void Minty::EntityManager::set_enabled(Entity const entity, Bool const enabled)
{
	if (get_enabled(entity) != enabled)
	{
		if (enabled)
		{
			m_registry.emplace<EnabledComponent>(entity);
		}
		else
		{
			m_registry.remove<EnabledComponent>(entity);
		}
	}
}

Bool Minty::EntityManager::get_enabled(Entity const entity) const
{
	return m_registry.all_of<EnabledComponent>(entity);
}

void Minty::EntityManager::set_visible(Entity const entity, Bool const visible)
{
	if (get_visible(entity) != visible)
	{
		if (visible)
		{
			m_registry.emplace<VisibleComponent>(entity);
		}
		else
		{
			m_registry.remove<VisibleComponent>(entity);
		}
	}
}

Bool Minty::EntityManager::get_visible(Entity const entity) const
{
	return m_registry.all_of<VisibleComponent>(entity);
}

void Minty::EntityManager::set_layer(Entity const entity, Layer const layer)
{
	// remove layer component if setting to default
	if (layer == LAYER_DEFAULT)
	{
		if (m_registry.all_of<LayerComponent>(entity))
		{
			m_registry.remove<LayerComponent>(entity);
		}
		return;
	}

	LayerComponent& layerComponent = m_registry.get_or_emplace<LayerComponent>(entity);
	layerComponent.layer = layer;
}

Layer Minty::EntityManager::get_layer(Entity const entity) const
{
	LayerComponent const* layerComponent = m_registry.try_get<LayerComponent>(entity);
	if (layerComponent)
	{
		return layerComponent->layer;
	}

	return LAYER_DEFAULT;
}

void Minty::EntityManager::set_parent(Entity const entity, Entity const parent)
{
	// verify there is no parent loop
#ifdef MINTY_DEBUG
	// check if this entity is a child of the parent
	Entity current = parent;
	while (current != INVALID_ENTITY)
	{
		MINTY_ASSERT(current != entity, "Entity is a child of itself.");
		// get the relationship component
		RelationshipComponent const* temp = m_registry.try_get<RelationshipComponent>(current);
		if (!temp)
		{
			break;
		}
		current = temp->parent;
	}
#endif // MINTY_DEBUG

	RelationshipComponent& relationshipComponent = m_registry.get_or_emplace<RelationshipComponent>(entity);

	// if existing parent, remove from parent
	if (relationshipComponent.parent != INVALID_ENTITY)
	{
		RelationshipComponent& parentRelationshipComponent = m_registry.get<RelationshipComponent>(relationshipComponent.parent);

		// if this is the first child, set parent's first to next
		if (relationshipComponent.prev != INVALID_ENTITY)
		{
			parentRelationshipComponent.first = relationshipComponent.next;
		}
		// if this is the last child, set parent's last to prev
		if (relationshipComponent.next != INVALID_ENTITY)
		{
			parentRelationshipComponent.last = relationshipComponent.prev;
		}

		// iterate from next to end and update indices
		Entity sibling = relationshipComponent.next;
		while (sibling != INVALID_ENTITY)
		{
			RelationshipComponent& siblingRelationshipComponent = m_registry.get<RelationshipComponent>(sibling);
			siblingRelationshipComponent.index--;
			sibling = siblingRelationshipComponent.next;
		}

		// update child count
		parentRelationshipComponent.children--;

		// clear this entity's relationship
		relationshipComponent.prev = INVALID_ENTITY;
		relationshipComponent.next = INVALID_ENTITY;
		relationshipComponent.depth = 0;
	}

	// set parent
	relationshipComponent.parent = parent;

	// if parent is valid, add to parent's children
	if (parent != INVALID_ENTITY)
	{
		RelationshipComponent& parentRelationshipComponent = m_registry.get_or_emplace<RelationshipComponent>(parent);

		// set this entity's index
		relationshipComponent.index = parentRelationshipComponent.children;

		// if this is the first child, set parent's first to this
		if (parentRelationshipComponent.first == INVALID_ENTITY)
		{
			parentRelationshipComponent.first = entity;
			relationshipComponent.prev = INVALID_ENTITY;
		}
		else
		{
			// else, set this entity's prev to parent's last
			relationshipComponent.prev = parentRelationshipComponent.last;
			m_registry.get<RelationshipComponent>(parentRelationshipComponent.last).next = entity;
		}

		// set this entity's next to INVALID_ENTITY
		relationshipComponent.next = INVALID_ENTITY;

		// set parent's last to this
		parentRelationshipComponent.last = entity;

		// increment child count
		parentRelationshipComponent.children++;

		// set depth
		relationshipComponent.depth = parentRelationshipComponent.depth + 1;
	}

	// if no parent or children, remove the relationship component
	if (relationshipComponent.parent == INVALID_ENTITY && relationshipComponent.children == 0)
	{
		m_registry.remove<RelationshipComponent>(entity);
		return;
	}

	// if children, update their depths
	if (relationshipComponent.children)
	{
		Stack<Tuple<UInt, Entity>> entitiesToUpdate;
		entitiesToUpdate.push({ relationshipComponent.depth + 1, relationshipComponent.first });

		while (!entitiesToUpdate.is_empty())
		{
			Tuple<UInt, Entity> pair = entitiesToUpdate.pop();

			// get the relationship component
			RelationshipComponent& comp = m_registry.get<RelationshipComponent>(pair.get_second());

			// update the depth
			comp.depth = pair.first;

			// add next and child, if any
			if (comp.next != INVALID_ENTITY)
			{
				entitiesToUpdate.push({ pair.first, comp.next });
			}
			if (comp.first != INVALID_ENTITY)
			{
				entitiesToUpdate.push({ pair.first + 1, comp.first });
			}
		}
	}
}

Entity Minty::EntityManager::get_parent(Entity const entity) const
{
	RelationshipComponent const* relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);
	if (relationshipComponent)
	{
		return relationshipComponent->parent;
	}
	return INVALID_ENTITY;
}

String Minty::EntityManager::get_name(Entity const entity) const
{
	NameComponent const* nameComponent = m_registry.try_get<NameComponent>(entity);
	if (nameComponent)
	{
		return nameComponent->name;
	}
	return String();
}

void Minty::EntityManager::set_name(Entity const entity, String const& name)
{
	// remove name
	if (name.is_empty())
	{
		if (m_registry.all_of<NameComponent>(entity))
		{
			m_registry.remove<NameComponent>(entity);
		}
		return;
	}

	// set name
	NameComponent& nameComponent = m_registry.get_or_emplace<NameComponent>(entity);
	nameComponent.name = name;
}

Bool Minty::EntityManager::is_in_layer(Entity const entity, Layer const mask) const
{
	Layer layer = get_layer(entity);

	// special case for LAYER_NONE
	if (mask == LAYER_NONE)
	{
		return layer == LAYER_NONE;
	}

	// check if layer is within mask
	return (layer & mask) == mask;
}

void Minty::EntityManager::dirty(Entity const entity)
{
	// mark the entity as dirty
	m_registry.emplace_or_replace<DirtyComponent>(entity);
}

Entity Minty::EntityManager::create_entity()
{
	return m_registry.create();
}

Entity Minty::EntityManager::create_entity(UUID const id)
{
	MINTY_ASSERT(!contains(id), "Entity with the given ID already exists.");

	// create empty entity
	Entity entity = m_registry.create();

	// add the id component
	UUIDComponent& idComponent = m_registry.emplace<UUIDComponent>(entity);
	idComponent.id = id;

	// link ID to Entity
	m_ids.add(id, entity);

	// done
	return entity;
}

Entity Minty::EntityManager::create_entity(String const& name)
{
	// create empty entity
	Entity entity = m_registry.create();

	// add the name component
	NameComponent& nameComponent = m_registry.emplace<NameComponent>(entity);
	nameComponent.name = name;

	// done
	return entity;
}

Entity Minty::EntityManager::create_entity(String const& name, UUID const id)
{
	// create empty entity
	Entity entity = m_registry.create();

	// add the name component
	NameComponent& nameComponent = m_registry.emplace<NameComponent>(entity);
	nameComponent.name = name;

	// add the id component
	UUIDComponent& idComponent = m_registry.emplace<UUIDComponent>(entity);
	idComponent.id = id;

	// link ID to Entity
	m_ids.add(id, entity);

	// done
	return entity;
}

void Minty::EntityManager::clear()
{
	m_registry.clear();
	m_ids.clear();
}

void Minty::EntityManager::sort()
{
	m_registry.sort<RelationshipComponent>([&](Entity const left, Entity const right)
		{
			RelationshipComponent const& leftRelationship = m_registry.get<RelationshipComponent>(left);
			RelationshipComponent const& rightRelationship = m_registry.get<RelationshipComponent>(right);
			RelationshipComponent const* leftR = &leftRelationship;
			RelationshipComponent const* rightR = &rightRelationship;

			// get equal depth relationships
			while (leftR->depth > rightR->depth)
			{
				leftR = &m_registry.get<RelationshipComponent>(leftR->parent);
			}
			while (rightR->depth > leftR->depth)
			{
				rightR = &m_registry.get<RelationshipComponent>(rightR->parent);
			}

			// if index is equal, they are part of the same tree
			if (leftR->index == rightR->index)
			{
				// use depth of originals
				return leftRelationship.depth < rightRelationship.depth;
			}
			else
			{
				// if not equal, use index, as they are part of different trees
				return leftR->index < rightR->index;
			}
		});
}

void Minty::EntityManager::swap_siblings(Entity const left, Entity const right)
{
	MINTY_ASSERT(left != right, "Cannot swap the same entity.");
	MINTY_ASSERT(contains(left), "Left entity does not exist.");
	MINTY_ASSERT(contains(right), "Right entity does not exist.");

	RelationshipComponent* leftRelationshipComponent = m_registry.try_get<RelationshipComponent>(left);
	RelationshipComponent* rightRelationshipComponent = m_registry.try_get<RelationshipComponent>(right);

	// if no relationship component, do nothing
	if (!leftRelationshipComponent || !rightRelationshipComponent)
	{
		return;
	}

	MINTY_ASSERT(leftRelationshipComponent->parent == rightRelationshipComponent->parent, "Entities are not siblings.");

	// swap the indices
	UInt tempIndex = leftRelationshipComponent->index;
	leftRelationshipComponent->index = rightRelationshipComponent->index;
	rightRelationshipComponent->index = tempIndex;

	// swap the siblings

	// if adjacent, handle differently
	if (leftRelationshipComponent->next == right)
	{
		leftRelationshipComponent->next = rightRelationshipComponent->next;
		rightRelationshipComponent->prev = leftRelationshipComponent->prev;
		leftRelationshipComponent->prev = right;
		rightRelationshipComponent->next = left;
	}
	else if(leftRelationshipComponent->prev == left)
	{
		rightRelationshipComponent->next = leftRelationshipComponent->next;
		leftRelationshipComponent->prev = right;
		rightRelationshipComponent->prev = left;
		leftRelationshipComponent->next = right;
	}
	else
	{
		Entity tempEntity = leftRelationshipComponent->next;
		leftRelationshipComponent->next = rightRelationshipComponent->next;
		rightRelationshipComponent->next = tempEntity;
		tempEntity = leftRelationshipComponent->prev;
		leftRelationshipComponent->prev = rightRelationshipComponent->prev;
		rightRelationshipComponent->prev = tempEntity;
	}

	// update the parent's first and last children
	RelationshipComponent& parent = m_registry.get<RelationshipComponent>(leftRelationshipComponent->parent);
	if (parent.first == left)
	{
		parent.first = right;
	}
	else if (parent.first == right)
	{
		parent.first = left;
	}
	if (parent.last == left)
	{
		parent.last = right;
	}
	else if (parent.last == right)
	{
		parent.last = left;
	}
}

void Minty::EntityManager::move_to_next(Entity const entity)
{
	MINTY_ASSERT(contains(entity), "Entity does not exist.");

	RelationshipComponent* relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);

	// if no relationship component, do nothing
	if (!relationshipComponent)
	{
		return;
	}

	// if no parent, do nothing
	if (relationshipComponent->parent == INVALID_ENTITY)
	{
		return;
	}

	// if last, do nothing
	if (relationshipComponent->next == INVALID_ENTITY)
	{
		return;
	}

	// swap with next
	swap_siblings(entity, relationshipComponent->next);
}

void Minty::EntityManager::move_to_previous(Entity const entity)
{
	MINTY_ASSERT(contains(entity), "Entity does not exist.");

	RelationshipComponent* relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);

	// if no relationship component, do nothing
	if (!relationshipComponent)
	{
		return;
	}

	// if no parent, do nothing
	if (relationshipComponent->parent == INVALID_ENTITY)
	{
		return;
	}

	// if first, do nothing
	if (relationshipComponent->prev == INVALID_ENTITY)
	{
		return;
	}

	// swap with prev
	swap_siblings(entity, relationshipComponent->prev);
}

void Minty::EntityManager::move_to_first(Entity const entity)
{
	MINTY_ASSERT(contains(entity), "Entity does not exist.");

	RelationshipComponent* relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);

	// if no relationship component, do nothing
	if (!relationshipComponent)
	{
		return;
	}

	// if no parent, do nothing
	if (relationshipComponent->parent == INVALID_ENTITY)
	{
		return;
	}

	// if first, do nothing
	if (relationshipComponent->prev == INVALID_ENTITY)
	{
		return;
	}

	// get the parent
	Entity parent = relationshipComponent->parent;
	RelationshipComponent& parentRelationshipComponent = m_registry.get<RelationshipComponent>(parent);

	// get the first child
	Entity first = parentRelationshipComponent.first;
	RelationshipComponent& firstRelationshipComponent = m_registry.get<RelationshipComponent>(first);

	// bridge the gap in the current position
	if (relationshipComponent->next != INVALID_ENTITY)
	{
		RelationshipComponent& nextRelationshipComponent = m_registry.get<RelationshipComponent>(relationshipComponent->next);
		nextRelationshipComponent.prev = relationshipComponent->prev;
	}
	RelationshipComponent& prevRelationshipComponent = m_registry.get<RelationshipComponent>(relationshipComponent->prev);
	prevRelationshipComponent.next = relationshipComponent->next;
	if (parentRelationshipComponent.last == entity)
	{
		parentRelationshipComponent.last = relationshipComponent->prev;
	}

	// insert into first position
	parentRelationshipComponent.first = entity;
	relationshipComponent->prev = INVALID_ENTITY;
	relationshipComponent->next = first;
	firstRelationshipComponent.prev = entity;

	// update indices
	Entity temp = entity;
	UInt index = 0;
	while (temp != INVALID_ENTITY)
	{
		RelationshipComponent& tempRelationshipComponent = m_registry.get<RelationshipComponent>(temp);
		tempRelationshipComponent.index = index;
		temp = tempRelationshipComponent.next;
		index++;
	}
}

void Minty::EntityManager::move_to_last(Entity const entity)
{
	MINTY_ASSERT(contains(entity), "Entity does not exist.");

	RelationshipComponent* relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);\

	// if no relationship component, do nothing
	if (!relationshipComponent)
	{
		return;
	}

	// if no parent, do nothing
	if (relationshipComponent->parent == INVALID_ENTITY)
	{
		return;
	}

	// if last, do nothing
	if (relationshipComponent->next == INVALID_ENTITY)
	{
		return;
	}

	// get the parent
	Entity parent = relationshipComponent->parent;
	RelationshipComponent& parentRelationshipComponent = m_registry.get<RelationshipComponent>(parent);

	// get the last child
	Entity last = parentRelationshipComponent.last;
	RelationshipComponent& lastRelationshipComponent = m_registry.get<RelationshipComponent>(last);

	// bridge the gap in the current position
	if (relationshipComponent->prev != INVALID_ENTITY)
	{
		RelationshipComponent& prevRelationshipComponent = m_registry.get<RelationshipComponent>(relationshipComponent->prev);
		prevRelationshipComponent.next = relationshipComponent->next;
	}
	Entity next = relationshipComponent->next;
	RelationshipComponent& nextRelationshipComponent = m_registry.get<RelationshipComponent>(next);
	nextRelationshipComponent.prev = relationshipComponent->prev;
	if (parentRelationshipComponent.first == entity)
	{
		parentRelationshipComponent.first = relationshipComponent->next;
	}

	// insert into last position
	parentRelationshipComponent.last = entity;
	relationshipComponent->prev = last;
	relationshipComponent->next = INVALID_ENTITY;
	lastRelationshipComponent.next = entity;

	// update indices
	Entity temp = next;
	UInt index = 0;
	while (temp != INVALID_ENTITY)
	{
		RelationshipComponent& tempRelationshipComponent = m_registry.get<RelationshipComponent>(temp);
		tempRelationshipComponent.index = index;
		temp = tempRelationshipComponent.next;
		index++;
	}
}

void Minty::EntityManager::finalize()
{
	// TODO: update all dirty components

	// sort the entities
	sort();
}

Owner<EntityManager> Minty::EntityManager::create(EntityManagerBuilder const& builder)
{
	return Owner<EntityManager>(builder);
}

EntityManager& Minty::EntityManager::get_singleton()
{
	// get the active scene
	Ref<Scene> const& activeScene = Context::get_singleton().get_scene_manager().get_active();
	MINTY_ASSERT(activeScene != nullptr, "No active scene. Cannot get EntityManager.");
	return activeScene->get_entity_manager();
}
