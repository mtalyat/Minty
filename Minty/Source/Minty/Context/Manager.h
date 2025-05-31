#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Event/Event.h"
#include "Minty/Time/Time.h"

namespace Minty
{
	/// <summary>
	/// Base class for all Managers.
	/// </summary>
	class Manager
	{
#pragma region Variables

	private:
		Bool m_initialized;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Manager.
		/// </summary>
		Manager()
			: m_initialized(false)
		{
		}

		virtual ~Manager();

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Checks if this Manager is initialized.
		/// </summary>
		/// <returns>True, if initialized.</returns>
		Bool is_initialized() const { return m_initialized; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when the Manager is created.
		/// </summary>
		virtual void initialize();

		/// <summary>
		/// Called when the Manager is destroyed.
		/// </summary>
		virtual void dispose();

		/// <summary>
		/// Called every frame.
		/// </summary>
		virtual void update(Time const& time) {}

		/// <summary>
		/// Called after every update operation.
		/// </summary>
		virtual void finalize() {}

		/// <summary>
		/// Called every frame to perform rendering.
		/// </summary>
		virtual void render() {}

		/// <summary>
		/// Called when the Manager needs to synchronize operations.
		/// </summary>
		virtual void sync() {}

		/// <summary>
		/// Handles the given Event.
		/// </summary>
		/// <param name="event">The Event to handle.</param>
		virtual void handle_event(Event& event) {}

#pragma endregion

	};
}