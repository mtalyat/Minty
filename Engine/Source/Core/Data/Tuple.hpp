#pragma once

/**
 * @file Tuple.hpp
 * @brief Header file defining the Tuple class for holding multiple values.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include <tuple>

namespace Minty
{
	/**
	 * @class Tuple
	 * @brief A class representing a fixed-size collection of heterogeneous values.
	 */
	template <typename... Types>
	class Tuple;

	/**
	 * @class Tuple
	 * @brief Specialization for the base case: an empty tuple.
	 */
	template <>
	class Tuple<>
	{
	public:
		constexpr bool operator==(const Tuple<> &) const noexcept { return true; }
		constexpr bool operator!=(const Tuple<> &) const noexcept { return false; }
		constexpr bool operator<(const Tuple<> &) const noexcept { return false; }
		constexpr bool operator>(const Tuple<> &) const noexcept { return false; }
		constexpr bool operator<=(const Tuple<> &) const noexcept { return true; }
		constexpr bool operator>=(const Tuple<> &) const noexcept { return true; }
	};

	/**
	 * @class Tuple
	 * @brief Specialization for tuples with at least one element.
	 * @tparam T The type of the first element.
	 * @tparam Rest The types of the remaining elements.
	 */
	template <typename T, typename... Rest>
	class Tuple<T, Rest...> : private Tuple<Rest...>
	{
#pragma region Types

	public:
		/**
		 * @brief The base class representing the rest of the tuple.
		 */
		using Base = Tuple<Rest...>;

#pragma endregion

#pragma region Constructors

		/**
		 * @brief Default constructor.
		 */
		constexpr Tuple()
			: Base(), first()
		{
		}

		/**
		 * @brief Variadic constructor to initialize all elements of the tuple.
		 * @tparam U The type of the first argument.
		 */
		template <typename U, typename... URest,
				  typename = std::enable_if_t<std::is_constructible_v<T, U &&>>>
		constexpr Tuple(U &&first, URest &&...rest)
			: Base(std::forward<URest>(rest)...), first(std::forward<U>(first))
		{
		}

		/**
		 * @brief Copy constructor.
		 */
		constexpr Tuple(Tuple const &other)
			: Base(other.rest()), first(other.first)
		{
		}

		/**
		 * @brief Move constructor.
		 */
		constexpr Tuple(Tuple &&other) noexcept
			: Base(std::move(other.rest())), first(std::move(other.first))
		{
		}

		~Tuple() = default;

#pragma endregion

#pragma region Operators

		constexpr Tuple &operator=(Tuple const &other)
		{
			if (this != &other)
			{
				first = other.first;
				Base::operator=(other.rest());
			}
			return *this;
		}

		constexpr Tuple &operator=(Tuple &&other) noexcept
		{
			if (this != &other)
			{
				first = std::move(other.first);
				Base::operator=(std::move(other.rest()));
			}
			return *this;
		}

		constexpr bool operator==(const Tuple &other) const
		{
			return first == other.first && rest() == other.rest();
		}

		constexpr bool operator!=(const Tuple &other) const
		{
			return !(*this == other);
		}

		constexpr bool operator<(const Tuple &other) const
		{
			if (first < other.first)
				return true;
			if (other.first < first)
				return false;
			return rest() < other.rest();
		}

		constexpr bool operator>(const Tuple &other) const
		{
			return other < *this;
		}

		constexpr bool operator<=(const Tuple &other) const
		{
			return !(other < *this);
		}

		constexpr bool operator>=(const Tuple &other) const
		{
			return !(*this < other);
		}

#pragma endregion

#pragma region Accessors

		/**
		 * @brief Access the rest of the tuple.
		 */
		constexpr const Base &rest() const noexcept { return *this; }

		/**
		 * @brief Access the rest of the tuple.
		 */
		constexpr Base &rest() noexcept { return *this; }

		/**
		 * @brief Access the value at the given index.
		 */
		template <Size Index>
		constexpr auto &get() noexcept
		{
			if constexpr (Index == 0)
				return first;
			else
				return rest().template get<Index - 1>();
		}

		/**
		 * @brief Access the value at the given index.
		 */
		template <Size Index>
		constexpr const auto &get() const noexcept
		{
			if constexpr (Index == 0)
				return first;
			else
				return rest().template get<Index - 1>();
		}

		/**
		 * @brief Access the first element of the tuple.
		 */
		constexpr const auto &get_first() const noexcept
		{
			return first;
		}

		/**
		 * @brief Access the first element of the tuple.
		 */
		constexpr auto &get_first() noexcept
		{
			return first;
		}

		/**
		 * @brief Access the second element of the tuple.
		 */
		constexpr const auto &get_second() const noexcept
		{
			return get<1>();
		}

		/**
		 * @brief Access the second element of the tuple.
		 */
		constexpr auto &get_second() noexcept
		{
			return get<1>();
		}

		/**
		 * @brief Access the third element of the tuple.
		 */
		constexpr const auto &get_third() const noexcept
		{
			return get<2>();
		}

		/**
		 * @brief Access the third element of the tuple.
		 */
		constexpr auto &get_third() noexcept
		{
			return get<2>();
		}

#pragma endregion

#pragma region Variables

	public:
		/**
		 * @brief The first element of the tuple.
		 */
		T first;

#pragma endregion
	};
}

namespace std
{
	template <typename... Types>
	struct tuple_size<Minty::Tuple<Types...>> : std::integral_constant<std::size_t, sizeof...(Types)>
	{
	};

	template <std::size_t Index, typename T, typename... Rest>
	struct tuple_element<Index, Minty::Tuple<T, Rest...>>
	{
		using type = typename tuple_element<Index - 1, Minty::Tuple<Rest...>>::type;
	};

	template <typename T, typename... Rest>
	struct tuple_element<0, Minty::Tuple<T, Rest...>>
	{
		using type = T;
	};
}