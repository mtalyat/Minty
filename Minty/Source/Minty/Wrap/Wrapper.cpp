#include "pch.h"
#include "Wrapper.h"

using namespace Minty;

void Minty::Wrapper::add(Wrap const& wrap)
{
	m_wraps.add(wrap);
}

void Minty::Wrapper::add(Path const& path)
{
	add(Wrap(path));
}

Size Minty::Wrapper::get_wrap_count() const
{
	return m_wraps.get_size();
}

Wrap& Minty::Wrapper::get_wrap(Size const index)
{
	return m_wraps.at(index);
}

Wrap const& Minty::Wrapper::get_wrap(Size const index) const
{
	return m_wraps.at(index);
}

Wrap* Minty::Wrapper::find_by_path(Path const& path)
{
	for (Wrap& wrap : m_wraps)
	{
		if (wrap.contains(path))
		{
			return &wrap;
		}
	}

	// not found
	return nullptr;
}

Wrap const* Minty::Wrapper::find_by_path(Path const& path) const
{
	for (Wrap const& wrap : m_wraps)
	{
		if (wrap.contains(path))
		{
			return &wrap;
		}
	}

	// not found
	return nullptr;
}

Wrap* Minty::Wrapper::find_by_name(String const& name)
{
	for (Wrap& wrap : m_wraps)
	{
		if (String(wrap.get_name()) == name)
		{
			return &wrap;
		}
	}

	// not found
	return nullptr;
}

Wrap const* Minty::Wrapper::find_by_name(String const& name) const
{
	for (Wrap const& wrap : m_wraps)
	{
		if (String(wrap.get_name()) == name)
		{
			return &wrap;
		}
	}

	// not found
	return nullptr;
}

Bool Minty::Wrapper::contains(Path const& path) const
{
	for (Wrap const& wrap : m_wraps)
	{
		if (wrap.contains(path))
		{
			return true;
		}
	}

	return false;
}

Bool Minty::Wrapper::open(Path const& path, VirtualFile& file) const
{
	// find wrapper
	Wrap const* wrap = find_by_path(path);

	if (!wrap) return false;

	// open file
	return wrap->open(path, file);
}

Vector<Char> Minty::Wrapper::read(Path const& path) const
{
	// find wrap
	Wrap const* wrap = find_by_path(path);

	if (!wrap) return Vector<Char>();

	// read file
	return wrap->read(path);
}