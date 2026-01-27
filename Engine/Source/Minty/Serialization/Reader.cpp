#include "pch.h"
#include "Reader.h"
#include "Minty/Data/StringBuilder.h"
#include "Minty/Stream/Stream.h"
#include "Minty/Serialization/Parser.h"

using namespace Minty;

Minty::Reader::Reader(Shared<Stream> const &stream)
    : m_stream(stream), m_userStack(), m_bookmarks(), m_indent(0)
{
}

Handle Minty::Reader::save_bookmark()
{
    StreamPosition const position = get_stream()->get_position();
    Handle const bookmark = static_cast<Handle>(m_bookmarks.get_size());
    m_bookmarks.add(bookmark, {position, m_indent});
    return bookmark;
}

void Minty::Reader::load_bookmark(Handle const bookmark)
{
    MINTY_ASSERT_F(m_bookmarks.contains(bookmark), ErrorCode::Serialization_InvalidBookmark, bookmark);
    Tuple<StreamPosition, UInt> const &data = m_bookmarks[bookmark];
    get_stream()->set_position(data.get_first());
    m_indent = data.get_second();

    consume_next_key();
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
    switch (type)
    {
    case Type::Bool:
        return read_bool(reinterpret_cast<Bool *>(data));
    case Type::Char:
        return read_char(reinterpret_cast<Char *>(data));
    case Type::Byte:
        return read_byte(reinterpret_cast<Byte *>(data));
    case Type::Int:
        return read_int32(reinterpret_cast<Int32 *>(data));
    case Type::UInt:
        return read_uint32(reinterpret_cast<UInt32 *>(data));
    case Type::Float:
        return read_float32(reinterpret_cast<Float32 *>(data));
    case Type::WInt:
        return read_int64(reinterpret_cast<Int64 *>(data));
    case Type::WUInt:
        return read_uint64(reinterpret_cast<UInt64 *>(data));
    case Type::WFloat:
        return read_float64(reinterpret_cast<Float64 *>(data));
    case Type::String:
    case Type::MultilineString:
        return read_string(*reinterpret_cast<String *>(data));
    case Type::Object:
        return specialized_read<UUID>(*reinterpret_cast<UUID *>(data));
    default:
        MINTY_NOT_IMPLEMENTED();
        return false;
    }
}
