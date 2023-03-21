#include "pch.h"
#include "M_C_Name.h"

std::string minty::Name::getName(entt::entity const entity, entt::registry* const registry)
{
	// get name component
	Name* name = registry->try_get<Name>(entity);

	// if has a name, return
	if (name)
	{
		return name->name;
	}

	// no name
	return "";
}
