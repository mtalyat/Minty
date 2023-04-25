#include "pch.h"
#include "M_Stopwatch.h"
#include "M_String.h"
#include <iostream>

#define NOW() std::chrono::steady_clock::now()

namespace minty
{
	inline Stopwatch::Stopwatch()
		: m_start(NOW())
		, m_elapsed(0)
		, m_running(false) {}

	void Stopwatch::start()
	{
		if (!m_running)
		{
			m_running = true;

			m_start = NOW();
		}
	}

	void Stopwatch::stop()
	{
		if (m_running)
		{
			m_elapsed += std::chrono::duration_cast<std::chrono::nanoseconds>(NOW() - m_start).count();

			m_running = false;
		}
	}

	void Stopwatch::reset()
	{
		m_elapsed = 0;
		m_start = NOW();
	}

	elapsed_t Stopwatch::lap(elapsed_t const mod)
	{
		// if mod is 0, do nothing
		if (!mod)
		{
			return 0;
		}

		elapsed_t time = elapsed();

		elapsed_t laps = time / mod;

		m_elapsed = time - laps * mod;
		m_start = NOW();

		return laps;
	}

	elapsed_t Stopwatch::elapsed() const
	{
		// if running, get until now, otherwise until stop
		if (m_running)
		{
			return m_elapsed + std::chrono::duration_cast<std::chrono::nanoseconds>(NOW() - m_start).count();
		}
		else
		{
			return m_elapsed;
		}
	}

	elapsed_t Stopwatch::elapsed_ms() const
	{
		return elapsed() / ONE_MILLISECOND;
	}

	float Stopwatch::elapsed_s() const
	{
		return elapsed() / static_cast<float>(ONE_SECOND);
	}

	std::string const Stopwatch::toString() const
	{
		// convert to seconds, minutes, and hours
		elapsed_t ns = elapsed();

		elapsed_t hours = ns / ONE_HOUR;
		ns -= hours * ONE_HOUR;
		elapsed_t minutes = ns / ONE_MINUTE;
		ns -= minutes * ONE_MINUTE;
		elapsed_t seconds = ns / ONE_SECOND;
		ns -= seconds * ONE_SECOND;

		// print in format: HH:MM:SS:nnnnnn

		std::string temp = std::format("{0}:{1}:{2}.{3}",
			string_pad_left(std::to_string(hours), 2, '0'),
			string_pad_left(std::to_string(minutes), 2, '0'),
			string_pad_left(std::to_string(seconds), 2, '0'),
			string_pad_left(std::to_string(ns / 100), 7, '0'));

		return temp;
	}
}
