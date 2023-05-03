#pragma once

#include "M_System.h"
#include "M_C_Selectable.h"
#include <boost/bimap.hpp>
#include "entt.hpp"

namespace minty
{
	/// <summary>
	/// Handles all animations within the Scene.
	/// </summary>
	class MINTY_API UserInterfaceSystem
		: public System
	{
	private:
		std::map<int, entt::entity>* mp_uiSelectables;
		int m_selected;

	public:
		/// <summary>
		/// Creates a new UserInterfaceSystem.
		/// </summary>
		/// <param name="registry">The entity registry belonging to this System.</param>
		UserInterfaceSystem(entt::registry* const registry);

		void unload() override;

		/// <summary>
		/// Puts a UI entity into the UI Selectable list at the given index.
		/// </summary>
		/// <param name="entity">The UI entity.</param>
		/// <param name="type">The type of entity.</param>
		/// <param name="index">The index in the next/prev list.</param>
		void emplace(entt::entity const entity, Selectable::Type const type, int const index = -1);

		/// <summary>
		/// Moves to the next selectable UI entity.
		/// </summary>
		/// <returns></returns>
		entt::entity next();

		/// <summary>
		/// Moves to the previous selectable UI entity.
		/// </summary>
		/// <returns></returns>
		entt::entity prev();

		/// <summary>
		/// Moves up on the selected UI entity.
		/// </summary>
		void up();

		/// <summary>
		/// Moves down on the selected UI entity.
		/// </summary>
		void down();

		/// <summary>
		/// Moves left on the selected UI entity.
		/// </summary>
		void left();

		/// <summary>
		/// Moves right on the selected UI entity.
		/// </summary>
		void right();
	private:
		void select(int const index);

		Selectable* getSelected();
	};
}