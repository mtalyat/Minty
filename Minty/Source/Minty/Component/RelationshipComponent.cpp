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
	void* userData = reader.get_user_data();
	MINTY_ASSERT(userData != nullptr, "Failed to get user data.");
	EntitySerializationData* entityData = static_cast<EntitySerializationData*>(userData);

	// read the parent id
	UUID parentId = INVALID_ID;
	if (reader.read_default(parentId) || reader.read("Parent", parentId))
	{
		// get the parent entity
		Entity parent = entityData->entityManager->get_entity(parentId);

		// set the parent
		EntityManager* entityManager = entityData->entityManager;
		MINTY_ASSERT(entityManager != nullptr, "Failed to get EntityManager.");
		entityManager->set_parent(entityData->entity, parent);

		// using set_parent because of all of the other stuff it does other than just set the parent value
	}

	return true;
}
