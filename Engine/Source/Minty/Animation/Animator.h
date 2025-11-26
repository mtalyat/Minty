#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	class Animation;
	struct AnimatorInfo;

	/// <summary>
	/// Handles animating an Entity.
	/// </summary>
	class Animator
		: public Asset
	{
#pragma region Variables

	private:
		FSM* mp_fsm;
		Bool m_force;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an Animator with the given arguments.
		 * @param info The arguments for the Animator.
		 */
		Animator(AnimatorInfo const& info);

#pragma endregion

#pragma region Get Set

	public:
		/**
		 * @brief Sets the force value of this Animator.
		 * @param force If true, animations will transition as soon as possible.
		 */
		inline void set_force(Bool const force) { m_force = force; }

		/**
		 * @brief Gets the force value of this Animator.
		 * @return True if animations will transition as soon as possible.
		 */
		inline Bool get_force() const { return m_force; }

		/**
		 * @brief Sets the value of the variable with the given name.
		 * @param name The name of the variable.
		 * @param value The new value of the variable.
		 */
		void set_variable(String const& name, Int const value);

		/**
		 * @brief Gets the value of the variable with the given name.
		 * @param name The name of the variable.
		 * @return The value of the variable.
		 */
		Int get_variable(String const& name) const;

		/**
		 * @brief Gets the Asset ID of the current Animation.
		 * @return The Asset ID of the current Animation.
		 */
		UUID get_current_animation() const;

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return The AssetType::Animator.
		 */
		inline AssetType get_asset_type() const override { return AssetType::Animator; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Updates the Animator, potentially transitioning to a new Animation.
		 * @param currentAnimation The current Animation Ref.
		 * @param currentTime The current time of the Animation.
		 * @return The Asset ID of the current Animation after the update.
		 */
		UUID update(Ref<Animation> const& currentAnimation, Float const currentTime);
		
		/**
		 * @brief Creates a new Animator from the given AnimatorInfo.
		 * @param info The arguments for the Animator.
		 * @return The created Animator.
		 */
		static Owner<Animator> create(AnimatorInfo const& info);

#pragma endregion
	};
}