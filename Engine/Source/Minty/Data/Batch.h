#ifndef MINTY_DATA_BATCH_H
#define MINTY_DATA_BATCH_H

/**
 * @file Batch.h
 * @brief Header file defining the Batch class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Array.h"
#include "Minty/Data/DynamicContainer.h"
#include "Minty/Data/Tuple.h"
#include <variant>

namespace Minty
{
	/**
	 * @brief A Batch is a collection of objects of varying types, compiled into a single data container.
	 * @tparam N The number of objects in the Batch.
	 * @tparam Args The types of the objects in the Batch.
	 */
	template<typename Size N, typename ...Args>
	class Batch
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Batch.
		 */
		Batch()
			: m_objects()
			, m_data()
			, m_count(0)
			, m_hash(0)
		{
		}

		/**
		 * @brief Creates a Batch with the given objects and data capacity.
		 * @param objects The objects to include in the Batch.
		 * @param dataCapacity The capacity of the compiled data.
		 */
		Batch(Array<std::variant<Args...>, sizeof...(Args)> const& objects, Size const dataCapacity = 0)
			: m_objects(objects)
			, m_data(dataCapacity)
			, m_count(0)
			, m_hash(generate_hash(objects))
		{
		}

		~Batch()
		{
		}

#pragma endregion

#pragma region Operators

	public:
		Bool operator==(Batch<N, Args...> const& other) const
		{
			auto const& otherObjects = other.get_objects();
			for (Size i = 0; i < N; i++)
			{
				if (m_objects[i] != otherObjects[i])
				{
					return false;
				}
			}

			return true;
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the number of objects in this Batch.
		 * @returns The number of objects.
		 */
		constexpr Size get_object_count() const { return sizeof...(Args); }

		/**
		 * @brief Gets the array of objects in this Batch.
		 * @returns The array of objects.
		 */
		Array<std::variant<Args...>, N>& get_objects() { return m_objects; }

		/**
		 * @brief Gets the array of objects in this Batch.
		 * @returns The array of objects.
		 */
		Array<std::variant<Args...>, N> const& get_objects() const { return m_objects; }

		/**
		 * @brief Gets the object at the given index, cast to the specified type.
		 * @tparam T The type to cast to.
		 * @param index The index of the object.
		 * @returns A reference to the object.
		 */
		template<typename T>
		T& get_object(Size const index)
		{
			auto& element = m_objects[index];

			if (auto* val = std::get_if<T>(&element))
			{
				return *val;
			}

			// not a valid type
			throw std::bad_variant_access();
		}

		/**
		 * @brief Gets the object at the given index, cast to the specified type.
		 * @tparam T The type to cast to.
		 * @param index The index of the object.
		 * @returns A reference to the object.
		 */
		template<typename T>
		T const& get_object(Size const index) const
		{
			auto const& element = m_objects[index];

			if (auto* val = std::get_if<T>(&element))
			{
				return *val;
			}

			// not a valid type
			throw std::bad_variant_access();
		}

		/**
		 * @brief Gets the compiled data container.
		 * @returns The data container.
		 */
		inline DynamicContainer& get_data_container() { return m_data; }

		/**
		 * @brief Gets the compiled data container.
		 * @returns The data container.
		 */
		inline DynamicContainer const& get_data_container() const { return m_data; }

		/**
		 * @brief Gets a pointer to the compiled data.
		 * @returns A pointer to the data.
		 */
		inline void* get_data() const { return m_data.get_data(); }

		/**
		 * @brief Gets the size of the compiled data.
		 * @returns The size of the data.
		 */
		inline Size get_data_size() const { return m_data.get_size(); }

		/**
		 * @brief Gets the number of elements in this Batch.
		 * @returns The number of elements.
		 */
		inline Size get_count() const { return m_count; }

		/**
		 * @brief Sets the number of elements in this Batch.
		 * @param count The number of elements.
		 */
		inline void set_count(Size const count) const { m_count = count; }

		/**
		 * @brief Gets the hash of this Batch.
		 * @returns The hash value.
		 */
		inline Size get_hash() const { return m_hash; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Checks if this Batch is empty.
		 * @returns True if the Batch has no elements.
		 */
		inline Bool empty() const { return m_count == 0; }

		/**
		 * @brief Increments the number of elements in this Batch.
		 */
		inline void increment() { m_count += 1; }
		
	private:
		static Size generate_hash(Array<std::variant<Args...>, sizeof...(Args)> const& objects)
		{
			Size hash = N;

			// generate the hash once here, since it will never change throughout this object's lifetime
			for (auto const& element : objects) {
				std::visit([&](auto const& val) {
					hash ^= std::hash<std::decay_t<decltype(val)>>{}(val)+0x9e3779b9 + (hash << 6) + (hash >> 2);
					}, element);
			}

			return hash;
		}

#pragma endregion

#pragma region Variables

	private:
		Array<std::variant<Args...>, N> m_objects;
		DynamicContainer m_data;
		Size m_count;
		Size m_hash;

#pragma endregion
	};
}

namespace std
{
	template<Minty::Size N, typename... Args>
	struct hash<Minty::Batch<N, Args...>>
	{
		size_t operator()(Minty::Batch<N, Args...> const& obj) const
		{
			return obj.get_hash();
		}
	};
}

#endif // MINTY_DATA_BATCH_H