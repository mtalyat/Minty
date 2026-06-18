#include "pch.h"
#include "RenderPassResource.h"

using namespace Minty;

Bool Minty::Serializer<RenderPassResource>::serialize(Writer &writer, RenderPassResource const &value)
{
	MINTY_NOT_IMPLEMENTED();
	return Bool();
}

Bool Minty::Serializer<RenderPassResource>::deserialize(Reader &reader, RenderPassResource &value)
{
	// Data to load
	Vector<RenderAttachment> attachments;

	// Data to load
	if (reader.indent("Attachments"))
	{
		RenderAttachment attachment{};
		String key;
		while (reader.indent_next(key))
		{
			if (!Serializer<RenderAttachment>::deserialize(reader, attachment))
			{
				MINTY_ERROR(ErrorCodeEnum::Serialization_Failed);
				return false;
			}
			attachments.add(attachment);
			reader.outdent();
		}
	}

	// Move loaded data to value
	value.attachments = std::move(attachments);

	return true;
}
