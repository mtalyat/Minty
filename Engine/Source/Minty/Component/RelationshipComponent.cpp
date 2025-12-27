#include "pch.h"
#include "RelationshipComponent.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<RelationshipComponent>::serialize(Writer &writer, RelationshipComponent const &value)
{
	// if no parent, print nothing
	if (value.parent == INVALID_ENTITY)
	{
		return;
	}

	// get the serialization data
	AnyConst userData = writer.get_user_data();
	EntitySerializationData const* entityData = static_cast<EntitySerializationData const*>(userData);

	// get the parent id
	UUID parentId = entityData->entityManager->get_id(value.parent);
	
	// write that id
	writer.write("Parent", parentId);
}

void Minty::Serializer<RelationshipComponent>::deserialize(Reader &reader, RelationshipComponent &value)
{
	// get the serialization data
	Any const userData = reader.get_user_data();
	MINTY_ASSERT(userData != nullptr, ErrorCode::InvalidUserData);
	EntitySerializationData* entityData = static_cast<EntitySerializationData*>(userData);

	EntityManager* const entityManager = entityData->entityManager;
	MINTY_ASSERT(entityManager != nullptr, ErrorCode::Argument_ExpectedNonNull);

	// read the parent id
	UUID parentId;
	if (reader.read_default(parentId) || reader.read("Parent", parentId))
	{
		// get the parent entity
		Entity const parent = entityData->get_entity(parentId);
		MINTY_ASSERT_F(parent != INVALID_ENTITY, ErrorCode::Entity_NotValid, parentId);

		// set the parent
		entityManager->set_parent(entityData->entity, value.parent);
	}
	else
	{
		// set parent as root
		entityManager->set_parent(entityData->entity, INVALID_ENTITY);
	}
}
