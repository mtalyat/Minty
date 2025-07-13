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
		/// The flags to use on this step.
		/// </summary>
		AnimationActionType type;

		/// <summary>
		/// A vector of key-value variable-names and values to set when the time is reached.
		/// </summary>
		Vector<Tuple<UInt, UInt>> values;

		Bool parse(String const& text) override;
		String to_string() const override;
	};
}