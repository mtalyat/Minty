#include "pch.h"
#include "Reader.h"
#include "Minty/Data/StringBuilder.h"
#include "Minty/Stream/Stream.h"
#include "Minty/Serialization/Parser.h"

using namespace Minty;

Minty::Reader::Reader(Shared<Stream> const& stream)
    : m_stream(stream)
    , m_userStack()
{
}

Bool Minty::Reader::read_from_stream(Any data, Size const size)
{
    return m_stream->read(data, size);
}

Bool Minty::Reader::peek(Char &ch)
{
    Char const peeked = m_stream->peek();
    if (peeked == '\0')
    {
        return false;
    }
    ch = peeked;
    return true;
}

Bool Minty::Reader::read_typed_value(Type const type, Any data)
{
    switch(type)
    {
    case Type::Bool:
        return read_bool(*reinterpret_cast<Bool*>(data));
    case Type::Char:
        return read_char(*reinterpret_cast<Char*>(data));
    case Type::Byte:
        return read_byte(*reinterpret_cast<Byte*>(data));
    case Type::Int:
        return read_int32(*reinterpret_cast<Int32*>(data));
    case Type::UInt:
        return read_uint32(*reinterpret_cast<UInt32*>(data));
    case Type::Float:
        return read_float32(*reinterpret_cast<Float32*>(data));
    case Type::WInt:
        return read_int64(*reinterpret_cast<Int64*>(data));
    case Type::WUInt:
        return read_uint64(*reinterpret_cast<UInt64*>(data));
    case Type::WFloat:
        return read_float64(*reinterpret_cast<Float64*>(data));
    default:
        MINTY_NOT_IMPLEMENTED();
        return false;
    }
}
