#pragma once

#pragma once

#include "M_Object.h"
#include "M_Debug.h"
#include <map>
#include <queue>

namespace minty
{
	// not exporting this class

	/// <summary>
	/// A basic queue which has a priority system. 
	/// Elements with a higher priority will be popped from the queue first. 
	/// Elements with the same priority will be popped in the order they were pushed into the queue.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class PriorityQueue
		: public Object
	{
	private:
		std::map<int, std::queue<T>*> m_data;

	public:
		/// <summary>
		/// Creates an empty PriorityQueue.
		/// </summary>
		PriorityQueue()
			: m_data()
		{}

		/// <summary>
		/// Puts a new element with the given priority and given object to the queue.
		/// </summary>
		/// <param name="priority">The priority of the element.</param>
		/// <param name="data">The element.</param>
		void push(int const priority, T const& data)
		{
			// if this priority already exists, find it
			auto d = m_data.find(priority);

			if (d != m_data.end())
			{
				// found list
				d->second->emplace(data);
			}
			else
			{
				// did not find list
				std::queue<T>* q = new std::queue<T>();
				q->emplace(data);
				m_data.emplace(priority, q);
			}
		}

		/// <summary>
		/// Gets the topmost element at the highest priority within the PriorityQueue.
		/// </summary>
		/// <param name="output"></param>
		/// <returns>True if an element was popped, otherwise false.</returns>
		bool pop(T& output)
		{
			// find the lowest list item

			if (!m_data.empty())
			{
				auto it = m_data.begin();

				int p = it->first;
				std::queue<T>* q = it->second;

				output = q->front();
				q->pop();

				// if the queue is empty, delete it
				if (q->empty())
				{
					delete q;
					m_data.erase(p);
				}

				return true;
			}

			// nothing to pop
			return false;
		}
	};
}