#include "pch.hpp"
#include "EntityManager.hpp"
#include "EntityManagerInfo.hpp"
#include "Core/Constant/Invalid.hpp"
#include "Core/Tool/Format.hpp"
#include "Core/Debug/DebugF.hpp"
#include "Core/Data/Stack.hpp"

#include "World/Component/NameComponent.hpp"
#include "World/Component/UUIDComponent.hpp"
#include "World/Component/RelationshipComponent.hpp"
#include "World/Component/TransformComponent.hpp"

using namespace Minty;

Minty::EntityManager::EntityManager(EntityManagerInfo const &info, Scene &scene)
	: mp_scene(&scene),
	  m_registry(),
	  m_needsSorted(false),
	  m_registeredComponents()
{
}

EntityHandle Minty::EntityManager::create()
{
	return entt_to_minty(m_registry.create());
}

EntityHandle Minty::EntityManager::create(UUID const id)
{
	entt::entity const entityEntt = m_registry.create();
	m_registry.emplace<UUIDComponent>(entityEntt, id);
	return entt_to_minty(entityEntt);
}

EntityHandle Minty::EntityManager::create(StringView const name)
{
	entt::entity const entityEntt = m_registry.create();
	m_registry.emplace<NameComponent>(entityEntt, name);
	return entt_to_minty(entityEntt);
}

EntityHandle Minty::EntityManager::create(UUID const id, StringView const name)
{
	entt::entity const entityEntt = m_registry.create();
	m_registry.emplace<UUIDComponent>(entityEntt, id);
	m_registry.emplace<NameComponent>(entityEntt, name);
	return entt_to_minty(entityEntt);
}

EntityHandle Minty::EntityManager::create(EntityHandle const parent)
{
	EntityHandle const entity = create();
	set_parent(entity, parent);
	return entity;
}

EntityHandle Minty::EntityManager::create(UUID const id, EntityHandle const parent)
{
	EntityHandle const entity = create(id);
	set_parent(entity, parent);
	return entity;
}

EntityHandle Minty::EntityManager::create(StringView const name, EntityHandle const parent)
{
	EntityHandle const entity = create(name);
	set_parent(entity, parent);
	return entity;
}

EntityHandle Minty::EntityManager::create(UUID const id, StringView const name, EntityHandle const parent)
{
	EntityHandle const entity = create(id, name);
	set_parent(entity, parent);
	return entity;
}

void Minty::EntityManager::destroy(EntityHandle const entity)
{
	MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);

	// remove the entity
	m_registry.destroy(minty_to_entt(entity));
}

EntityHandle Minty::EntityManager::find(UUID const id) const
{
	for (auto const &[entity, uuidComp] : m_registry.view<UUIDComponent>().each())
	{
		if (uuidComp.id == id)
		{
			return entt_to_minty(entity);
		}
	}
	return INVALID_ENTITY;
}

String Minty::EntityManager::to_string(EntityHandle const entity) const
{
	MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);

	if (m_registry.all_of<NameComponent>(minty_to_entt(entity)))
	{
		return m_registry.get<NameComponent>(minty_to_entt(entity)).name;
	}
	else
	{
		return F("Entity({})", static_cast<UInt>(entity));
	}
}

Bool Minty::EntityManager::add_by_name(EntityHandle const entity, StringView const componentName)
{
	MINTY_ASSERT(is_valid(entity), ErrorCodeEnum::Entity_NotValid);
	MINTY_ASSERT(m_registeredComponents.is_registered(componentName), ErrorCodeEnum::Component_NotRegistered);
	MINTY_ASSERT(!m_registeredComponents.has(componentName, entity), ErrorCodeEnum::Object_InvalidState); // already has component
	m_registeredComponents.add(componentName, entity);
	return true;
}

