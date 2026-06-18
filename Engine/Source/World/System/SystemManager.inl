#pragma once
#include "Core/Debug/Debug.h"
#include "SystemManager.h"

template <typename System>
void Minty::SystemManager::register_system(StringView const name)
{
    // ensure not already registered
    MINTY_ASSERT(!m_registeredComponents.is_registered<System>(), ErrorCodeEnum::System_AlreadyRegistered);

    // create system data
    RegistryData<> data{};
    data.name = name;
    data.add = [this]() { add_system<System>(); };

    // register system
    m_registeredComponents.register_type<System>(std::move(data));
}