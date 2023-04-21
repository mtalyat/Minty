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
        /// <summary>
        /// Creates an empty, 0 size Grid.
        /// </summary>
        Grid()
            : m_width(0)
            , m_height(0)
            , m_elements()
        {}

        /// <summary>
        /// Creates a Grid of the given width and height.
        /// </summary>
        /// <param name="width"></param>
        /// <param name="height"></param>
        Grid(int const width, int const height)
            : m_width(width)
            , m_height(height)
            , m_elements()
        {
            m_elements.resize(width * height);
        }

        // copy constructor
        Grid(Grid const& other)
            : m_width(other.m_width)
            , m_height(other.m_height)
            , m_elements(other.m_elements)
        {}

        // index operator
        T& operator[](int const i) { return m_elements[i]; }
        // index operator
        T const& operator[](int const i) const { return m_elements[i]; }

        /// <summary>
        /// Checks if the Grid contains the given X and Y position.
        /// </summary>
        /// <param name="x">The column position.</param>
        /// <param name="y">The row position.</param>
        /// <returns>True if X and Y are within 0 and the width or height, respectively.</returns>
        inline bool contains(int const x, int const y) const { return x >= 0 && x < m_width&& y >= 0 && y < m_height; }
        /// <summary>
        /// Checks if the Grid contains the given index.
        /// </summary>
        /// <param name="i">The index position.</param>
        /// <returns>True if i is within 0 and the size of the Grid.</returns>
        inline bool contains(int const i) const { return i >= 0 && i < static_cast<int>(m_elements.size()); }

        /// <summary>
        /// Gets the element at the given index.
        /// </summary>
        /// <param name="i">The index of the element.</param>
        /// <returns>The element at index i.</returns>
        inline T& get(int const i) { return m_elements[i]; }
        /// <summary>
        /// Gets the element at the given X and Y position.
        /// </summary>
        /// <param name="x">The column position.</param>
        /// <param name="y">The row position.</param>
        /// <returns>The element at the given position.</returns>
        inline T& get(int const x, int const y) { return m_elements[y * m_width + x]; }
        /// <summary>
        /// Gets the element at the given index.
        /// </summary>
        /// <param name="i">The index of the element.</param>
        /// <returns>The element at index i.</returns>
        inline T get(int const i) const { return m_elements[i]; }
        /// <summary>
        /// Gets the element at the given X and Y position.
        /// </summary>
        /// <param name="x">The column position.</param>
        /// <param name="y">The row position.</param>
        /// <returns>The element at the given position.</returns>
        inline T get(int const x, int const y) const { return m_elements[y * m_width + x]; }
        /// <summary>
        /// Sets the element at the given index.
        /// </summary>
        /// <param name="i">The index of the element.</param>
        /// <param name="t">The Grid element type.</param>
        inline void set(int const i, T const& t) { m_elements[i] = t; }
        /// <summary>
        /// Sets the element at the given X and Y position.
        /// </summary>
        /// <param name="x">The column position.</param>
        /// <param name="y">The row position.</param>
        /// <param name="t">The Grid element type.</param>
        inline void set(int const x, int const y, T const& t) { m_elements[y * m_width + x] = t; }

        /// <summary>
        /// Swaps the two Grid elements at the given indices.
        /// </summary>
        /// <param name="i">The index of the first element.</param>
        /// <param name="j">The index of the second element.</param>
        inline void swap(int i, int j)
        {
            T temp = m_elements[i];
            m_elements[i] = m_elements[j];
            m_elements[j] = temp;
        }
        /// <summary>
        /// Swaps the two Grid elements at the given X and Y positions.
        /// </summary>
        /// <param name="x1">The column of the first position.</param>
        /// <param name="y1">The row of the first position.</param>
        /// <param name="x2">The column of the second position.</param>
        /// <param name="y2">The row of the second position.</param>
        inline void swap(int const x1, int const y1, int const x2, int const y2)
        {
            swap(y1 * m_width + x1, y2 * m_width + x2);
        }

        /// <summary>
        /// Gets the width of the Grid.
        /// </summary>
        /// <returns>The width.</returns>
        constexpr int width() const { return m_width; }
        /// <summary>
        /// Gets the height of the Grid.
        /// </summary>
        /// <returns>The height.</returns>
        constexpr int height() const { return m_height; }
        /// <summary>
        /// Gets the size of the Grid.
        /// </summary>
        /// <returns>The width * height.</returns>
        constexpr int size() const { return m_width * m_height; }

        std::string const toString() const override { return std::format("Grid({0}, {1})", m_width, m_height); }
    };
}