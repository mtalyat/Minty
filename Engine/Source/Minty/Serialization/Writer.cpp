#include "pch.h"
#include "Writer.h"

using namespace Minty;

Minty::Writer::Writer(Shared<Stream> const &stream)
    : m_stream(stream), m_userStack(), m_indent(0), m_state(State::None)
{
}

void Minty::Writer::write_to_stream(AnyConst const data, Size const size)
{
    m_stream->write(data, size);
}

void Minty::Writer::write_typed_value(Type const type, AnyConst const data)
{
    switch (type)
    {
    case Type::Bool:
        write_bool(*reinterpret_cast<Bool const *>(data));
        return;
    case Type::Char:
        write_char(*reinterpret_cast<Char const *>(data));
        return;
    case Type::Byte:
        write_byte(*reinterpret_cast<Byte const *>(data));
        return;
    case Type::Int:
        write_int32(*reinterpret_cast<Int32 const *>(data));
        return;
    case Type::UInt:
        write_uint32(*reinterpret_cast<UInt32 const *>(data));
        return;
    case Type::Float:
        write_float32(*reinterpret_cast<Float32 const *>(data));
        return;
    case Type::WInt:
        write_int64(*reinterpret_cast<Int64 const *>(data));
        return;
    case Type::WUInt:
        write_uint64(*reinterpret_cast<UInt64 const *>(data));
        return;
    case Type::WFloat:
        write_float64(*reinterpret_cast<Float64 const *>(data));
        return;
    }
    
    MINTY_NOT_IMPLEMENTED();
}
