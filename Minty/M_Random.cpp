#include "pch.h"
#include "M_Random.h"
#include <stdlib.h>
#include <time.h>

namespace minty
{
	MINTY_API void random_seed(unsigned int const seed)
	{
		srand(seed);
	}

	MINTY_API void random_seed_time()
	{
		srand(static_cast<unsigned int>(time(0)));
	}

	MINTY_API int random_int()
	{
		return rand();
	}

	MINTY_API float random_float()
	{
		return float(rand()) / float(RAND_MAX);
	}

	MINTY_API int random_range(int const min, int const max)
	{
		return rand() % (max - min) + min;
	}

	MINTY_API int random_range(int const max)
	{
		return rand() % max;
	}

	MINTY_API float random_range(float const min, float const max)
	{
		return float(rand()) / float(RAND_MAX) * (max - min) + min;
	}

	MINTY_API float random_range(float const max)
	{
		return float(rand()) / float(RAND_MAX) * max;
	}

	MINTY_API int random_direction()
	{
		return (rand() % 2) * 2 - 1;
	}

	MINTY_API bool random_chance(int const value, int const range)
	{
		return (rand() % range) < value;
	}
}