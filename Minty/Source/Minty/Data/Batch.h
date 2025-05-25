#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Array.h"
#include "Minty/Data/DynamicContainer.h"
#include "Minty/Data/Tuple.h"
#include <variant>

namespace Minty
{
	/// <summary>
	/// Holds a batch, or a compilation of a collection of data. Useful for rendering batches.
	/// </summary>
	template<typename Size N, typename ...Args>
	class Batch
	{
#pragma region Variables

	private:
		Array<std::variant<Args...>, N> m_objects;

		// The compilation of data for this Batch.
		DynamicContainer m_data;

		// The number of elements that have been included in this Batch.
		Size m_count;

		Size m_hash;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Batch.
		/// </summary>
		Batch()
			: m_objects()
			, m_data()
			, m_count(0)
			, m_hash(0)
		{
		}

		/// <summary>
		/// Creates a Batch with the given objects.
		/// </summary>
		/// <param name="objects">The objects.</param>
		/// <param name="dataCapacity">The capacity of the compiled data.</param>
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

#pragma region Get Set

	public:
		constexpr Size get_object_count() const { return sizeof...(Args); }

		Array<std::variant<Args...>, N>& get_objects() { return m_objects; }
		Array<std::variant<Args...>, N> const& get_objects() const { return m_objects; }

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

		inline DynamicContainer& get_data_container() { return m_data; }

		inline DynamicContainer const& get_data_container() const { return m_data; }

		inline void* get_data() const { return m_data.data(); }

		inline Size get_data_size() const { return m_data.size(); }

		inline Size get_count() const { return m_count; }

		inline void set_count(Size const count) const { m_count = count; }

		inline Size get_hash() const { return m_hash; }

#pragma endregion

#pragma region Methods

	public:
		inline Bool empty() const { return m_count == 0; }

		inline void increment() { m_count += 1; }

#pragma endregion

#pragma region Statics

	public:
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