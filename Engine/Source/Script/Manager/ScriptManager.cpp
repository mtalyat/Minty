#include "pch.hpp"
#include "ScriptManager.hpp"
#include "ScriptManagerInfo.hpp"
#include "Script/Script/ScriptInfo.hpp"
#include "Script/Script/Script.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Resource/Script/ScriptResource.hpp"

#include "Independence/Tui/Tui_ScriptManager.hpp"

using namespace Minty;

Minty::ScriptManager::ScriptManager(ScriptManagerInfo const &info)
    : m_scriptPool(), m_scriptCache()
{
}

ScriptHandle Minty::ScriptManager::create(ScriptInfo const &info)
{
    // Create a new Script
    Script script{};

    // Get the script object
    Bool result = false;
    switch(info.type.value)
    {
        case ScriptTypeEnum::Tui:
            result = Tui_ScriptManager::load_script(info.path, script);
            break;
        default:
            MINTY_NOT_SUPPORTED();
            break;
    }

    // Check if the script was successfully loaded
    if (!result)
    {
        return ScriptHandle{};
    }

    // Add the script to the pool and return its handle
    ScriptHandle handle = m_scriptPool.add(std::move(script));
    return handle;
}

ScriptHandle Minty::ScriptManager::create(ScriptResourceHandle const handle)
{
    // Check if the script is already cached
    auto it = m_scriptCache.find(handle);
    if (it != m_scriptCache.end())
    {
        return it->get_second();
    }

    // Create a new Script and cache it
    ResourceManager &resourceManager = ResourceManager::get_instance();
    ScriptResource const &resource = resourceManager.at<ScriptResource>(handle);
    ScriptInfo scriptInfo{};
    scriptInfo.type = resource.type;
    scriptInfo.path = resource.path;

    ScriptHandle newHandle = create(scriptInfo);
    m_scriptCache[handle] = newHandle;
    return newHandle;
}

void Minty::ScriptManager::destroy(ScriptHandle handle)
{
    // Destroy the script and remove it from the cache
    for (auto it = m_scriptCache.begin(); it != m_scriptCache.end(); ++it)
    {
        if (it->get_second() == handle)
        {
            m_scriptCache.remove(it->get_first());
            break;
        }
    }
    m_scriptPool.remove(handle);
}

Bool Minty::ScriptManager::contains(ScriptHandle handle)
{
    // Check if the script exists in the pool
    return m_scriptPool.contains(handle);
}

void Minty::ScriptManager::call_load(ScriptHandle handle)
{
    // Ensure the script exists in the pool before calling load
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Call the load function on the script, if it exists
    Script& script = m_scriptPool.at(handle);
    if (script.load)
    {
        script.load();
    }
}

void Minty::ScriptManager::call_unload(ScriptHandle handle)
{
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    Script& script = m_scriptPool.at(handle);
    if (script.unload)
    {
        script.unload();
    }
}

void Minty::ScriptManager::call_enable(ScriptHandle handle)
{
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    Script& script = m_scriptPool.at(handle);
    if (script.enable)
    {
        script.enable();
    }
}

void Minty::ScriptManager::call_disable(ScriptHandle handle)
{
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    Script& script = m_scriptPool.at(handle);
    if (script.disable)
    {
        script.disable();
    }
}

void Minty::ScriptManager::call_frame_update(ScriptHandle handle)
{
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    Script& script = m_scriptPool.at(handle);
    if (script.frameUpdate)
    {
        script.frameUpdate();
    }
}

void Minty::ScriptManager::call_fixed_update(ScriptHandle handle)
{
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    Script& script = m_scriptPool.at(handle);
    if (script.fixedUpdate)
    {
        script.fixedUpdate();
    }
}

void Minty::ScriptManager::call_finalize(ScriptHandle handle)
{
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    Script& script = m_scriptPool.at(handle);
    if (script.finalize)
    {
        script.finalize();
    }
}

void Minty::ScriptManager::call_render(ScriptHandle handle)
{
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    Script& script = m_scriptPool.at(handle);
    if (script.render)
    {
        script.render();
    }
}

void Minty::ScriptManager::call_event(ScriptHandle handle)
{
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    Script& script = m_scriptPool.at(handle);
    if (script.event)
    {
        script.event();
    }
}
