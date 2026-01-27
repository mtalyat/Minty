#ifndef MINTY_AUDIO_AUDIOLISTENER_H
#define MINTY_AUDIO_AUDIOLISTENER_H

/**
 * @file AudioListener.h
 * @brief Header file defining the AudioListener class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Serialization/Serializer.h"

namespace Minty
{
	/**
	 * @brief Holds the data for an audio listener.
	 */
	class AudioListener
	{
		friend struct Serializer<AudioListener>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty AudioListener.
		 */
		AudioListener()
			: m_position(Float3(0.0f, 0.0f, 0.0f))
			, m_forward(Float3(0.0f, 0.0f, 1.0f))
			, m_up(Float3(0.0f, 1.0f, 0.0f))
			, m_velocity(Float3(0.0f, 0.0f, 0.0f))
		{
		}

		/**
		 * @brief Creates a new AudioListener with the given parameters.
		 * @param position The position of the audio listener in 3D space.
		 * @param m_forward The m_forward direction vector of the audio listener.
		 * @param m_up The m_up direction vector of the audio listener.
		 * @param velocity The velocity vector of the audio listener.
		 */
		AudioListener(Float3 const& position, Float3 const& m_forward, Float3 const& m_up, Float3 const& velocity)
			: m_position(position)
			, m_forward(m_forward)
			, m_up(m_up)
			, m_velocity(velocity)
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the position of the audio listener.
		 * @return The position as a Float3.
		 */
		inline Float3 const& get_position() const { return m_position; }

		/**
		 * @brief Sets the position of the audio listener.
		 * @param value The new position as a Float3.
		 */
		inline void set_position(Float3 const& value) { m_position = value; }

		/**
		 * @brief Gets the m_forward direction of the audio listener.
		 * @return The m_forward direction as a Float3.
		 */
		inline Float3 const& get_forward() const { return m_forward; }

		/**
		 * @brief Sets the m_forward direction of the audio listener.
		 * @param value The new m_forward direction as a Float3.
		 */
		inline void set_forward(Float3 const& value) { m_forward = value; }

		/**
		 * @brief Gets the m_up direction of the audio listener.
		 * @return The m_up direction as a Float3.
		 */
		inline Float3 const& get_up() const { return m_up; }

		/**
		 * @brief Sets the m_up direction of the audio listener.
		 * @param value The new m_up direction as a Float3.
		 */
		inline void set_up(Float3 const& value) { m_up = value; }

		/**
		 * @brief Gets the velocity of the audio listener.
		 * @return The velocity as a Float3.
		 */
		inline Float3 const& get_velocity() const { return m_velocity; }

		/**
		 * @brief Sets the velocity of the audio listener.
		 * @param value The new velocity as a Float3.
		 */
		inline void set_velocity(Float3 const& value) { m_velocity = value; }

#pragma endregion

#pragma region Variables

	private:
		Float3 m_position;
		Float3 m_forward;
		Float3 m_up;
		Float3 m_velocity;

#pragma endregion
	};

	template<>
	struct Serializer<AudioListener>
	{
		static void serialize(Writer& writer, AudioListener const& value);
        static Bool deserialize(Reader& reader, AudioListener& value);
	};
}

#endif // MINTY_AUDIO_AUDIOLISTENER_H