#include "pch.h"
#include "AnimatorComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::AnimatorComponent::serialize(Writer& writer) const
{
	writer.write("Animator", animator->get_id());
}

Bool Minty::AnimatorComponent::deserialize(Reader& reader)
{
	UUID id;
	if (reader.read_default(id) || reader.read("Animator", id))
	{
		AssetManager& assetManager = AssetManager::get_singleton();

		// make a copy of the animator
		animator = assetManager.clone<Animator>(id);
		MINTY_ASSERT(animator != nullptr, F("Failed to load Animator with ID {}.", id));

		// get the animation
		id = animator->get_current_animation();
		if (id.is_valid())
		{
			animation = assetManager.get<Animation>(id);
		}
	}

	return true;
}
