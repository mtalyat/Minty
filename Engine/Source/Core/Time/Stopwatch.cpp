#include "pch.h"
#include "Stopwatch.h"
#include "Time.h"
#include "Core/Constant/Convert.h"
#include "Core/Debug/Debug.h"
#include <format>

using namespace Minty;

Stopwatch::Stopwatch()
	: m_start(Time::get_time())
	, m_elapsed(0)
	, m_running(false) {
}

void Stopwatch::start()
{
	if (!m_running)
	{
		m_running = true;

		m_start = Time::get_time();
	}
}

void Stopwatch::stop()
{
	if (m_running)
	{
		m_elapsed += Time::get_time() - m_start;

		m_running = false;
	}
}

void Stopwatch::reset()
{
	m_elapsed = 0;
	m_start = Time::get_time();
}

Size Stopwatch::lap(TimePoint const mod)
{
	MINTY_ASSERT(mod > 0, ErrorCodeEnum::Argument_ExpectedAboveZero);

	TimePoint time = get_elapsed();
	TimePoint laps = time / mod;

	m_elapsed = time - laps * mod;
	m_start = Time::get_time();

	return laps;
}

TimePoint Stopwatch::get_elapsed() const
{
	// if running, get until now, otherwise until stop
	if (m_running)
	{
		return m_elapsed + Time::get_time() - m_start;
	}
	else
	{
		return m_elapsed;
	}
}

Float Stopwatch::get_elapsed_s() const
{
	return get_elapsed() / static_cast<Float>(ONE_SECOND);
}

String Minty::Stopwatch::get_elapsed_string() const
{
	// convert to seconds, minutes, and hours
	TimePoint ns = get_elapsed();

	// Should be big enoughfor any reasonable time span, and avoids heap allocation for the string formatting
	Char buffer[128];

	TimePoint hours = ns / ONE_HOUR;
	ns -= hours * ONE_HOUR;
	TimePoint minutes = ns / ONE_MINUTE;
	ns -= minutes * ONE_MINUTE;
	TimePoint seconds = ns / ONE_SECOND;
	ns -= seconds * ONE_SECOND;

	// print in format: HH:MM:SS:nnnnnn
	std::format_to(buffer, "{}:{}:{}.{}",
		hours,
		minutes,
		seconds,
		ns / 100);
	return String(buffer);
}
