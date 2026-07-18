#pragma once

/**
 * @file Any.h
 * @brief A type-erased container for any type of object.
 * @author Mitchell Talyat
 */

#include "Unique.hpp"
#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    /**
     * @class Any
     * @brief A type-erased container for any type of object.
     */
    class Any
    {
#pragma region Type

    private:
        struct Base
        {
            virtual ~Base() = default;
            virtual Base* clone() const = 0;
            virtual TypeInfo const &get_type() const = 0;
        };

        template <typename T>
        struct Derived : Base
        {
            T value;

            Derived(T &&val)
                : value(std::move(val))
            {
            }

            template <typename U>
            Derived(U &&value)
                : value(std::forward<U>(value))
            {
            }

            Base* clone() const override
            {
                return new Derived<T>(value);
            }

            TypeInfo const &get_type() const override
            {
                return typeid(T);
            }
        };

#pragma endregion

#pragma region Constructors

    public:
        /**
         * @brief Creates an empty Any.
         */
        Any()
            : mp_data(nullptr)
        {
        }

        /**
         * @brief Creates an Any containing the given value.
         * @param value The value to store in the Any.
         */
        template <typename T>
        Any(T const &value)
            : mp_data(new Derived<T>(value))
        {
        }

        /**
         * @brief Creates an Any containing the given value, using perfect forwarding.
         * @param value The value to store in the Any.
         */
        template<typename T>
        Any(T &&value)
            : mp_data(new Derived<T>(std::forward<T>(value)))
        {
        }
        
        Any(Any const &other)
            : mp_data(other.mp_data ? other.mp_data->clone() : nullptr)
        {
        }

        Any(Any &&other) noexcept
            : mp_data(other.mp_data)
        {
            other.mp_data = nullptr;
        }

        ~Any()
        {
            delete mp_data;
        }

#pragma endregion

#pragma region Operators

    public:
        Any &operator=(Any const &other)
        {
            if (this != &other)
            {
                delete mp_data;
                mp_data = other.mp_data ? other.mp_data->clone() : nullptr;
            }
            return *this;
        }

        Any &operator=(Any &&other) noexcept
        {
            if (this != &other)
            {
                delete mp_data;
                mp_data = other.mp_data;
                other.mp_data = nullptr;
            }
            return *this;
        }

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Checks if the Any contains a value.
         * @return True if the Any contains a value, false otherwise.
         */
        Bool is_valid() const
        {
            return mp_data != nullptr;
        }

#pragma endregion

#pragma region Methods

    public:
        TypeInfo const &get_type() const
        {
            return mp_data ? mp_data->get_type() : typeid(void);
        }

        template <typename T>
        T &cast() const
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCodeEnum::Object_InvalidState);
            MINTY_ASSERT(mp_data->get_type() == typeid(T), ErrorCodeEnum::Object_TypeMismatch);
            return static_cast<Derived<T> *>(mp_data)->value;
        }

        template <typename T>
        T const &cast() const
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCodeEnum::Object_InvalidState);
            MINTY_ASSERT(mp_data->get_type() == typeid(T), ErrorCodeEnum::Object_TypeMismatch);
            return static_cast<Derived<T> *>(mp_data)->value;
        }

#pragma endregion

#pragma region Variables

    private:
        Base* mp_data;

#pragma endregion
    };
}