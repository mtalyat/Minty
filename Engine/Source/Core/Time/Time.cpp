#include "pch.hpp"
#include "Time.hpp"
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace Minty;

TimePoint Minty::Time::get_time()
{
    static auto const start = std::chrono::high_resolution_clock::now();
    auto const now = std::chrono::high_resolution_clock::now();
    return static_cast<TimePoint>(std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count());
}

TimePoint Minty::Time::get_system_time()
{
    auto now = std::chrono::system_clock::now();
    auto epoch = now.time_since_epoch();
    return static_cast<TimePoint>(std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count());
}

void Minty::Time::format(TimePoint const time, Char *const buffer, Size const bufferSize)
{
    auto nanoseconds = std::chrono::nanoseconds(time);
    auto duration = std::chrono::duration_cast<std::chrono::system_clock::duration>(nanoseconds);
    auto timePoint = std::chrono::system_clock::time_point(duration);
    
    auto timeT = std::chrono::system_clock::to_time_t(timePoint);
    std::tm timeStruct;
#ifdef MINTY_WINDOWS
    localtime_s(&timeStruct, &timeT);
#else
    #error "Platform not supported"
#endif
    std::strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", &timeStruct);
}

String Minty::Time::get_timestamp()
{
    Char buffer[64] = {0};
    format(get_system_time(), buffer, sizeof(buffer));
    return String(buffer);
}