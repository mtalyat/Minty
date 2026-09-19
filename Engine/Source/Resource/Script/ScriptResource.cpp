#include "pch.hpp"
#include "ScriptResource.hpp"

using namespace Minty;

Bool Minty::Serializer<ScriptResource>::serialize(Writer &writer, ScriptResource const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<ScriptResource>::deserialize(Reader &reader, ScriptResource &value)
{
    // Get the data to deserialize
    Path path = value.path;
    ScriptType type = value.type;

    // Deserialize the data
    if(reader.read("Path", path))
    {
        // Determine type from path
        String extension = path.get_extension().get_string();
        type = ScriptType::from_extension(extension);
    } else
    {
        MINTY_ERROR(ErrorCodeEnum::Serialization_MissingKey);
        return false;
    }

    // Update the resource with the deserialized data
    value.path = path;
    value.type = type;

    return true;
}
