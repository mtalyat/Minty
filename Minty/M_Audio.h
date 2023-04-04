#pragma once

#include "M_Object.h"

namespace minty
{
	class Audio
		: public Object
	{
	private:
		unsigned char m_volume;

	public:
		Audio();

		virtual ~Audio() {}

		void setVolume(unsigned char const volume) { m_volume = volume; }

		constexpr unsigned char getVolume() const { return m_volume; }
	};
}