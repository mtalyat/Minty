#pragma once
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

	/// <summary>
	/// The arguments for an animation.
	/// </summary>
	struct AnimationBuilder
	{
		/// <summary>
		/// The Asset ID.
		/// </summary>
		UUID id;

		/// <summary>
		/// The amount of time this animation takes to complete, in seconds.
		/// </summary>
		Float duration;

		/// <summary>
		/// When true, the animation will restart after it ends.
		/// </summary>
		Bool loop;

		/// <summary>
		/// The paths to the Entities to animate.
		/// </summary>
		Vector<EntityPath> entities;

		/// <summary>
		/// The components being modified by this Animation.
		/// </summary>
		Vector<String> components;

		/// <summary>
		/// The names of the variables being modified by this Animation.
		/// </summary>
		Vector<String> variables;

		/// <summary>
		/// The values to set the variables to.
		/// </summary>
		Vector<Node> values;

		/// <summary>
		/// The actions to take during the Animation.
		/// </summary>
		Vector<AnimationAction> actions;

		/// <summary>
		/// The times and indices to the actions to take during the Animation.
		/// The times are expected to be in ascending order.
		/// There are to be no duplicate times.
		/// </summary>
		Vector<Tuple<Float, Vector<Size>>> steps;

		/// <summary>
		/// Indices to the actions to take to reset the Animation to the beginning.
		/// </summary>
		Vector<Size> resetSteps;
	};

	/// <summary>
	/// A single animation. A collection of actions to move or change an Entity.
	/// </summary>
	class Animation
		: public Asset
	{
#pragma region Classes

	private:
		using StepKey = UInt;
		using StepTime = UInt;
		using StepValue = UInt;

	public:
		using Index = UInt;

#pragma endregion

#pragma region Variables

	private:
		Float m_duration;
		Bool m_loop;
		Vector<EntityPath> m_entities;
		Vector<ComponentInfo const*> m_components;
		Vector<String> m_variables;
		Vector<Node> m_values;
		Vector<Float> m_times;
		Map<StepKey, Map<StepTime, StepValue>> m_steps;
		Map<StepKey, Vector<StepValue>> m_resetSteps;

	public:
		constexpr static Int ENTITY_OFFSET = 16;
		constexpr static Int COMPONENT_OFFSET = 8;
		constexpr static Int VARIABLE_OFFSET = 0;
		constexpr static Int TIME_OFFSET = 0;
		constexpr static Int VALUE_OFFSET = 4;
		constexpr static Int FLAGS_OFFSET = 0;
		constexpr static UInt MAX_ENTITY_INDEX = 0xff;
		constexpr static UInt MAX_COMPONENT_INDEX = 0xff;
		constexpr static UInt MAX_VARIABLE_INDEX = 0xff;
		constexpr static UInt MAX_TIME_INDEX = 0xffffffff;
		constexpr static UInt MAX_VALUE_INDEX = 0xfffffff;
		constexpr static UInt MAX_FLAGS_INDEX = 0xf;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Animation using the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		Animation(AnimationBuilder const& builder);

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Checks if this Animation is looping.
		/// </summary>
		/// <returns>True if looping.</returns>
		Bool is_looping() const { return m_loop; }

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Animation.</returns>
		AssetType get_asset_type() const override { return AssetType::Animation; }

#pragma endregion

#pragma region Methods

	private:
		StepKey compile_key(Index const entityIndex, Index const componentIndex, Index const variableIndex) const;

		StepValue compile_value(Index const valueIndex, AnimationActionType const flags) const;

		void perform_step(StepKey const key, StepTime const time, StepValue const value, Entity const thisEntity, EntityManager& entityManager) const;

		void perform_step(AnimationAction const& step, Entity const thisEntity, EntityManager& entityManager) const;

	public:
		/// <summary>
		/// Performs an animation on an Entity.
		/// </summary>
		/// <param name="time">The current time. This will be updated.</param>
		/// <param name="elapsedTime">The time that has elapsed over the last frame.</param>
		/// <param name="index">The index of the next step to perform.</param>
		/// <param name="thisEntity">The Entity being reset.</param>
		/// <param name="entityManager">The EntityManager thisEntity belongs to.</param>
		/// <returns>True when the animation has completed, otherwise false.</returns>
		Bool animate(Float& time, Float const elapsedTime, Index& index, Entity const thisEntity, EntityManager& entityManager) const;

		/// <summary>
		/// Resets the Animation to the beginning.
		/// </summary>
		/// <param name="thisEntity">The Entity being reset.</param>
		/// <param name="entityManager">The EntityManager thisEntity belongs to.</param>
		void reset(Entity const thisEntity, EntityManager& entityManager);

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Animation.
		/// </summary>
		/// <param name="builder">The arguments for the Animation.</param>
		static Owner<Animation> create(AnimationBuilder const& builder = {});

#pragma endregion
	};
}