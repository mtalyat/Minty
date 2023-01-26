#include "pch.h"
#include "M_Time.h"
#include <ctime>

namespace minty
{
	float Time::s_deltaTime = 0.0f;

	long Time::s_deltaTimeRaw = 0;

	float Time::s_timeScale = 1.0f;

	inline float Time::deltaTimeUnscaled() { return s_deltaTime; }

	inline float Time::deltaTime() { return s_deltaTime * s_timeScale; }

	inline clock_t Time::deltaTimeRaw() { return s_deltaTimeRaw; }

	void Time::setDeltaTime(long const time)
	{
		s_deltaTimeRaw = time;
		s_deltaTime = time / 1000.0f;
	}

	inline float Time::timeScale() { return s_timeScale; }

	inline void Time::setTimeScale(float const scale) { s_timeScale = scale; }

	inline clock_t minty::Time::time() { return clock(); }
}
