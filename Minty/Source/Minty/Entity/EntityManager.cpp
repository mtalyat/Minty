#include "pch.h"
#include "EntityManager.h"
#include "Minty/Component/_Component.h"
#include "Minty/Context/Context.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Entity/Prefab.h"

using namespace Minty;

void Minty::EntityManager::remove_from_parent(RelationshipComponent& relationshipComp, RelationshipComponent& parentRelationshipComp)
{
	// if this is the first child, set parent's first to next
	if (relationshipComp.prev != INVALID_ENTITY)
	{
		parentRelationshipComp.first = relationshipComp.next;
	}
	// if this is the last child, set parent's last to prev
	if (relationshipComp.next != INVALID_ENTITY)
	{
		parentRelationshipComp.last = relationshipComp.prev;
	}

	// iterate from next to end and update indices
	Entity sibling = relationshipComp.next;
	while (sibling != INVALID_ENTITY)
	{
		RelationshipComponent& siblingRelationshipComponent = m_registry.get<RelationshipComponent>(sibling);
		siblingRelationshipComponent.index--;
		sibling = siblingRelationshipComponent.next;
	}

	// update child count
	parentRelationshipComp.children--;

	// clear this entity's relationship
	relationshipComp.prev = INVALID_ENTITY;
	relationshipComp.next = INVALID_ENTITY;
	relationshipComp.depth = 0;
}

void Minty::EntityManager::add_to_parent(Entity const entity, RelationshipComponent& relationshipComp, RelationshipComponent& parentRelationshipComp)
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
			m_registry.get<RelationshipComponent>(parentRelationshipComp.last).next = entity;
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

void Minty::EntityManager::set_id(Entity const entity, UUID const id)
{
	// ignore invalid entity
	if (entity == INVALID_ENTITY)
	{
		return;
	}

	// check if same ID
	UUID const currentId = get_id(entity);
	if (currentId == id)
	{
		return;
	}

	// remove old ID mapping
	if (currentId.is_valid())
	{
		m_ids.remove(currentId);
	}

	// set new ID mapping
	if (id.is_valid())
	{
		m_ids.add(id, entity);
		m_registry.get_or_emplace<UUIDComponent>(entity).id = id;
	}
	else
	{
		m_registry.remove<UUIDComponent>(entity);
	}
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

Entity Minty::EntityManager::get_entity(Entity const source, EntityPath const& path) const
{
	// if no path, it is the source entity
	if (path.is_empty())
	{
		return source;
	}

	// follow the children indices down until found
	Entity entity = source;
	RelationshipComponent const* relationshipComponent;
	for (Byte index : path.get_path())
	{
		relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);
		if (!relationshipComponent)
		{
			return INVALID_ENTITY;
		}

		// get the child entity
		entity = get_child(entity, index);
		if (entity == INVALID_ENTITY)
		{
			return INVALID_ENTITY;
		}
	}

	// found the entity
	return entity;
}

