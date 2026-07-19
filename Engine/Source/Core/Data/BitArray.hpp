#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Core/Debug/Debug.hpp"

namespace Minty
{
    template<Size N>
    class BitArray
    {
#pragma region Constructor

    public:
        constexpr BitArray()
            : m_data()
        {
        }

#pragma endregion

#pragma region Operator

    public:
        constexpr Bool operator==(BitArray const &other) const
        {
            for (Size i = 0; i < get_byte_size(); ++i)
            {
                if (m_data[i] != other.m_data[i])
                {
                    return false;
                }
            }
            return true;
        }

        constexpr Bool operator!=(BitArray const &other) const
        {
            return !(*this == other);
        }

        constexpr Bool operator[](Size const index) const
        {
            return get(index);
        }

#pragma endregion

#pragma region Accessor

public:
        constexpr Size get_size() const { return N; }

        constexpr Size get_byte_size() const { return (N + 7) / 8; }

#pragma endregion

#pragma region Method

    public:
        constexpr Bool get(Size const index) const
        {
            MINTY_ASSERT(index < N, ErrorCodeEnum::Argument_OutOfRange);
            
            return (m_data[index / 8] & (1 << (index % 8))) != 0;
        }

        constexpr void set(Size const index, Bool const value)
        {
            MINTY_ASSERT(index < N, ErrorCodeEnum::Argument_OutOfRange);

            if (value)
            {
                m_data[index / 8] |= (1 << (index % 8));
            }
            else
            {
                m_data[index / 8] &= ~(1 << (index % 8));
            }
        }

#pragma endregion

#pragma region Variable

    private:
        Byte m_data[(N + 7) / 8];

#pragma endregion
    };
}