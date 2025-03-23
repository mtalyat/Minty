#include "pch.h"
#include "Stopwatch.h"
#include "Minty/Time/Time.h"

using namespace Minty;

Stopwatch::Stopwatch()
	: m_start(Time::now())
	, m_elapsed(0)
	, m_running(false) {
}

void Stopwatch::start()
{
	if (!m_running)
	{
		m_running = true;

		m_start = Time::now();
	}
}

void Stopwatch::stop()
{
	if (m_running)
	{
		m_elapsed += std::chrono::duration_cast<std::chrono::nanoseconds>(Time::now() - m_start).count();

		m_running = false;
	}
}

void Stopwatch::reset()
{
	m_elapsed = 0;
	m_start = Time::now();
}

Size Stopwatch::lap(TimeElapsed const mod)
{
	MINTY_ASSERT(mod > 0, "Mod must be greater than zero.");

	TimeElapsed time = get_elapsed();
	TimeElapsed laps = time / mod;

	m_elapsed = time - laps * mod;
	m_start = Time::now();

	return laps;
}

TimeElapsed Stopwatch::get_elapsed() const
{
	// if running, get until now, otherwise until stop
	if (m_running)
	{
		return m_elapsed + std::chrono::duration_cast<std::chrono::nanoseconds>(Time::now() - m_start).count();
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
	TimeElapsed ns = get_elapsed();

	TimeElapsed hours = ns / ONE_HOUR;
	ns -= hours * ONE_HOUR;
	TimeElapsed minutes = ns / ONE_MINUTE;
	ns -= minutes * ONE_MINUTE;
	TimeElapsed seconds = ns / ONE_SECOND;
	ns -= seconds * ONE_SECOND;

	// print in format: HH:MM:SS:nnnnnn
	return String(std::format("{}:{}:{}.{}",
		std::to_string(hours),
		std::to_string(minutes),
		std::to_string(seconds),
		std::to_string(ns / 100)).c_str());
}
