#pragma once
#include "Core/Debug/Debug.h"
#include "SystemManager.h"
#include "System.h"

template <typename T, typename... Args>
inline T &Minty::SystemManager::create_system(Args &&...args)
{
    // create system
    T *system = new T(std::forward<Args>(args)...);

    // add to systems list
    m_systems.add(system);

    // add hooks
    if constexpr (HasUpdate<T>)
    {
        m_frameUpdateHooks.add({system, [](Pointer const systemPtr, Timestep const &timestep)
                                {
                                    static_cast<T *>(systemPtr)->frame_update(timestep);
                                }});
    }
    if constexpr (HasFixedUpdate<T>)
    {
        m_fixedUpdateHooks.add({system, [](Pointer const systemPtr, Timestep const &timestep)
                                {
                                    static_cast<T *>(systemPtr)->fixed_update(timestep);
                                }});
    }
    if constexpr (HasLateUpdate<T>)
    {
        m_lateUpdateHooks.add({system, [](Pointer const systemPtr, Timestep const &timestep)
                               {
                                   static_cast<T *>(systemPtr)->late_update(timestep);
                               }});
    }
    if constexpr (HasLoad<T>)
    {
        m_loadHooks.add({system, [](Pointer const systemPtr)
                         {
                             static_cast<T *>(systemPtr)->load();
                         }});
    }
    if constexpr (HasUnload<T>)
    {
        m_unloadHooks.add({system, [](Pointer const systemPtr)
                           {
                               static_cast<T *>(systemPtr)->unload();
                           }});
    }

    // return system
    return *system;
}

template <typename System>
void Minty::SystemManager::register_system(StringView const name)
{
    // ensure not already registered
    MINTY_ASSERT(!m_registeredSystems.is_registered<System>(), ErrorCodeEnum::System_AlreadyRegistered);

    // create system data
    RegistryData<> data{};
    data.name = name;
    data.add = [this]()
    { create_system<System>(); };

    // register system
    m_registeredSystems.register_type<System>(std::move(data));
}