#include "pch.h"
#include "M_Time.h"
#include <ctime>

namespace minty
{
	float Time::s_deltaTime = 0.0f;

	long Time::s_deltaTimeRaw = 0;

	float Time::s_timeScale = 1.0f;

	void Time::setDeltaTime(long const time)
	{
		// only set if not zero
		if (time)
		{
			s_deltaTimeRaw = time;
			s_deltaTime = time / 1000.0f;
		}
		else {
			s_deltaTimeRaw = 1;
			s_deltaTime = 1.0f / 1000.0f;
		}
	}
}
