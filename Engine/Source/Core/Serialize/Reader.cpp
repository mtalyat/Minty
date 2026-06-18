#include "pch.h"
#include "Reader.h"
#include "Core/Data/StringBuilder.h"
#include "Core/Stream/Stream.h"
#include "Core/Serialize/Parser.h"
#include "Core/Meta/Type.h"
#include "Core/Data/UUID.h"
#include "Core/Debug/Debug.h"

using namespace Minty;

Minty::Reader::Reader(Unique<Stream> &&stream)
    : m_stream(std::move(stream)), m_userStack(), m_bookmarks(), m_indent(0), m_validation(true)
{
}

Bookmark Minty::Reader::save_bookmark()
{
    Stream& stream = get_stream();
    StreamPosition const position = stream.get_position();
    Bookmark const bookmark = static_cast<Bookmark>(m_bookmarks.get_size());
    m_bookmarks.add(bookmark, {position, m_indent});
    return bookmark;
}

void Minty::Reader::load_bookmark(Bookmark const bookmark)
{
    // consume any pending key/value
    consume_next_key_and_value();

    MINTY_ASSERT_A(m_bookmarks.contains(bookmark), ErrorCodeEnum::Serialization_InvalidBookmark, static_cast<WUInt>(bookmark));
    Tuple<StreamPosition, UInt> const &data = m_bookmarks[bookmark];
    Stream& stream = get_stream();
    stream.set_position(data.get_first());
    m_indent = data.get_second();
}

Bool Minty::Reader::read_from_stream(Pointer data, Size const size)
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

Bool Minty::Reader::read_typed_value(TypeEnum const type, Pointer data)
{
    switch (type)
    {
    case TypeEnum::Bool:
        return read_bool(reinterpret_cast<Bool *>(data));
    case TypeEnum::Char:
        return read_char(reinterpret_cast<Char *>(data));
    case TypeEnum::Byte:
        return read_byte(reinterpret_cast<Byte *>(data));
    case TypeEnum::Int:
        return read_int32(reinterpret_cast<Int32 *>(data));
    case TypeEnum::UInt:
        return read_uint32(reinterpret_cast<UInt32 *>(data));
    case TypeEnum::Float:
        return read_float32(reinterpret_cast<Float32 *>(data));
    case TypeEnum::WInt:
        return read_int64(reinterpret_cast<Int64 *>(data));
    case TypeEnum::WUInt:
        return read_uint64(reinterpret_cast<UInt64 *>(data));
    case TypeEnum::WFloat:
        return read_float64(reinterpret_cast<Float64 *>(data));
    case TypeEnum::String:
    case TypeEnum::MultilineString:
        return read_string(*reinterpret_cast<String *>(data));
    case TypeEnum::Object:
        return specialized_read<UUID>(*reinterpret_cast<UUID *>(data));
    default:
        MINTY_NOT_IMPLEMENTED();
        return false;
    }
}

Bool Minty::Reader::get_typed_default_value(TypeEnum const type, Pointer data)
{
    Size const typeSize = Type(type).get_size();
    if (typeSize > 0)
    {
        memset(data, 0, typeSize);
        return true;
    }
    return false;
}
