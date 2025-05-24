#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Asset/Asset.h"
#include "Minty/FSM/FSM.h"

namespace Minty
{
	/// <summary>
	/// The arguments for an Animator.
	/// </summary>
	struct AnimatorBuilder
	{
		/// <summary>
		/// The Asset ID.
		/// </summary>
		UUID id;

		/// <summary>
		/// The FSM to use for this Animator.
		/// </summary>
		FSM fsm;
	};

	/// <summary>
	/// Handles animating an Entity.
	/// </summary>
	class Animator
		: public Asset
	{
#pragma region Variables

	private:
		FSM m_fsm;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Animator using the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Animator(AnimatorBuilder const& builder)
			: Asset(builder.id)
			, m_fsm(builder.fsm)
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Sets the value of the variable with the given name.
		/// </summary>
		/// <param name="name">The name of the variable.</param>
		/// <param name="value">The new value of the variable.</param>
		void set_variable(String const& name, Int const value);

		/// <summary>
		/// Gets the value of the variable with the given name.
		/// </summary>
		/// <param name="name">The name of the variable.</param>
		/// <returns>The value of the variable.</returns>
		Int get_variable(String const& name) const;

		/// <summary>
		/// Gets the ID of the current Animation.
		/// </summary>
		/// <returns>The ID of the animation, or INVALID_ID if no Animation is currently being played.</returns>
		UUID get_current_animation() const;

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Animator.</returns>
		AssetType get_asset_type() const override { return AssetType::Animator; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Updates the state of this Animator based on the values of the variables in the FSM.
		/// </summary>
		/// <returns>The ID to the Animation that should be playing.</returns>
		UUID update();

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates an Animator using the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>An Animator Owner.</returns>
		static Owner<Animator> create(AnimatorBuilder const& builder = {});

#pragma endregion
	};
}