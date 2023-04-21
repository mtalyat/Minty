#pragma once

#include "M_Object.h"

namespace minty
{
	/// <summary>
	/// A generic object that holds audio information.
	/// </summary>
	class Audio
		: public Object
	{
	private:
		// the individual volume of this audio
		unsigned char m_volume;

	public:
		/// <summary>
		/// Creates a new Audio at max volume.
		/// </summary>
		Audio();

		virtual ~Audio() {}

		/// <summary>
		/// Sets the volume of this Audio.
		/// </summary>
		/// <param name="volume">The new volume.</param>
		void setVolume(unsigned char const volume) { m_volume = volume; }

		/// <summary>
		/// Gets the volume of this Audio.
		/// </summary>
		/// <returns>The volume of this Audio.</returns>
		constexpr unsigned char volume() const { return m_volume; }
	};
}