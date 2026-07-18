#pragma once
#include "SystemManager.hpp"
#include "Core/Debug/Debug.hpp"
#include "World/System/System.hpp"

template <typename T, typename... Args>
T &Minty::SystemManager::create_system(Args &&...args)
{
    // Create the system
    Pointer const system = m_registeredSystems.create<T>(std::forward<Args>(args)...);

    // Add the system
    m_registeredSystems.add<T>(system);

    // Return the system
    return *static_cast<T *>(system);
}

template <typename T>
void Minty::SystemManager::destroy_system()
{
    // Get the system, ensure it exists
    TypeID const typeId = typeid(T);
    MINTY_ASSERT(m_systems.contains(typeId), ErrorCodeEnum::Argument_KeyNotFound);
    Pointer const system = m_systems.at(typeId);

    // Remove the system
    m_registeredSystems.remove<T>(system);

    // Destroy the system
    m_registeredSystems.destroy<T>(system);
}

template <typename T>
void Minty::SystemManager::register_system(StringView const name, Int const priority)
{
    // ensure not already registered
    MINTY_ASSERT(!m_registeredSystems.is_registered<T>(), ErrorCodeEnum::System_AlreadyRegistered);

    // create system data
    RegistryData<> data{};
    data.name = name;
    data.create = [this]()
    {
        return new T();
    };
    data.destroy = [](Pointer const system)
    {
        // Delete the system
        delete static_cast<T *>(system);
    };
    data.add = [this, priority](Pointer const system)
    {
        // Add to systems list
        m_systems.add(system);

        // Add to hooks
        if constexpr (HasOnFrameUpdate<T>)
        {
            m_frameUpdateHooks.add({system, [](Pointer const system, Timestep const &timestep)
                                    {
                                        static_cast<T *>(system)->frame_update(timestep);
                                    }},
                                   priority);
        }
        if constexpr (HasOnFixedUpdate<T>)
        {
            m_fixedUpdateHooks.add({system, [](Pointer const system, Timestep const &timestep)
                                    {
                                        static_cast<T *>(system)->fixed_update(timestep);
                                    }},
                                   priority);
        }
        if constexpr (HasOnFinalize<T>)
        {
            m_finalizeHooks.add({system, [](Pointer const system, Timestep const &timestep)
                                 {
                                     static_cast<T *>(system)->finalize(timestep);
                                 }},
                                priority);
        }
        if constexpr (HasOnRender<T>)
        {
            m_renderHooks.add({system, [](Pointer const system, Timestep const &timestep)
                               {
                                   static_cast<T *>(system)->render(timestep);
                               }},
                              priority);
        }
        if constexpr (HasOnEvent<T>)
        {
            m_eventHooks.add({system, [](Pointer const system, Event &event)
                              {
                                  static_cast<T *>(system)->on_event(event);
                              }},
                             priority);
        }
        if constexpr (HasOnLoad<T>)
        {
            m_loadHooks.add({system, [](Pointer const system)
                             {
                                 static_cast<T *>(system)->load();
                             }},
                            priority);
        }
        if constexpr (HasOnUnload<T>)
        {
            m_unloadHooks.add({system, [](Pointer const system)
                               {
                                   static_cast<T *>(system)->unload();
                               }},
                              priority);
        }
    };
    data.remove = [this](Pointer const system)
    {
        // Remove from systems list
        m_systems.remove(system);

        // Remove from hooks
        if constexpr (HasOnFrameUpdate<T>)
        {
            for (Size i = 0; i < m_frameUpdateHooks.get_size(); ++i)
            {
                if (m_frameUpdateHooks[i].system == system)
                {
                    m_frameUpdateHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnFixedUpdate<T>)
        {
            for (Size i = 0; i < m_fixedUpdateHooks.get_size(); ++i)
            {
                if (m_fixedUpdateHooks[i].system == system)
                {
                    m_fixedUpdateHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnFinalize<T>)
        {
            for (Size i = 0; i < m_finalizeHooks.get_size(); ++i)
            {
                if (m_finalizeHooks[i].system == system)
                {
                    m_finalizeHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnRender<T>)
        {
            for (Size i = 0; i < m_renderHooks.get_size(); ++i)
            {
                if (m_renderHooks[i].system == system)
                {
                    m_renderHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnEvent<T>)
        {
            for (Size i = 0; i < m_eventHooks.get_size(); ++i)
            {
                if (m_eventHooks[i].system == system)
                {
                    m_eventHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnLoad<T>)
        {
            for (Size i = 0; i < m_loadHooks.get_size(); ++i)
            {
                if (m_loadHooks[i].system == system)
                {
                    m_loadHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnUnload<T>)
        {
            for (Size i = 0; i < m_unloadHooks.get_size(); ++i)
            {
                if (m_unloadHooks[i].system == system)
                {
                    m_unloadHooks.remove(i);
                    break;
                }
            }
        }
    };

    // register system
    m_registeredSystems.register_type<T>(std::move(data));
}