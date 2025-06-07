#include "pch.h"
#include "EntityManager.h"
#include "Minty/Component/_Component.h"
#include "Minty/Context/Context.h"
#include "Minty/Entity/EntitySerializationData.h"

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

	// update dirty transforms with relationships
	for (auto&& [entity, dirty, transform, relationship] : m_registry.view<DirtyComponent const, TransformComponent, RelationshipComponent const>().each())
	{
		// if parent, use parent's global matrix
		if (relationship.parent != INVALID_ENTITY)
		{
			// get the parent transform
			TransformComponent const* parentTransform = m_registry.try_get<TransformComponent>(relationship.parent);
			if (parentTransform)
			{
				Matrix4 matrix = parentTransform->transform.get_global_matrix() * transform.transform.get_local_matrix();
				transform.transform.set_global_matrix(matrix);

				continue;
			}
		}

		// if no parent, or if no parent transform, use local matrix
		transform.transform.set_global_matrix(transform.transform.get_local_matrix());
	}

	// update dirty transforms with no relationships
	for (auto&& [entity, dirty, transform] : m_registry.view<DirtyComponent const, TransformComponent>(entt::exclude<RelationshipComponent>).each())
	{
		// no parent
		transform.transform.set_global_matrix(transform.transform.get_local_matrix());
	}

	// get window size as a rect
	Ref<Window> window = Context::get_singleton().get_window();
	UInt2 windowSize = window->get_size();
	Rect windowRect(0.0f, 0.0f, static_cast<Float>(windowSize.x), static_cast<Float>(windowSize.y));

	// update dirty canvas transforms
	for (auto&& [entity, dirtyComp, uiTransformComp, canvasComp] : m_registry.view<DirtyComponent const, UITransformComponent, CanvasComponent const>().each())
	{
		// canvas controls the size and position
		uiTransformComp.transform.set_position(windowRect.x, windowRect.y);
		uiTransformComp.transform.set_size(windowRect.width, windowRect.height);
		uiTransformComp.transform.set_global_rect(canvasComp.canvas.get_rect());
	}

	// update dirty UI transforms with relationships
	for (auto&& [entity, dirtyComp, uiTransformComp, relationshipComp] : m_registry.view<DirtyComponent const, UITransformComponent, RelationshipComponent const>().each())
	{
		// if parent, use parent's global rect
		UITransformComponent const* parentUITransform = m_registry.try_get<UITransformComponent>(relationshipComp.parent);
		if (parentUITransform)
		{
			uiTransformComp.transform.update_global_rect(parentUITransform->transform.get_global_rect());
			continue;
		}

		// if no parent, use canvas
		CanvasComponent const* canvas = m_registry.try_get<CanvasComponent>(uiTransformComp.canvas);
		if (canvas)
		{
			uiTransformComp.transform.update_global_rect(canvas->canvas.get_rect());
			continue;
		}

		// if no parent and no canvas...
		uiTransformComp.transform.update_global_rect(windowRect);
	}

	// update dirty UI transforms with no relationships
	for (auto&& [entity, dirtyComp, uiTransformComp] : m_registry.view<DirtyComponent const, UITransformComponent>(entt::exclude_t<RelationshipComponent>{}).each())
	{
		// if canvas, use canvas
		CanvasComponent const* canvas = m_registry.try_get<CanvasComponent>(uiTransformComp.canvas);
		if (canvas)
		{
			uiTransformComp.transform.update_global_rect(canvas->canvas.get_rect());
			continue;
		}

		// if no parent and no canvas...
		uiTransformComp.transform.update_global_rect(windowRect);
	}

	// clear all dirties
	clear<DirtyComponent>();
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

void Minty::EntityManager::destroy(Entity const entity)
{
	MINTY_ASSERT(contains(entity), "Entity does not exist.");
	m_registry.destroy(entity);
}

void Minty::EntityManager::initialize()
{
	// dirty all components on load
	mark_all_entities<DirtyComponent>();

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
	String name;
	UUID id;
	if (reader.read_name(index, name) && !name.is_empty())
	{
		if (reader.read(index, id) && id.is_valid())
		{
			return create_entity(name, id);
		}
		else
		{
			return create_entity(name);
		}
	}
	else
	{
		if (reader.read(index, id) && id.is_valid())
		{
			return create_entity(id);
		}
		else
		{
			return create_entity();
		}
	}
}

Bool Minty::EntityManager::deserialize_components(Reader& reader, Entity const entity, Size const index)
{
	MINTY_ASSERT(contains(entity), F("Failed to deserialize Entity at index {}.", index));

	if (!reader.indent(index))
	{
		MINTY_ERROR(F("Failed to indent for entity {}.", get_entity_string(entity)));
		return false;
	}

	Context const& context = Context::get_singleton();

	// create the serialization data
	EntitySerializationData data{};
	data.entity = entity;
	data.entityManager = this;
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

		info = context.get_component_info(componentName);
		MINTY_ASSERT(info != nullptr, F("Component \"{}\" does not exist.", componentName));

		// create the component
		Component& component = info->create(*this, entity);

		// deserialize the component
		if (reader.indent(i))
		{
			if (!component.deserialize(reader))
			{
				MINTY_ERROR(F("Failed to deserialize component \"{}\" for entity {}.", componentName, get_entity_string(entity)));
				continue;
			}

			reader.outdent();
		}
	}

	reader.pop_user_data();
	reader.outdent();

	return true;
}

void Minty::EntityManager::serialize(Writer& writer) const
{

}

Bool Minty::EntityManager::deserialize(Reader& reader)
{
	// NOTE: The entities must be all loaded before the components, as some components will have Entity dependencies.

	// unload old data
	dispose();

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
		if (!deserialize_components(reader, entities[i], i))
		{
			MINTY_ERROR(F("Failed to deserialize components for entity {}.", get_entity_string(entities[i])));
			return false;
		}
	}

	// load new data
	initialize();

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
