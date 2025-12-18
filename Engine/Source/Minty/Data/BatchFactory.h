#ifndef MINTY_DATA_BATCHFACTORY_H
#define MINTY_DATA_BATCHFACTORY_H

/**
 * @file BatchFactory.h
 * @brief Header file for the BatchFactory class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Batch.h"
#include "Minty/Data/Ordered.h"

namespace Minty
{
	/**
	 * @brief A factory for creating and managing Batches.
	 * @tparam N The number of objects in each Batch.
	 * @tparam Args The types of the objects in each Batch.
	 */
	template<typename Size N, typename ...Args>
	class BatchFactory
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new BatchFactory.
		 * @param newBatchCapacity The capacity for new Batches created by this factory.
		 */
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
		inline Ordered<Batch<N, Args...>>::Iterator begin() { return m_batches.begin(); }
		inline Ordered<Batch<N, Args...>>::Iterator end() { return m_batches.end(); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the number of Batches managed by this factory.
		 * @returns The number of Batches.
		 */
		Size get_size() const { return m_batches.size(); }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Checks if a Batch with the given objects exists.
		 * @param objects The objects to check for.
		 * @returns True if a matching Batch exists, false otherwise.
		 */
		Bool has_batch(Array<std::variant<Args...>, sizeof...(Args)> const& objects)
		{
			Batch<N, Args...> temp(objects);
			return m_batches.contains(temp);
		}

		/**
		 * @brief Gets an existing Batch with the given objects, or creates a new one if none exists.
		 * @param objects The objects for the Batch.
		 * @returns A reference to the Batch.
		 */
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

#pragma region Variables

	private:
		Ordered<Batch<N, Args...>> m_batches;
		Size m_newBatchCapacity;

#pragma endregion
	};
}

#endif // MINTY_DATA_BATCHFACTORY_H