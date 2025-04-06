#pragma once
#include "Minty/Core/Types.h"

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
		virtual ~Manager();

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
		virtual void update() {}

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

#pragma endregion

	};
}