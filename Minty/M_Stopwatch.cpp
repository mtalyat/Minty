#include "pch.h"
#include "M_Stopwatch.h"
#include "M_Text.h"
#include <iostream>

constexpr long ONE_HOUR_IN_MS = 3600000;
constexpr long ONE_MINUTE_IN_MS = 60000;
constexpr long ONE_SECOND_IN_MS = 1000;

namespace minty
{
	inline Stopwatch::Stopwatch()
		: m_start(clock())
		, m_elapsed(0)
		, m_running(false) {}

	void Stopwatch::start()
	{
		if (!m_running)
		{
			m_start = clock();

			m_running = true;
		}
	}

	void Stopwatch::stop()
	{
		if (m_running)
		{
			m_elapsed += clock() - m_start;

			m_running = false;
		}
	}

	void Stopwatch::reset()
	{
		m_start = clock();
		m_elapsed = 0;
	}

	long Stopwatch::elapsed() const
	{
		// if running, get until now, otherwise until stop
		if (m_running)
		{
			return m_elapsed + (clock() - m_start);
		}
		else
		{
			return m_elapsed;
		}
	}

	std::string const Stopwatch::toString() const
	{
		// convert to seconds, minutes, and hours
		long ms = elapsed();

		long hours = ms / ONE_HOUR_IN_MS;
		ms -= hours * ONE_HOUR_IN_MS;
		long minutes = ms / ONE_MINUTE_IN_MS;
		ms -= minutes * ONE_MINUTE_IN_MS;
		long seconds = ms / ONE_SECOND_IN_MS;
		ms -= seconds * ONE_SECOND_IN_MS;

		// print in format: HH:MM:SS:mmm

		std::string temp = std::format("{0}:{1}:{2}.{3}",
			text_pad_left(std::to_string(hours), 2, '0'),
			text_pad_left(std::to_string(minutes), 2, '0'),
			text_pad_left(std::to_string(seconds), 2, '0'),
			text_pad_left(std::to_string(ms), 3, '0'));

		return temp;
	}
}
