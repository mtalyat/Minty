#include "Object.h"
#include "Minty/Debug/Assert.h"

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

Bool Minty::Object::contains(String const &name) const
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

Variable const &Minty::Object::at(String const &name) const
{
    for (auto const &[varName, variable] : m_variables)
    {
        if (name == varName)
        {
            return variable;
        }
    }

    MINTY_ABORT(ErrorCode::Argument_KeyNotFound);
}

Variable &Minty::Object::at(String const &name)
{
    for (auto &[varName, variable] : m_variables)
    {
        if (name == varName)
        {
            return variable;
        }
    }

    MINTY_ABORT(ErrorCode::Argument_KeyNotFound);
}

void Minty::Object::add(String const &name, Variable const &variable)
{
    MINTY_ASSERT(!contains(name), ErrorCode::Argument_KeyAlreadyExists, name);
    m_variables.add({name, variable});
}

void Minty::Object::set(String const &name, Variable const &variable)
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
    m_variables.add({name, variable});
}

Bool Minty::Object::remove(String const &name)
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
        size += sizeof_type(type);
    }

    // create the container
    ConstantContainer container(size);

    // pack data into the container
    Size offset = 0;
    for (auto const &[name, variable] : m_variables)
    {
        type = variable.get_type();
        Size typeSize = sizeof_type(type);
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
