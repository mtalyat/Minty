#pragma once

/**
 * @file IndexPool.h
 * @brief Header file for the IndexPool class, a container that manages a pool of indices for storing objects.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Type/Handle.h"
#include "Core/Data/Vector.h"
#include "Core/Data/Stack.h"
#include "Core/Constant/Invalid.h"
#include <iterator>

namespace Minty
{
    template <typename T, typename IndexT = Index>
    class IndexPool
    {
#pragma region Constructors

    public:
        IndexPool()
            : m_data(), m_free(), m_freeCount(0)
        {
        }

        IndexPool(IndexPool const &other) = default;
        IndexPool(IndexPool &&other) noexcept = default;
        ~IndexPool() = default;

#pragma endregion

#pragma region Iterators

    public:
        class Iterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

        private:
            Vector<T>::Iterator m_iter;
            Vector<Bool>::Iterator m_freeIter;

        private:
            inline explicit Iterator(Vector<T>::Iterator const &iter, Vector<Bool>::Iterator const &freeIter)
                : m_iter(iter), m_freeIter(freeIter)
            {
            }

        public:
            inline reference operator*() const
            {
                return *m_iter;
            }

            inline pointer operator->() const
            {
                return m_iter.operator->();
            }

            Iterator &operator++()
            {
                do
                {
                    ++m_iter;
                    ++m_freeIter;
                } while (m_freeIter != m_free.end() && *m_freeIter == true);

                return *this;
            }

            Iterator operator++(int)
            {
                Iterator temp = *this;
                do
                {
                    ++m_iter;
                    ++m_freeIter;
                } while (m_freeIter != m_free.end() && *m_freeIter == true);
                return temp;
            }

            inline Iterator operator+(Size const value)
            {
                return Iterator(m_iter + value, m_freeIter + value);
            }

            inline Bool operator==(Iterator const &other) const { return m_iter == other.m_iter; }
            inline Bool operator!=(Iterator const &other) const { return m_iter != other.m_iter; }
        };

        class ConstIterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = value_type const *;
            using reference = value_type const &;

        private:
            Vector<T>::ConstIterator m_iter;
            Vector<Bool>::ConstIterator m_freeIter;

        private:
            inline explicit ConstIterator(Vector<T>::ConstIterator const &iter, Vector<Bool>::ConstIterator const &freeIter)
                : m_iter(iter), m_freeIter(freeIter)
            {
            }

        public:
            inline reference operator*() const
            {
                return *m_iter;
            }

            inline pointer operator->() const
            {
                return m_iter.operator->();
            }

            ConstIterator &operator++()
            {
                do
                {
                    ++m_iter;
                    ++m_freeIter;
                } while (m_freeIter != m_free.end() && *m_freeIter == true);
                return *this;
            }

            ConstIterator operator++(int)
            {
                ConstIterator temp = *this;
                do
                {
                    ++m_iter;
                    ++m_freeIter;
                } while (m_freeIter != m_free.end() && *m_freeIter == true);
                return temp;
            }

            inline ConstIterator operator+(Size const value)
            {
                return ConstIterator(m_iter + value, m_freeIter + value);
            }

            inline Bool operator==(ConstIterator const &other) const { return m_iter == other.m_iter; }
            inline Bool operator!=(ConstIterator const &other) const { return m_iter != other.m_iter; }
        };

        Iterator begin() { return Iterator(m_data.begin(), m_free.begin()); }

        Iterator end() { return Iterator(m_data.end(), m_free.end()); }

        ConstIterator begin() const { return ConstIterator(m_data.begin(), m_free.begin()); }

        ConstIterator end() const { return ConstIterator(m_data.end(), m_free.end()); }

#pragma endregion

#pragma region Operators

    public:
        IndexPool &operator=(IndexPool const &other) = default;
        IndexPool &operator=(IndexPool &&other) noexcept = default;

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the number of entries currently stored in the list.
         * @return The number of entries in the list.
         */
        inline Size get_size() const { return m_data.get_size() - m_freeCount; }

        /**
         * @brief Gets the total capacity of the list.
         * @return The capacity of the list.
         */
        inline Size get_capacity() const { return m_data.get_capacity(); }

        /**
         * @brief Checks if the list is empty (contains no entries).
         * @return True if the list is empty, false otherwise.
         */
        inline Bool is_empty() const { return m_freeCount == m_data.get_size(); }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Adds a new entry with the given value to the list and returns a handle to it.
         * @param value The value to store in the new entry.
         * @return A handle that can be used to access the new entry.
         */
        IndexT add(T const &value)
        {
            Index index;

            // add a new one if no free entries, otherwise use a free entry
            if (m_freeCount == 0)
            {
                index = static_cast<Index>(m_data.get_size());
                m_data.add(value);
                m_free.add(false);
            }
            else
            {
                // find an empty slot
                index = find_empty_slot();
                m_data.at(index) = value;
                m_free.at(index) = false;
                m_freeCount--;
            }

            return static_cast<IndexT>(index);
        }

        /**
         * @brief Adds a new entry with the given value to the list and returns a handle to it.
         * @param value The value to store in the new entry.
         * @return A handle that can be used to access the new entry.
         */
        IndexT add(T &&value)
        {
            Index index;

            // add a new one if no free entries, otherwise use a free entry
            if (m_freeCount == 0)
            {
                index = static_cast<Index>(m_data.get_size());
                m_data.add(std::forward<T>(value));
                m_free.add(false);
            }
            else
            {
                index = find_empty_slot();
                m_data.at(index) = std::forward<T>(value);
                m_free.at(index) = false;
                m_freeCount--;
            }

            return static_cast<IndexT>(index);
        }

        /**
         * @brief Inserts a new entry with the given value at the specified index in the list.
         * @param index The index at which to insert the new entry.
         * @param value The value to store in the new entry.
         */
        void insert(IndexT const indext, T const& value)
        {
            Index const index = static_cast<Index>(indext);
            MINTY_ASSERT(index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            MINTY_ASSERT(m_free.at(index) == true, ErrorCodeEnum::Argument_KeyNotFound);
            m_data.at(index) = value;
            m_free.at(index) = false;
            m_freeCount--;
        }

        /**
         * @brief Inserts a new entry with the given value at the specified index in the list.
         * @param index The index at which to insert the new entry.
         * @param value The value to store in the new entry.
         */
        void insert(IndexT const indext, T &&value)
        {
            Index const index = static_cast<Index>(indext);
            MINTY_ASSERT(index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            MINTY_ASSERT(m_free.at(index) == true, ErrorCodeEnum::Argument_KeyNotFound);
            m_data.at(index) = std::forward<T>(value);
            m_free.at(index) = false;
            m_freeCount--;
        }

        /**
         * @brief Removes the entry corresponding to the given index from the list.
         * @param index The index of the entry to remove.
         * @return True if the entry was successfully removed, false if the index was invalid.
         */
        void remove(IndexT const indext)
        {
            Index const index = static_cast<Index>(indext);
            MINTY_ASSERT(index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            MINTY_ASSERT(m_free.at(index) == false, ErrorCodeEnum::Argument_KeyNotFound);
            m_data.at(index) = T();
            m_free.at(index) = true;
            m_freeCount++;
        }

        /**
         * @brief Checks if the given index corresponds to a valid entry in the list.
         * @param index The index to check.
         * @return True if the index is valid, false otherwise.
         */
        Bool contains(IndexT const indext) const
        {
            Index const index = static_cast<Index>(indext);
            if (index >= m_data.get_size())
            {
                return false;
            }
            return m_free.at(index) == false;
        }

        /**
         * @brief Gets a reference to the value stored in the entry corresponding to the given index.
         * @param index The index of the entry to access.
         */
        T &at(IndexT const indext)
        {
            Index const index = static_cast<Index>(indext);
            MINTY_ASSERT(index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            MINTY_ASSERT(m_free.at(index) == false, ErrorCodeEnum::Argument_KeyNotFound);
            return m_data.at(index);
        }

        /**
         * @brief Gets a const reference to the value stored in the entry corresponding to the given index.
         * @param index The index of the entry to access.
         */
        T const &at(IndexT const indext) const
        {
            Index const index = static_cast<Index>(indext);
            MINTY_ASSERT(index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            MINTY_ASSERT(m_free.at(index) == false, ErrorCodeEnum::Argument_KeyNotFound);
            return m_data.at(index);
        }

        /**
         * @brief Gets a pointer to the value stored in the entry corresponding to the given index, or nullptr if the index is invalid.
         * @param index The index of the entry to access.
         * @return A pointer to the value, or nullptr if the index is invalid.
         */
        T *get(IndexT const indext)
        {
            Index const index = static_cast<Index>(indext);
            if (index >= m_data.get_size())
            {
                return nullptr;
            }
            if (m_free.at(index) == true)
            {
                return nullptr;
            }
            return &m_data.at(index);
        }

        /**
         * @brief Gets a const pointer to the value stored in the entry corresponding to the given index.
         * @param index The index of the entry to access.
         * @return A const pointer to the value, or nullptr if the index is invalid.
         */
        T const *get(IndexT const indext) const
        {
            Index const index = static_cast<Index>(indext);
            if (index >= m_data.get_size())
            {
                return nullptr;
            }
            if (m_free.at(index) == true)
            {
                return nullptr;
            }
            return &m_data.at(index);
        }

        /**
         * @brief Reserves space for at least the given number of entries in the list.
         * @param capacity The minimum capacity to reserve.
         */
        void reserve(Size const capacity)
        {
            m_data.reserve(capacity);
            m_free.reserve(capacity);
        }

        /**
         * @brief Resizes the list to contain exactly the given number of entries. If the new size is larger than the current size, new entries will be added and marked as free. If the new size is smaller than the current size, existing entries will be removed from the end of the list.
         * @param size The new size of the list.
         */
        void resize(Size const size)
        {
            MINTY_ASSERT(size >= get_size(), ErrorCodeEnum::Argument_OutOfRange);
            m_data.resize(size);
            m_free.resize(size, true);
            m_freeCount += size;
        }

        /**
         * @brief Clears all entries from the list, resetting it to an empty state.
         */
        void clear()
        {
            m_data.clear();
            m_free.clear();
            m_freeCount = 0;
        }

    private:
        Index find_empty_slot()
        {
            for (Index i = 0; i < m_free.get_size(); i++)
            {
                if (m_free.at(i) == true)
                {
                    return i;
                }
            }
            return INVALID_INDEX;
        }

#pragma endregion

#pragma region Variables

    private:
        Vector<T> m_data;
        Vector<Bool> m_free;
        Size m_freeCount;

#pragma endregion
    };
}