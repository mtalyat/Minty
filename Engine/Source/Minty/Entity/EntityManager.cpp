#include "pch.h"
#include "EntityManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Component/CanvasComponent.h"
#include "Minty/Component/DirtyComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Component/LayerComponent.h"
#include "Minty/Component/MeshComponent.h"
#include "Minty/Component/NameComponent.h"
#include "Minty/Component/RelationshipComponent.h"
#include "Minty/Component/TextComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Component/UITransformComponent.h"
#include "Minty/Component/UUIDComponent.h"
#include "Minty/Component/VisibleComponent.h"
#include "Minty/Data/Stack.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Entity/EntityPath.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Entity/Prefab.h"
#include "Minty/Render/MeshInfo.h"
#include "Minty/Render/Texture.h"
#include "Minty/Window/Window.h"
#include "Minty/Data/ListContainer.h"
#include "Minty/Render/Mesh.h"
#include "Minty/Render/FontVariant.h"
#include "Minty/Component/DirtyTextComponent.h"
#include "Minty/Component/DestroyComponent.h"
#include "Minty/Component/PrefabComponent.h"
#include "Minty/Scene/SceneManager.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Render/Font.h"
#include "Minty/Entity/EntityManagerInfo.h"

using namespace Minty;

Lookup<TypeID, ComponentData> EntityManager::s_registeredComponents;

Minty::EntityManager::EntityManager(Ref<Scene> const &scene, EntityManagerInfo const &info)
	: SubManager(scene), m_registry(), m_ids(), m_needsSorted(false)
{
}

Minty::EntityManager::EntityManager(EntityManager &&other) noexcept
	: SubManager(std::move(other)), m_registry(std::move(other.m_registry)), m_ids(std::move(other.m_ids)), m_needsSorted(std::move(other.m_needsSorted))
{
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
		m_registry.get<RelationshipComponent>(relationshipComp.prev).next = relationshipComp.next;
	}

	// update next sibling's prev
	if (relationshipComp.next != INVALID_ENTITY)
	{
		m_registry.get<RelationshipComponent>(relationshipComp.next).prev = relationshipComp.prev;
	}

	// iterate from next to end and update indices
	Entity sibling = relationshipComp.next;
	while (sibling != INVALID_ENTITY)
	{
		RelationshipComponent &siblingRelationshipComponent = m_registry.get<RelationshipComponent>(sibling);
		siblingRelationshipComponent.index--;
		sibling = siblingRelationshipComponent.next;
	}

	// update child count
	parentRelationshipComp.children--;
	// Children count is not zero, yet there is no first and last children.
	MINTY_ASSERT_F(
		parentRelationshipComp.children == 0 ||
			(parentRelationshipComp.first != INVALID_ENTITY &&
			 parentRelationshipComp.last != INVALID_ENTITY),
		ErrorCode::Entity_InvalidRelationship);

	// clear this entity's relationship
	relationshipComp.prev = INVALID_ENTITY;
	relationshipComp.next = INVALID_ENTITY;
	relationshipComp.depth = 0;
}

void Minty::EntityManager::add_to_parent(Entity const entity, RelationshipComponent &relationshipComp, RelationshipComponent &parentRelationshipComp)
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
			m_registry.get<RelationshipComponent>(relationshipComp.prev).next = entity;
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
		return UUID();
	}

	UUIDComponent const *uuidComponent = m_registry.try_get<UUIDComponent>(entity);
	if (uuidComponent)
	{
		return uuidComponent->id;
	}
	// no related ID
	return UUID();
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

