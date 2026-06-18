#include "pch.h"
#include "TextureResource.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"
#include "Core/Data/Path.h"
#include "Resource/Manager/ResourceManager.h"

using namespace Minty;

Bool Minty::Serializer<TextureResource>::serialize(Writer &writer, TextureResource const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<TextureResource>::deserialize(Reader &reader, TextureResource &value)
{
    // Data to load
    UUID imageId;
    UInt mipmapLevels = value.mipLevels;
    TextureFilter filter = value.filter;
    TextureAddressMode addressMode = value.addressMode;
    ImageAspectFlags aspect = value.aspect;
    Bool normalize = value.normalizeCoordinates;

    // Read the texture data
    if (!reader.read("Image", imageId))
    {
        return false;
    }
    reader.read("Mip", mipmapLevels);
    reader.read("Filter", filter);
    reader.read("AddressMode", addressMode);
    reader.read("Aspect", aspect);
    reader.read("Normalize", normalize);

    // Find the image
    ResourceManager &resourceManager = ResourceManager::get_instance();
    ImageResourceHandle const imageHandle = resourceManager.find_handle<ImageResource>(imageId);
    if (!imageHandle.is_valid())
    {
        MINTY_ERROR_A(ErrorCodeEnum::Resource_LoadFailed, Parser<UUID>::to_string(imageId).get_data());
        return false;
    }

    // Set the texture data
    value.imageHandle = imageHandle;
    value.mipLevels = mipmapLevels;
    value.filter = filter;
    value.addressMode = addressMode;
    value.aspect = aspect;
    value.normalizeCoordinates = normalize;
    return true;
}