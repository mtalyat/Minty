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
		// the data to manange
		std::unordered_map<std::string, T*>* mp_data;

	public:
		/// <summary>
		/// Creates a new Manager.
		/// </summary>
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

		/// <summary>
		/// Adds a new object to manage.
		/// </summary>
		/// <param name="name"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		virtual bool emplace(std::string const& name, T* const value)
		{
			return mp_data->emplace(name, value)->second;
		}

		/// <summary>
		/// Removes an object from management.
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		virtual bool erase(std::string const& name)
		{
			return mp_data->erase(name)->second;
		}

		/// <summary>
		/// Checks if the given name has an object that is being managed.
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		virtual bool contains(std::string const& name)
		{
			return mp_data->contains(name);
		}
	};
}