void Minty::EntityManager::set_parent(EntityHandle const entity, EntityHandle const parent)
{
	// verify there is no parent loop
#ifdef MINTY_DEBUG
	// check if this entity is a child of the parent
	EntityHandle current = parent;
	Vector<EntityHandle> visited;
	visited.add(entity);
	while (current != INVALID_ENTITY)
	{
		visited.add(current);
		if (current == entity)
		{
			StringBuilder builder;
			for (EntityHandle const e : visited)
			{
				builder.append(to_string(e));
				builder.append(", ");
			}
			builder.slice(0, builder.get_size() - 2);
			MINTY_ERROR_F(
				ErrorCodeEnum::Entity_CyclicRelationship,
				"Cyclic relationship detected when setting parent. Visited entities: {}",
				builder.get_view());
			break;
		}
		// get the relationship component
		entt::entity currentEntt = minty_to_entt(current);
		RelationshipComponent const *temp = m_registry.try_get<RelationshipComponent>(currentEntt);
		if (!temp)
		{
			break;
		}
		current = temp->parent;
	}
#endif // MINTY_DEBUG

	entt::entity entityEntt = minty_to_entt(entity);
	RelationshipComponent &relationshipComponent = m_registry.get_or_emplace<RelationshipComponent>(entityEntt);

	if (relationshipComponent.parent != INVALID_ENTITY)
	{
		// remove from parent
		entt::entity parentEntt = minty_to_entt(relationshipComponent.parent);
		RelationshipComponent &parentRelationshipComponent = m_registry.get<RelationshipComponent>(parentEntt);
		remove_from_parent(relationshipComponent, parentRelationshipComponent);
	}

	// set parent
	relationshipComponent.parent = parent;

	// if parent is valid, add to parent's children
	if (parent != INVALID_ENTITY)
	{
		// add to parent
		entt::entity parentEntt = minty_to_entt(parent);
		if (!m_registry.all_of<RelationshipComponent>(parentEntt))
		{
			// if parent does not have a relationship component, create one
			set_parent(parent, INVALID_ENTITY);
		}
		RelationshipComponent &parentRelationshipComponent = m_registry.get<RelationshipComponent>(parentEntt);
		add_to_parent(entity, relationshipComponent, parentRelationshipComponent);
	}

	// manager needs to resort the relationships
	m_needsSorted = true;

	// if children, update their depths
	if (relationshipComponent.children)
	{
		Stack<Tuple<UInt, EntityHandle>> entitiesToUpdate;
		entitiesToUpdate.push({relationshipComponent.depth + 1, relationshipComponent.first});

		while (!entitiesToUpdate.is_empty())
		{
			Tuple<UInt, EntityHandle> pair = entitiesToUpdate.pop();

			// get the relationship component
			entt::entity entityToUpdateEntt = minty_to_entt(pair.get_second());
			RelationshipComponent &comp = m_registry.get<RelationshipComponent>(entityToUpdateEntt);

			// update the depth
			comp.depth = pair.first;

			// add next and child, if any
			if (comp.next != INVALID_ENTITY)
			{
				entitiesToUpdate.push({pair.first, comp.next});
			}
			if (comp.first != INVALID_ENTITY)
			{
				entitiesToUpdate.push({pair.first + 1, comp.first});
			}
		}
	}

	// // if the entity has a UITransform, update its Canvas value
	// if (UITransformComponent *uiTransform = try_get<UITransformComponent>(entity))
	// {
	// 	uiTransform->canvas = INVALID_ENTITY;

	// 	EntityHandle parent = entity;

	// 	while (parent != INVALID_ENTITY)
	// 	{
	// 		// if parent has canvas, set value
	// 		if (CanvasComponent *canvas = try_get<CanvasComponent>(parent))
	// 		{
	// 			uiTransform->canvas = parent;
	// 			break;
	// 		}

	// 		// move to next parent
	// 		RelationshipComponent const *parentRelationship = try_get<RelationshipComponent const>(parent);
	// 		if (!parentRelationship)
	// 		{
	// 			break;
	// 		}
	// 		parent = parentRelationship->parent;
	// 	}
	// }
}

EntityHandle Minty::EntityManager::get_parent(EntityHandle const entity) const
{
	RelationshipComponent const *relationship = try_get<RelationshipComponent const>(entity);
	if (!relationship)
	{
		return INVALID_ENTITY;
	}
	return relationship->parent;
}

void Minty::EntityManager::on_finalize()
{
	// Sort if needed
	if (m_needsSorted)
	{
		sort();
		m_needsSorted = false;
	}

	update_global_transforms();
}

void Minty::EntityManager::sort()
{
	// Sort the entities based on their depth in the hierarchy
	m_registry.sort<RelationshipComponent>([&](RelationshipComponent const &leftRelationship, RelationshipComponent const &rightRelationship)
										   { 
											if (leftRelationship.depth == rightRelationship.depth)
											{
												// If equal depth, sort by index
												return leftRelationship.index < rightRelationship.index;
											} else
											{
												// If not equal depth, sort by depth
												return leftRelationship.depth < rightRelationship.depth;
											} });
}

