#include "pch.h"
#include "GenericResource.h"
#include "GenericResourceInfo.h"

using namespace Minty;

Minty::GenericResource::GenericResource()
	: m_container()
{
}

Minty::GenericResource::GenericResource(GenericResourceInfo &&info)
    : m_container(Shared<ConstantContainer>::create(std::move(info.data)))
{
}

String Minty::GenericResource::get_text() const
{
	Vector<Char> text;
	text.resize(m_container->get_size() + 1, '\0');
	memcpy(text.get_data(), m_container->get_data(), m_container->get_size());
	return String(text.get_data());
}

Unique<Reader> Minty::GenericResource::open_reader() const
{
	if (m_container->get_size() == 0)
	{
		return nullptr;
	}

    Unique<Stream> stream = Unique<MemoryStream>::create(m_container);
	return Unique<TextReader>::create(std::move(stream));
}

Bool Minty::Serializer<GenericResource>::serialize(Writer &writer, GenericResource const &value)
{
    return Bool();
}

Bool Minty::Serializer<GenericResource>::deserialize(Reader &reader, GenericResource &value)
{
    return Bool();
}
