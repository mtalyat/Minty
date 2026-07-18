#pragma once

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    class View
    {
#pragma region Constructor

    public:
        constexpr View()
            : mp_data(nullptr), m_size(0)
        {
        }

        constexpr View(PointerConst data, Size size)
            : mp_data(data), m_size(size)
        {
        }

#pragma endregion

#pragma region Operator

    public:
        constexpr operator PointerConst() const { return mp_data; }

        constexpr Bool operator==(View const &other) const { return mp_data == other.mp_data && m_size == other.m_size; }
        constexpr Bool operator!=(View const &other) const { return !(*this == other); }
        constexpr Bool operator==(Null const) const { return mp_data == nullptr; }
        constexpr Bool operator!=(Null const) const { return mp_data != nullptr; }

#pragma endregion

#pragma region Accessors

    public:
        inline PointerConst get_data() const { return mp_data; }

        inline Size get_size() const { return m_size; }

        inline Bool is_empty() const { return mp_data == nullptr || m_size == 0; }

#pragma endregion

    private:
        PointerConst mp_data;
        Size m_size;
    };
}