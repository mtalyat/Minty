#pragma once
#include "Minty/Audio/Attenuation.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Math.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/// <summary>
	/// Holds the data for an audio source.
	/// </summary>
	class AudioSource
		: public SerializableObject
	{
#pragma region Variables

	private:
		Float3 m_position;
		Float3 m_velocity;
		Attenuation m_attenuation;
		Float m_attenuationRolloff;
		Float m_minDistance;
		Float m_maxDistance;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty AudioSource.
		/// </summary>
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

		/// <summary>
		/// Creates a new AudioSource with the given parameters.
		/// </summary>
        /// <param name="position">The position of the audio source in 3D space.</param>
        /// <param name="velocity">The velocity of the audio source in 3D space.</param>
        /// <param name="attenuation">The attenuation model used for distance-based volume reduction.</param>
        /// <param name="attenuationRolloff">The rolloff factor for attenuation calculation.</param>
        /// <param name="minDistance">The minimum distance at which attenuation begins.</param>
        /// <param name="maxDistance">The maximum distance at which attenuation is applied.</param>
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

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the position of this audio source.
		/// </summary>
		/// <returns>The position.</returns>
		inline Float3 const& get_position() const { return m_position; }

		/// <summary>
		/// Sets the position of this audio source.
		/// </summary>
		/// <param name="value">The position.</param>
		inline void set_position(Float3 const& value) { m_position = value; }

        /// <summary>
        /// Gets the velocity of this audio source.
        /// </summary>
        /// <returns>The velocity.</returns>
        inline Float3 const& get_velocity() const { return m_velocity; }

        /// <summary>
        /// Sets the velocity of this audio source.
        /// </summary>
        /// <param name="value">The velocity.</param>
        inline void set_velocity(Float3 const& value) { m_velocity = value; }

        /// <summary>
        /// Gets the attenuation type of this audio source.
        /// </summary>
        /// <returns>The attenuation type.</returns>
        inline Attenuation get_attenuation() const { return m_attenuation; }

        /// <summary>
        /// Sets the attenuation type of this audio source.
        /// </summary>
        /// <param name="value">The attenuation type.</param>
        inline void set_attenuation(Attenuation value) { m_attenuation = value; }

        /// <summary>
        /// Gets the attenuation rolloff value of this audio source.
        /// </summary>
        /// <returns>The attenuation rolloff value.</returns>
        inline Float get_attenuation_rolloff() const { return m_attenuationRolloff; }

        /// <summary>
        /// Sets the attenuation rolloff value of this audio source.
        /// </summary>
        /// <param name="value">The attenuation rolloff value.</param>
        inline void set_attenuation_rolloff(Float value) { m_attenuationRolloff = value; }

        /// <summary>
        /// Gets the minimum distance for this audio source.
        /// </summary>
        /// <returns>The minimum distance.</returns>
        inline Float get_min_distance() const { return m_minDistance; }

        /// <summary>
        /// Sets the minimum distance for this audio source.
        /// </summary>
        /// <param name="value">The minimum distance.</param>
        inline void set_min_distance(Float value) { m_minDistance = value; }

        /// <summary>
        /// Gets the maximum distance for this audio source.
        /// </summary>
        /// <returns>The maximum distance.</returns>
        inline Float get_max_distance() const { return m_maxDistance; }

        /// <summary>
        /// Sets the maximum distance for this audio source.
        /// </summary>
        /// <param name="value">The maximum distance.</param>
        inline void set_max_distance(Float value) { m_maxDistance = value; }

#pragma endregion

#pragma region Methods

	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}