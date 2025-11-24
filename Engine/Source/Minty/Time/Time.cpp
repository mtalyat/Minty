#include "pch.h"
#include "Time.h"
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

String Minty::Time::format(TimePoint const time)
{
    // Fix the time_point construction issue
    auto nanoseconds = std::chrono::nanoseconds(time);
    auto duration = std::chrono::duration_cast<std::chrono::system_clock::duration>(nanoseconds);
    auto timePoint = std::chrono::system_clock::time_point(duration);
    
    auto timeT = std::chrono::system_clock::to_time_t(timePoint);
    std::stringstream ss;
    std::tm timeStruct;
#ifdef MINTY_WINDOWS
    localtime_s(&timeStruct, &timeT);
#else
    #error "Platform not supported"
#endif
    ss << std::put_time(&timeStruct, "%Y-%m-%d %H:%M:%S");
    
    // Use the const char* constructor for your String class
    return String(ss.str().c_str());
}

String Minty::Time::get_timestamp()
{
    return format(get_system_time());
}