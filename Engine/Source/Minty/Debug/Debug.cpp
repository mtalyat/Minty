#include "pch.h"
#include "Debug.h"
#include "Minty/Core/Macro.h"
#include "Minty/Data/String.h"
#include "Minty/Log/Logger.h"
#include "Minty/Log/LoggerInfo.h"
#include <filesystem>

#ifdef MINTY_WINDOWS
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "Dbghelp.lib")
#endif

using namespace Minty;

DebugFlags Debug::s_flags = DebugFlags::Default;
Logger *Debug::sp_logger = nullptr;

void Minty::Debug::set_flags(DebugFlags const flags)
{
    MINTY_ASSERT(sp_logger != nullptr, ErrorCode::Object_NotInitialized);

    // Set the debug flags
    s_flags = flags;

    // Set the logger's enabled levels based on the flags
    LogLevel levels = LogLevel::None;
    if ((flags & DebugFlags::Debug) != DebugFlags::None)
    {
        levels = levels | LogLevel::Debug;
    }
    if ((flags & DebugFlags::Info) != DebugFlags::None)
    {
        levels = levels | LogLevel::Info;
    }
    if ((flags & DebugFlags::Message) != DebugFlags::None)
    {
        levels = levels | LogLevel::Message;
    }
    if ((flags & DebugFlags::Warning) != DebugFlags::None)
    {
        levels = levels | LogLevel::Warning;
    }
    if ((flags & DebugFlags::Error) != DebugFlags::None)
    {
        levels = levels | LogLevel::Error;
    }
    if ((flags & DebugFlags::Critical) != DebugFlags::None)
    {
        levels = levels | LogLevel::Critical;
    }
    sp_logger->set_enabled_levels(levels);
}

void Minty::Debug::initialize(DebugFlags const flags)
{
    MINTY_ASSERT(sp_logger == nullptr, ErrorCode::Object_AlreadyInitialized);

    LoggerInfo info{};

    // convert debug flags to log levels
    if ((flags & DebugFlags::Debug) != DebugFlags::None)
    {
        info.enabledLevels = info.enabledLevels | LogLevel::Debug;
    }
    if ((flags & DebugFlags::Info) != DebugFlags::None)
    {
        info.enabledLevels = info.enabledLevels | LogLevel::Info;
    }
    if ((flags & DebugFlags::Message) != DebugFlags::None)
    {
        info.enabledLevels = info.enabledLevels | LogLevel::Message;
    }
    if ((flags & DebugFlags::Warning) != DebugFlags::None)
    {
        info.enabledLevels = info.enabledLevels | LogLevel::Warning;
    }
    if ((flags & DebugFlags::Error) != DebugFlags::None)
    {
        info.enabledLevels = info.enabledLevels | LogLevel::Error;
    }
    if ((flags & DebugFlags::Critical) != DebugFlags::None)
    {
        info.enabledLevels = info.enabledLevels | LogLevel::Critical;
    }

    sp_logger = new Logger(info);

    set_flags(flags);
}

void Minty::Debug::dispose()
{
    MINTY_ASSERT(sp_logger != nullptr, ErrorCode::Object_NotInitialized);

    delete sp_logger;
    sp_logger = nullptr;
}

void Minty::Debug::log(LogLevel const level, StringView const message)
{
    if (sp_logger)
    {
        sp_logger->log(level, message);
    }
    else
    {
        Logger::print(level, message);
    }
}

void Minty::Debug::log(LogLevel const level, ErrorCode const errorCode)
{
    StringView const message = get_error_message(errorCode);
    log(level, message);
}

void Minty::Debug::log(LogLevel const level, ErrorCode const errorCode, StringView const message)
{
    StringView const errorMessage = get_error_message(errorCode);
    String const fullMessage = String(errorMessage) + message;
    log(level, fullMessage);
}

void Minty::Debug::log_stack_trace()
{
    if ((s_flags & DebugFlags::StackTrace) == DebugFlags::None)
    {
        return; // Stack trace logging is disabled
    }

#ifdef MINTY_WINDOWS
    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();

    CONTEXT context;
    memset(&context, 0, sizeof(CONTEXT));
    context.ContextFlags = CONTEXT_FULL;
    RtlCaptureContext(&context);

    SymInitialize(process, NULL, TRUE);

    STACKFRAME64 stackframe;
    memset(&stackframe, 0, sizeof(STACKFRAME64));
    DWORD machineType;

#ifdef _M_IX86
    machineType = IMAGE_FILE_MACHINE_I386;
    stackframe.AddrPC.Offset = context.Eip;
    stackframe.AddrPC.Mode = AddrModeFlat;
    stackframe.AddrFrame.Offset = context.Ebp;
    stackframe.AddrFrame.Mode = AddrModeFlat;
    stackframe.AddrStack.Offset = context.Esp;
    stackframe.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
    machineType = IMAGE_FILE_MACHINE_AMD64;
    stackframe.AddrPC.Offset = context.Rip;
    stackframe.AddrPC.Mode = AddrModeFlat;
    stackframe.AddrFrame.Offset = context.Rsp;
    stackframe.AddrFrame.Mode = AddrModeFlat;
    stackframe.AddrStack.Offset = context.Rsp;
    stackframe.AddrStack.Mode = AddrModeFlat;
#elif _M_IA64
    machineType = IMAGE_FILE_MACHINE_IA64;
    stackframe.AddrPC.Offset = context.StIIP;
    stackframe.AddrPC.Mode = AddrModeFlat;
    stackframe.AddrFrame.Offset = context.IntSp;
    stackframe.AddrFrame.Mode = AddrModeFlat;
    stackframe.AddrBStore.Offset = context.RsBSP;
    stackframe.AddrBStore.Mode = AddrModeFlat;
    stackframe.AddrStack.Offset = context.IntSp;
    stackframe.AddrStack.Mode = AddrModeFlat;
#endif

    for (Int i = 0; i < 25; i++)
    {
        if (!StackWalk64(machineType, process, thread, &stackframe, &context, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL))
        {
            break;
        }

        if (stackframe.AddrPC.Offset == 0)
        {
            break;
        }

        Char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
        PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = MAX_SYM_NAME;

        DWORD64 displacement = 0;
        if (SymFromAddr(process, stackframe.AddrPC.Offset, &displacement, symbol))
        {
            // Get line number info
            IMAGEHLP_LINE64 line;
            DWORD dwDisplacement;
            memset(&line, 0, sizeof(line));
            line.SizeOfStruct = sizeof(line);

            if (SymGetLineFromAddr64(process, stackframe.AddrPC.Offset, &dwDisplacement, &line))
            {
                // Extract only the file name
                std::filesystem::path filePath(line.FileName);
                std::cout << symbol->Name << " at " << filePath.filename().string() << ":" << line.LineNumber << "\n";
            }
            else
            {
                std::cout << symbol->Name << " at 0x" << std::hex << stackframe.AddrPC.Offset << std::dec << "\n";
            }
        }
        else
        {
            std::cout << std::hex << stackframe.AddrPC.Offset << std::dec << "\n";
        }
    }

    SymCleanup(process);
#endif
}

void Minty::Debug::flush()
{
    // If there is a logger, flush it, otherwise flushing is a no-op
    if (sp_logger)
    {
        sp_logger->flush();
    }
}
