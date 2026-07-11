#include "pch.h"
#include "RenderPassResource.h"
#include "Resource/Manager/ResourceManager.h"

namespace
{
	template<typename T>
	Minty::Bool read_optional_resource_handle(Minty::Reader &reader, Minty::StringView const key, Minty::Handle<T> &handle)
	{
		Minty::String value;
		if (!reader.read(key, value))
		{
			return true;
		}

		if (value == "Default")
		{
			handle = Minty::INVALID_HANDLE;
			return true;
		}

		Minty::UUID id;
		if (!Minty::Parser<Minty::UUID>::parse(value, id))
		{
			MINTY_ERROR(Minty::ErrorCodeEnum::Serialization_InvalidFormat);
			return false;
		}

		Minty::ResourceManager &resourceManager = Minty::ResourceManager::get_instance();
		handle = resourceManager.find_handle<T>(id);
		if (!handle.is_valid())
		{
			MINTY_ERROR_A(Minty::ErrorCodeEnum::Resource_LoadFailed, value.get_data());
			return false;
		}

		return true;
	}
}

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
	RenderTargetResourceHandle renderTarget = value.renderTarget;
	ViewportResourceHandle viewport = value.viewport;
	Color clearColor = value.clearColor;
	Float clearDepth = value.clearDepth;
	UInt clearStencil = value.clearStencil;

	if (!read_optional_resource_handle(reader, "RenderTarget", renderTarget))
	{
		return false;
	}
	if (!read_optional_resource_handle(reader, "Viewport", viewport))
	{
		return false;
	}
	reader.read("ClearColor", clearColor);
	reader.read("ClearDepth", clearDepth);
	reader.read("ClearStencil", clearStencil);

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
	value.renderTarget = renderTarget;
	value.viewport = viewport;
	value.clearColor = clearColor;
	value.clearDepth = clearDepth;
	value.clearStencil = clearStencil;

	return true;
}
