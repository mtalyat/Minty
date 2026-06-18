#include "pch.h"
#include "Cargo.h"
#include "Core/Debug/Debug.h"
#include "Core/Serialize/Reader.h"
#include "Core/Serialize/Writer.h"

using namespace Minty;

Minty::Cargo::Cargo()
	: m_objects()
{
}

Minty::Cargo::Cargo(Size const capacity)
	: m_objects(capacity)
{
}

Minty::Cargo::Cargo(std::initializer_list<Tuple<String, Vector<Tuple<String, Variable>>>> const &list)
	: m_objects(list.size() * 2)
{
	for (auto const &[name, variables] : list)
	{
		m_objects.add({name, Object(variables)});
	}
}

Bool Minty::Cargo::contains(String const &name) const
{
	for (auto const &[objectName, object] : m_objects)
	{
		if (name == objectName)
		{
			return true;
		}
	}
	return false;
}

Object &Minty::Cargo::at(String const &name)
{
	for (auto &[objectName, object] : m_objects)
	{
		if (name == objectName)
		{
			return object;
		}
	}
	MINTY_ABORT(ErrorCodeEnum::Argument_KeyNotFound);
}

Object const &Minty::Cargo::at(String const &name) const
{
	for (auto const &[objectName, object] : m_objects)
	{
		if (name == objectName)
		{
			return object;
		}
	}
	MINTY_ABORT(ErrorCodeEnum::Argument_KeyNotFound);
}

void Minty::Cargo::add(String const &name, Object const &object)
{
	MINTY_ASSERT_A(!contains(name), ErrorCodeEnum::Argument_KeyAlreadyExists, name.get_data());
	m_objects.add({String(name), object});
}

void Minty::Cargo::set(String const &name, Object const &object)
{
	// replace if found
	for (auto &[objectName, obj] : m_objects)
	{
		if (objectName == name)
		{
			obj = object;
			return;
		}
	}

	// add new
	MINTY_ASSERT_A(!contains(name), ErrorCodeEnum::Argument_KeyAlreadyExists, name.get_data());
	m_objects.add({String(name), object});
}

Bool Minty::Cargo::remove(String const &name)
{
	// find the object and remove it
	for (Size i = 0; i < m_objects.get_size(); ++i)
	{
		if (m_objects[i].get_first() == name)
		{
			m_objects.remove(i);
			return true;
		}
	}

	// not found
	return false;
}

Minty::Cargo::Iterator Minty::Cargo::find(String const &name)
{
	auto it = m_objects.begin();
	while (it != m_objects.end())
	{
		if (it->get_first() == name)
		{
			return it;
		}
		++it;
	}
	return it;
}

Minty::Cargo::ConstIterator Minty::Cargo::find(String const &name) const
{
	auto it = m_objects.begin();
	while (it != m_objects.end())
	{
		if (it->get_first() == name)
		{
			return it;
		}
		++it;
	}
	return it;
}

ConstantContainer Minty::Cargo::pack() const
{
	// get each container, and its size
	Vector<ConstantContainer> containers(m_objects.get_size());
	Size size = 0;
	for (auto const &[name, object] : m_objects)
	{
		ConstantContainer container = object.pack();
		size += container.get_size();
		containers.add(std::move(container));
	}

	// create the container
	ConstantContainer packed(size);

	// pack data into the container
	Size offset = 0;
	for (auto const &container : containers)
	{
		packed.set_at(container.get_data(), container.get_size(), offset);
		offset += container.get_size();
	}

	return packed;
}

Bool Minty::Serializer<Cargo>::serialize(Writer &writer, Cargo const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<Cargo>::deserialize(Reader &reader, Cargo &value)
{
	// Data to load
    Vector<Tuple<String, Object>> objects;

	// Load objects
	String name;
	Object object;
	while(reader.read_next(name, object))
	{
		objects.add({name, object});
	}

	// Set the loaded objects to the cargo
	value.m_objects = std::move(objects);
	return true;
}
