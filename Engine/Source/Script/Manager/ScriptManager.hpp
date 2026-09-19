#pragma once

#include "Core/Data/HandlePool.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Time/Timestep.hpp"
#include "Resource/Type/Handle.hpp"
#include "Script/Script/Script.hpp"
#include "Script/Type/Handle.hpp"

namespace Minty
{
    struct ScriptManagerInfo;
    struct ScriptInfo;
    struct ScriptResourceInfo;

    class ScriptManager
    {
#pragma region Constructor

    public:
        ScriptManager(ScriptManagerInfo const &info);

        ~ScriptManager();

#pragma endregion

#pragma region Accessor

    public:
        /**
         * @brief Gets the singleton instance of the ScriptManager.
         * @return The ScriptManager instance.
         */
        static ScriptManager &get_instance();

#pragma endregion

#pragma region Method

    public:
        ScriptHandle create(ScriptInfo const &info);
        ScriptHandle create(ScriptResourceHandle const handle);
        void destroy(ScriptHandle handle);
        Bool contains(ScriptHandle handle);
        void call_load(ScriptHandle handle);
        void call_unload(ScriptHandle handle);
        void call_enable(ScriptHandle handle);
        void call_disable(ScriptHandle handle);
        void call_frame_update(ScriptHandle handle);
        void call_fixed_update(ScriptHandle handle);
        void call_finalize(ScriptHandle handle);
        void call_render(ScriptHandle handle);
        void call_event(ScriptHandle handle);

#pragma endregion

#pragma region Variable

    private:
        HandlePool<Script> m_scriptPool;
        Map<ScriptResourceHandle, ScriptHandle> m_scriptCache;

        static ScriptManager* s_instance;

#pragma endregion
    };
}