Entity Minty::EntityManager::get_entity(Entity const source, EntityPath const &path) const
{
	// if no path, it is the source entity
	if (path.is_empty())
	{
		return source;
	}

	// follow the children indices down until found
	Entity entity = source;
	RelationshipComponent const *relationshipComponent;
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
	String const &name = get_name(entity);
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

	// set children as well
	RelationshipComponent const *const relationshipComp = m_registry.try_get<RelationshipComponent>(entity);
	if (relationshipComp && relationshipComp->children > 0)
	{
		Entity child = relationshipComp->first;
		while (child != INVALID_ENTITY)
		{
			set_enabled(child, enabled);
			child = m_registry.get<RelationshipComponent>(child).next;
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

	// set children as well
	RelationshipComponent const *const relationshipComp = m_registry.try_get<RelationshipComponent>(entity);
	if (relationshipComp && relationshipComp->children > 0)
	{
		Entity child = relationshipComp->first;
		while (child != INVALID_ENTITY)
		{
			set_visible(child, visible);
			child = m_registry.get<RelationshipComponent>(child).next;
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
	}
	else
	{
		LayerComponent &layerComponent = m_registry.get_or_emplace<LayerComponent>(entity);
		layerComponent.layer = layer;
	}

	// set children as well
	RelationshipComponent const *const relationshipComp = m_registry.try_get<RelationshipComponent>(entity);
	if (relationshipComp && relationshipComp->children > 0)
	{
		Entity child = relationshipComp->first;
		while (child != INVALID_ENTITY)
		{
			set_layer(child, layer);
			child = m_registry.get<RelationshipComponent>(child).next;
		}
	}
}

Layer Minty::EntityManager::get_layer(Entity const entity) const
{
	LayerComponent const *layerComponent = m_registry.try_get<LayerComponent>(entity);
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
		MINTY_ASSERT(current != entity, ErrorCode::Entity_CyclicRelationship);
		// get the relationship component
		RelationshipComponent const *temp = m_registry.try_get<RelationshipComponent>(current);
		if (!temp)
		{
			break;
		}
		current = temp->parent;
	}
#endif // MINTY_DEBUG

	RelationshipComponent &relationshipComponent = m_registry.get_or_emplace<RelationshipComponent>(entity);

	if (relationshipComponent.parent != INVALID_ENTITY)
	{
		// remove from parent
		RelationshipComponent &parentRelationshipComponent = m_registry.get<RelationshipComponent>(relationshipComponent.parent);
		remove_from_parent(relationshipComponent, parentRelationshipComponent);
	}

	// set parent
	relationshipComponent.parent = parent;

	// if parent is valid, add to parent's children
	if (parent != INVALID_ENTITY)
	{
		// add to parent
		if (!m_registry.all_of<RelationshipComponent>(parent))
		{
			// if parent does not have a relationship component, create one
			set_parent(parent, INVALID_ENTITY);
		}
		RelationshipComponent &parentRelationshipComponent = m_registry.get<RelationshipComponent>(parent);
		add_to_parent(entity, relationshipComponent, parentRelationshipComponent);
	}

	// manager needs to resort the relationships
	m_needsSorted = true;

	// if children, update their depths
	if (relationshipComponent.children)
	{
		Stack<Tuple<UInt, Entity>> entitiesToUpdate;
		entitiesToUpdate.push({relationshipComponent.depth + 1, relationshipComponent.first});

		while (!entitiesToUpdate.is_empty())
		{
			Tuple<UInt, Entity> pair = entitiesToUpdate.pop();

			// get the relationship component
			RelationshipComponent &comp = m_registry.get<RelationshipComponent>(pair.get_second());

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

	// if the entity has a UITransform, update its Canvas value
	if (UITransformComponent *uiTransform = try_get_component<UITransformComponent>(entity))
	{
		uiTransform->canvas = INVALID_ENTITY;

		Entity parent = entity;

		while (parent != INVALID_ENTITY)
		{
			// if parent has canvas, set value
			if (CanvasComponent *canvas = try_get_component<CanvasComponent>(parent))
			{
				uiTransform->canvas = parent;
				break;
			}

			// move to next parent
			RelationshipComponent const *parentRelationship = try_get_component<RelationshipComponent const>(parent);
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
	RelationshipComponent const *relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);
	if (relationshipComponent)
	{
		return relationshipComponent->parent;
	}
	return INVALID_ENTITY;
}

Entity Minty::EntityManager::get_child(Entity const entity, Size const index) const
{
	RelationshipComponent const *relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);
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
	NameComponent const *nameComponent = m_registry.try_get<NameComponent>(entity);
	if (nameComponent)
	{
		return nameComponent->name;
	}
	return String();
}

void Minty::EntityManager::set_name(Entity const entity, String const &name)
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
	NameComponent &nameComponent = m_registry.get_or_emplace<NameComponent>(entity);
	nameComponent.name = name;
}

void Minty::EntityManager::finalize_dirties()
{
	MINTY_TRACE_SCOPE();

	// update dirty text components
	AssetManager &assetManager = AssetManager::get_singleton();
	for (auto &&[entity, uiTransformComp, textComp, meshComp, dirtyComp, enabledComp] : m_registry.view<UITransformComponent const, TextComponent const, MeshComponent, DirtyComponent const, EnabledComponent const>().each())
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

		// create a info
		MeshInfo info{};
		info.type = MeshType::Custom;

		// (re)generate the mesh
		ListContainer vertices(sizeof(Float) * 4, textComp.text.get_size());
		ListContainer indices(sizeof(UShort), (textComp.text.get_size() * 6) / 4); // 6 indices for every 4 vertices

		Float xAdvance = 0.0f;
		Float yAdvance = 0.0f;
		UShort index = 0;

		Ref<Font> const &font = textComp.font;
		Ref<FontVariant> const &fontVariant = textComp.fontVariant;
		Ref<Texture> const &fontVariantTexture = fontVariant->get_texture();
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
			FontChar const *fc = fontVariant->get_char(c);
			if (!fc)
			{
				MINTY_ERROR_F(ErrorCode::Asset_Font_CharNotFound, c, font->get_name());

				last = c;

				continue;
			}

			Float2 const min(fc->x, fc->y);
			Float2 const max(fc->x + fc->width, fc->y + fc->height);
			Float2 const offset(fc->xOffset, fc->yOffset);

			// adjust spacing for special cases
			xAdvance += fontVariant->get_kerning(last, c);

			// create vertices based on each Char
			Float4 value = {xAdvance + offset.x, yAdvance + offset.y, min.x, min.y};
			vertices.append_object(value); // bottom left
			value = {xAdvance + fc->width + offset.x, yAdvance + offset.y, max.x, min.y};
			vertices.append_object(value); // bottom right
			value = {xAdvance + fc->width + offset.x, yAdvance + fc->height + offset.y, max.x, max.y};
			vertices.append_object(value); // top left
			value = {xAdvance + offset.x, yAdvance + fc->height + offset.y, min.x, max.y};
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

		// set the mesh data
		info.vertexData = vertices.get_data();
		info.vertexStride = vertices.get_stride();
		info.vertexCount = vertices.get_count();
		info.indexData = indices.get_data();
		info.indexStride = indices.get_stride();
		info.indexCount = indices.get_count();

		// create the new mesh
		// if no mesh, create a new mesh quickly
		if (meshComp.mesh == nullptr)
		{
			// create new mesh outright
			info.id = UUID::create();
			meshComp.mesh = assetManager.create<Mesh>(info).to_ref();
		}
		else
		{
			// replace existing mesh
			info.id = meshComp.mesh->get_id();
			*meshComp.mesh = Mesh(info);
		}

		// update the material
		meshComp.material = fontVariant->get_material();
	}
	clear<DirtyTextComponent>();

	// update dirty canvas transforms
	Shared<Window> const &window = Application::get_singleton().get_window();
	if (window)
	{
		// get window size as a rect
		UInt2 windowSize = window->get_size();
		Rect windowRect(0.0f, 0.0f, static_cast<Float>(windowSize.x), static_cast<Float>(windowSize.y));

		auto view = m_registry.view<UITransformComponent, CanvasComponent const, DirtyComponent const, EnabledComponent const>();
		view.use<UITransformComponent>();
		for (auto &&[entity, uiTransformComp, canvasComp, dirtyComp, enabledComp] : view.each())
		{
			// canvas controls the size and position
			uiTransformComp.transform.set_position(windowRect.x, windowRect.y);
			uiTransformComp.transform.set_size(windowRect.width, windowRect.height);
			uiTransformComp.transform.update(windowRect, 0.0f, 0.0f);
		}
	}

	// update entities with relationships
	{
		auto view = m_registry.view<RelationshipComponent, DirtyComponent const, EnabledComponent const>();
		view.use<RelationshipComponent>();
		for (auto &&[entity, relationshipComp, dirtyComp, enabledComp] : view.each())
		{
			if (TransformComponent *transformComp = m_registry.try_get<TransformComponent>(entity))
			{
				update_transform(entity, relationshipComp.parent, *transformComp);
			}
			else if (UITransformComponent *uiTransformComp = m_registry.try_get<UITransformComponent>(entity))
			{
				update_uiTransform(entity, relationshipComp.parent, *uiTransformComp);
			}
		}
	}

	// update entities without relationships
	for (auto &&[entity, transformComp, dirtyComp, enabledComp] : m_registry.view<TransformComponent, DirtyComponent const, EnabledComponent const>(entt::exclude<RelationshipComponent>).each())
	{
		// if no relationship, update the transform with no parent
		update_transform(entity, INVALID_ENTITY, transformComp);
	}
	for (auto &&[entity, uiTransformComp, dirtyComp, enabledComp] : m_registry.view<UITransformComponent, DirtyComponent const, EnabledComponent const>(entt::exclude<RelationshipComponent>).each())
	{
		// if no relationship, update the UITransform with no parent
		update_uiTransform(entity, INVALID_ENTITY, uiTransformComp);
	}

	// clear all dirties
	clear<DirtyComponent>();
}

Entity Minty::EntityManager::create_entity_smart(String const &name, UUID const id)
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

void Minty::EntityManager::strip_entity(Entity const entity)
{
	// remove from parent
	set_parent(entity, INVALID_ENTITY);

	// remove ID, if any
	if (UUIDComponent const *const uuidComponent = m_registry.try_get<UUIDComponent>(entity))
	{
		m_ids.remove(uuidComponent->id);
	}
}

void Minty::EntityManager::update_transform(Entity const entity, Entity const parent, TransformComponent &transformComp)
{
	// if parent, use parent's global matrix
	if (parent != INVALID_ENTITY)
	{
		// get the parent transform
		TransformComponent const *parentTransform = m_registry.try_get<TransformComponent>(parent);
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

void Minty::EntityManager::update_uiTransform(Entity const entity, Entity const parent, UITransformComponent &uiTransformComp)
{
	// use the parent, if there is one and it is not the canvas
	if (parent != INVALID_ENTITY && parent != uiTransformComp.canvas)
	{
		UITransformComponent const *parentUITransform = m_registry.try_get<UITransformComponent>(parent);
		if (parentUITransform)
		{
			uiTransformComp.transform.update(parentUITransform->transform);
			return;
		}
	}

	// if no parent, use canvas
	if (uiTransformComp.canvas != INVALID_ENTITY)
	{
		CanvasComponent const *canvas = m_registry.try_get<CanvasComponent>(uiTransformComp.canvas);
		if (canvas)
		{
			uiTransformComp.transform.update(canvas->canvas.get_rect(), 0.0f, 0.0f);
			return;
		}
	}

	// get window size as a rect
	Shared<Window> const& window = Application::get_singleton().get_window();
	UInt2 windowSize = window->get_size();
	Rect windowRect(0.0f, 0.0f, static_cast<Float>(windowSize.x), static_cast<Float>(windowSize.y));

	// if no parent and no canvas, default to Window rect
	uiTransformComp.transform.update(windowRect, 0.0f, 0.0f);
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
	RelationshipComponent const *relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);
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
		RelationshipComponent const &relationship = m_registry.get<RelationshipComponent>(currentEntity);

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
	RelationshipComponent const *relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);
	if (relationshipComponent && relationshipComponent->parent != INVALID_ENTITY && has_component<DirtyComponent>(relationshipComponent->parent))
	{
		// refresh the parent
		refresh(relationshipComponent->parent);
	}

	// if Transform, update global matrix
	TransformComponent *transformComponent = m_registry.try_get<TransformComponent>(entity);
	if (transformComponent)
	{
		update_transform(entity, get_parent(entity), *transformComponent);
	}

	// if UITransform, update the global rect
	UITransformComponent *uiTransformComponent = m_registry.try_get<UITransformComponent>(entity);
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
	MINTY_ASSERT_F(!contains(id), ErrorCode::Argument_KeyAlreadyExists, id);

	// create empty entity
	Entity entity = m_registry.create();

	// add the id component
	UUIDComponent &idComponent = m_registry.emplace<UUIDComponent>(entity);
	idComponent.id = id;

	// link ID to Entity
	m_ids.add(id, entity);

	// done
	return entity;
}

Entity Minty::EntityManager::create_entity(String const &name)
{
	// create empty entity
	Entity entity = m_registry.create();

	// add the name component
	if (!name.is_empty())
	{
		NameComponent &nameComponent = m_registry.emplace<NameComponent>(entity);
		nameComponent.name = name;
	}

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

Entity Minty::EntityManager::create_entity(String const &name, UUID const id)
{
	// create empty entity
	Entity entity = m_registry.create();

	// add the name component
	if (!name.is_empty())
	{
		NameComponent &nameComponent = m_registry.emplace<NameComponent>(entity);
		nameComponent.name = name;
	}

	// add the id component
	UUIDComponent &idComponent = m_registry.emplace<UUIDComponent>(entity);
	idComponent.id = id;

	// link ID to Entity
	m_ids.add(id, entity);

	// done
	return entity;
}

Entity Minty::EntityManager::create_entity(String const &name, UUID const id, Entity const parent)
{
	// create empty entity
	Entity entity = create_entity(name, id);

	// set the parent
	set_parent(entity, parent);

	// done
	return entity;
}

Entity Minty::EntityManager::spawn_entity(Ref<Prefab> const &prefab)
{
	MINTY_ASSERT(prefab != nullptr, ErrorCode::Argument_ExpectedNonNull);
	TextNodeReader reader(prefab->get_node());
	if (reader.get_size() == 0)
	{
		return INVALID_ENTITY;
	}

	// get the header of the first entity
	String name;
	UUID id;
	UUID prefabId;
	deserialize_entity_header(reader, 0, name, id, prefabId);

	// create the first entity
	Entity entity = create_entity(name);

	// deserialize the entities
	Map<UUID, Entity> idMap;
	deserialize_entities(reader, &idMap, entity);

	// refresh the entity so it is ready to be used
	refresh(entity);

	// done
	return entity;
}

Entity Minty::EntityManager::spawn_entity(Ref<Prefab> const &prefab, String const &name)
{
	Entity const entity = spawn_entity(prefab);
	set_name(entity, name);
	return entity;
}

Entity Minty::EntityManager::spawn_entity(Ref<Prefab> const &prefab, UUID const id)
{
	Entity const entity = spawn_entity(prefab);
	set_id(entity, id);
	return entity;
}

Entity Minty::EntityManager::spawn_entity(Ref<Prefab> const &prefab, Entity const parent)
{
	Entity const entity = spawn_entity(prefab);
	set_parent(entity, parent);
	return entity;
}

Entity Minty::EntityManager::spawn_entity(Ref<Prefab> const &prefab, String const &name, UUID const id)
{
	Entity const entity = spawn_entity(prefab);
	set_name(entity, name);
	set_id(entity, id);
	return entity;
}

Entity Minty::EntityManager::spawn_entity(Ref<Prefab> const &prefab, String const &name, UUID const id, Entity const parent)
{

	Entity const entity = spawn_entity(prefab);
	set_name(entity, name);
	set_id(entity, id);
	set_parent(entity, parent);
	return entity;
}

Component &Minty::EntityManager::add_component(Entity const entity, String const &name)
{
	ComponentData const &info = get_component_info(name);
	return info.create(*this, entity);
}

Component &Minty::EntityManager::get_component(Entity const entity, String const &name)
{
	ComponentData const &info = get_component_info(name);
	Component *component = info.get(*this, entity);
	MINTY_ASSERT_F(component, ErrorCode::Entity_MissingComponent, name);
	return *component;
}

Component const &Minty::EntityManager::get_component(Entity const entity, String const &name) const
{
	ComponentData const &info = get_component_info(name);
	Component const *component = info.get_const(*this, entity);
	MINTY_ASSERT_F(component, ErrorCode::Entity_MissingComponent, name);
	return *component;
}

Component &Minty::EntityManager::get_or_add_component(Entity const entity, String const &name)
{
	ComponentData const &info = get_component_info(name);
	Component *component = info.get(*this, entity);
	if (component == nullptr)
	{
		// create the component if it does not exist
		return info.create(*this, entity);
	}
	else
	{
		// return the existing component
		return *component;
	}
}

Component *Minty::EntityManager::try_get_component(Entity const entity, String const &name)
{
	ComponentData const &info = get_component_info(name);
	Component *component = info.get(*this, entity);
	return component;
}

Component const *Minty::EntityManager::try_get_component(Entity const entity, String const &name) const
{
	ComponentData const &info = get_component_info(name);
	Component const *component = info.get_const(*this, entity);
	return component;
}

Bool Minty::EntityManager::has_component(Entity const entity, String const &name) const
{
	ComponentData const &info = get_component_info(name);
	Component const *component = info.get_const(*this, entity);
	return component != nullptr;
}

void Minty::EntityManager::remove_component(Entity const entity, String const &name)
{
	ComponentData const &info = get_component_info(name);
	info.destroy(*this, entity);
}

void Minty::EntityManager::clear()
{
	m_registry.clear();
	m_ids.clear();
}

void Minty::EntityManager::sort()
{
	MINTY_TRACE_SCOPE();

	if (!m_needsSorted)
	{
		return;
	}

	m_registry.sort<RelationshipComponent>([&](RelationshipComponent const &leftRelationship, RelationshipComponent const &rightRelationship)
										   {
											   return leftRelationship.depth < rightRelationship.depth;

											   // if (left == right)
											   //{
											   //	return false;
											   // }

											   // RelationshipComponent const& leftRelationship = m_registry.get<RelationshipComponent>(left);
											   // RelationshipComponent const& rightRelationship = m_registry.get<RelationshipComponent>(right);

											   //// if the depths are different, compare by depth first
											   // if(leftRelationship.depth != rightRelationship.depth)
											   //{
											   //	return leftRelationship.depth < rightRelationship.depth;
											   // }

											   //// keep going up until they have the same parent
											   // RelationshipComponent const* leftR = &leftRelationship;
											   // RelationshipComponent const* rightR = &rightRelationship;
											   // while (leftR->parent != rightR->parent)
											   //{
											   //	leftR = &m_registry.get<RelationshipComponent>(leftR->parent);
											   //	rightR = &m_registry.get<RelationshipComponent>(rightR->parent);
											   // }

											   //// sort by index of ancestor
											   // return leftR->index < rightR->index;
										   });
}

void Minty::EntityManager::swap_siblings(Entity const left, Entity const right)
{
	MINTY_ASSERT(left != right, ErrorCode::Argument_InvalidValue);
	MINTY_ASSERT(contains(left), ErrorCode::Entity_NotValid);
	MINTY_ASSERT(contains(right), ErrorCode::Entity_NotValid);

	RelationshipComponent *leftRelationshipComponent = m_registry.try_get<RelationshipComponent>(left);
	RelationshipComponent *rightRelationshipComponent = m_registry.try_get<RelationshipComponent>(right);

	// if no relationship component, do nothing
	if (!leftRelationshipComponent || !rightRelationshipComponent)
	{
		return;
	}

	// verify they have the same parent
	MINTY_ASSERT(leftRelationshipComponent->parent == rightRelationshipComponent->parent, ErrorCode::Argument_InvalidValue);

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
	RelationshipComponent &parent = m_registry.get<RelationshipComponent>(leftRelationshipComponent->parent);
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
	MINTY_ASSERT(contains(entity), ErrorCode::Entity_NotValid);

	RelationshipComponent *relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);

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
	MINTY_ASSERT(contains(entity), ErrorCode::Entity_NotValid);

	RelationshipComponent *relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);

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
	MINTY_ASSERT(contains(entity), ErrorCode::Entity_NotValid);

	RelationshipComponent *relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);

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
	RelationshipComponent &parentRelationshipComponent = m_registry.get<RelationshipComponent>(parent);

	// get the first child
	Entity first = parentRelationshipComponent.first;
	RelationshipComponent &firstRelationshipComponent = m_registry.get<RelationshipComponent>(first);

	// bridge the gap in the current position
	if (relationshipComponent->next != INVALID_ENTITY)
	{
		RelationshipComponent &nextRelationshipComponent = m_registry.get<RelationshipComponent>(relationshipComponent->next);
		nextRelationshipComponent.prev = relationshipComponent->prev;
	}
	RelationshipComponent &prevRelationshipComponent = m_registry.get<RelationshipComponent>(relationshipComponent->prev);
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
		MINTY_ASSERT(index < parentRelationshipComponent.children, ErrorCode::Entity_CyclicRelationship);
		RelationshipComponent &tempRelationshipComponent = m_registry.get<RelationshipComponent>(temp);
		tempRelationshipComponent.index = index;
		temp = tempRelationshipComponent.next;
		index++;
	}
}

