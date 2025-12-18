#include "pch.h"
#include "BufferContainerFactory.h"
#include "Minty/Core/Format.h"

using namespace Minty;

Minty::BufferContainerFactory::BufferContainerFactory(Size const initialCapacity, BufferUsage const usage)
    : m_initialCapacity(initialCapacity), m_usage(usage), m_containers()
{
}

BufferContainer &Minty::BufferContainerFactory::get_container(Size const size)
{
    // calculate index based on the size
    Size index = 0;
    Size bufferSize = 0;
    while (bufferSize < size)
    {
        index++;
        bufferSize = Math::pow(m_initialCapacity, index);
    }

    // if index is too large, add new lists
    while (index >= m_containers.get_size())
    {
        m_containers.add(Vector<Tuple<Bool, BufferContainer>>());
    }

    // get the containers at that index
    Vector<Tuple<Bool, BufferContainer>> &containers = m_containers.at(index);

    // if there is one that is unused, return it
    for (auto &[used, container] : containers)
    {
        if (!used)
        {
            used = true;
            return container;
        }
    }

    // if there is no unused container, create a new one
    BufferContainer newContainer(bufferSize, m_usage);
    containers.add({true, std::move(newContainer)});

    // return the new container
    return containers.back().get_second();
}

void Minty::BufferContainerFactory::reset()
{
    // mark all containers as unused
    for (auto &containers : m_containers)
    {
        for (auto &[used, container] : containers)
        {
            used = false;
        }
    }
}