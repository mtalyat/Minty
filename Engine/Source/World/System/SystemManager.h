#pragma once

#include "World/Entity/Entity.h"
#include "Library/EnTT/EnTT.h"
#include "Core/Data/Registry.h"
#include "Core/Data/UUID.h"
#include "Core/Data/StringView.h"

namespace Minty
{
    struct SystemManagerInfo;

    class SystemManager
    {
        #pragma region Constructor

    public:
        SystemManager(SystemManagerInfo const &info);
        ~SystemManager();

        SystemManager(SystemManager const &) = delete;
        SystemManager(SystemManager &&) = delete;

#pragma endregion

#pragma region Operator

    public:
        SystemManager &operator=(SystemManager const &) = delete;
        SystemManager &operator=(SystemManager &&) = delete;

#pragma endregion

#pragma region Method

    public:
        template <typename T, typename... Args>
        T &add_system(Args &&...args)
        {
            return mp_impl->systems.emplace<T>(std::forward<Args>(args)...);
        }
    
        template<typename System>
        void register_system(StringView const name);

#pragma endregion

#pragma region Variable
    
    private:
        Registry<> m_registeredComponents;

#pragma endregion
    };
}

#include "SystemManager.inl"