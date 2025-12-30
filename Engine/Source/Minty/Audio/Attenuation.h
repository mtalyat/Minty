#ifndef MINTY_AUDIO_ATTENUATION_H
#define MINTY_AUDIO_ATTENUATION_H

/**
 * @file Attenuation.h
 * @brief Header file defining the Attenuation enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines how spatial audio scales based on the distance from the source to the listener.
	 */
	enum class Attenuation
	{
		/**
		 * @brief No attenuation is applied. The sound is always at full volume.
		 */
		None,

		/**
		 * @brief The sound gets linearly quieter as the source approaches the listener.
		 */
		InverseDistance,

		/**
		 * @brief The sound gets linearly louder as the source approaches the listener.
		 */
		LinearDistance,

		/**
		 * @brief The sound gets exponentially louder as the source approaches the listener.
		 */
		ExponentialDistance,

		/**
		 * @brief Default attenuation mode, set to LinearDistance.
		 */
		Default = LinearDistance,
	};

	template<>
	struct Parser<Attenuation>
	{
		static Bool parse(StringView const str, Attenuation &value);
		static String to_string(Attenuation const &value);
	};
}

#endif // MINTY_AUDIO_ATTENUATION_H