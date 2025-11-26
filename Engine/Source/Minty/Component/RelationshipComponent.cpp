#include "pch.h"
#include "RelationshipComponent.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::RelationshipComponent::serialize(Writer& writer) const
{
	// if no parent, print nothing
	if (parent == INVALID_ENTITY)
	{
		return;
	}

	// get the serialization data
	void const* userData = writer.get_user_data();
	EntitySerializationData const* entityData = static_cast<EntitySerializationData const*>(userData);

	// get the parent id
	UUID parentId = entityData->entityManager->get_id(parent);
	
	// write that id
	writer.write("Parent", parentId);
}

Bool Minty::RelationshipComponent::deserialize(Reader& reader)
{
	// get the serialization data
	void* const userData = reader.get_user_data();
	MINTY_ASSERT(userData != nullptr, ErrorCode::InvalidUserData);
	EntitySerializationData* entityData = static_cast<EntitySerializationData*>(userData);

	EntityManager* const entityManager = entityData->entityManager;
	MINTY_ASSERT(entityManager != nullptr, ErrorCode::Argument_ExpectedNonNull);

	// read the parent id
	UUID const parentId = INVALID_ID;
	if (reader.read_default(parentId) || reader.read("Parent", parentId))
	{
		// get the parent entity
		Entity const parent = entityData->get_entity(parentId);
		MINTY_ASSERT(parent != INVALID_ENTITY, ErrorCode::Entity_NotValid, parentId);

		// set the parent
		entityManager->set_parent(entityData->entity, parent);
	}
	else
	{
		// set parent as root
		entityManager->set_parent(entityData->entity, INVALID_ENTITY);
	}

	return true;
}