void Minty::EntityManager::move_to_last(Entity const entity)
{
	MINTY_ASSERT(contains(entity), ErrorCode::Entity_NotValid);

	RelationshipComponent *relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);

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
	RelationshipComponent &parentRelationshipComponent = m_registry.get<RelationshipComponent>(parent);

	// get the last child
	Entity last = parentRelationshipComponent.last;
	RelationshipComponent &lastRelationshipComponent = m_registry.get<RelationshipComponent>(last);

	// bridge the gap in the current position
	if (relationshipComponent->prev != INVALID_ENTITY)
	{
		RelationshipComponent &prevRelationshipComponent = m_registry.get<RelationshipComponent>(relationshipComponent->prev);
		prevRelationshipComponent.next = relationshipComponent->next;
	}
	Entity next = relationshipComponent->next;
	RelationshipComponent &nextRelationshipComponent = m_registry.get<RelationshipComponent>(next);
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
		RelationshipComponent &tempRelationshipComponent = m_registry.get<RelationshipComponent>(temp);
		tempRelationshipComponent.index = index;
		temp = tempRelationshipComponent.next;
		index++;
	}
}

void Minty::EntityManager::destroy(Entity const entity)
{
	MINTY_ASSERT(contains(entity), ErrorCode::Entity_NotValid);

	// mark the entity for destruction, if not already marked
	if (!m_registry.all_of<DestroyComponent>(entity))
	{
		m_registry.emplace<DestroyComponent>(entity);
	}

	// destroy all children as well
	RelationshipComponent const *relationshipComponent = m_registry.try_get<RelationshipComponent>(entity);
	if (relationshipComponent && relationshipComponent->children > 0)
	{
		Entity child = relationshipComponent->first;
		while (child != INVALID_ENTITY)
		{
			destroy(child);
			child = m_registry.get<RelationshipComponent>(child).next;
		}
	}
}

