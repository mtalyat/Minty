#pragma once
#include "SystemManager.hpp"
#include "Core/Debug/Debug.hpp"
#include "World/System/System.hpp"

template <typename T, typename... Args>
T &Minty::SystemManager::create_system(Args &&...args)
{
    // Create the system
    Pointer const system = new T(*mp_scene, std::forward<Args>(args)...);

    // Add the system
    s_registeredSystems.add<T>(system, *this);

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
    s_registeredSystems.remove<T>(system, *this);

    // Destroy the system
    delete static_cast<T *>(system);
}

template <typename T>
void Minty::SystemManager::register_system(StringView const name, Int const priority)
{
    // ensure not already registered
    MINTY_ASSERT(!s_registeredSystems.is_registered<T>(), ErrorCodeEnum::System_AlreadyRegistered);

    // create system data
    RegistryData<Pointer, SystemManager&> data{};
    data.name = name;
    data.add = [priority](Pointer const system, SystemManager &manager)
    {
        // Add to systems list
        manager.m_systems.add(typeid(T), system);

        // Add to hooks
        if constexpr (HasOnFrameUpdate<T>)
        {
            manager.m_frameUpdateHooks.add({system, [](Pointer const system, Timestep const &timestep)
                                    {
                                        static_cast<T *>(system)->on_frame_update(timestep);
                                    }},
                                   priority);
        }
        if constexpr (HasOnFixedUpdate<T>)
        {
            manager.m_fixedUpdateHooks.add({system, [](Pointer const system, Timestep const &timestep)
                                    {
                                        static_cast<T *>(system)->on_fixed_update(timestep);
                                    }},
                                   priority);
        }
        if constexpr (HasOnFinalize<T>)
        {
            manager.m_finalizeHooks.add({system, [](Pointer const system)
                                 {
                                     static_cast<T *>(system)->on_finalize();
                                 }},
                                priority);
        }
        if constexpr (HasOnRender<T>)
        {
            manager.m_renderHooks.add({system, [](Pointer const system)
                               {
                                   static_cast<T *>(system)->on_render();
                               }},
                              priority);
        }
        if constexpr (HasOnEvent<T>)
        {
            manager.m_eventHooks.add({system, [](Pointer const system, Event &event)
                              {
                                  static_cast<T *>(system)->on_event(event);
                              }},
                             priority);
        }
        if constexpr (HasOnLoad<T>)
        {
            manager.m_loadHooks.add({system, [](Pointer const system)
                             {
                                 static_cast<T *>(system)->on_load();
                             }},
                            priority);
        }
        if constexpr (HasOnUnload<T>)
        {
            manager.m_unloadHooks.add({system, [](Pointer const system)
                               {
                                   static_cast<T *>(system)->on_unload();
                               }},
                              priority);
        }
    };
    data.remove = [](Pointer const system, SystemManager &manager)
    {
        // Remove from systems list
        manager.m_systems.remove(typeid(T));

        // Remove from hooks
        if constexpr (HasOnFrameUpdate<T>)
        {
            for (Size i = 0; i < manager.m_frameUpdateHooks.get_size(); ++i)
            {
                if (manager.m_frameUpdateHooks[i].system == system)
                {
                    manager.m_frameUpdateHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnFixedUpdate<T>)
        {
            for (Size i = 0; i < manager.m_fixedUpdateHooks.get_size(); ++i)
            {
                if (manager.m_fixedUpdateHooks[i].system == system)
                {
                    manager.m_fixedUpdateHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnFinalize<T>)
        {
            for (Size i = 0; i < manager.m_finalizeHooks.get_size(); ++i)
            {
                if (manager.m_finalizeHooks[i].system == system)
                {
                    manager.m_finalizeHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnRender<T>)
        {
            for (Size i = 0; i < manager.m_renderHooks.get_size(); ++i)
            {
                if (manager.m_renderHooks[i].system == system)
                {
                    manager.m_renderHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnEvent<T>)
        {
            for (Size i = 0; i < manager.m_eventHooks.get_size(); ++i)
            {
                if (manager.m_eventHooks[i].system == system)
                {
                    manager.m_eventHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnLoad<T>)
        {
            for (Size i = 0; i < manager.m_loadHooks.get_size(); ++i)
            {
                if (manager.m_loadHooks[i].system == system)
                {
                    manager.m_loadHooks.remove(i);
                    break;
                }
            }
        }
        if constexpr (HasOnUnload<T>)
        {
            for (Size i = 0; i < manager.m_unloadHooks.get_size(); ++i)
            {
                if (manager.m_unloadHooks[i].system == system)
                {
                    manager.m_unloadHooks.remove(i);
                    break;
                }
            }
        }
    };

    // register system
    s_registeredSystems.register_type<T>(std::move(data));
}