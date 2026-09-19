#include "Tui_ScriptManager.hpp"
#include "Script/Script/Script.hpp"
#include "Script/Constant/Function.hpp"

using namespace Minty;

Bool Minty::Tui_ScriptManager::load_script(Path const &path, Script &script)
{
    // Load the script file and return it as a TuiTable
    String pathString = path.get_string();
    script.data = static_cast<TuiTable*>(TuiRef::runScriptFile(pathString.get_data()));
    
    // Check if not loaded
    if (!script.data)
    {
        return false;
    }

    // Register functions if the script was successfully loaded
    TuiTable* table = static_cast<TuiTable*>(script.data);
    TuiFunction* func = nullptr;
    if (func = table->getFunction(SCRIPT_FUNC_CREATE.get_data()))
    {
        script.load = [func]()
        {
            TuiTable* args = new TuiTable();
            func->call(args, nullptr, nullptr, nullptr);
            args->release();
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_DESTROY.get_data()))
    {
        script.unload = [func]()
        {
            TuiTable* args = new TuiTable();
            func->call(args, nullptr, nullptr, nullptr);
            args->release();
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_ENABLE.get_data()))
    {
        script.enable = [func]()
        {
            TuiTable* args = new TuiTable();
            func->call(args, nullptr, nullptr, nullptr);
            args->release();
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_DISABLE.get_data()))
    {
        script.disable = [func]()
        {
            TuiTable* args = new TuiTable();
            func->call(args, nullptr, nullptr, nullptr);
            args->release();
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_FRAME_UPDATE.get_data()))
    {
        script.frameUpdate = [func]()
        {
            TuiTable* args = new TuiTable();
            func->call(args, nullptr, nullptr, nullptr);
            args->release();
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_FIXED_UPDATE.get_data()))
    {
        script.fixedUpdate = [func]()
        {
            TuiTable* args = new TuiTable();
            func->call(args, nullptr, nullptr, nullptr);
            args->release();
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_FINALIZE.get_data()))
    {
        script.finalize = [func]()
        {
            TuiTable* args = new TuiTable();
            func->call(args, nullptr, nullptr, nullptr);
            args->release();
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_RENDER.get_data()))
    {
        script.render = [func]()
        {
            TuiTable* args = new TuiTable();
            func->call(args, nullptr, nullptr, nullptr);
            args->release();
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_EVENT.get_data()))
    {
        script.event = [func]()
        {
            TuiTable* args = new TuiTable();
            func->call(args, nullptr, nullptr, nullptr);
            args->release();
        };
    }

    // Successfully loaded the script
    return true;
}
