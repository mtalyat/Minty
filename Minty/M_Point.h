#pragma once

#include "M_Saveable.h"
#include "M_Math.h"
#include <iostream>

namespace minty
{
    struct PointF;

    /// <summary>
    /// Holds X and Y coordinates for a point in space.
    /// </summary>
    struct MINTY_API Point :
        public Saveable
    {
        /// <summary>
        /// The X position.
        /// </summary>
        int x;

        /// <summary>
        /// The Y position.
        /// </summary>
        int y;

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

        // copy constructor
        Point(Point const& other)
            : x(other.x)
            , y(other.y)
        {}

        // equals operator
        bool operator ==(Point const& other) const
        {
            return x == other.x && y == other.y;
        }

        // less than operator
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

        // add operator
        Point operator +(Point const& other) const
        {
            return Point(x + other.x, y + other.y);
        }

        // subtract operator
        Point operator -(Point const& other) const
        {
            return Point(x - other.x, y - other.y);
        }

        /// <summary>
        /// Converts this Point to a PointF.
        /// </summary>
        /// <returns>A PointF containing this Point's values.</returns>
        PointF toPointF() const;

        std::string const toString() const override { return std::format("Point({0}, {1})", x, y); }

        void serialize(boost::property_tree::ptree& ptree) override;
        void deserialize(boost::property_tree::ptree const& ptree) override;
        
        /// <summary>
        /// Converts the given polar coordinates to cartesian coordinates.
        /// </summary>
        /// <param name="polar">The polar coordinates.</param>
        /// <returns>The cartesian coordinates.</returns>
        static Point polarToCartesian(Point& const polar);

        /// <summary>
        /// Converts the given cartesian coordinates to polar coordinates.
        /// </summary>
        /// <param name="cartesian">The cartesian coordinates.</param>
        /// <returns>The polar coordinates.</returns>
        static Point cartesianToPolar(Point& const cartesian);
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