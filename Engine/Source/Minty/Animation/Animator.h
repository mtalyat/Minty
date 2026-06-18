#ifndef MINTY_ANIMATION_ANIMATOR_H
#define MINTY_ANIMATION_ANIMATOR_H

/**
 * @file Animator.h
 * @brief Defines the Animator class used for controlling animations on an Entity.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Types.h"
#include "Minty/Entity/Entity.h"
#include "Minty/Memory/DefaultAllocator.h"

namespace Minty
{
	class Animation;
	class EntityManager;
	struct AnimatorInfo;
	struct AnimatorComponent;
	class FSM;

	/**
	 * @brief The Animator is responsible for controlling animations on an Entity using a finite state machine (FSM).
	 */
	class Animator
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an Animator with the given arguments.
		 * @param info The arguments for the Animator.
		 */
		Animator(AnimatorInfo const &info);

		/**
		 * @brief Copy constructor.
		 * @param other The Animator to copy from.
		 */
		Animator(Animator const &other);

		~Animator();

#pragma endregion

#pragma region Operators

	public:
		Animator &operator=(Animator const &other);

#pragma endregion

#pragma region Accessors

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
		void set_variable(String const &name, Int const value);

		/**
		 * @brief Gets the value of the variable with the given name.
		 * @param name The name of the variable.
		 * @return The value of the variable.
		 */
		Int get_variable(String const &name) const;

		/**
		 * @brief Gets the Asset ID of the current Animation.
		 * @return The Asset ID of the current Animation.
		 */
		UUID get_current_animation() const;

		/**
		 * @brief Gets the FSM used by this Animator.
		 * @return A pointer to the FSM.
		 */
		FSM const* get_fsm() const { return mp_fsm; }

		/**
		 * @brief Gets the time scale of this Animator.
		 * @return The time scale.
		 */
		Float get_time_scale() const { return m_timeScale; }

		/**
		 * @brief Sets the time scale of this Animator.
		 * @param timeScale The new time scale. A value of 1.0 means normal speed, 0.5 means half speed, etc.
		 */
		void set_time_scale(Float const timeScale) { m_timeScale = timeScale; }

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
		UUID update(Ref<Animation> const &currentAnimation, Float const currentTime);

		/**
		 * @brief Flushes the AnimatorComponent to apply any changes from the Animator.
		 * @param animatorComp The AnimatorComponent to flush.
		 * @param deltaTime The time elapsed since the last update.
		 * @param thisEntity The Entity this AnimatorComponent belongs to.
		 * @param entityManager The EntityManager managing the Entity.
		 */
		void flush(AnimatorComponent &animatorComp, Float const deltaTime, Entity const thisEntity, EntityManager &entityManager);

		/**
		 * @brief Creates a new Animator from the given AnimatorInfo.
		 * @param info The arguments for the Animator.
		 * @return The created Animator.
		 */
		static Shared<Animator> create(AnimatorInfo const &info);

		/**
		 * @brief Creates a default Animator.
		 * @return The created default Animator.
		 */
		static Shared<Animator> create();

#pragma endregion

#pragma region Variables

	private:
		FSM *mp_fsm;
		Float m_timeScale;
		Bool m_force;
		DefaultAllocator m_allocator;

#pragma endregion
	};
}

#endif // MINTY_ANIMATION_ANIMATOR_H