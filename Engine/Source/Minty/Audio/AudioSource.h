#ifndef MINTY_AUDIO_AUDIOSOURCE_H
#define MINTY_AUDIO_AUDIOSOURCE_H

#include "Minty/Audio/Attenuation.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Math.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	/**
	 * @brief Holds the data for an audio source.
	 */
	class AudioSource
	{
		friend struct Serializer<AudioSource>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty AudioSource.
		 */
		AudioSource()
			: SerializableObject()
			, m_position(Float3(0.0f, 0.0f, 0.0f))
			, m_velocity(Float3(0.0f, 0.0f, 0.0f))
			, m_attenuation(Attenuation::LinearDistance)
			, m_attenuationRolloff(DEFAULT_AUDIO_ATTENUATION_ROLL_OFF)
			, m_minDistance(DEFAULT_AUDIO_MIN_DISTANCE)
			, m_maxDistance(DEFAULT_AUDIO_MAX_DISTANCE)
		{
		}

		/**
		 * @brief Creates a new AudioSource with the given parameters.
		 * @param position The position of the audio source in 3D space.
		 * @param velocity The velocity of the audio source in 3D space.
		 * @param attenuation The attenuation model used for distance-based volume reduction.
		 * @param attenuationRolloff The rolloff factor for attenuation calculation.
		 * @param minDistance The minimum distance at which attenuation begins.
		 * @param maxDistance The maximum distance at which attenuation is applied.
		 */
		AudioSource(Float3 const& position, Float3 const& velocity, Attenuation attenuation, Float attenuationRolloff, Float minDistance, Float maxDistance)
			: SerializableObject()
			, m_position(position)
			, m_velocity(velocity)
			, m_attenuation(attenuation)
			, m_attenuationRolloff(attenuationRolloff)
			, m_minDistance(minDistance)
			, m_maxDistance(maxDistance)
		{
		}

		~AudioSource() override
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the position of this audio source.
		 * @return The position.
		 */
		inline Float3 const& get_position() const { return m_position; }

		/**
		 * @brief Sets the position of this audio source.
		 * @param value The position.
		 */
		inline void set_position(Float3 const& value) { m_position = value; }

		/**
		 * @brief Gets the velocity of this audio source.
		 * @return The velocity.
		 */
		inline Float3 const& get_velocity() const { return m_velocity; }

		/**
		 * @brief Sets the velocity of this audio source.
		 * @param value The velocity.
		 */
		inline void set_velocity(Float3 const& value) { m_velocity = value; }

		/**
		 * @brief Gets the attenuation type of this audio source.
		 * @return The attenuation type.
		 */
		inline Attenuation get_attenuation() const { return m_attenuation; }

		/**
		 * @brief Sets the attenuation type of this audio source.
		 * @param value The attenuation type.
		 */
		inline void set_attenuation(Attenuation value) { m_attenuation = value; }

		/**
		 * @brief Gets the attenuation rolloff value of this audio source.
		 * @return The attenuation rolloff value.
		 */
		inline Float get_attenuation_rolloff() const { return m_attenuationRolloff; }

		/**
		 * @brief Sets the attenuation rolloff value of this audio source.
		 * @param value The attenuation rolloff value.
		 */
		inline void set_attenuation_rolloff(Float value) { m_attenuationRolloff = value; }

		/**
		 * @brief Gets the minimum distance for this audio source.
		 * @return The minimum distance.
		 */
		inline Float get_min_distance() const { return m_minDistance; }

		/**
		 * @brief Sets the minimum distance for this audio source.
		 * @param value The minimum distance.
		 */
		inline void set_min_distance(Float value) { m_minDistance = value; }

		/**
		 * @brief Gets the maximum distance for this audio source.
		 * @return The maximum distance.
		 */
		inline Float get_max_distance() const { return m_maxDistance; }

		/**
		 * @brief Sets the maximum distance for this audio source.
		 * @param value The maximum distance.
		 */
		inline void set_max_distance(Float value) { m_maxDistance = value; }

#pragma endregion

#pragma region Variables

	private:
		Float3 m_position;
		Float3 m_velocity;
		Attenuation m_attenuation;
		Float m_attenuationRolloff;
		Float m_minDistance;
		Float m_maxDistance;

#pragma endregion
	};

	template<>
    struct Serializer<AudioSource>
    {
        static void serialize(Writer& writer, AudioSource const& value);
        static void deserialize(Reader& reader, AudioSource& value);
    };
}

#endif // MINTY_AUDIO_AUDIOSOURCE_H