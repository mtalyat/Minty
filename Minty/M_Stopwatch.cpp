#include "pch.h"
#include "M_Stopwatch.h"
#include "M_Text.h"
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

	void Stopwatch::reset(elapsed_t const mod)
	{
		m_elapsed %= mod;
		m_start = NOW();
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

	void Stopwatch::setElapsed(elapsed_t const elapsed)
	{
		// set elapsed time
		m_elapsed = elapsed;

		// if running, restart clock
		if (m_running)
		{
			m_start = NOW();
		}
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
		elapsed_t milli = ns / ONE_MILLISECOND;
		ns -= milli * ONE_MILLISECOND;

		// print in format: HH:MM:SS:nnnnnn

		std::string temp = std::format("{0}:{1}:{2}.{3}",
			text_pad_left(std::to_string(hours), 2, '0'),
			text_pad_left(std::to_string(minutes), 2, '0'),
			text_pad_left(std::to_string(seconds), 2, '0'),
			text_pad_left(std::to_string(ns), 6, '0'));

		return temp;
	}
}
