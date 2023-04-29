#pragma once

#include "M_System.h"
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

		void emplace(entt::entity const entity, int const index = -1);

		entt::entity next();

		entt::entity prev();

	private:
		void select(int const index);
	};
}