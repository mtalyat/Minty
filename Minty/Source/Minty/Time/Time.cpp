#include "pch.h"
#include "Time.h"
#include "Minty/Core/Format.h"
#include <thread>

using namespace Minty;

TimePoint Minty::Time::now()
{
	return std::chrono::steady_clock::now();
}

Float Minty::Time::calculate_duration_seconds(TimePoint const start, TimePoint const end)
{
	Size frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

	// change from nanoseconds to seconds
	return frameTime / 1000000000.0f;
}

String Minty::Time::timestamp()
{
	auto now = std::chrono::system_clock::now();
	auto current_time = std::chrono::zoned_time(std::chrono::current_zone(), now);
	return String(std::format("{:%Y-%m-%d %H:%M:%S}", current_time).c_str());
}

void Minty::Time::sleep(TimeElapsed const time)
{
	std::this_thread::sleep_for(std::chrono::nanoseconds(time));
}
