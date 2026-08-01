#pragma once

#include "Core/Data/Map.hpp"

namespace Minty
{
    template <typename Key, typename Value>
    class Factory
    {
#pragma region Constructor

    public:
        Factory()
            : m_data()
        {
        }

        Factory(Size const capacity)
            : m_data(capacity)
        {
        }

#pragma endregion

#pragma region Iterator

    public:
        using Iterator = typename Map<Key, Value>::Iterator;
        using ConstIterator = typename Map<Key, Value>::ConstIterator;

        Iterator begin()
        {
            return m_data.begin();
        }

        Iterator end()
        {
            return m_data.end();
        }

        ConstIterator begin() const
        {
            return m_data.begin();
        }

        ConstIterator end() const
        {
            return m_data.end();
        }

#pragma endregion

#pragma region Accessors

    public:
        inline Size get_size() const
        {
            return m_data.get_size();
        }

        inline Bool is_empty() const
        {
            return m_data.is_empty();
        }

#pragma endregion

#pragma region Methods

    public:
        Value &create(Key const &key)
        {
            MINTY_ASSERT(!m_data.contains(key), ErrorCodeEnum::Argument_KeyAlreadyExists);
            m_data.add(key, Value());
            return m_data.at(key);
        }

        Value &get_or_create(Key const &key)
        {
            if (!m_data.contains(key))
            {
                m_data.add(key, Value());
            }
            return m_data.at(key);
        }

        Value &get(Key const &key)
        {
            MINTY_ASSERT(m_data.contains(key), ErrorCodeEnum::Argument_KeyNotFound);
            return m_data.at(key);
        }

        Value const &get(Key const &key) const
        {
            MINTY_ASSERT(m_data.contains(key), ErrorCodeEnum::Argument_KeyNotFound);
            return m_data.at(key);
        }

#pragma endregion

#pragma region Variables

    private:
        Map<Key, Value> m_data;

#pragma endregion
    };
}