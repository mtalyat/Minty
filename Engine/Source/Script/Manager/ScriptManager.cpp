#include "pch.hpp"
#include "ScriptManager.hpp"
#include "ScriptManagerInfo.hpp"
#include "Script/Script/ScriptInfo.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Resource/Script/ScriptResource.hpp"

#include "Independence/Tui/Tui_ScriptManager.hpp"

using namespace Minty;

ScriptManager* Minty::ScriptManager::s_instance = nullptr;

Minty::ScriptManager::ScriptManager(ScriptManagerInfo const &info)
    : m_scriptPool(), 
    m_scriptCache(),
    m_status()
{
    MINTY_ASSERT(s_instance == nullptr, ErrorCodeEnum::Singleton_AlreadyExists);
    s_instance = this;
}

Minty::ScriptManager::~ScriptManager()
{
    MINTY_ASSERT(s_instance != nullptr, ErrorCodeEnum::Singleton_DifferentObject);
    s_instance = nullptr;
}

ScriptManager &Minty::ScriptManager::get_instance()
{
    MINTY_ASSERT(s_instance != nullptr, ErrorCodeEnum::Singleton_DoesNotExist);
    return *s_instance;
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
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);

    // Remove it from the cache and pool
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

void Minty::ScriptManager::update_global_context(ScriptGlobalContext const &context)
{
    // Set global context for all script managers
    Tui_ScriptManager::set_global_context(context);
}

void Minty::ScriptManager::call_create(ScriptHandle handle, ScriptLocalContext const &context)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);

    // Call the create function for the script if it exists
    if (script.create)
    {
        // Set the context for the script before calling the create function
        script.setContext(script, context);

        // Call the create function for the script
        script.create();
    }
}

void Minty::ScriptManager::call_destroy(ScriptHandle handle, ScriptLocalContext const &context)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);

    // Call the destroy function for the script if it exists
    if (script.destroy)
    {
        // Set the context for the script before calling the destroy function
        script.setContext(script, context);

        // Call the destroy function for the script
        script.destroy();
    }
}

void Minty::ScriptManager::call_load(ScriptHandle handle, ScriptLocalContext const &context)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);

    // Call the load function for the script if it exists
    if (script.load)
    {
        // Set the context for the script before calling the load function
        script.setContext(script, context);

        // Call the load function for the script
        script.load();
    }
}

void Minty::ScriptManager::call_unload(ScriptHandle handle, ScriptLocalContext const &context)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);

    // Call the unload function for the script if it exists
    if (script.unload)
    {
        // Set the context for the script before calling the unload function
        script.setContext(script, context);

        // Call the unload function for the script
        script.unload();
    }
}

void Minty::ScriptManager::call_enable(ScriptHandle handle, ScriptLocalContext const &context)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);

    // Call the enable function for the script if it exists
    if (script.enable)
    {
        // Set the context for the script before calling the enable function
        script.setContext(script, context);

        // Call the enable function for the script
        script.enable();
    }
}

void Minty::ScriptManager::call_disable(ScriptHandle handle, ScriptLocalContext const &context)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);

    // Call the disable function for the script if it exists
    if (script.disable)
    {
        // Set the context for the script before calling the disable function
        script.setContext(script, context);

        // Call the disable function for the script
        script.disable();
    }
}

void Minty::ScriptManager::call_frame_update(ScriptHandle handle, ScriptLocalContext const &context)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);
    if (script.frameUpdate)
    {
        // Set the context for the script before calling the frame update
        script.setContext(script, context);

        // Call the frame update function for the script
        script.frameUpdate();
    }
}

void Minty::ScriptManager::call_fixed_update(ScriptHandle handle, ScriptLocalContext const &context)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);
    if (script.fixedUpdate)
    {
        // Set the context for the script before calling the fixed update
        script.setContext(script, context);

        // Call the fixed update function for the script
        script.fixedUpdate();
    }
}

void Minty::ScriptManager::call_finalize(ScriptHandle handle, ScriptLocalContext const &context)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);
    if (script.finalize)
    {
        // Set the context for the script before calling the finalize function
        script.setContext(script, context);

        // Call the finalize function for the script
        script.finalize();
    }
}

void Minty::ScriptManager::call_render(ScriptHandle handle, ScriptLocalContext const &context)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);
    if (script.render)
    {
        // Set the context for the script before calling the render function
        script.setContext(script, context);

        // Call the render function for the script
        script.render();
    }
}

void Minty::ScriptManager::call_event(ScriptHandle handle, ScriptLocalContext const &context, Event &event)
{
    // Ensure the script exists in the pool
    MINTY_ASSERT(m_scriptPool.contains(handle), ErrorCodeEnum::Argument_ExpectedDefined);

    // Get the script from the pool
    Script& script = m_scriptPool.at(handle);
    if (script.event)
    {
        // Set the context for the script before calling the event function
        script.setContext(script, context);

        // Call the event function for the script
        // TODO: Call the respective event handling function within the script
        script.event();
    }
}
