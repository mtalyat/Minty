#include "pch.hpp"
#include "PrefabResource.hpp"

using namespace Minty;

Bool Minty::Serializer<PrefabResource>::serialize(Writer &writer, PrefabResource const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<PrefabResource>::deserialize(Reader &reader, PrefabResource &value)
{
    // Data to load
    Vector<Byte> data;

    // Read the prefab data
    Stream& stream = reader.get_stream();
    Size const size = stream.get_size() - stream.get_position();
    data.resize(size);
    if (!stream.read(data.get_data(), size))
    {
        return false;
    }

    // Set the prefab data
    value.data = std::move(data);
    return true;
}
