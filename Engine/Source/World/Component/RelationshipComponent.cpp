#include "pch.h"
#include "RelationshipComponent.h"
#include "Core/Debug/DebugF.h"
#include "World/Entity/EntityManager.h"
#include "World/Entity/EntitySerializationData.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Bool Minty::Serializer<RelationshipComponent>::serialize(Writer &writer, RelationshipComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<RelationshipComponent>::deserialize(Reader &reader, RelationshipComponent &value)
{
	// get the serialization data
	Pointer const userData = reader.get_user_data();
	MINTY_ASSERT(userData != nullptr, ErrorCodeEnum::InvalidUserData);
	EntitySerializationData* entityData = static_cast<EntitySerializationData*>(userData);

	EntityManager* const entityManager = entityData->entityManager;
	MINTY_ASSERT(entityManager != nullptr, ErrorCodeEnum::Argument_ExpectedNonNull);

	// read the parent id
	UUID parentId;
	if (reader.read_primary("Parent", parentId))
	{
		// get the parent entity
		EntityHandle const newParent = entityData->get_entity(parentId);
		MINTY_CHECK_B(newParent != INVALID_ENTITY, ErrorCodeEnum::Entity_NotValid, parentId);

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
