#pragma once

#include "M_Object.h"
#include "M_Debug.h"
#include <vector>
#include <functional>

namespace minty
{
	template<typename T = void>
	class MINTY_API Event
		: public Object
	{
	public:
		typedef std::function<void(T)> func;

	private:
		std::vector<func>* mp_functions;

	public:

		Event()
			: mp_functions(new std::vector<func>())
		{}

		~Event()
		{
			delete mp_functions;
		}

		/// <summary>
		/// Add a new function to be ran when this event is invoked.
		/// </summary>
		/// <param name="f"></param>
		inline void emplace(func const& f)
		{
			mp_functions->push_back(f);
		}

		/// <summary>
		/// Runs the functions within this Event using the given argument.
		/// </summary>
		/// <param name="arg"></param>
		void invoke(T const arg) const
		{
			for (func f : *mp_functions)
			{
				f(arg);
			}
		}
	};

	template<>
	class MINTY_API Event<void>
		: public Object
	{
	public:
		typedef std::function<void(void)> func;

	private:
		std::vector<func>* mp_functions;

	public:

		Event()
			: mp_functions(new std::vector<func>())
		{}

		~Event()
		{
			delete mp_functions;
		}

		void operator()() const
		{
			invoke();
		}

		/// <summary>
		/// Add a new function to be ran when this event is invoked.
		/// </summary>
		/// <param name="f"></param>
		inline void emplace(func const& f)
		{
			mp_functions->push_back(f);
		}

		/// <summary>
		/// Run the functions within this Event.
		/// </summary>
		void invoke() const
		{
			for (func f : *mp_functions)
			{
				f();
			}
		}
	};
}