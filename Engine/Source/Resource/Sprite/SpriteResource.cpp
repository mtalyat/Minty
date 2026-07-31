#include "pch.hpp"
#include "SpriteResource.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"
#include "Resource/Manager/ResourceManager.hpp"

using namespace Minty;

Bool Minty::Serializer<SpriteResource>::serialize(Writer &writer, SpriteResource const &value)
{
    return Bool();
}

Bool Minty::Serializer<SpriteResource>::deserialize(Reader &reader, SpriteResource &value)
{
    ResourceManager &resourceManager = ResourceManager::get_instance();

    // Data to load
    TextureResourceHandle textureResourceHandle = value.textureResourceHandle;
    Float pixelsPerUnit = value.pixelsPerUnit;
    SpriteLayout layout = value.layout;

    // Read the data
    if(!resourceManager.read(reader, "Texture", textureResourceHandle))
    {
        MINTY_ERROR(ErrorCodeEnum::Serialization_MissingKey);
        return false;
    }

    reader.read("PPU", pixelsPerUnit);
    if(!reader.read("Layout", layout))
    {
        MINTY_ERROR(ErrorCodeEnum::Serialization_MissingKey);
        return false;
    }

    value.textureResourceHandle = textureResourceHandle;
    value.pixelsPerUnit = pixelsPerUnit;
    value.layout = layout;

    return true;
}
