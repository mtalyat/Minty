#include "Scope.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::Scope::Scope()
    : m_values()
{
}

UUID Minty::Scope::find(StringView const name) const
{
    auto found = m_values.find(name);
    if (found == m_values.end())
    {
        return UUID();
    }
    return found->get_second();
}

UUID Minty::Scope::add(String const& name, Int const value)
{
    UUID id = UUID::create();
    m_values.add(name, id, value);
    return id;
}

void Minty::Scope::set(UUID const id, Int const value)
{
    MINTY_ASSERT_F(m_values.contains(id), ErrorCode::Argument_KeyNotFound, id);
    m_values.at(id) = value;
}

void Minty::Scope::reset()
{
    for (auto &&[string, key, value] : m_values)
    {
        memset(&value, 0, sizeof(Int));
    }
}

void Minty::Serializer<Scope>::serialize(Writer &writer, Scope const &scope)
{
    // write each name: value in the scope as a pair
    for (auto const &[string, key, value] : scope.m_values)
    {
        writer.write(string, value);
    }
}

Bool Minty::Serializer<Scope>::deserialize(Reader &reader, Scope &scope)
{
    scope.clear();

    // read each name: value in the scope as a pair
    String name;
    Int value;
    while(reader.read_next(name, value))
    {
        // add to scope
        UUID id = UUID::create();
        scope.m_values.add(name, id, value);
    }

    return true;
}

Bool Minty::Parser<Scope>::parse(StringView const str, Scope &value)
{
    MINTY_NOT_IMPLEMENTED();
    return false;
}

String Minty::Parser<Scope>::to_string(Scope const &value)
{
    // useful for debugging
    StringBuilder builder;
    builder.append("{");
    for (auto const &[string, key, val] : value.m_values)
    {
        builder.append(string);
        builder.append("=");
        builder.append(Parser<Int>::to_string(val));
        builder.append(", ");
    }
    builder.slice(0, builder.get_size() - 2); // remove last comma and space
    builder.append("}");
    return builder.get_string();
}
