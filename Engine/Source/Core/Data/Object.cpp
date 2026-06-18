#include "Object.h"
#include "Core/Debug/Debug.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Minty::Object::Object()
    : m_variables()
{
}

Minty::Object::Object(Size const capcity)
    : m_variables(capcity)
{
}

Minty::Object::Object(std::initializer_list<Tuple<String, Variable>> const &list)
    : m_variables(list)
{
}

Minty::Object::Object(Vector<Tuple<String, Variable>> const &variables)
    : m_variables(variables)
{
}

Size Minty::Object::get_size() const
{
    Size size = 0;
    for (auto const &[name, variable] : m_variables)
    {
        size += variable.get_size();
    }
    return size;
}

Bool Minty::Object::contains(StringView const name) const
{
    for (auto const &[varName, variable] : m_variables)
    {
        if (name == varName)
        {
            return true;
        }
    }
    return false;
}

Variable const &Minty::Object::at(StringView const name) const
{
    for (auto const &[varName, variable] : m_variables)
    {
        if (name == varName)
        {
            return variable;
        }
    }

    MINTY_ABORT(ErrorCodeEnum::Argument_KeyNotFound);
}

Variable &Minty::Object::at(StringView const name)
{
    for (auto &[varName, variable] : m_variables)
    {
        if (name == varName)
        {
            return variable;
        }
    }

    MINTY_ABORT(ErrorCodeEnum::Argument_KeyNotFound);
}

void Minty::Object::add(StringView const name, Variable const &variable)
{
    MINTY_ASSERT_A(!contains(name), ErrorCodeEnum::Argument_KeyAlreadyExists, name.get_data());
    m_variables.add({String(name), variable});
}

void Minty::Object::add(StringView const name, Variable &&variable)
{
    MINTY_ASSERT_A(!contains(name), ErrorCodeEnum::Argument_KeyAlreadyExists, name.get_data());
    m_variables.add({String(name), std::move(variable)});
}

void Minty::Object::set(StringView const name, Variable const &variable)
{
    for (auto &[varName, var] : m_variables)
    {
        if (name == varName)
        {
            var = variable;
            return;
        }
    }

    // if not found, add new
    m_variables.add({String(name), variable});
}

Bool Minty::Object::remove(StringView const name)
{
    for (Size i = 0; i < m_variables.get_size(); ++i)
    {
        if (m_variables[i].get_first() == name)
        {
            m_variables.remove(i);
            return true;
        }
    }

    return false;
}

ConstantContainer Minty::Object::pack() const
{
    // get the size of the container
    Size size = 0;
    Type type;
    for (auto const &[name, variable] : m_variables)
    {
        type = variable.get_type();
        size += variable.get_size();
    }

    // create the container
    ConstantContainer container(size);

    // pack data into the container
    Size offset = 0;
    for (auto const &[name, variable] : m_variables)
    {
        type = variable.get_type();
        Size typeSize = variable.get_size();
        // if variable is empty, set to zeros, otherwise set the variable data
        if (variable.is_empty())
        {
            Byte *ptr = static_cast<Byte *>(container.get_data()) + offset;
            memset(ptr, 0, typeSize);
        }
        else
        {
            container.set_at(variable.get_data().get_data(), typeSize, offset);
        }
        offset += typeSize;
    }

    return container;
}

Bool Minty::Serializer<Object>::serialize(Writer &writer, Object const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<Object>::deserialize(Reader &reader, Object &value)
{
    // Data to load
    Vector<Tuple<String, Variable>> variables;

    // Load variables
    String name;
    Variable variable;
    while(reader.read_next(name, variable))
    {
        variables.add({name, variable});
    }

    // Set the loaded variables to the object
    value.m_variables = std::move(variables);
    return true;
}
