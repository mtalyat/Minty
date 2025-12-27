#include "pch.h"
#include "TextComponent.h"
#include "Minty/Component/DirtyTextComponent.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Entity/EntitySerializationData.h"
#include "Minty/Render/Font.h"
#include "Minty/Render/FontVariant.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::Serializer<TextComponent>::serialize(Writer &writer, TextComponent const &value)
{
	writer.write("Text", value.text);
	writer.write("Color", value.color);
	writer.write("Font", value.font);
	writer.write("Size", value.fontVariant == nullptr ?  0 : value.fontVariant->get_size());
	writer.write("Flags", value.fontVariant == nullptr ? FontFlags::None : value.fontVariant->get_flags());
}

void Minty::Serializer<TextComponent>::deserialize(Reader &reader, TextComponent &value)
{
	// get data
	EntitySerializationData* data = static_cast<EntitySerializationData*>(reader.get_user_data());
	MINTY_ASSERT(data != nullptr, ErrorCode::InvalidUserData);
	MINTY_ASSERT(data->entityManager != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT_F(data->entityManager->contains(data->entity), ErrorCode::Entity_NotValid, data->entity);

	// mark as dirty
	EntityManager& entityManager = *data->entityManager;
	entityManager.mark<DirtyTextComponent>(data->entity);

	// read text info
	reader.read_default(value.text);
	reader.read<String>("Text", value.text, "");
	reader.read("Color", value.color, Color::white());
	reader.read<Ref<Font>>("Font", value.font, nullptr);

	// read variant info
	UInt fontSize;
	reader.read<UInt>("Size", fontSize, 0);
	FontFlags fontFlags;
	reader.read<FontFlags>("Flags", fontFlags, FontFlags::None);

	// get variant if able
	if (value.font != nullptr)
	{
		// if font is set, try to get the variant
		value.fontVariant = value.font->get(fontSize, fontFlags).to_ref();
		if (value.fontVariant == nullptr)
		{
			MINTY_ABORT_F(ErrorCode::Asset_MissingDependency, value.font->get_name(), fontSize, to_string(fontFlags));
			return false; // no variant found
		}
	}
	else
	{
		value.fontVariant = nullptr; // no font set
	}
}