void Minty::EntityManager::on_scene_load()
{
	MINTY_TRACE_SCOPE();

	// dirty all components on load
	mark_all<DirtyComponent>();
}

void Minty::EntityManager::frame_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	// remove any entities that are marked for destruction
	cleanup();

	// sort the entities
	sort();

	// refresh the dirty components
	finalize_dirties();
}

void Minty::EntityManager::fixed_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	// update any transforms from the position, rotation, scale changes
}

void Minty::EntityManager::finalize()
{
	MINTY_TRACE_SCOPE();

	// sort the entities
	sort();

	// refresh the dirty components
	finalize_dirties();
}

void Minty::EntityManager::destroy_immediately(Entity const entity)
{
	MINTY_ASSERT(contains(entity), ErrorCode::Entity_NotValid);

	// strip entity
	strip_entity(entity);

	// destroy the entity
	m_registry.destroy(entity);
}

void Minty::EntityManager::cleanup()
{
	// destroy all entities that are marked for destruction
	auto view = m_registry.view<DestroyComponent>();

	// strip all entities before destroying them
	for (auto &&[entity, destroyComponent] : view.each())
	{
		strip_entity(entity);
	}

	// destroy the entities
	m_registry.destroy(view.begin(), view.end());
}

Bool Minty::EntityManager::deserialize_entities(Reader &reader, Map<UUID, Entity> *idMap, Entity const baseEntity)
{
	// NOTE: The entities must be all loaded before the components, as some components will have Entity dependencies.

	// get entities
	Vector<Entity> entities;
	entities.resize(reader.get_size(), INVALID_ENTITY);
	for (Size i = 0; i < reader.get_size(); i++)
	{
		// get header info
		String name;
		UUID id;
		UUID prefabId;
		deserialize_entity_header(reader, i, name, id, prefabId);

		// get or create the entity
		Entity entity;
		if (i == 0 && baseEntity != INVALID_ENTITY)
		{
			entity = baseEntity;
		}
		else
		{
			entity = create_entity(name);
		}

		// map the ID, or set it directly if no map
		if (idMap && id.is_valid())
		{
			idMap->add(id, entity);
		}
		else
		{
			set_id(entity, id);
		}

		// if there is a prefab ID, set it
		if (prefabId.is_valid())
		{
			// add the prefab ID component
			PrefabComponent &prefabIdComponent = m_registry.emplace<PrefabComponent>(entity);
			prefabIdComponent.id = prefabId;
		}

		entities[i] = entity;
	}

	// get components/prefabs
	AssetManager &assetManager = AssetManager::get_singleton();
	for (Size i = 0; i < entities.get_size(); i++)
	{
		Entity const entity = entities[i];

		reader.indent(i);

		// if a prefab, handle differently
		PrefabComponent const *const prefabComponent = m_registry.try_get<PrefabComponent>(entity);
		if (prefabComponent)
		{
			// get the prefab
			MINTY_ASSERT_F(assetManager.contains(prefabComponent->id), ErrorCode::Asset_NotLoaded, prefabComponent->id);
			Ref<Prefab> prefab = assetManager.get_ref<Prefab>(prefabComponent->id);

			// remove prefab component, as it is not needed anymore
			m_registry.remove<PrefabComponent>(entity);

			// deserialize the prefab
			Node const &prefabNode = prefab->get_node();
			TextNodeReader prefabReader(prefabNode);
			Map<UUID, Entity> prefabIdMap;
			if (!deserialize_entities(prefabReader, &prefabIdMap, entity))
			{
				MINTY_ABORT(ErrorCode::OperationFailed);
			}

			// read the override values
			for (Size j = 0; j < reader.get_size(); j++)
			{
				// get header info
				String name;
				UUID id;
				UUID prefabId;
				deserialize_entity_header(reader, j, name, id, prefabId);

				// get the entity to override
				MINTY_ASSERT_F(prefabIdMap.contains(prefabId), ErrorCode::Asset_Prefab_OverrideNotFound, prefabId, prefab->get_id());
				Entity const overrideEntity = prefabIdMap.at(prefabId);

				// override the name, if specified
				if (!name.is_empty())
				{
					set_name(overrideEntity, name);
				}

				// override the ID, if specified
				if (id.is_valid())
				{
					set_id(overrideEntity, id);
				}

				// deserialize the components
				reader.indent(j);

				if (!deserialize_components(reader, overrideEntity, idMap))
				{
					MINTY_ABORT(ErrorCode::OperationFailed);
				}

				reader.outdent();
			}
		}
		else
		{
			if (!deserialize_components(reader, entity, idMap))
			{
				MINTY_ABORT(ErrorCode::OperationFailed);
			}
		}

		reader.outdent();
	}

	return true;
}

