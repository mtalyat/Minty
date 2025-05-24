#pragma once
#include "Minty/Animation/Animation.h"
#include "Minty/Animation/Animator.h"
#include "Minty/Component/Component.h"

namespace Minty
{
	/// <summary>
	/// Handles animating an Entity.
	/// </summary>
	struct AnimatorComponent
		: public Component
	{
		/// <summary>
		/// The Animator to use for this Component.
		/// </summary>
		Ref<Animator> animator = nullptr;

		/// <summary>
		/// The current Animation being played.
		/// </summary>
		Ref<Animation> animation = nullptr;

		/// <summary>
		/// The current time in the Animation.
		/// </summary>
		Float time = 0.0f;

		/// <summary>
		/// The current index in the Animation.
		/// </summary>
		Animation::Index index = 0;

		virtual void serialize(Writer& writer) const override;
		virtual Bool deserialize(Reader& reader) override;
	};
}