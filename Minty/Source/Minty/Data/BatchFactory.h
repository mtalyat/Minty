#pragma once
#include "Minty/Data/Batch.h"
#include "Minty/Data/Set.h"

namespace Minty
{
	/// <summary>
	/// Handles creating and managing Batches.
	/// </summary>
	/// <typeparam name="...Args">The type arguements for each Batch.</typeparam>
	template<typename Size N, typename ...Args>
	class BatchFactory
	{
#pragma region Variables

	private:
		Set<Batch<N, Args...>> m_batches;
		Size m_newBatchCapacity;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new BatchFactory.
		/// </summary>
		/// <param name="newBatchCapacity">The capacity of each Batch's internal compiled data.</param>
		BatchFactory(Size const newBatchCapacity = 0)
			: m_batches()
			, m_newBatchCapacity(newBatchCapacity)
		{
			m_batches.reserve(16);
		}

		~BatchFactory()
		{
		}

#pragma endregion

#pragma region Iterators

	public:
		inline Set<Batch<N, Args...>>::Iterator begin() { return m_batches.begin(); }
		inline Set<Batch<N, Args...>>::Iterator end() { return m_batches.end(); }

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the number of batches in this BatchFactory.
		/// </summary>
		/// <returns></returns>
		Size get_size() const { return m_batches.size(); }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Checks if there is a Batch with the given objects.
		/// </summary>
		/// <param name="objects">The objects to check for.</param>
		/// <returns>True if there is a batch that contains the objects.</returns>
		Bool has_batch(Array<std::variant<Args...>, sizeof...(Args)> const& objects)
		{
			Batch<N, Args...> temp(objects);
			return m_batches.contains(temp);
		}

		/// <summary>
		/// Gets the previous Batch, or creates a new one if the objects do not match.
		/// </summary>
		/// <param name="objects">The objects to check for.</param>
		/// <returns>A batch with the given objects.</returns>
		Batch<N, Args...>& get_or_create_batch(Array<std::variant<Args...>, sizeof...(Args)> const& objects)
		{
			Batch<N, Args...> batch(objects);
			auto found = m_batches.find(batch);

			if (found == m_batches.end())
			{
				auto temp = m_batches.add(batch);
				return const_cast<Batch<N, Args...>&>(*m_batches.find(batch));
			}

			return const_cast<Batch<N, Args...>&>(*found);
		}

#pragma endregion
	};
}