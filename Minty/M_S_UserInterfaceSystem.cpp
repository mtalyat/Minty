#include "pch.h"
#include "M_S_UserInterfaceSystem.h"
#include "M_Debug.h"

namespace minty
{
	UserInterfaceSystem::UserInterfaceSystem(entt::registry* const registry)
		: System(registry)
		, mp_uiSelectables(new std::map<uint, entt::entity>())
		, m_next()
		, m_selected()
	{}

	void UserInterfaceSystem::unload()
	{
		// TODO: clean up selectable events?

		// clear array
		mp_uiSelectables->clear();
	}
	
	void UserInterfaceSystem::emplace(entt::entity const entity, Selectable::Type const type, int const index)
	{
		int i = index < 0 ? m_next : index;

		m_next++;

		auto found = mp_uiSelectables->find(i);

		if (found != mp_uiSelectables->end())
		{
			// selectable already exists
			Debug::logError(std::format("An entity already exists with the index {0}.", i));
			return;
		}

		// get selectable component
		Selectable& selectable = mp_registry->get_or_emplace<Selectable>(entity);
		selectable.type = type;
		selectable.index = i;

		// add to map
		mp_uiSelectables->emplace(i, entity);
	}
	
	entt::entity UserInterfaceSystem::next()
	{
		auto it = mp_uiSelectables->find(m_selected);

		// do nothing if nothing selected
		if (it == mp_uiSelectables->end())
		{
			return entt::null;
		}

		// get iterator, get next element
		it = std::next(it, 1);

		// get next
		if (it == mp_uiSelectables->end())
		{
			// at the end, so use the first entity
			select(mp_uiSelectables->begin()->first);
		}
		else
		{
			// not at the end, use the next item
			select(it->first);
		}

		//return mp_uiSelectables->at(m_selected);
		return entt::null;
	}
	
	entt::entity UserInterfaceSystem::prev()
	{
		auto it = mp_uiSelectables->find(m_selected);

		// do nothing if nothing selected
		if (it == mp_uiSelectables->end())
		{
			return entt::null;
		}

		// get prev
		if (it == mp_uiSelectables->begin())
		{
			// at the beginning, so use the last entity
			select(std::prev(mp_uiSelectables->end(), 1)->first);
		}
		else
		{
			// not at the end, use the prev item
			select(std::prev(it, 1)->first);
		}

		return mp_uiSelectables->at(m_selected);
	}

	void UserInterfaceSystem::up()
	{
		Selectable* selected = getSelected();

		if (!selected)
		{
			return;
		}
	}

	void UserInterfaceSystem::down()
	{
		Selectable* selected = getSelected();

		if (!selected)
		{
			return;
		}
	}

	void UserInterfaceSystem::left()
	{
		Selectable* selected = getSelected();

		if (!selected)
		{
			return;
		}
	}

	void UserInterfaceSystem::right()
	{
		Selectable* selected = getSelected();

		if (!selected)
		{
			return;
		}
	}

	void UserInterfaceSystem::select(int const index)
	{
		// do nothing if index not changing
		if (index == m_selected)
		{
			return;
		}

		// call unselect event
		Selectable const& old = mp_registry->get<Selectable>(mp_uiSelectables->at(m_selected));
		if (old.onDeselect)
		{
			old.onDeselect->invoke();
		}

		// switch to new
		m_selected = index;

		// call select event
		Selectable const& selected = mp_registry->get<Selectable>(mp_uiSelectables->at(m_selected));
		if (selected.onSelect)
		{
			selected.onSelect->invoke();
		}
	}
	
	Selectable* UserInterfaceSystem::getSelected()
	{
		auto found = mp_uiSelectables->find(m_selected);

		if (found == mp_uiSelectables->end())
		{
			// nothing selected
			return nullptr;
		}

		// get Selectable component from selected
		return mp_registry->try_get<Selectable>(found->second);
	}
}
