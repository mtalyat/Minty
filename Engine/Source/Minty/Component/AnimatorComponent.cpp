#include "pch.h"
#include "AnimatorComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Animation/Animator.h"
#include "Minty/Animation/Animation.h"

using namespace Minty;

void Minty::AnimatorComponent::serialize(Writer& writer) const
{
	writer.write("Animator", animator->get_id());
}

Bool Minty::AnimatorComponent::deserialize(Reader& reader)
{
	auto const& assetManager = AssetManager::get_instance();
	if(!assetManager)
	{
		MINTY_ERROR(ErrorCode::Application_AssetManagerNotInitialized);
		return false;
	}

	UUID id;
	if (reader.read_default(id) || reader.read("Animator", id))
	{
		// make a copy of the animator
		animator = assetManager->clone<Animator>(id);
		MINTY_ASSERT_F(animator != nullptr, ErrorCode::Asset_MissingDependency, id);

		// get the animation
		id = animator->get_current_animation();
		if (id.is_valid())
		{
			animation = assetManager->get_ref<Animation>(id);
		}
	}

	return true;
}
