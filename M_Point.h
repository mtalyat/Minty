#pragma once

#include "M_Object.h"
#include "M_Math.h"
#include <iostream>

namespace minty
{
    /// <summary>
    /// Holds X and Y coordinates for a point in space.
    /// </summary>
    struct MINTY_API Point :
        public Object
    {
        int x, y;

        /// <summary>
        /// Creates a new Point at (0, 0).
        /// </summary>
        Point()
            : x(0), y(0) {}

        /// <summary>
        /// Creates a new Point using the given X and Y values.
        /// </summary>
        /// <param name="_x"></param>
        /// <param name="_y"></param>
        Point(int const _x, int const _y)
            : x(_x), y(_y) {}

        /// <summary>
        /// Creates a Point using the given X and Y values, floored.
        /// </summary>
        /// <param name="_x"></param>
        /// <param name="_y"></param>
        Point(float const _x, float const _y);

        Point(Point const& other)
            : x(other.x)
            , y(other.y)
        {}

        bool operator ==(Point const& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator < (Point const& other) const
        {
            if (y == other.y)
            {
                return x < other.x;
            }
            else {
                return y < other.y;
            }
        }

        Point operator +(Point const& other) const
        {
            return Point(x + other.x, y + other.y);
        }

        Point operator -(Point const& other) const
        {
            return Point(x - other.x, y - other.y);
        }

        std::string const toString() const override { return std::format("Point({0}, {1})", x, y); }
    };
}

namespace std
{
    template<>
    struct hash<minty::Point>
    {
        std::size_t operator()(const minty::Point& obj) const
        {
            return hash<int>()(obj.x) ^ (hash<int>()(obj.y) << 1);
        }
    };
}