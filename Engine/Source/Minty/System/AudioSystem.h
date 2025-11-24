#pragma once
#include "Minty/System/System.h"

namespace Minty
{
	class AudioSystem
		: public System
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new AudioSystem using the given SystemBuilder.
		/// </summary>
		AudioSystem(SystemBuilder const& builder);

		~AudioSystem() override
		{
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when the Scene is unloaded.
		/// </summary>
		void on_unload() override;

		/// <summary>
		/// Called when the Scene is finalized.
		/// </summary>
		void on_finalize() override;

#pragma endregion
	};
}