Bool Minty::EntityManager::deserialize_components(Reader &reader, Entity const entity, Map<UUID, Entity> *idMap)
{
	EntitySerializationData data{};
	data.entityManager = this;
	data.entity = entity;
	data.idMap = idMap;
	reader.push_user_data(&data);

	// read each component on the Entity
	String componentName;
	for (Size i = 0; i < reader.get_size(); i++)
	{
		Bool const nameResult = reader.read_name(i, componentName);
		MINTY_ASSERT(nameResult && !componentName.is_empty(), ErrorCode::Serialization_ReadName);

		// fix name
		componentName = componentName.trim_end();

		ComponentData const &info = get_component_info(componentName);

		// get the component
		Component *component = info.get(*this, data.entity);

		// create the component if it does not exist yet
		if (!component)
		{
			component = &info.create(*this, data.entity);
		}

		// deserialize the component
		if (reader.indent(i))
		{
			if (!component->deserialize(reader))
			{
				MINTY_ABORT(ErrorCode::OperationFailed);
			}

			reader.outdent();
		}
	}

	reader.pop_user_data();

	return true;
}

void Minty::EntityManager::serialize(Writer &writer) const
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::EntityManager::deserialize(Reader &reader)
{
	return deserialize_entities(reader);
}

Shared<EntityManager> Minty::EntityManager::create(Ref<Scene> const &scene, EntityManagerInfo const &info)
{
	return Shared<EntityManager>::create(scene, info);
}

