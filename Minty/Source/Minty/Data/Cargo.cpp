#include "pch.h"
#include "Cargo.h"

using namespace Minty;

Bool Minty::Object::contains(String const& name) const
{
	for (auto const& [varName, variable] : m_variables)
	{
		if (varName == name)
		{
			return true;
		}
	}
	return false;
}

Variable const& Minty::Object::at(String const& name) const
{
	MINTY_ASSERT(!m_variables.is_empty(), "Object has no variables.");
	for (auto const& [varName, variable] : m_variables)
	{
		if (varName == name)
		{
			return variable;
		}
	}
	MINTY_ASSERT(false, "Variable not found.");
	throw std::runtime_error("Variable not found.");
}

Variable& Minty::Object::at(String const& name)
{
	MINTY_ASSERT(!m_variables.is_empty(), "Object has no variables.");
	for (auto& [varName, variable] : m_variables)
	{
		if (varName == name)
		{
			return variable;
		}
	}
	MINTY_ASSERT(false, "Variable not found.");
	throw std::runtime_error("Variable not found.");
}

void Minty::Object::add(String const& name, Variable const& variable)
{
	MINTY_ASSERT(!contains(name), "Object already contains variable with name: " + name);
	m_variables.add({ name, variable });
}

void Minty::Object::set(String const& name, Variable const& variable)
{
	// replace if found
	for (auto& [varName, var] : m_variables)
	{
		if (varName == name)
		{
			var = variable;
			return;
		}
	}
	// add to end
	m_variables.add({ name, variable });
}

Bool Minty::Object::remove(String const& name)
{
	for (Size i = 0; i < m_variables.get_size(); ++i)
	{
		if (m_variables[i].first == name)
		{
			m_variables.remove(i);
			return true;
		}
	}
	return false;
}

/// <summary>
/// Packs the data within this Cargo into a byte array.
/// </summary>
/// <returns>A ConstContainer containing the byte data.</returns>
ConstantContainer Minty::Object::pack() const
{
	// get the size of the container
	Size size = 0;
	Type type;
	for (auto const& [name, variable] : m_variables)
	{
		type = variable.get_type();
		size += sizeof_type(type);
	}

	// create the container
	ConstantContainer container(size);

	// pack data into the container
	Size offset = 0;
	for (auto const& [name, variable] : m_variables)
	{
		type = variable.get_type();
		Size typeSize = sizeof_type(type);
		// if variable is empty, set to zeros, otherwise set the variable data
		if (variable.is_empty())
		{
			Byte* ptr = static_cast<Byte*>(container.get_data()) + offset;
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

ConstantContainer Minty::Cargo::pack() const
{
	// get each container, and its size
	Vector<ConstantContainer> containers(m_objects.get_size());
	Size size = 0;
	for (auto const& [name, object] : m_objects)
	{
		ConstantContainer container = object.pack();
		size += container.get_size();
		containers.add(std::move(container));
	}

	// create the container
	ConstantContainer packed(size);

	// pack data into the container
	Size offset = 0;
	for (auto const& container : containers)
	{
		packed.set_at(container.get_data(), container.get_size(), offset);
		offset += container.get_size();
	}

	return packed;
}
