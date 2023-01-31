#include "pch.h"
#include "M_System.h"

namespace minty
{
	bool System::emplace(entt::entity const entity)
	{
		return mp_entities->emplace(entity).second;
	}

	bool System::erase(entt::entity const entity)
	{
		mp_entities->erase(entity);

		return true;
	}
}
