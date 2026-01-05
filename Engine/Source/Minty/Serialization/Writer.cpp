#include "pch.h"
#include "Writer.h"

using namespace Minty;

Minty::Writer::Writer(Shared<Stream> const& stream)
    : m_stream(stream), m_userStack()
{
}

Bool Minty::Writer::write_to_stream(AnyConst const data, Size const size)
{
    return m_stream->write(data, size);
}

Bool Minty::Writer::write_typed_value(Type const type, AnyConst const data)
{
    switch(type)
    {
    case Type::Bool:
        return write_bool(*reinterpret_cast<Bool const*>(data));
    case Type::Char:
        return write_char(*reinterpret_cast<Char const*>(data));
    case Type::Byte:
        return write_byte(*reinterpret_cast<Byte const*>(data));
    case Type::Int:
        return write_int32(*reinterpret_cast<Int32 const*>(data));
    case Type::UInt:
        return write_uint32(*reinterpret_cast<UInt32 const*>(data));
    case Type::Float:
        return write_float32(*reinterpret_cast<Float32 const*>(data));
    case Type::WInt:
        return write_int64(*reinterpret_cast<Int64 const*>(data));
    case Type::WUInt:
        return write_uint64(*reinterpret_cast<UInt64 const*>(data));
    case Type::WFloat:
        return write_float64(*reinterpret_cast<Float64 const*>(data));
    default:
        MINTY_NOT_IMPLEMENTED();
        return false;
    }
}
