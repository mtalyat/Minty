#include "pch.h"
#include "ClipResource.h"
#include "ClipInfo.h"
#include "Core/Constant/Invalid.h"
#include "Core/Debug/Debug.h"
#include "Core/Data/Path.h"
#include "Core/Serialize/Reader.h"
#include "Core/Constant/Invalid.h"
#include "Resource/Manager/ResourceManager.h"

using namespace Minty;

Bool Minty::Serializer<ClipResource>::serialize(Writer &writer, ClipResource const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<ClipResource>::deserialize(Reader &reader, ClipResource &value)
{
    // Data to load
    Path pathToData;
    Float volume = value.volume;
    Float loopPoint = value.loopPoint;
    Bool looping = value.looping;
    Bool exclusive = value.exclusive;

    // Load data
    if (!reader.read("Path", pathToData))
    {
        MINTY_ERROR_A(ErrorCodeEnum::Resource_LoadFailed, "Path");
        return false;
    }
    reader.read("Volume", volume);
    reader.read("LoopPoint", loopPoint);
    reader.read("Looping", looping);
    reader.read("Exclusive", exclusive);

    // Read data from the file at the path
    ResourceManager &resourceManager = ResourceManager::get_instance();
    Vector<Byte> data = resourceManager.read_file(pathToData);

    // Set the values
    value.data = std::move(data);
    value.volume = volume;
    value.loopPoint = loopPoint;
    value.looping = looping;
    value.exclusive = exclusive;
    return true;
}