Shared<EntityManager> Minty::EntityManager::create(Ref<Scene> const &scene)
{
	EntityManagerInfo info{};
	return create(scene, info);
}

EntityManager &Minty::EntityManager::get_singleton()
{
	// get the active scene
	Ref<Scene> const &activeScene = SceneManager::get_singleton().get_active();
	MINTY_ASSERT(activeScene != nullptr, ErrorCode::Scene_NoActiveScene);
	return activeScene->get_entity_manager();
}

void Minty::EntityManager::deserialize_entity_header(Reader &reader, Size const index, String &name, UUID &id, UUID &prefabId)
{
	// get name
	if (!reader.read_name(index, name))
	{
		name = "";
	}

	// get ID string
	String idString;
	reader.read(index, idString);

	// if name starts with "- " and idString is empty, it is a prefab ID
	if (name.starts_with("- ") && idString.is_empty())
	{
		// this is a prefab ID
		idString = name.sub(2); // remove the "- " prefix
		name = "";
	}

	if (!idString.is_empty())
	{
		// trim the string down
		idString = idString.trim();

		// check if there is a prefab id
		Size prefabIndex = idString.find_first('[');
		Size prefabIndexEnd = idString.find_first(']', prefabIndex);
		if (prefabIndex != INVALID_INDEX || prefabIndexEnd != INVALID_INDEX)
		{
			// Malformed prefab ID in entity ID string. Expecting [ and ] to be UUID_HEX_CHAR_COUNT characters apart, with a UUID in between them.
			MINTY_ASSERT_F(prefabIndex != INVALID_INDEX && prefabIndexEnd != INVALID_INDEX, ErrorCode::Serialization_InvalidFormat, idString);
			StringView prefabIdView = idString.peek(prefabIndex + 1, prefabIndexEnd - prefabIndex - 1);

			// there is a prefab
			Bool const prefabParseResult = prefabId.parse(prefabIdView);
			MINTY_ASSERT_F(prefabParseResult, ErrorCode::Serialization_InvalidFormat, prefabIdView);

			// remove prefab from id string
			idString = idString.sub(0, prefabIndex) + idString.sub(prefabIndexEnd + 1);
			idString = idString.trim();
		}
		else
		{
			prefabId = UUID();
		}

		// get the ID, if any
		if (!idString.is_empty())
		{
			Bool const idParseResult = id.parse(idString);
			MINTY_ASSERT_F(idParseResult, ErrorCode::Serialization_InvalidFormat, idString);
		}
		else
		{
			id.clear();
		}
	}
	else
	{
		id.clear();
		prefabId.clear();
	}
}