void Minty::EntityManager::update_global_transforms()
{
	// Entities without hierarchy data are treated as roots.
	auto transformView = m_registry.view<TransformComponent>();
	for (auto &&[entity, transformComponent] : transformView.each())
	{
		if (!m_registry.all_of<RelationshipComponent>(entity))
		{
			transformComponent.transform.set_global_matrix(transformComponent.transform.get_local_matrix());
		}
	}

	// RelationshipComponent storage is kept sorted parent-first by depth.
	auto relationshipView = m_registry.view<RelationshipComponent>();
	for (auto &&[entity, relationshipComponent] : relationshipView.each())
	{
		TransformComponent *transformComponent = m_registry.try_get<TransformComponent>(entity);
		if (!transformComponent)
		{
			continue;
		}

		Matrix4 const &local = transformComponent->transform.get_local_matrix();
		if (relationshipComponent.parent == INVALID_ENTITY)
		{
			transformComponent->transform.set_global_matrix(local);
			continue;
		}

		entt::entity parentEntity = minty_to_entt(relationshipComponent.parent);
		TransformComponent const *parentTransform = m_registry.try_get<TransformComponent>(parentEntity);
		if (!parentTransform)
		{
			transformComponent->transform.set_global_matrix(local);
			continue;
		}

		transformComponent->transform.set_global_matrix(parentTransform->transform.get_global_matrix() * local);
	}
}

void Minty::EntityManager::remove_from_parent(RelationshipComponent &relationshipComp, RelationshipComponent &parentRelationshipComp)
{
	// if this is the first child, set parent's first to next
	if (relationshipComp.prev == INVALID_ENTITY)
	{
		parentRelationshipComp.first = relationshipComp.next;
	}
	// if this is the last child, set parent's last to prev
	if (relationshipComp.next == INVALID_ENTITY)
	{
		parentRelationshipComp.last = relationshipComp.prev;
	}

	// update previous sibling's next
	if (relationshipComp.prev != INVALID_ENTITY)
	{
		entt::entity prevSibling = minty_to_entt(relationshipComp.prev);
		m_registry.get<RelationshipComponent>(prevSibling).next = relationshipComp.next;
	}

	// update next sibling's prev
	if (relationshipComp.next != INVALID_ENTITY)
	{
		entt::entity nextSibling = minty_to_entt(relationshipComp.next);
		m_registry.get<RelationshipComponent>(nextSibling).prev = relationshipComp.prev;
	}

	// iterate from next to end and update indices
	EntityHandle sibling = relationshipComp.next;
	while (sibling != INVALID_ENTITY)
	{
		entt::entity siblingEntt = minty_to_entt(sibling);
		RelationshipComponent &siblingRelationshipComponent = m_registry.get<RelationshipComponent>(siblingEntt);
		siblingRelationshipComponent.index--;
		sibling = siblingRelationshipComponent.next;
	}

	// update child count
	parentRelationshipComp.children--;
	// Children count is not zero, yet there is no first and last children.
	MINTY_ASSERT(
		parentRelationshipComp.children == 0 ||
			(parentRelationshipComp.first != INVALID_ENTITY &&
			 parentRelationshipComp.last != INVALID_ENTITY),
		ErrorCodeEnum::Entity_InvalidRelationship);

	// clear this entity's relationship
	relationshipComp.prev = INVALID_ENTITY;
	relationshipComp.next = INVALID_ENTITY;
	relationshipComp.depth = 0;
}

void Minty::EntityManager::add_to_parent(EntityHandle const entity, RelationshipComponent &relationshipComp, RelationshipComponent &parentRelationshipComp)
{
	// set this entity's index
	relationshipComp.index = parentRelationshipComp.children;

	// if this is the first child, set parent's first to this
	if (parentRelationshipComp.first == INVALID_ENTITY)
	{
		parentRelationshipComp.first = entity;
		relationshipComp.prev = INVALID_ENTITY;
	}
	else
	{
		// else, set this entity's prev to parent's last
		relationshipComp.prev = parentRelationshipComp.last;
		if (relationshipComp.prev != INVALID_ENTITY)
		{
			entt::entity prevSibling = minty_to_entt(relationshipComp.prev);
			m_registry.get<RelationshipComponent>(prevSibling).next = entity;
		}
	}

	// set this entity's next to INVALID_ENTITY
	relationshipComp.next = INVALID_ENTITY;

	// set parent's last to this
	parentRelationshipComp.last = entity;

	// increment child count
	parentRelationshipComp.children++;

	// set depth
	relationshipComp.depth = parentRelationshipComp.depth + 1;
}
