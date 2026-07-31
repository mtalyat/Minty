#include "pch.hpp"
#include "SpriteAtlasResource.hpp"
#include "Core/Serialize/Reader.hpp"
#include "Core/Serialize/Writer.hpp"
#include "Resource/Manager/ResourceManager.hpp"

using namespace Minty;

Bool Minty::Serializer<SpriteAtlasResource>::serialize(Writer &writer, SpriteAtlasResource const &value)
{
    return Bool();
}

Bool Minty::Serializer<SpriteAtlasResource>::deserialize(Reader &reader, SpriteAtlasResource &value)
{
    ResourceManager &resourceManager = ResourceManager::get_instance();

    // Data to load
    TextureResourceHandle textureResourceHandle = value.textureResourceHandle;
    Float pixelsPerUnit = value.pixelsPerUnit;
    Vector<SpriteLayoutGroup> spriteGroups{};
    
    // Read the data
    if(!resourceManager.read<TextureResource>(reader, "Texture", textureResourceHandle))
    {
        MINTY_ERROR(ErrorCodeEnum::Serialization_MissingKey);
        return false;
    }

    reader.read("PPU", pixelsPerUnit);

    // Read default coordinate mode if any given
    CoordinateMode coordinateModeOverride = CoordinateModeEnum::Normalized;
    Bool const overrideCoordinateMode = reader.read("CoordinateMode", coordinateModeOverride);

    // Read the groups
    if(!reader.read("Groups", spriteGroups))
    {
        MINTY_ERROR(ErrorCodeEnum::Serialization_MissingKey);
        return false;
    }

    // Replace any undefined coordinate modes with the default
    if(overrideCoordinateMode)
    {
        for(SpriteLayoutGroup &group : spriteGroups)
        {
            if(group.layout.coordinateMode == CoordinateModeEnum::Undefined)
            {
                group.layout.coordinateMode = coordinateModeOverride;
            }
        }
    }

    // Set the loaded data to the resource
    value.textureResourceHandle = textureResourceHandle;
    value.pixelsPerUnit = pixelsPerUnit;
    value.spriteGroups = std::move(spriteGroups);

    return true;
}
