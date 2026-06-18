#include "pch.h"
#include "TextComponent.h"
#include "Minty/Component/DirtyTextTag.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Render/Font.h"
#include "Minty/Render/FontVariant.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Bool Minty::Serializer<TextComponent>::serialize(Writer &writer, TextComponent const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<TextComponent>::deserialize(Reader &reader, TextComponent &value)
{
	// get data
	EntitySerializationData* data = static_cast<EntitySerializationData*>(reader.get_user_data());
	MINTY_ASSERT(data != nullptr, ErrorCodeEnum::InvalidUserData);
	MINTY_ASSERT(data->entityManager != nullptr, ErrorCodeEnum::Argument_ExpectedNonNull);
	MINTY_ASSERT_F(data->entityManager->contains(data->entity), ErrorCodeEnum::Entity_NotValid, data->entityManager->to_string(data->entity));

	// mark as dirty
	EntityManager& entityManager = *data->entityManager;
	entityManager.mark<DirtyTextTag>(data->entity);

	// read text info
	reader.read_primary<String>("Text", value.text);
	reader.read("Color", value.color);
	reader.read<Ref<Font>>("Font", value.font);

	// read variant info
	UInt fontSize;
	reader.read<UInt>("Size", fontSize);
	FontFlags fontFlags;
	reader.read<FontFlags>("Flags", fontFlags);

	// get variant if able
	if (value.font != nullptr)
	{
		// if font is set, try to get the variant
		value.fontVariant = value.font->get(fontSize, fontFlags).to_ref();
		if (value.fontVariant == nullptr)
		{
			MINTY_ABORT_F(ErrorCodeEnum::Asset_MissingDependency, value.font->get_name(), fontSize, fontFlags);
			return false; // no variant found
		}
	}
	else
	{
		value.fontVariant = nullptr; // no font set
	}

	return true;
}
