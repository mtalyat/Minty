#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// A tuple that holds a variable number of values.
	/// </summary>
	/// <typeparam name="Types">The types of the values.</typeparam>
	template<typename... Types>
	class Tuple;

	/// <summary>
	/// Specialization for the base case: an empty tuple.
	/// </summary>
	template<>
	class Tuple<>
	{
	public:
		constexpr Tuple() = default;
	};

	/// <summary>
	/// Specialization for a non-empty tuple.
	/// </summary>
	/// <typeparam name="T">The type of the first value.</typeparam>
	/// <typeparam name="Rest">The types of the remaining values.</typeparam>
	template<typename T, typename... Rest>
	class Tuple<T, Rest...> : private Tuple<Rest...>
	{
	public:
		/// <summary>
		/// The first value in the tuple.
		/// </summary>
		T first;

		/// <summary>
		/// The rest of the tuple.
		/// </summary>
		using Base = Tuple<Rest...>;

		constexpr Tuple()
			: Base(), first()
		{
		}

		/// <summary>
		/// Constructor to initialize the tuple.
		/// </summary>
		template<typename U, typename... URest,
			typename = std::enable_if_t<std::is_constructible_v<T, U&&>>>
		constexpr Tuple(U&& first, URest&&... rest)
			: Base(std::forward<URest>(rest)...), first(std::forward<U>(first))
		{
		}

		constexpr Tuple(Tuple const& other)
			: Base(other.rest()), first(other.first)
		{
		}

		constexpr Tuple(Tuple&& other) noexcept
			: Base(std::move(other.rest())), first(std::move(other.first))
		{
		}

		constexpr Tuple& operator=(Tuple const& other)
		{
			if (this != &other)
			{
				first = other.first;
				Base::operator=(other.rest());
			}
			return *this;
		}

		constexpr Tuple& operator=(Tuple&& other) noexcept
		{
			if (this != &other)
			{
				first = std::move(other.first);
				Base::operator=(std::move(other.rest()));
			}
			return *this;
		}

		/// <summary>
		/// Access the rest of the tuple.
		/// </summary>
		constexpr Base& rest() noexcept { return *this; }
		constexpr const Base& rest() const noexcept { return *this; }

		/// <summary>
		/// Access the value at the given index.
		/// </summary>
		template<Size Index>
		constexpr auto& get() noexcept
		{
			if constexpr (Index == 0)
				return first;
			else
				return rest().template get<Index - 1>();
		}

		/// <summary>
		/// Access the value at the given index (const version).
		/// </summary>
		template<Size Index>
		constexpr const auto& get() const noexcept
		{
			if constexpr (Index == 0)
				return first;
			else
				return rest().template get<Index - 1>();
		}

		constexpr const auto& get_first() const noexcept
		{
			return first;
		}

		constexpr auto& get_first() noexcept
		{
			return first;
		}

		constexpr const auto& get_second() const noexcept
		{
			return get<1>();
		}

		constexpr auto& get_second() noexcept
		{
			return get<1>();
		}

		constexpr const auto& get_third() const noexcept
		{
			return get<2>();
		}

		constexpr auto& get_third() noexcept
		{
			return get<2>();
		}
	};
}

namespace std
{
	template<typename... Types>
	struct tuple_size<Minty::Tuple<Types...>> : std::integral_constant<std::size_t, sizeof...(Types)>
	{
	};

	/// <summary>
	/// Specialization of std::tuple_element for Minty::Tuple.
	/// </summary>
	template<std::size_t Index, typename T, typename... Rest>
	struct tuple_element<Index, Minty::Tuple<T, Rest...>>
	{
		using type = typename tuple_element<Index - 1, Minty::Tuple<Rest...>>::type;
	};

	template<typename T, typename... Rest>
	struct tuple_element<0, Minty::Tuple<T, Rest...>>
	{
		using type = T;
	};
}