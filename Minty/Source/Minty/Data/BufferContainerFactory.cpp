#include "pch.h"
#include "BufferContainerFactory.h"
#include "Minty/Core/Format.h"

using namespace Minty;

BufferContainer& Minty::BufferContainerFactory::get_container(UUID const groupId, Size const index)
{
    MINTY_ASSERT(m_groups.contains(groupId), "BufferCargo does not contain a group with the given ID.");

    // find group
    Vector<BufferContainer>& group = m_groups.at(groupId);

    MINTY_ASSERT(index <= group.get_size(), F("BufferCargo getting container at index {} when the get_size of the cargo is {}. The given index should be <= the group get_size.", index, group.get_size()));

    // ensure there is a value at that index
    if (index == group.get_size())
    {
        group.add(BufferContainer(m_initialCapacity, m_usage));
    }

    // return buffer
    return group.at(index);
}

UUID Minty::BufferContainerFactory::create_group()
{
    // create ID
    UUID id = UUID::create();

    // make group
    m_groups.add(id, Vector<BufferContainer>());

    // return ID to that group
    return id;
}
