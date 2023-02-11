#pragma once

#include "M_Object.h"

namespace minty
{
    struct Point;

    /// <summary>
    /// Holds X and Y coordinates for a floating point pair in space.
    /// </summary>
    struct MINTY_API PointF :
        public Object
    {
        float x, y;

        /// <summary>
        /// Creates a new floating Point at (0, 0).
        /// </summary>
        PointF()
            : x(0.0f), y(0.0f) {}

        /// <summary>
        /// Creates a new floating Point at the given X and Y.
        /// </summary>
        /// <param name="_x"></param>
        /// <param name="_y"></param>
        PointF(float const _x, float const _y)
            : x(_x), y(_y) {}

        /// <summary>
        /// Creates a new floating Point at the given X and Y.
        /// </summary>
        /// <param name="_x"></param>
        /// <param name="_y"></param>
        PointF(int const _x, int const _y)
            : x(static_cast<float>(_x)), y(static_cast<float>(_y)) {}

        PointF(PointF const& other)
            : x(other.x)
            , y(other.y)
        {}

        bool operator ==(PointF const& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator < (PointF const& other) const
        {
            if (y == other.y)
            {
                return x < other.x;
            }
            else {
                return y < other.y;
            }
        }

        PointF operator +(PointF const& other) const
        {
            return PointF(x + other.x, y + other.y);
        }

        PointF operator -(PointF const& other) const
        {
            return PointF(x - other.x, y - other.y);
        }

        Point toPointF() const;

        std::string const toString() const override;
    };
}

namespace std
{
    template<>
    struct hash<minty::PointF>
    {
        std::size_t operator()(const minty::PointF& obj) const
        {
            return hash<float>()(obj.x) ^ (hash<float>()(obj.y) << 1);
        }
    };
}