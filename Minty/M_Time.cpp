#include "pch.h"
#include "M_Time.h"

namespace minty
{
	float Time::s_deltaTime = 0.0f;

	long Time::s_deltaTimeRaw = 0;

	float Time::s_fixedDeltaTime = 0.0f;

	long Time::s_fixedDeltaTimeRaw = 0;

	float Time::s_timeScale = 1.0f;

	void Time::setDeltaTime(elapsed_t const time)
	{
		// only set if not zero
		if (time > 0)
		{
			s_deltaTimeRaw = time;
			s_deltaTime = time / static_cast<float>(ONE_SECOND);
		}
		else
		{
			s_deltaTimeRaw = 1;
			s_deltaTime = 1.0f / static_cast<float>(ONE_SECOND);
		}
	}
	
	void Time::setFixedDeltaTime(elapsed_t const time)
	{
		// only set if not zero
		if (time > 0)
		{
			s_fixedDeltaTimeRaw = time;
			s_fixedDeltaTime = time / static_cast<float>(ONE_SECOND);
		}
		else
		{
			s_fixedDeltaTimeRaw = 1;
			s_fixedDeltaTime = 1.0f / static_cast<float>(ONE_SECOND);
		}
	}
}
