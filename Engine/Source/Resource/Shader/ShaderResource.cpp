#include "pch.h"
#include "ShaderResource.h"
#include "Core/Debug/Debug.h"
#include "Core/Data/Path.h"
#include "Resource/Manager/ResourceManager.h"

using namespace Minty;

Bool Minty::Serializer<ShaderResource>::serialize(Writer &writer, ShaderResource const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<ShaderResource>::deserialize(Reader &reader, ShaderResource &value)
{
    // Data to load
    Path pathToData;
    ShaderStage stage = value.stage;
    String entryPoint = value.entryPoint;

    // Read the data
    if (!reader.read("Path", pathToData))
    {
        MINTY_ERROR_A(ErrorCodeEnum::Resource_LoadFailed, pathToData.get_string().get_data());
        return false;
    }
    reader.read("Stage", stage);
    if(stage == ShaderStageEnum::Undefined)
    {
        MINTY_ERROR_A(ErrorCodeEnum::Resource_LoadFailed, pathToData.get_string().get_data());
        return false;
    }
    reader.read("Entry", entryPoint);
    if (entryPoint.is_empty())
    {
        entryPoint = DEFAULT_ENTRY_POINT;
    }

    // Read the shader data from the file
    ResourceManager &resourceManager = ResourceManager::get_instance();
    Vector<Byte> data = resourceManager.read_file(pathToData);
    if (data.is_empty())
    {
        MINTY_ERROR_A(ErrorCodeEnum::Resource_LoadFailed, pathToData.get_string().get_data());
        return false;
    }

    // Set the shader data
    value.data = std::move(data);
    value.stage = stage;
    value.entryPoint = entryPoint;
    return true;
}
