#pragma once
#include "Minty/System/System.h"

namespace Minty
{
	/// <summary>
	/// Controls the animation of entities.
	/// </summary>
	class AnimationSystem
		: public System
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates an AnimationSystem using the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		AnimationSystem(SystemBuilder const& builder)
			: System(builder)
		{
		}

		~AnimationSystem() override
		{
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when the Scene is updated.
		/// </summary>
		/// <param name="time"></param>
		void on_update(Time const& time) override;

#pragma endregion
	};
}