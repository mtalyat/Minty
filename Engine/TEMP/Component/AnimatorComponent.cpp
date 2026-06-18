#include "pch.h"
#include "AnimatorComponent.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"
#include "Minty/Animation/Animator.h"
#include "Minty/Animation/Animation.h"

using namespace Minty;

Bool Minty::Serializer<AnimatorComponent>::serialize(Writer &writer, AnimatorComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<AnimatorComponent>::deserialize(Reader &reader, AnimatorComponent &value)
{
	AssetManager& assetManager = AssetManager::get_singleton();

	UUID id;
	if (reader.read_primary("Animator", id))
	{
		// make a copy of the animator
		value.animator = assetManager.clone<Animator>(id);
		MINTY_ASSERT_F(value.animator != nullptr, ErrorCodeEnum::Asset_MissingDependency, id);
	}
	return true;
}