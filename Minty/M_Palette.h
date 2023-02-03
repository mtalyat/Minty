#pragma once

#include "M_Object.h"

namespace minty
{
    /// <summary>
    /// Holds a collection of data that represents a palette.
    /// </summary>
    /// <typeparam name="ID"></typeparam>
    /// <typeparam name="V"></typeparam>
    template<typename ID, typename V>
    class Palette
        : public Object
    {
    private:
        ID const m_capacity;
        std::map<ID, V> m_data;

    public:
        Palette(ID const capacity)
            : m_capacity(capacity)
            , m_data(std::map<ID, V>(capacity))
        {}

        /// <summary>
        /// Gets the value using the given id.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        V get(ID const id) const { return m_data.at(id); }

        /// <summary>
        /// Checks if this Palette contains the given id.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        bool contains(ID const id) { return m_data.find(id) != m_data.end(); }

        /// <summary>
        /// Adds the given value to this Palette, using the given id.
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        bool add(ID const id, V const value)
        {
            if (contains(id)) return false;

            m_data.emplace(id, value);

            return true;
        }

        /// <summary>
        /// Sets the value of the given id to the given value.
        /// </summary>
        /// <param name="id"></param>
        /// <param name="value"></param>
        void set(ID const id, V const value)
        {
            m_data[id] = value;
        }
    };
}