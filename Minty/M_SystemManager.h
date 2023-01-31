#pragma once

#include "M_Object.h"
#include "M_System.h"

namespace minty
{
	/// <summary>
	/// Holds and managers data relevant to systems. Can hold multiple types of systems.
	/// </summary>
	class MINTY_API SystemManager
		: public Object
	{
	private:
		std::vector<System*>* mp_systems;

	public:
		/// <summary>
		/// Creates an empty SystemManager.
		/// </summary>
		SystemManager();

		~SystemManager();

		/// <summary>
		/// Places the given System within the SystemManager.
		/// </summary>
		/// <param name="system"></param>
		void emplace(System* const system);

		/// <summary>
		/// Removes the given System from the SystemManager.
		/// </summary>
		/// <param name="system"></param>
		void erase(System* const system);

		/// <summary>
		/// Runs the update method on each System within this SystemManager.
		/// </summary>
		void update();

		/// <summary>
		/// Returns the vector of Systems within this SystemManager.
		/// </summary>
		/// <returns></returns>
		std::vector<System*>* list() const { return mp_systems; }
	};
}