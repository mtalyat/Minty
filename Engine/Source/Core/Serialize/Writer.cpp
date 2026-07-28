#include "pch.hpp"
#include "Writer.hpp"

using namespace Minty;

Minty::Writer::Writer(Shared<Stream> const &stream)
    : m_stream(stream), m_userStack(), m_indent(0), m_state(StateEnum::None)
{
}

Bool Minty::Writer::write_to_stream(PointerConst const data, Size const size)
{
    m_stream->write(data, size);
    return true;
}

Bool Minty::Writer::write_typed_value(TypeEnum const type, PointerConst const data)
{
    switch (type)
    {
    case TypeEnum::Bool:
        return write_bool(*reinterpret_cast<Bool const *>(data));
    case TypeEnum::Char:
        return write_char(*reinterpret_cast<Char const *>(data));
    case TypeEnum::Byte:
        return write_byte(*reinterpret_cast<Byte const *>(data));
    case TypeEnum::Int:
        return write_int32(*reinterpret_cast<Int32 const *>(data));
    case TypeEnum::UInt:
        return write_uint32(*reinterpret_cast<UInt32 const *>(data));
    case TypeEnum::Float:
        return write_float32(*reinterpret_cast<Float32 const *>(data));
    case TypeEnum::WInt:
        return write_int64(*reinterpret_cast<Int64 const *>(data));
    case TypeEnum::WUInt:
        return write_uint64(*reinterpret_cast<UInt64 const *>(data));
    case TypeEnum::WFloat:
        return write_float64(*reinterpret_cast<Float64 const *>(data));
    }
    
    MINTY_NOT_IMPLEMENTED();
    return false;
}
