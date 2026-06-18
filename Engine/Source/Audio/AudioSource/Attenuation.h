#pragma once

/**
 * @file Attenuation.h
 * @brief Header file defining the Attenuation enumeration.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.h"
#include "Core/Type/Enum.h"

namespace Minty
{
	/**
	 * @brief Determines how spatial audio scales based on the distance from the source to the listener.
	 */
	enum class AttenuationEnum
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

		Count,

		/**
		 * @brief Default attenuation mode, set to LinearDistance.
		 */
		Default = LinearDistance,
	};

	MINTY_ENABLE_ENUM_OPERATORS(AttenuationEnum)

	struct Attenuation
	{
		AttenuationEnum type;

		constexpr Attenuation() : type(AttenuationEnum::Default) {}
		constexpr Attenuation(AttenuationEnum const type) : type(type) {}
		constexpr operator AttenuationEnum() const { return type; }
	};

	template<>
	struct Parser<AttenuationEnum>
	{
		static Bool parse(StringView const str, AttenuationEnum &value);
		static String to_string(AttenuationEnum const &value);
	};

	template<>
	struct Parser<Attenuation>
	{
		static Bool parse(StringView const str, Attenuation &value) { return Parser<AttenuationEnum>::parse(str, value.type); }
		static String to_string(Attenuation const &value) { return Parser<AttenuationEnum>::to_string(value.type); }
	};
}
