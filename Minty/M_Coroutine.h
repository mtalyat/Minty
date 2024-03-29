#pragma once

#include "M_Object.h"
#include "M_Debug.h"

#include <coroutine>
#include <concepts>
#include <exception>
#include <vector>

#define YIELD co_yield 0

namespace minty
{
	// template from:
	// https://www.scs.stanford.edu/~dm/blog/c++-coroutines.html
	template <typename T>
	struct Coroutine
	{
		/// <summary>
		/// Is this Coroutine still valid and representative of an active Coroutine?
		/// </summary>
		bool valid;

		struct promise_type;
		using handle_type = std::coroutine_handle<promise_type>;

		struct promise_type
		{
			T value;
			std::exception_ptr exception;

			Coroutine get_return_object()
			{
				return Coroutine(handle_type::from_promise(*this));
			}

			std::suspend_always initial_suspend() { return {}; }

			std::suspend_always final_suspend() noexcept { return {}; }

			void unhandled_exception() { exception = std::current_exception(); }

			template<std::convertible_to<T> From>
			std::suspend_always yield_value(From&& from)
			{
				value = std::forward<From>(from);
				return {};
			}

			void return_void() {}

			promise_type()
				: value()
			{}
		};

		handle_type handle;

		/// <summary>
		/// Creates an empty Coroutine.
		/// </summary>
		Coroutine() : valid(false), handle() {}

		/// <summary>
		/// Creates a Coroutine from the given handle.
		/// </summary>
		/// <param name="h"></param>
		Coroutine(handle_type h) : valid(true), handle(h) {}

		// copy constructor
		Coroutine(Coroutine const& other)
			: valid(other.valid)
			, handle(other.handle)
			, m_isFull(other.m_isFull)
		{}

		// move constructor
		Coroutine(Coroutine&& other) noexcept
			: valid(other.valid)
			, handle(other.handle)
			, m_isFull(other.m_isFull)
		{}

		// assignment operator
		Coroutine& operator=(Coroutine const& other)
		{
			valid = other.valid;
			handle = other.handle;
			m_isFull = other.m_isFull;

			return *this;
		}

		/// <summary>
		/// Stop this Coroutine.
		/// </summary>
		void stop()
		{
			// if a valid coroutine, and not done doing work, destroy self
			if (valid && !handle.done())
			{
				destroy();
			}
		}

		/// <summary>
		/// Destroy this Coroutine.
		/// </summary>
		void destroy()
		{
			handle.destroy();
			valid = false;
		}

		//~Coroutine() { handle.destroy(); }

		// iterates the coroutine
		explicit operator bool()
		{
			fill();
			return !handle.done();
		}

		// runs the coroutine
		T operator()()
		{
			fill();
			m_isFull = false;
			return std::move(handle.promise().value_);
		}

	private:
		bool m_isFull = false;

		void fill()
		{
			if (!m_isFull)
			{
				handle();
				if (handle.promise().exception)
				{
					//std::rethrow_exception(handle.promise().exception);
					Debug::log("handle.promise().exception");
				}
				m_isFull = true;
			}
		}
	};

	/// <summary>
	/// Manages and runs coroutines in an orderly method.
	/// </summary>
	class MINTY_API CoroutineManager
		: public Object
	{
	private:
		// the coroutines to run
		std::vector<Coroutine<int>>* mp_coroutines;

	public:
		/// <summary>
		/// Creates a new CoroutineManager.
		/// </summary>
		CoroutineManager()
			: mp_coroutines(new std::vector<Coroutine<int>>())
		{}

		~CoroutineManager()
		{
			delete mp_coroutines;
		}

		/// <summary>
		/// Adds a new Coroutine to the CoroutineManager.
		/// </summary>
		/// <param name="coroutine">The coroutine to add.</param>
		void emplace(Coroutine<int> const& coroutine)
		{
			mp_coroutines->push_back(coroutine);
		}

		/// <summary>
		/// Runs all of the Coroutines within the CoroutineManager.
		/// </summary>
		void run()
		{
			// iterate backwards, so we can remove completed coroutines as we go
			for (int i = mp_coroutines->size() - 1; i >= 0; i--)
			{
				Coroutine<int> c = mp_coroutines->at(i);

				if (!c)
				{
					// completed

					// delete and remove
					// delete c;
					mp_coroutines->erase(mp_coroutines->begin() + i);
					c.destroy();
				}
			}
		}
	};
}