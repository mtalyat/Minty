#pragma once

#include "M_Object.h"
#include <vector>

namespace minty
{
    /// <summary>
    /// A grid is a 2D collection of objects.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    template<typename T>
    class Grid :
        public Object
    {
    private:
        int const m_width;
        int const m_height;
        std::vector<T> m_elements;

    public:
        Grid()
            : m_width(0)
            , m_height(0)
            , m_elements()
        {}

        Grid(int const width, int const height)
            : m_width(width)
            , m_height(height)
            , m_elements()
        {
            m_elements.resize(width * height);
        }

        Grid(Grid const& other)
            : m_width(other.m_width)
            , m_height(other.m_height)
            , m_elements(other.m_elements)
        {}

        T& operator[](int const i) { return m_elements[i]; }
        T const& operator[](int const i) const { return m_elements[i]; }

        inline bool contains(int const x, int const y) const { return x >= 0 && x < m_width&& y >= 0 && y < m_height; }
        inline bool contains(int const i) const { return i >= 0 && i < static_cast<int>(m_elements.size()); }

        inline T& get(int const i) { return m_elements[i]; }
        inline T& get(int const x, int const y) { return m_elements[y * m_width + x]; }
        inline T get(int const i) const { return m_elements[i]; }
        inline T get(int const x, int const y) const { return m_elements[y * m_width + x]; }
        inline void set(int const i, T const& t) { m_elements[i] = t; }
        inline void set(int const x, int const y, T const& t) { m_elements[y * m_width + x] = t; }

        inline void swap(int i, int j)
        {
            T temp = m_elements[i];
            m_elements[i] = m_elements[j];
            m_elements[j] = temp;
        }

        inline void swap(int const x1, int const y1, int const x2, int const y2)
        {
            swap(y1 * m_width + x1, y2 * m_width + x2);
        }

        constexpr int width() const { return m_width; }
        constexpr int height() const { return m_height; }
        constexpr int size() const { return m_width * m_height; }

        std::string const toString() const override { return std::format("Grid({0}, {1})", m_width, m_height); }
    };
}