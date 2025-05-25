#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/// <summary>
	/// Holds the data for an audio listener.
	/// </summary>
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
		/// <summary>
		/// Creates an empty AudioListener.
		/// </summary>
		AudioListener()
			: SerializableObject()
			, position(Float3(0.0f, 0.0f, 0.0f))
			, forward(Float3(0.0f, 0.0f, 1.0f))
			, up(Float3(0.0f, 1.0f, 0.0f))
			, velocity(Float3(0.0f, 0.0f, 0.0f))
		{
		}

		/// <summary>
		/// Creates a new AudioListener with the given parameters.
		/// </summary>
		/// <param name="position">The position of the audio listener in 3D space.</param>
		/// <param name="forward">The forward direction vector of the audio listener.</param>
		/// <param name="up">The up direction vector of the audio listener.</param>
		/// <param name="velocity">The velocity vector of the audio listener.</param>
		AudioListener(Float3 const& position, Float3 const& forward, Float3 const& up, Float3 const& velocity)
			: SerializableObject()
			, position(position)
			, forward(forward)
			, up(up)
			, velocity(velocity)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the position of the audio listener.
		/// </summary>
		/// <returns>The position as a Float3.</returns>
		inline Float3 const& get_position() const { return position; }

		/// <summary>
		/// Sets the position of the audio listener.
		/// </summary>
		/// <param name="value">The new position as a Float3.</param>
		inline void set_position(Float3 const& value) { position = value; }

		/// <summary>
		/// Gets the forward direction of the audio listener.
		/// </summary>
		/// <returns>The forward direction as a Float3.</returns>
		inline Float3 const& get_forward() const { return forward; }

		/// <summary>
		/// Sets the forward direction of the audio listener.
		/// </summary>
		/// <param name="value">The new forward direction as a Float3.</param>
		inline void set_forward(Float3 const& value) { forward = value; }

		/// <summary>
		/// Gets the up direction of the audio listener.
		/// </summary>
		/// <returns>The up direction as a Float3.</returns>
		inline Float3 const& get_up() const { return up; }

		/// <summary>
		/// Sets the up direction of the audio listener.
		/// </summary>
		/// <param name="value">The new up direction as a Float3.</param>
		inline void set_up(Float3 const& value) { up = value; }

		/// <summary>
		/// Gets the velocity of the audio listener.
		/// </summary>
		/// <returns>The velocity as a Float3.</returns>
		inline Float3 const& get_velocity() const { return velocity; }

		/// <summary>
		/// Sets the velocity of the audio listener.
		/// </summary>
		/// <param name="value">The new velocity as a Float3.</param>
		inline void set_velocity(Float3 const& value) { velocity = value; }

#pragma endregion

#pragma region Methods

	public:
		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;

#pragma endregion
	};
}