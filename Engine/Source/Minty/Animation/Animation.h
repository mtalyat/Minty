#ifndef MINTY_ANIMATION_ANIMATION_H
#define MINTY_ANIMATION_ANIMATION_H

/**
 * @file Animation.h
 * @brief Defines the Animation class used for animating Entities.
 * @author Mitchell Talyat
 */

#include "Minty/Animation/AnimationAction.h"
#include "Minty/Asset/Asset.h"
#include "Minty/Component/Component.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Entity/EntityPath.h"
#include "Minty/Serialization/Node.h"

namespace Minty
{
	class EntityManager;
	struct AnimationInfo;
	struct ComponentData;

	/// <summary>
	/// A single animation. A collection of actions to move or change an Entity.
	/// </summary>
	class Animation
		: public Asset
	{
#pragma region Types

	private:
		using StepKey = ULong;
		using StepValue = UInt;

	public:
		using Index = UInt;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an Animation with the given arguments.
		 * @param info The arguments for the Animation.
		 */
		Animation(AnimationInfo const& info);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Checks if this Animation is looping.
		 * @return True if looping, otherwise false.
		 */
		inline Bool is_looping() const { return m_loop; }

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return The AssetType::Animation.
		 */
		inline AssetType get_asset_type() const override { return AssetType::Animation; }

		/**
		 * @brief Gets the duration of this Animation, in seconds.
		 * @return The duration, in seconds.
		 */
		inline Float get_duration() const { return m_duration; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Advances the Animation by the given elapsed time.
		 * @param time The current time of the Animation. This will be updated.
		 * @param elapsedTime The time to advance the Animation by, in seconds.
		 * @param thisEntity The Entity being animated.
		 * @param entityManager The EntityManager thisEntity belongs to.
		 * @return True if the Animation is still playing, false if it has ended.
		 */
		Bool animate(Float& time, Float const elapsedTime, Entity const thisEntity, EntityManager& entityManager) const;

		/**
		 * @brief Resets the animated Entities to their original state before the Animation was played.
		 * @param thisEntity The Entity being animated.
		 * @param entityManager The EntityManager thisEntity belongs to.
		 */
		void reset(Entity const thisEntity, EntityManager& entityManager);

		/**
		 * @brief Creates a new Animation from the given AnimationInfo.
		 * @param info The arguments for the Animation.
		 * @return The created Animation.
		 */
		static Shared<Animation> create(AnimationInfo const& info);
		
	private:
		StepKey compile_key(Index const entityIndex, Index const componentIndex, AnimationActionType const type) const;

		void extract_key(StepKey const key, Index& entityIndex, Index& componentIndex, AnimationActionType& flags) const;

		StepValue compile_value(Index const variableIndex, Index const valueIndex) const;

		void extract_value(StepValue const value, Index& variableIndex, Index& valueIndex) const;

		void build_action(StepKey& key, Vector<StepValue>& values, AnimationAction const& action) const;

		void perform_action(StepKey const key, Vector<StepValue> const& values, Entity const thisEntity, EntityManager& entityManager) const;

		void perform_action(AnimationAction const& action, Entity const thisEntity, EntityManager& entityManager) const;

#pragma endregion

#pragma region Variables

	private:
		Float m_duration;
		Bool m_loop;
		Vector<EntityPath> m_entities;
		Vector<ComponentData const*> m_components;
		Vector<Tuple<String, Bool>> m_variables;
		Vector<Node> m_values;
		Map<StepKey, Tuple<UInt, Vector<Tuple<Float, Vector<StepValue>>>>> m_steps;
		Map<StepKey, Tuple<UInt, Vector<StepValue>>> m_resetSteps;

	public:
		constexpr static Int ENTITY_OFFSET = 0;
		constexpr static Int COMPONENT_OFFSET = 16;
		constexpr static Int FLAGS_OFFSET = 32;
		constexpr static Int VARIABLE_OFFSET = 0;
		constexpr static Int VALUE_OFFSET = 16;
		constexpr static UInt MAX_ENTITY_INDEX = 0xffff;
		constexpr static UInt MAX_COMPONENT_INDEX = 0xffff;
		constexpr static UInt MAX_FLAGS_INDEX = 0xf;
		constexpr static UInt MAX_VARIABLE_INDEX = 0xffff;
		constexpr static UInt MAX_VALUE_INDEX = 0xffff;

#pragma endregion
	};
}

#endif // MINTY_ANIMATION_ANIMATION_H