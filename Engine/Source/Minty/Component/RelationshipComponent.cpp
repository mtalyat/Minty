#include "pch.h"
#include "RelationshipComponent.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<RelationshipComponent>::serialize(Writer &writer, RelationshipComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<RelationshipComponent>::deserialize(Reader &reader, RelationshipComponent &value)
{
	// get the serialization data
	Any const userData = reader.get_user_data();
	MINTY_ASSERT(userData != nullptr, ErrorCode::InvalidUserData);
	EntitySerializationData* entityData = static_cast<EntitySerializationData*>(userData);

	EntityManager* const entityManager = entityData->entityManager;
	MINTY_ASSERT(entityManager != nullptr, ErrorCode::Argument_ExpectedNonNull);

	// read the parent id
	UUID parentId;
	if (reader.read_primary("Parent", parentId))
	{
		// get the parent entity
		Entity const newParent = entityData->get_entity(parentId);
		MINTY_CHECK_F(newParent != INVALID_ENTITY, ErrorCode::Entity_NotValid, parentId);

		// set the parent
		entityManager->set_parent(entityData->entity, newParent);
	}
	else
	{
		// set parent as root
		entityManager->set_parent(entityData->entity, INVALID_ENTITY);
	}
	return true;
}
