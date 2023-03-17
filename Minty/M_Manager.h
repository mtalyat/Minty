#pragma once

#include "M_Object.h"
#include <unordered_map>

namespace minty
{
	/// <summary>
	/// Manages a map of objects. Will delete values when the manager is deleted.
	/// </summary>
	template<class T>
	class Manager
		: public Object
	{
	private:
		std::unordered_map<std::string, T*>* mp_data;

	public:
		Manager()
			: mp_data(new std::unordered_map<std::string, T*>())
		{}

		virtual ~Manager()
		{
			for (auto const& pair : *mp_data)
			{
				delete pair.second;
			}

			delete mp_data;
		}

		virtual bool emplace(std::string const& name, T* const value)
		{
			return mp_data->emplace(name, value)->second;
		}

		virtual bool erase(std::string const& name)
		{
			return mp_data->erase(name)->second;
		}

		virtual bool contains(std::string const& name)
		{
			return mp_data->contains(name);
		}
	};
}