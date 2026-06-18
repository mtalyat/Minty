#include "pch.h"
#include "Debug.h"
#include "Core/Log/Logger.h"
#include "Core/Log/LoggerInfo.h"
#include "Core/Data/StringBuilder.h"
#include <filesystem>
#include <iostream>

#ifdef MINTY_WINDOWS
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "Dbghelp.lib")
#endif

using namespace Minty;

SeverityFlagsEnum Debug::s_flags = SeverityFlagsEnum::Default;
Logger *Debug::sp_logger = nullptr;

void Minty::Debug::set_flags(SeverityFlagsEnum const flags)
{
    MINTY_ASSERT(sp_logger != nullptr, ErrorCodeEnum::Object_NotInitialized);

    // Set the debug flags
    s_flags = flags;

    // Set the logger's enabled levels based on the flags
    sp_logger->set_enabled_levels(flags);
}

void Minty::Debug::initialize(SeverityFlagsEnum const flags)
{
    MINTY_ASSERT(sp_logger == nullptr, ErrorCodeEnum::Object_AlreadyInitialized);

    LoggerInfo info{};

    // convert debug flags to log levels
    info.enabledLevels = flags;

    sp_logger = new Logger(info);

    set_flags(flags);
}

void Minty::Debug::dispose()
{
    MINTY_ASSERT(sp_logger != nullptr, ErrorCodeEnum::Object_NotInitialized);

    delete sp_logger;
    sp_logger = nullptr;
}

void Minty::Debug::log(SeverityFlagsEnum const level, Char const* const message)
{
    SeverityFlagsEnum const logLevel = level;
    if (sp_logger)
    {
        sp_logger->log(logLevel, message);
    }
    else
    {
        Logger::print(logLevel, message);
    }
}

void Minty::Debug::log(SeverityFlagsEnum const level, ErrorCodeEnum const errorCode)
{
    Char const* const message = get_error_message(errorCode);
    log(level, message);
}

void Minty::Debug::log(SeverityFlagsEnum const level, ErrorCodeEnum const errorCode, Char const* const message)
{
    StringBuilder builder;
    builder.append(get_error_message(errorCode));
    builder.append(' ');
    builder.append('\"');
    builder.append(message);
    builder.append('\"');
    log(level, builder.get_data());
}

void Minty::Debug::log(SeverityFlagsEnum const level, ErrorCodeEnum const errorCode, WInt const value)
{
    StringBuilder builder;
    builder.append(get_error_message(errorCode));
    builder.append(' ');
    builder.append('\"');
    builder.append(std::to_string(value).c_str());
    builder.append('\"');
    log(level, builder.get_data());
}

void Minty::Debug::log(SeverityFlagsEnum const level, ErrorCodeEnum const errorCode, WUInt const value)
{
    StringBuilder builder;
    builder.append(get_error_message(errorCode));
    builder.append(' ');
    builder.append('\"');
    builder.append(std::to_string(value).c_str());
    builder.append('\"');
    log(level, builder.get_data());
}

void Minty::Debug::log(SeverityFlagsEnum const level, ErrorCodeEnum const errorCode, WFloat const value)
{
    StringBuilder builder;
    builder.append(get_error_message(errorCode));
    builder.append(' ');
    builder.append('\"');
    builder.append(std::to_string(value).c_str());
    builder.append('\"');
    log(level, builder.get_data());
}

void Minty::Debug::log_stack_trace()
{
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
