#include "pch.h"
#include "RenderTargetResource.h"
#include "Resource/Manager/ResourceManager.h"

using namespace Minty;

Bool Minty::Serializer<RenderTargetResource>::serialize(Writer &writer, RenderTargetResource const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<RenderTargetResource>::deserialize(Reader &reader, RenderTargetResource &value)
{
    ResourceManager &resourceManager = ResourceManager::get_instance();
    Vector<TextureResourceHandle> images;

    if (reader.indent("Images"))
    {
        String key;
        UUID id;
        while (reader.read_next(key, id))
        {
            TextureResourceHandle const handle = resourceManager.find_handle<TextureResource>(id);
            if (!handle.is_valid())
            {
                MINTY_ERROR_A(ErrorCodeEnum::Resource_LoadFailed, Parser<UUID>::to_string(id).get_data());
                return false;
            }

            images.add(handle);
        }

        reader.outdent();
    }

    value.images = std::move(images);
    return true;
}