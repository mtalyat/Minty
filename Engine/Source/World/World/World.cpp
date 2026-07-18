#include "pch.hpp"
#include "World.hpp"

using namespace Minty;

Minty::World::World(WorldInfo const &info)
    : mp_impl(new Impl(info))
{
}

Minty::World::~World()
{
    delete mp_impl;
}
