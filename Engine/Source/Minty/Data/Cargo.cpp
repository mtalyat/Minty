#include "pch.h"
#include "Cargo.h"
#include "Minty/Debug/Assert.h"

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
	MINTY_ABORT(ErrorCode::Argument_KeyNotFound);
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
	MINTY_ABORT(ErrorCode::Argument_KeyNotFound);
}

void Minty::Cargo::add(String const &name, Object const &object)
{
	MINTY_ASSERT_F(!contains(name), ErrorCode::Argument_KeyAlreadyExists, name);
	m_objects.add({name, object});
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
	m_objects.add({name, object});
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
