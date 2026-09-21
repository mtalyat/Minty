#include "Tui_ScriptManager.hpp"
#include "Script/Script/Script.hpp"
#include "Script/Constant/Function.hpp"
#include "Script/Script/ScriptLocalContext.hpp"
#include "Script/Script/ScriptGlobalContext.hpp"
#include "Script/Constant/Script.hpp"

#include "Input/Key/Key.hpp"
#include "Input/Key/KeyAction.hpp"
#include "Input/Key/KeyModifier.hpp"
#include "Input/Mouse/MouseButton.hpp"
#include "Input/Mouse/MouseAction.hpp"

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

template<typename Enum>
static TuiTable* populate_enum(TuiTable* const table, const char* const name, Int const count)
{
    String str;

    TuiTable* enumTable = table->getOrCreateTable(name);

    for(Int i = 0; i < count; i++)
    {
        str = Parser<Enum>::to_string(static_cast<Enum>(i));
        if (str.get_length() > 0)
        {
            enumTable->set(str.get_data(), TuiLocal<TuiNumber>(i));
        }
    }

    return enumTable;
}

template<typename Enum>
static TuiTable* populate_enum_flags(TuiTable* const table, const char* const name, Int const count)
{
    String str;

    TuiTable* enumTable = table->getOrCreateTable(name);

    for(Int j, i = 0; i < count; i++)
    {
        j = static_cast<Int>(1) << i;
        str = Parser<Enum>::to_string(static_cast<Enum>(j));
        if (str.get_length() > 0)
        {
            enumTable->set(str.get_data(), TuiLocal<TuiNumber>(j));
        }
    }

    return enumTable;
}

void Minty::Tui_ScriptManager::initialize()
{
    // Get the root table
    TuiTable *rootTable = Tui::getRootTable();

    if (rootTable)
    {
        // Initialize the global namespace if it doesn't exist
        TuiTable* globalNamespace = rootTable->getOrCreateTable(SCRIPT_NAMESPACE_GLOBAL);

        // Create each necessary global namespace table
        // Initialize the input namespace variables, types, functions, enums, etc. for each namespace

        // Time
        TuiTable* timeNamespace = globalNamespace->getOrCreateTable(SCRIPT_NAMESPACE_TIME);
        timeNamespace->set(SCRIPT_VAR_TIME_FRAME_DELTA, TuiLocal<TuiNumber>(0.0));
        timeNamespace->set(SCRIPT_VAR_TIME_FRAME, TuiLocal<TuiNumber>(0.0));
        timeNamespace->set(SCRIPT_VAR_TIME_FIXED_DELTA, TuiLocal<TuiNumber>(0.0));
        timeNamespace->set(SCRIPT_VAR_TIME_TOTAL, TuiLocal<TuiNumber>(0.0));

        // Input
        TuiTable* inputNamespace = globalNamespace->getOrCreateTable(SCRIPT_NAMESPACE_INPUT);
        populate_enum<KeyEnum>(inputNamespace, SCRIPT_ENUM_INPUT_KEY, static_cast<Int>(KeyEnum::Count));
        populate_enum<KeyActionEnum>(inputNamespace, SCRIPT_ENUM_INPUT_KEY_ACTION, static_cast<Int>(KeyActionEnum::Count));
        populate_enum_flags<KeyModifierFlagsEnum>(inputNamespace, SCRIPT_ENUM_INPUT_KEY_MODIFIER, static_cast<Int>(KeyModifierFlagsEnum::Count));
        populate_enum<MouseButtonEnum>(inputNamespace, SCRIPT_ENUM_INPUT_MOUSE_BUTTON, static_cast<Int>(MouseButtonEnum::Count));
        populate_enum<MouseActionEnum>(inputNamespace, SCRIPT_ENUM_INPUT_MOUSE, static_cast<Int>(MouseActionEnum::Count));
        
        inputNamespace->setFunction(SCRIPT_FUNC_INPUT_REGISTER_KEY_PRESS, TuiLocal<TuiFunction>([](TuiTable* args, TuiRef* existingResult, TuiFunctionCallData* incomingCallData, TuiDebugInfo* callingDebugInfo) -> TuiRef*
        {
            MINTY_NOT_IMPLEMENTED();
            return nullptr;
        }));
        inputNamespace->setFunction(SCRIPT_FUNC_INPUT_REGISTER_KEY_RELEASE, TuiLocal<TuiFunction>([](TuiTable* args, TuiRef* existingResult, TuiFunctionCallData* incomingCallData, TuiDebugInfo* callingDebugInfo) -> TuiRef*
        {
            MINTY_NOT_IMPLEMENTED();
            return nullptr;
        }));
    }
}

void Minty::Tui_ScriptManager::set_local_context(Script &script, ScriptLocalContext const &context)
{
    // Get the table
    TuiTable *table = static_cast<TuiTable *>(script.data);

    // Set the local context in the table
    if (table)
    {
        // Get context table if it exists, otherwise create a new one
        TuiTable* localNamespace = table->getOrCreateTable(SCRIPT_NAMESPACE_LOCAL);

        // Create and populate each namespace

        // Entity
        TuiLocal<TuiNumber> entityNumberLocal(static_cast<Int64>(context.entity));
        localNamespace->set(SCRIPT_VAR_LOCAL_ENTITY, entityNumberLocal);
    }
}

void Minty::Tui_ScriptManager::set_global_context(ScriptGlobalContext const &context)
{
    // Get the root table
    TuiTable *rootTable = Tui::getRootTable();

    if (rootTable)
    {
        // Get context table if it exists, otherwise create a new one
        TuiTable *globalNamespace = rootTable->getOrCreateTable(SCRIPT_NAMESPACE_GLOBAL);

        // Create and populate each namespace

        // Time namespace
        TuiTable* timeNamespace = globalNamespace->getOrCreateTable(SCRIPT_NAMESPACE_TIME);
        
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
