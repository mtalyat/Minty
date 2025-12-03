#include "Scope.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::Scope::Scope()
    : m_values()
{
}

UUID Minty::Scope::find(String const &name) const
{
    auto found = m_values.find(name);
    if (found == m_values.end())
    {
        return UUID();
    }
    return found->get_second();
}

UUID Minty::Scope::add(String const &name, Int const value)
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

void Minty::Scope::serialize(Writer &writer) const
{
    // write each name: value in the scope as a pair
    for (auto const &[string, key, value] : m_values)
    {
        writer.write(string, value);
    }
}

Bool Minty::Scope::deserialize(Reader &reader)
{
    clear();

    // read each name: value in the scope as a pair
    String name;
    Int value;
    for (Size i = 0; i < reader.get_size(); i++)
    {
        Bool const nameResult = reader.read_name(i, name);
        MINTY_ASSERT(nameResult, ErrorCode::Serialization_ReadName);

        Bool const valueResult = reader.read(i, value);
        MINTY_ASSERT(valueResult, ErrorCode::Serialization_ReadValue);

        // add to scope
        UUID id = UUID::create();
        m_values.add(name, id, value);
    }

    return true;
}