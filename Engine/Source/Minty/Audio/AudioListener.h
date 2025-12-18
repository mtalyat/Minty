#ifndef MINTY_AUDIO_AUDIOLISTENER_H
#define MINTY_AUDIO_AUDIOLISTENER_H

/**
 * @file AudioListener.h
 * @brief Header file defining the AudioListener class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/**
	 * @brief Holds the data for an audio listener.
	 */
	class AudioListener
		: public SerializableObject
	{
#pragma region Variables

	private:
		Float3 position = Float3(0.0f, 0.0f, 0.0f);
		Float3 forward = Float3(0.0f, 0.0f, 1.0f);
		Float3 up = Float3(0.0f, 1.0f, 0.0f);
		Float3 velocity = Float3(0.0f, 0.0f, 0.0f);

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty AudioListener.
		 */
		AudioListener()
			: SerializableObject()
			, position(Float3(0.0f, 0.0f, 0.0f))
			, forward(Float3(0.0f, 0.0f, 1.0f))
			, up(Float3(0.0f, 1.0f, 0.0f))
			, velocity(Float3(0.0f, 0.0f, 0.0f))
		{
		}

		/**
		 * @brief Creates a new AudioListener with the given parameters.
		 * @param position The position of the audio listener in 3D space.
		 * @param forward The forward direction vector of the audio listener.
		 * @param up The up direction vector of the audio listener.
		 * @param velocity The velocity vector of the audio listener.
		 */
		AudioListener(Float3 const& position, Float3 const& forward, Float3 const& up, Float3 const& velocity)
			: SerializableObject()
			, position(position)
			, forward(forward)
			, up(up)
			, velocity(velocity)
		{
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the position of the audio listener.
		 * @return The position as a Float3.
		 */
		inline Float3 const& get_position() const { return position; }

		/**
		 * @brief Sets the position of the audio listener.
		 * @param value The new position as a Float3.
		 */
		inline void set_position(Float3 const& value) { position = value; }

		/**
		 * @brief Gets the forward direction of the audio listener.
		 * @return The forward direction as a Float3.
		 */
		inline Float3 const& get_forward() const { return forward; }

		/**
		 * @brief Sets the forward direction of the audio listener.
		 * @param value The new forward direction as a Float3.
		 */
		inline void set_forward(Float3 const& value) { forward = value; }

		/**
		 * @brief Gets the up direction of the audio listener.
		 * @return The up direction as a Float3.
		 */
		inline Float3 const& get_up() const { return up; }

		/**
		 * @brief Sets the up direction of the audio listener.
		 * @param value The new up direction as a Float3.
		 */
		inline void set_up(Float3 const& value) { up = value; }

		/**
		 * @brief Gets the velocity of the audio listener.
		 * @return The velocity as a Float3.
		 */
		inline Float3 const& get_velocity() const { return velocity; }

		/**
		 * @brief Sets the velocity of the audio listener.
		 * @param value The new velocity as a Float3.
		 */
		inline void set_velocity(Float3 const& value) { velocity = value; }

#pragma endregion

#pragma region Methods

	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}

#endif // MINTY_AUDIO_AUDIOLISTENER_H