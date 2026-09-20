#pragma once

#include "Core/Data/HandlePool.hpp"
#include "Core/Data/Map.hpp"
#include "Core/Time/Timestep.hpp"
#include "Resource/Type/Handle.hpp"
#include "Script/Script/Script.hpp"
#include "Script/Type/Handle.hpp"
#include "Core/Type/Status.hpp"

namespace Minty
{
    struct ScriptManagerInfo;
    struct ScriptInfo;
    struct ScriptResourceInfo;
    struct ScriptLocalContext;
    struct ScriptGlobalContext;
    class Event;
    struct Timestep;

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
        // Script
        ScriptHandle create(ScriptInfo const &info);
        ScriptHandle create(ScriptResourceHandle const handle);
        void destroy(ScriptHandle handle);
        Bool contains(ScriptHandle handle);
        void update_global_context(ScriptGlobalContext const &context);
        void call_create(ScriptHandle handle, ScriptLocalContext const &context);
        void call_destroy(ScriptHandle handle, ScriptLocalContext const &context);
        void call_load(ScriptHandle handle, ScriptLocalContext const &context);
        void call_unload(ScriptHandle handle, ScriptLocalContext const &context);
        void call_enable(ScriptHandle handle, ScriptLocalContext const &context);
        void call_disable(ScriptHandle handle, ScriptLocalContext const &context);
        void call_frame_update(ScriptHandle handle, ScriptLocalContext const &context);
        void call_fixed_update(ScriptHandle handle, ScriptLocalContext const &context);
        void call_finalize(ScriptHandle handle, ScriptLocalContext const &context);
        void call_render(ScriptHandle handle, ScriptLocalContext const &context);
        void call_event(ScriptHandle handle, ScriptLocalContext const &context, Event &event);

#pragma endregion

#pragma region Variable

    private:
        HandlePool<Script> m_scriptPool;
        Map<ScriptResourceHandle, ScriptHandle> m_scriptCache;

        static ScriptManager* s_instance;

#pragma endregion
    };
}