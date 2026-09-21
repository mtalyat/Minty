#include "Tui_ScriptManager.hpp"
#include "Script/Script/Script.hpp"
#include "Script/Constant/Function.hpp"
#include "Script/Script/ScriptLocalContext.hpp"
#include "Script/Script/ScriptGlobalContext.hpp"
#include "Script/Constant/Script.hpp"

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
        contextTable->set(SCRIPT_VAR_LOCAL_ENTITY, entityNumberLocal);
        table->set(SCRIPT_NAMESPACE_LOCAL, contextTable);
    }
}

void Minty::Tui_ScriptManager::set_global_context(ScriptGlobalContext const &context)
{
    // Get the root table
    TuiTable *rootTable = Tui::getRootTable();

    if (rootTable)
    {
        // Get context table if it exists, otherwise create a new one
        TuiTable *globalNamespace = nullptr;
        if (!rootTable->hasKey(SCRIPT_NAMESPACE_GLOBAL))
        {
            // Create a new table and release it after setting it in the root table
            TuiLocal<TuiTable> contextTableLocal;
            rootTable->set(SCRIPT_NAMESPACE_GLOBAL, contextTableLocal);
        }

        // No need to release this since it is reference
        globalNamespace = static_cast<TuiTable *>(rootTable->get(SCRIPT_NAMESPACE_GLOBAL));

        // Create and populate each namespace

        // Time namespace
        if (!globalNamespace->hasKey(SCRIPT_NAMESPACE_TIME))
        {
            TuiLocal<TuiTable> timeNamespace;
            globalNamespace->set(SCRIPT_NAMESPACE_TIME, timeNamespace);
        }
        TuiTable* timeNamespace = static_cast<TuiTable *>(globalNamespace->get(SCRIPT_NAMESPACE_TIME));
        globalNamespace->set(SCRIPT_NAMESPACE_TIME, timeNamespace);
        
        TuiLocal<TuiNumber> deltaTimeNumber(static_cast<Float64>(context.frameDeltaTime));
        TuiLocal<TuiNumber> fixedDeltaTimeNumber(static_cast<Float64>(context.fixedDeltaTime));
        TuiLocal<TuiNumber> totalTimeNumber(static_cast<Float64>(context.totalTime));
        TuiLocal<TuiNumber> frameNumber(static_cast<Float64>(context.frameCount));
        timeNamespace->set(SCRIPT_VAR_TIME_FRAME_DELTA, deltaTimeNumber);
        timeNamespace->set(SCRIPT_VAR_TIME_FRAME, frameNumber);
        timeNamespace->set(SCRIPT_VAR_TIME_FIXED_DELTA, fixedDeltaTimeNumber);
        timeNamespace->set(SCRIPT_VAR_TIME_TOTAL, totalTimeNumber);
    }
}
