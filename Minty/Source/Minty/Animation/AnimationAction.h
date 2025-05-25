#pragma once
#include "Minty/Animation/AnimationActionFlags.h"
#include "Minty/Serialization/Parseable.h"

namespace Minty
{
	/// <summary>
	/// A single step within an animation.
	/// </summary>
	struct AnimationAction
		: public Parseable
	{
		/// <summary>
		/// The index to the Entity to act upon.
		/// </summary>
		UInt entityIndex;

		/// <summary>
		/// The index to the Component to act upon.
		/// </summary>
		UInt componentIndex;

		/// <summary>
		/// The index to the variable to act upon.
		/// </summary>
		UInt variableIndex;

		/// <summary>
		/// The index to the time of when to act.
		/// </summary>
		UInt timeIndex;

		/// <summary>
		/// The index to the value to use upon reaching the set time.
		/// </summary>
		UInt valueIndex;

		/// <summary>
		/// The flags to use on this step.
		/// </summary>
		AnimationActionType type;

		Bool parse(String const& text) override;
		String to_string() const override;
	};
}