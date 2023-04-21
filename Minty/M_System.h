#pragma once

#include "M_Object.h"
#include "entt.hpp"
#include <set>

namespace minty
{
	/// <summary>
	/// The base class for systems, which provide functionality and conduct the behavior of the ECS engine.
	/// </summary>
	class MINTY_API System
		: public Object
	{
	private:
		// is this system enabled?
		bool m_enabled;

	protected:
		/// <summary>
		/// The registry that this System is part of.
		/// </summary>
		entt::registry* const mp_registry;

	public:
		/// <summary>
		/// Creates a new System.
		/// </summary>
		/// <param name="registry">The entity registry belonging to this System.</param>
		System(entt::registry* const registry)
			: m_enabled(true)
			, mp_registry(registry)
		{}

		virtual ~System(){}

		/// <summary>
		/// Enables this System. The System will run update() or fixedUpdate() when enabled.
		/// </summary>
		void enable() { m_enabled = true; }

		/// <summary>
		/// Disables this System. The System will not run update() or fixedUpdate() when disabled.
		/// </summary>
		void disable() { m_enabled = false; }

		/// <summary>
		/// Sets the enabled state of this System.
		/// </summary>
		/// <param name="enabled"></param>
		void setEnabled(bool const enabled) { m_enabled = enabled; }

		/// <summary>
		/// Checks if this System is enabled or not.
		/// </summary>
		/// <returns></returns>
		constexpr bool isEnabled() const { return m_enabled; }

		/// <summary>
		/// Called when the Scene is being loaded.
		/// </summary>
		virtual void load() {}

		/// <summary>
		/// Does one frame of work on the System.
		/// </summary>
		virtual void update() {}

		/// <summary>
		/// Does one fixed frame of work on the System.
		/// </summary>
		virtual void fixedUpdate() {}

		/// <summary>
		/// Called when the Scene is being unloaded.
		/// </summary>
		virtual void unload() {}
	};
}