String Minty::EntityManager::get_entity_string(Entity const entity) const
{
	String const& name = get_name(entity);
	UUID const id = get_id(entity);

	if (name.is_empty())
	{
		if (id.is_valid())
		{
			return format("({})", id);
		}
		else
		{
			return "";
		}
	}
	else
	{
		if (id.is_valid())
		{
			return format("{} ({})", name, id);
		}
		else
		{
			return name;
		}
	}
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

	if (relationshipComponent.parent == INVALID_ENTITY)
	{
		// remove from root, if part of root
		Entity child = m_root.first;
		while(child != INVALID_ENTITY && child != entity)
		{
			child = m_registry.get<RelationshipComponent>(child).next;
		}
		if (child != INVALID_ENTITY)
		{
			// child must be part of root, so remove it
			remove_from_parent(relationshipComponent, m_root);
		}
	}
	else
	{
		// remove from parent
		RelationshipComponent& parentRelationshipComponent = m_registry.get<RelationshipComponent>(relationshipComponent.parent);
		remove_from_parent(relationshipComponent, parentRelationshipComponent);
	}

	// set parent
	relationshipComponent.parent = parent;

	// if parent is valid, add to parent's children
	if (parent == INVALID_ENTITY)
	{
		// add to root
		add_to_parent(entity, relationshipComponent, m_root);
	}
	else
	{
		// add to parent
		if(!m_registry.all_of<RelationshipComponent>(parent))
		{
			// if parent does not have a relationship component, create one
			set_parent(parent, INVALID_ENTITY);
		}
		RelationshipComponent& parentRelationshipComponent = m_registry.get<RelationshipComponent>(parent);
		add_to_parent(entity, relationshipComponent, parentRelationshipComponent);
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

	// if the entity has a UITransform, update its Canvas value
	if (UITransformComponent* uiTransform = try_get_component<UITransformComponent>(entity))
	{
		uiTransform->canvas = INVALID_ENTITY;

		Entity parent = entity;

		while (parent != INVALID_ENTITY)
		{
			// if parent has canvas, set value
			if (CanvasComponent* canvas = try_get_component<CanvasComponent>(parent))
			{
				uiTransform->canvas = parent;
				break;
			}

			// move to next parent
			RelationshipComponent const* parentRelationship = try_get_component<RelationshipComponent const>(parent);
			if (!parentRelationship)
			{
				break;
			}
			parent = parentRelationship->parent;
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

Entity Minty::EntityManager::get_child(Entity const entity, Size const index) const
{
	RelationshipComponent const* relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);
	if (relationshipComponent)
	{
		Entity child = relationshipComponent->first;
		for (Size i = 0; i < index && child != INVALID_ENTITY; i++)
		{
			child = m_registry.get<RelationshipComponent>(child).next;
		}
		return child;
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

void Minty::EntityManager::finalize_dirties()
{
	// update dirty text components
	AssetManager& assetManager = AssetManager::get_singleton();
	for (auto&& [entity, dirtyComp, uiTransformComp, textComp, meshComp] : m_registry.view<DirtyComponent const, UITransformComponent const, TextComponent const, MeshComponent>().each())
	{
		// if no font or variant or text, destroy the mesh
		if (textComp.font == nullptr || textComp.fontVariant == nullptr || textComp.text == nullptr || textComp.text.is_empty())
		{
			if (meshComp.mesh != nullptr)
			{
				// unload the mesh
				assetManager.unload(meshComp.mesh->get_id());
				meshComp.mesh = nullptr;
			}

			continue;
		}

		// create a builder
		MeshBuilder builder{};
		builder.type = MeshType::Custom;

		// (re)generate the mesh
		builder.vertices = ListContainer(sizeof(Float) * 4, textComp.text.get_size());
		ListContainer& vertices = builder.vertices;
		builder.indices = ListContainer(sizeof(UShort), (textComp.text.get_size() * 6) / 4); // 6 indices for every 4 vertices
		ListContainer& indices = builder.indices;

		Float xAdvance = 0.0f;
		Float yAdvance = 0.0f;
		UShort index = 0;

		Ref<Font> const& font = textComp.font;
		Ref<FontVariant> const& fontVariant = textComp.fontVariant;
		Ref<Texture> const& fontVariantTexture = fontVariant->get_texture();
		UInt2 textureSize = fontVariantTexture->get_size();
		Float const width = static_cast<Float>(textureSize.x);
		Float const height = static_cast<Float>(textureSize.y);
		Char last = '\0';

		for (Char c : textComp.text)
		{
			// special characters
			Bool cont = true;
			switch (c)
			{
			case '\n':
				yAdvance += fontVariant->get_line_height();
				xAdvance = 0;
				break;
			default:
				cont = false;
				break;
			}

			// if special character handled, skip, keep going
			if (cont)
			{
				last = c;
				continue;
			}

			// get font character data
			FontChar const* fc = fontVariant->get_char(c);

			if (!fc)
			{
				MINTY_ERROR(F("There is no FontChar data for character \"{}\" in font \"{}\".", c, font->get_name()));

				last = c;

				continue;
			}

			Float2 const min(fc->x, fc->y);
			Float2 const max(fc->x + fc->width, fc->y + fc->height);
			Float2 const offset(fc->xOffset, fc->yOffset);

			// adjust spacing for special cases
			xAdvance += fontVariant->get_kerning(last, c);

			// create vertices based on each Char
			Float4 value = { xAdvance + offset.x, yAdvance + offset.y, min.x, min.y };
			vertices.append_object(value); // bottom left
			value = { xAdvance + fc->width + offset.x, yAdvance + offset.y, max.x, min.y };
			vertices.append_object(value); // bottom right
			value = { xAdvance + fc->width + offset.x, yAdvance + fc->height + offset.y, max.x, max.y };
			vertices.append_object(value); // top left
			value = { xAdvance + offset.x, yAdvance + fc->height + offset.y, min.x, max.y };
			vertices.append_object(value); // top right

			// create indices, always in the same order
			indices.append_object(index);
			indices.append_object(static_cast<UShort>(index + 1));
			indices.append_object(static_cast<UShort>(index + 2));
			indices.append_object(index);
			indices.append_object(static_cast<UShort>(index + 2));
			indices.append_object(static_cast<UShort>(index + 3));

			index += 4;

			// advance the "cursor"
			xAdvance += fc->xAdvance;

			// update new last Char
			last = c;
		}

		// create the new mesh
		// if no mesh, create a new mesh quickly
		if (meshComp.mesh == nullptr)
		{
			// create new mesh outright
			builder.id = UUID::create();
			meshComp.mesh = assetManager.create<Mesh>(builder);
		}
		else
		{
			// replace existing mesh
			builder.id = meshComp.mesh->get_id();
			*meshComp.mesh = Mesh(builder);
		}

		// update the material
		meshComp.material = fontVariant->get_material();
	}
	clear<DirtyTextComponent>();

	// update dirty canvas transforms
	for (auto&& [entity, uiTransformComp, canvasComp, dirty] : m_registry.view<UITransformComponent, CanvasComponent const, DirtyComponent const>().each())
	{
		// get window size as a rect
		Window& window = Context::get_singleton().get_window();
		UInt2 windowSize = window.get_size();
		Rect windowRect(0.0f, 0.0f, static_cast<Float>(windowSize.x), static_cast<Float>(windowSize.y));

		// canvas controls the size and position
		uiTransformComp.transform.set_position(windowRect.x, windowRect.y);
		uiTransformComp.transform.set_size(windowRect.width, windowRect.height);
		uiTransformComp.transform.set_global_rect(canvasComp.canvas.get_rect());
	}

	// update entities with relationships
	for (auto&& [entity, relationshipComp] : m_registry.view<RelationshipComponent>().each())
	{
		if(TransformComponent* transformComp = m_registry.try_get<TransformComponent>(entity))
		{
			update_transform(entity, relationshipComp.parent, *transformComp);
		}
		else if (UITransformComponent* uiTransformComp = m_registry.try_get<UITransformComponent>(entity))
		{
			update_uiTransform(entity, relationshipComp.parent, *uiTransformComp);
		}
	}

	// update entities without relationships
	for (auto&& [entity, transformComp] : m_registry.view<TransformComponent>(entt::exclude<RelationshipComponent>).each())
	{
		// if no relationship, update the transform with no parent
		update_transform(entity, INVALID_ENTITY, transformComp);
	}
	for (auto&& [entity, uiTransformComp] : m_registry.view<UITransformComponent>(entt::exclude<RelationshipComponent>).each())
	{
		// if no relationship, update the UITransform with no parent
		update_uiTransform(entity, INVALID_ENTITY, uiTransformComp);
	}

	// clear all dirties
	clear<DirtyComponent>();
}

Entity Minty::EntityManager::create_entity_smart(String const& name, UUID const id)
{
	if (id.is_valid())
	{
		if (name.is_empty())
		{
			return create_entity(id);
		}
		else
		{
			return create_entity(name, id);
		}
	}
	else
	{
		if (name.is_empty())
		{
			return create_entity();
		}
		else
		{
			return create_entity(name);
		}
	}
}

void Minty::EntityManager::update_transform(Entity const entity, Entity const parent, TransformComponent& transformComp)
{
	// if parent, use parent's global matrix
	if (parent != INVALID_ENTITY)
	{
		// get the parent transform
		TransformComponent const* parentTransform = m_registry.try_get<TransformComponent>(parent);
		if (parentTransform)
		{
			Matrix4 matrix = parentTransform->transform.get_global_matrix() * transformComp.transform.get_local_matrix();
			transformComp.transform.set_global_matrix(matrix);

			return;
		}
	}

	// if no parent, or if no parent transform, use local matrix
	transformComp.transform.set_global_matrix(transformComp.transform.get_local_matrix());
}

void Minty::EntityManager::update_uiTransform(Entity const entity, Entity const parent, UITransformComponent& uiTransformComp)
{
	// use the parent, if there is one and it is not the canvas
	if (parent != INVALID_ENTITY && parent != uiTransformComp.canvas)
	{
		UITransformComponent const* parentUITransform = m_registry.try_get<UITransformComponent>(parent);
		if (parentUITransform)
		{
			uiTransformComp.transform.update_global_rect(parentUITransform->transform.get_global_rect());
			return;
		}
	}

	// if no parent, use canvas
	if (uiTransformComp.canvas != INVALID_ENTITY)
	{
		CanvasComponent const* canvas = m_registry.try_get<CanvasComponent>(uiTransformComp.canvas);
		if (canvas)
		{
			uiTransformComp.transform.update_global_rect(canvas->canvas.get_rect());
			return;
		}
	}

	// get window size as a rect
	Window& window = Context::get_singleton().get_window();
	UInt2 windowSize = window.get_size();
	Rect windowRect(0.0f, 0.0f, static_cast<Float>(windowSize.x), static_cast<Float>(windowSize.y));

	// if no parent and no canvas, default to Window rect
	uiTransformComp.transform.update_global_rect(windowRect);
}

Bool Minty::EntityManager::is_in_layer(Entity const entity, Layer const layer) const
{
	Layer entityLayer = get_layer(entity);

	// special case for LAYER_NONE
	if (layer == LAYER_NONE)
	{
		return entityLayer == LAYER_NONE;
	}

	// check if the layer is within the Entity's layers
	return (entityLayer & layer) == layer;
}

Bool Minty::EntityManager::is_in_mask(Entity const entity, Layer const mask) const
{
	Layer entityLayer = get_layer(entity);

	// special case for LAYER_NONE
	if (mask == LAYER_NONE)
	{
		return entityLayer == LAYER_NONE;
	}

	// check if the Entity's layers are within the layer mask
	return (entityLayer & mask) == entityLayer;
}

void Minty::EntityManager::dirty(Entity const entity)
{
	// mark the entity as dirty
	m_registry.emplace_or_replace<DirtyComponent>(entity);

	// stop if no children
	RelationshipComponent const* relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);
	if (!relationshipComponent || relationshipComponent->children == 0)
	{
		return;
	}

	// dirty all children, and their children
	Stack<Entity> entitiesToDirty;
	entitiesToDirty.push(entity);
	while (!entitiesToDirty.is_empty())
	{
		Entity currentEntity = entitiesToDirty.pop();
		m_registry.emplace_or_replace<DirtyComponent>(currentEntity);

		// get the relationship component
		RelationshipComponent const& relationship = m_registry.get<RelationshipComponent>(currentEntity);

		// dirty all children
		Entity child = relationship.first;
		while (child != INVALID_ENTITY)
		{
			entitiesToDirty.push(child);
			child = m_registry.get<RelationshipComponent>(child).next;
		}
	}
}

void Minty::EntityManager::refresh(Entity const entity)
{
	// remove dirty component
	if (m_registry.all_of<DirtyComponent>(entity))
	{
		m_registry.remove<DirtyComponent>(entity);
	}

	// if parent is dirty, refresh it as well
	RelationshipComponent const* relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);
	if (relationshipComponent && relationshipComponent->parent != INVALID_ENTITY && has_component<DirtyComponent>(relationshipComponent->parent))
	{
		// refresh the parent
		refresh(relationshipComponent->parent);
	}

	// if Transform, update global matrix
	TransformComponent* transformComponent = m_registry.try_get<TransformComponent>(entity);
	if (transformComponent)
	{
		update_transform(entity, get_parent(entity), *transformComponent);
	}

	// if UITransform, update the global rect
	UITransformComponent* uiTransformComponent = m_registry.try_get<UITransformComponent>(entity);
	if (uiTransformComponent)
	{
		update_uiTransform(entity, get_parent(entity), *uiTransformComponent);
	}

	// if there are children, refresh all of those
	if (relationshipComponent && relationshipComponent->children > 0)
	{
		Entity child = relationshipComponent->first;
		while (child != INVALID_ENTITY)
		{
			refresh(child);
			child = m_registry.get<RelationshipComponent>(child).next;
		}
	}
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

Entity Minty::EntityManager::create_entity(Entity const parent)
{
	// create empty entity
	Entity entity = m_registry.create();

	// set the parent
	set_parent(entity, parent);

	// done
	return entity;
}

Entity Minty::EntityManager::create_entity(Ref<Prefab> const& prefab)
{
	MINTY_ASSERT(prefab != nullptr, "Prefab is null.");

	TextNodeReader reader(prefab->get_node());
	if (reader.get_size() == 0)
	{
		return INVALID_ENTITY;
	}
	Map<UUID, UUID> idMap;

	// add first entity to the ID map
	UUID id = UUID::create();
	String name;
	UUID eId;
	UUID pId;
	deserialize_entity(reader, 0, name, eId, pId);
	idMap.add(eId, id);
	Entity entity = create_entity(name, id);

	// deserialize the rest of the entities
	if (!deserialize_prefab(reader, idMap))
	{
		MINTY_ABORT(F("Failed to create Entity from Prefab \"{}\".", prefab->get_id()));
		return INVALID_ENTITY;
	}

	dirty(entity);
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

Entity Minty::EntityManager::create_entity(String const& name, UUID const id, Entity const parent)
{
	// create empty entity
	Entity entity = create_entity(name, id);

	// set the parent
	set_parent(entity, parent);

	// done
	return entity;
}

Entity Minty::EntityManager::create_entity(String const& name, UUID const id, Entity const parent, Ref<Prefab> const& prefab)
{
	MINTY_ASSERT(id.is_valid(), "ID is not valid.");
	MINTY_ASSERT(prefab != nullptr, "Prefab is null.");
	TextNodeReader reader(prefab->get_node());
	if (reader.get_size() == 0)
	{
		return INVALID_ENTITY;
	}
	Map<UUID, UUID> idMap;

	// add first entity to the ID map
	String oldName;
	UUID eId;
	UUID pId;
	deserialize_entity(reader, 0, oldName, eId, pId);
	idMap.add(eId, id);
	Entity entity = create_entity(name, id, parent);

	// deserialize the rest of the entities
	if (!deserialize_prefab(reader, idMap))
	{
		MINTY_ABORT(F("Failed to create Entity from Prefab \"{}\".", prefab->get_id()));
		return INVALID_ENTITY;
	}

	dirty(entity);
	return entity;
}

Component& Minty::EntityManager::add_component(Entity const entity, String const& name)
{
	Context& context = Context::get_singleton();
	ComponentInfo const* info = context.get_component_info(name);
	MINTY_ASSERT(info, F("Failed to find_first component info for \"{}\".", name));
	return info->create(*this, entity);
}

Component& Minty::EntityManager::get_component(Entity const entity, String const& name)
{
	Context& context = Context::get_singleton();
	ComponentInfo const* info = context.get_component_info(name);
	MINTY_ASSERT(info, F("Failed to find_first component info for \"{}\".", name));
	Component* component = info->get(*this, entity);
	MINTY_ASSERT(component, F("Failed to get component \"{}\".", name));
	return *component;
}

Component const& Minty::EntityManager::get_component(Entity const entity, String const& name) const
{
	Context const& context = Context::get_singleton();
	ComponentInfo const* info = context.get_component_info(name);
	MINTY_ASSERT(info, F("Failed to find_first component info for \"{}\".", name));
	Component const* component = info->get_const(*this, entity);
	MINTY_ASSERT(component, F("Failed to get component \"{}\".", name));
	return *component;
}

Component& Minty::EntityManager::get_or_add_component(Entity const entity, String const& name)
{
	Context& context = Context::get_singleton();
	ComponentInfo const* info = context.get_component_info(name);
	MINTY_ASSERT(info, F("Failed to find_first component info for \"{}\".", name));
	Component* component = info->get(*this, entity);
	if (component == nullptr)
	{
		// create the component if it does not exist
		return info->create(*this, entity);
	}
	else
	{
		// return the existing component
		return *component;
	}
}

Component* Minty::EntityManager::try_get_component(Entity const entity, String const& name)
{
	Context& context = Context::get_singleton();
	ComponentInfo const* info = context.get_component_info(name);
	MINTY_ASSERT(info, F("Failed to find_first component info for \"{}\".", name));
	Component* component = info->get(*this, entity);
	return component;
}

Component const* Minty::EntityManager::try_get_component(Entity const entity, String const& name) const
{
	Context const& context = Context::get_singleton();
	ComponentInfo const* info = context.get_component_info(name);
	MINTY_ASSERT(info, F("Failed to find_first component info for \"{}\".", name));
	Component const* component = info->get_const(*this, entity);
	return component;
}

Bool Minty::EntityManager::has_component(Entity const entity, String const& name) const
{
	Context const& context = Context::get_singleton();
	ComponentInfo const* info = context.get_component_info(name);
	MINTY_ASSERT(info, F("Failed to find_first component info for \"{}\".", name));
	Component const* component = info->get_const(*this, entity);
	return component != nullptr;
}

void Minty::EntityManager::remove_component(Entity const entity, String const& name)
{
	Context& context = Context::get_singleton();
	ComponentInfo const* info = context.get_component_info(name);
	MINTY_ASSERT(info, F("Failed to find_first component info for \"{}\".", name));
	info->destroy(*this, entity);
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
			if (left == right)
			{
				return false;
			}

			RelationshipComponent const& leftRelationship = m_registry.get<RelationshipComponent>(left);
			RelationshipComponent const& rightRelationship = m_registry.get<RelationshipComponent>(right);

			// if the depths are different, compare by depth first
			if(leftRelationship.depth != rightRelationship.depth)
			{
				return leftRelationship.depth < rightRelationship.depth;
			}

			// keep going up until they have the same parent
			RelationshipComponent const* leftR = &leftRelationship;
			RelationshipComponent const* rightR = &rightRelationship;
			while (leftR->parent != rightR->parent)
			{
				leftR = &m_registry.get<RelationshipComponent>(leftR->parent);
				rightR = &m_registry.get<RelationshipComponent>(rightR->parent);
			}

			// sort by index of ancestor
			return leftR->index < rightR->index;
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
	else if (leftRelationshipComponent->prev == left)
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

void Minty::EntityManager::destroy(Entity const entity)
{
	MINTY_ASSERT(contains(entity), "Entity does not exist.");
	m_registry.destroy(entity);
}

void Minty::EntityManager::initialize()
{
	// dirty all components on load
	mark_all<DirtyComponent>();

	Manager::initialize();
}

void Minty::EntityManager::update(Time const& time)
{
	// remove any entities that are marked for destruction
	cleanup();

	// sort the entities
	sort();

	// refresh the dirty components
	finalize_dirties();

	Manager::update(time);
}

void Minty::EntityManager::finalize()
{
	// sort the entities
	sort();

	// refresh the dirty components
	finalize_dirties();

	Manager::finalize();
}

void Minty::EntityManager::cleanup()
{
	destroy_with<DestroyComponent>();
}

Entity Minty::EntityManager::deserialize_entity(Reader& reader, Size const index)
{
	// deserialize the entity data
	String name;
	UUID id;
	UUID prefabId;
	deserialize_entity(reader, index, name, id, prefabId);

	// create the entity
	Entity entity = create_entity_smart(name, id);

	// if a prefab, save ID for later
	if (prefabId.is_valid())
	{
		PrefabComponent& prefabComponent = m_registry.emplace<PrefabComponent>(entity);
		prefabComponent.id = prefabId;
	}

	return entity;
}

Bool Minty::EntityManager::deserialize_components(Reader& reader, Size const index, EntitySerializationData data)
{
	MINTY_ASSERT(contains(data.entity), F("Failed to deserialize Entity at index {}.", index));

	// step into the entity
	if (!reader.indent(index))
	{
		MINTY_ERROR(F("Failed to indent for entity {}.", get_entity_string(data.entity)));
		return false;
	}

	Context const& context = Context::get_singleton();

	// create the serialization data
	reader.push_user_data(&data);

	// read each component on the Entity
	String componentName;
	ComponentInfo const* info;
	for (Size i = 0; i < reader.get_size(); i++)
	{
		if (!reader.read_name(i, componentName) || componentName.is_empty())
		{
			MINTY_ERROR(F("Failed to read component name at index {}.", i));
			continue;
		}

		// fix name
		componentName = componentName.trim_end();

		info = context.get_component_info(componentName);
		MINTY_ASSERT(info != nullptr, F("Component \"{}\" does not exist.", componentName));

		// get the component
		Component* component = info->get(*this, data.entity);

		// create the component if it does not exist yet
		if (!component)
		{
			component = &info->create(*this, data.entity);
		}

		// deserialize the component
		if (reader.indent(i))
		{
			if (!component->deserialize(reader))
			{
				MINTY_ERROR(F("Failed to deserialize component \"{}\" for entity {}.", componentName, get_entity_string(data.entity)));
				continue;
			}

			reader.outdent();
		}
	}

	reader.pop_user_data();
	reader.outdent();

	return true;
}

Bool Minty::EntityManager::deserialize_prefab(Reader& reader, Map<UUID, UUID>& idMap)
{
	// deserialize each entity
	Vector<Entity> entities;
	for (Size i = 0; i < reader.get_size(); i++)
	{
		// deserialize the entity
		String name;
		UUID id;
		UUID prefabId;
		deserialize_entity(reader, i, name, id, prefabId);

		// get the new ID of the entity, and the entity
		UUID newId;
		Entity entity;
		auto it = idMap.find(id);
		if (it == idMap.end())
		{
			// create new ID
			newId = UUID::create();
			idMap.add(id, newId);
			if (name.is_empty())
			{
				entity = create_entity(newId);
			}
			else
			{
				entity = create_entity(name, newId);
			}
		}
		else
		{
			// existing ID
			newId = it->get_second();
			entity = get_entity(newId);
		}
		entities.add(entity);

		// if another prefab, run this recursively
		if (prefabId.is_valid())
		{
			// get the prefab asset
			AssetManager& assetManager = AssetManager::get_singleton();
			Ref<Prefab> const& prefab = assetManager.get<Prefab>(prefabId);
			MINTY_ASSERT(prefab != nullptr, F("Failed to find prefab with ID {}.", prefabId));

			// deserialize the prefab
			Node const& node = prefab->get_node();
			TextNodeReader prefabReader(node);
			if (!deserialize_prefab(prefabReader, idMap))
			{
				MINTY_ERROR(F("Failed to deserialize nested prefab {}.", prefabId));
				return false;
			}
		}
	}

	// deserialize the components on each entity
	for (Size i = 0; i < reader.get_size(); i++)
	{
		// get the entity
		Entity entity = entities.at(i);

		// deserialize the components
		EntitySerializationData data{};
		data.entityManager = this;
		data.entity = entity;
		data.idMap = &idMap;
		if (!deserialize_components(reader, i, data))
		{
			MINTY_ERROR(F("Failed to deserialize components for entity {}.", get_entity_string(entity)));
			return false;
		}
	}

	return true;
}

Bool Minty::EntityManager::deserialize_prefab_entity(Reader& reader, Ref<Prefab> const& prefab)
{
	// get all of the entities and map their IDs
	Map<UUID, UUID> idMap(reader.get_size() * 2);
	Vector<Entity> entities(reader.get_size());
	for (Size i = 0; i < reader.get_size(); i++)
	{
		String name; // the name of the entity
		UUID id; // the ID within the scene
		UUID pId; // the ID within the prefab
		deserialize_entity(reader, i, name, id, pId);

		MINTY_ASSERT(pId.is_valid(), "No prefab ID found for entity within prefab.");

		// set up the ID mapping
		UUID newId = id.is_valid() ? id : UUID::create();
		idMap.add(pId, newId);

		// create an entity with the new ID
		if (name.is_empty())
		{
			entities.add(create_entity(newId));
		}
		else
		{
			entities.add(create_entity(name, newId));
		}
	}

	// deserialize the prefab
	Node const& node = prefab->get_node();
	TextNodeReader prefabReader(node);
	if (!deserialize_prefab(prefabReader, idMap))
	{
		MINTY_ERROR(F("Failed to deserialize prefab {}.", prefab->get_id()));
		return false;
	}

	// deserialize the override values for the entity components
	for (Size i = 0; i < reader.get_size(); i++)
	{
		// get the entity
		Entity entity = entities.at(i);

		// deserialize the components
		EntitySerializationData data{};
		data.entityManager = this;
		data.entity = entity;
		data.idMap = &idMap;
		if (!deserialize_components(reader, i, data))
		{
			MINTY_ERROR(F("Failed to deserialize components for entity {}.", get_entity_string(entity)));
			return false;
		}
	}

	return true;
}

void Minty::EntityManager::serialize(Writer& writer) const
{

}

Bool Minty::EntityManager::deserialize(Reader& reader)
{
	// NOTE: The entities must be all loaded before the components, as some components will have Entity dependencies.

	// read the entities
	Vector<Entity> entities;
	entities.resize(reader.get_size(), INVALID_ENTITY);
	for (Size i = 0; i < reader.get_size(); i++)
	{
		entities[i] = deserialize_entity(reader, i);
	}

	// read the components
	for (Size i = 0; i < reader.get_size(); i++)
	{
		Entity entity = entities.at(i);

		// if a prefab, delete the entity and serialize the prefab
		PrefabComponent const* prefabComponent = m_registry.try_get<PrefabComponent>(entity);
		if (prefabComponent)
		{
			// deserialize the prefab entity
			reader.indent(i);
			AssetManager& assetManager = AssetManager::get_singleton();
			Ref<Prefab> const& prefab = assetManager.get<Prefab>(prefabComponent->id);
			MINTY_ASSERT(prefab != nullptr, F("Failed to find prefab with ID {}.", prefabComponent->id));
			if (!deserialize_prefab_entity(reader, prefab))
			{
				MINTY_ERROR(F("Failed to deserialize prefab entity {}.", get_entity_string(entity)));
				reader.outdent();
				return false;
			}
			reader.outdent();

			// destroy the temporary entity
			destroy(entity);
		}
		else
		{
			// deserialize the components
			EntitySerializationData data{};
			data.entityManager = this;
			data.entity = entity;
			data.idMap = nullptr;
			if (!deserialize_components(reader, i, data))
			{
				MINTY_ERROR(F("Failed to deserialize components for entity {}.", get_entity_string(entities[i])));
				return false;
			}
		}
	}

	return true;
}

Owner<EntityManager> Minty::EntityManager::create(Scene* scene, EntityManagerBuilder const& builder)
{
	return Owner<EntityManager>(scene, builder);
}

EntityManager& Minty::EntityManager::get_singleton()
{
	// get the active scene
	Ref<Scene> const& activeScene = Context::get_singleton().get_scene_manager().get_active();
	MINTY_ASSERT(activeScene != nullptr, "No active scene. Cannot get EntityManager.");
	return activeScene->get_entity_manager();
}

void Minty::EntityManager::deserialize_entity(Reader& reader, Size const index, String& name, UUID& id, UUID& prefabId)
{
	// get name
	if (!reader.read_name(index, name))
	{
		name = "";
	}

	// get ID string
	String idString;
	if (!reader.read(index, idString) || idString.is_empty())
	{
		id = INVALID_ID;
		prefabId = INVALID_ID;
	}
	else
	{
		// trim the string down
		idString = idString.trim();

		// check if there is a prefab id
		Size prefabIndex = idString.find_first('[');
		Size prefabIndexEnd = idString.find_first(']', prefabIndex);
		if (prefabIndex != INVALID_INDEX || prefabIndexEnd != INVALID_INDEX)
		{
			MINTY_ASSERT(prefabIndex != INVALID_INDEX && prefabIndexEnd != INVALID_INDEX && prefabIndexEnd - prefabIndex - 1 == UUID_HEX_CHAR_COUNT, F("Malformed prefab ID in entity ID string. Expecting [ and ] to be {} characters apart, with a UUID in between them.", UUID_HEX_CHAR_COUNT));

			// there is a prefab
			String prefabIdString = idString.sub(prefabIndex + 1, UUID_HEX_CHAR_COUNT);
			prefabId = parse_to_uuid(prefabIdString);

			// remove prefab from id string
			idString = idString.sub(0, prefabIndex).trim();
		}
		else
		{
			prefabId = INVALID_ID;
		}

		// get the ID
		id = parse_to_uuid(idString);
	}
}
