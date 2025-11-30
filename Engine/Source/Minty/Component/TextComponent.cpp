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

void Minty::TextComponent::serialize(Writer& writer) const
{
	writer.write("Text", text);
	writer.write("Color", color);
	writer.write("Font", font);
	writer.write("Size", fontVariant == nullptr ?  0 : fontVariant->get_size());
	writer.write("Flags", fontVariant == nullptr ? FontFlags::None : fontVariant->get_flags());
}

Bool Minty::TextComponent::deserialize(Reader& reader)
{
	// get data
	EntitySerializationData* data = static_cast<EntitySerializationData*>(reader.get_user_data());
	MINTY_ASSERT(data != nullptr, ErrorCode::InvalidUserData);
	MINTY_ASSERT(data->entityManager != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(data->entityManager->contains(data->entity), ErrorCode::Entity_NotValid, data->entity);

	// mark as dirty
	EntityManager& entityManager = *data->entityManager;
	entityManager.mark<DirtyTextComponent>(data->entity);

	// read text info
	reader.read_default(text);
	reader.read<String>("Text", text, "");
	reader.read("Color", color, Color::white());
	reader.read<Ref<Font>>("Font", font, nullptr);

	// read variant info
	UInt fontSize;
	reader.read<UInt>("Size", fontSize, 0);
	FontFlags fontFlags;
	reader.read<FontFlags>("Flags", fontFlags, FontFlags::None);

	// get variant if able
	if (font != nullptr)
	{
		// if font is set, try to get the variant
		fontVariant = font->get(fontSize, fontFlags);
		if (fontVariant == nullptr)
		{
			MINTY_ABORT(ErrorCode::Asset_MissingDependency, font->get_name(), fontSize, to_string(fontFlags));
			return false; // no variant found
		}
	}
	else
	{
		fontVariant = nullptr; // no font set
	}

	return true;
}
