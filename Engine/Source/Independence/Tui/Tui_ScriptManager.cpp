#include "Tui_ScriptManager.hpp"
#include "Script/Script/Script.hpp"
#include "Script/Constant/Function.hpp"
#include "Script/Script/ScriptLocalContext.hpp"
#include "Script/Script/ScriptGlobalContext.hpp"

using namespace Minty;

Bool Minty::Tui_ScriptManager::load_script(Path const &path, Script &script)
{
    // Load the script file and return it as a TuiTable
    String pathString = path.get_string();
    script.data = static_cast<TuiTable *>(TuiRef::runScriptFile(pathString.get_data()));

    // Check if not loaded
    if (!script.data)
    {
        return false;
    }

    // Register functions if the script was successfully loaded
    TuiTable *table = static_cast<TuiTable *>(script.data);
    TuiFunction *func = nullptr;
    script.setContext = Tui_ScriptManager::set_local_context;
    if (func = table->getFunction(SCRIPT_FUNC_CREATE.get_data()))
    {
        script.create = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_DESTROY.get_data()))
    {
        script.destroy = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_UNLOAD.get_data()))
    {
        script.unload = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_LOAD.get_data()))
    {
        script.load = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_ENABLE.get_data()))
    {
        script.enable = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_DISABLE.get_data()))
    {
        script.disable = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_FRAME_UPDATE.get_data()))
    {
        script.frameUpdate = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_FIXED_UPDATE.get_data()))
    {
        script.fixedUpdate = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_FINALIZE.get_data()))
    {
        script.finalize = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_RENDER.get_data()))
    {
        script.render = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }
    if (func = table->getFunction(SCRIPT_FUNC_EVENT.get_data()))
    {
        script.event = [func]()
        {
            TuiLocal<TuiTable> args;
            func->call(args.get(), nullptr, nullptr, nullptr);
        };
    }

    // Successfully loaded the script
    return true;
}

void Minty::Tui_ScriptManager::set_local_context(Script &script, ScriptLocalContext const &context)
{
    // Get the table
    TuiTable *table = static_cast<TuiTable *>(script.data);

    // Set the local context in the table
    if (table)
    {
        TuiLocal<TuiTable> contextTable;
        TuiLocal<TuiNumber> entityNumberLocal(static_cast<Int64>(context.entity));
        contextTable->set("entity", entityNumberLocal);
        table->set("this", contextTable);
    }
}

void Minty::Tui_ScriptManager::set_global_context(ScriptGlobalContext const &context)
{
    // Get the root table
    TuiTable *rootTable = Tui::getRootTable();

    if (rootTable)
    {
        // Get context table if it exists, otherwise create a new one
        TuiTable *contextTable = nullptr;
        if (!rootTable->hasKey("context"))
        {
            // Create a new table and release it after setting it in the root table
            TuiLocal<TuiTable> contextTableLocal;
            rootTable->set("context", contextTableLocal);
        }

        // No need to release this since it is reference
        contextTable = static_cast<TuiTable *>(rootTable->get("context"));

        // Set the timestep values in the context table
        TuiLocal<TuiNumber> deltaTimeNumber(static_cast<Float64>(context.frameDeltaTime));
        TuiLocal<TuiNumber> fixedDeltaTimeNumber(static_cast<Float64>(context.fixedDeltaTime));
        TuiLocal<TuiNumber> totalTimeNumber(static_cast<Float64>(context.totalTime));
        contextTable->set("frameDeltaTime", deltaTimeNumber);
        contextTable->set("fixedDeltaTime", fixedDeltaTimeNumber);
        contextTable->set("totalTime", totalTimeNumber);
    }
}
