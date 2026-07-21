#pragma once

/**
 * @file ResourcePool.hpp
 * @brief Header file for the ResourcePool class, a container that manages a pool of handles for storing objects.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Type/Handle.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Data/Stack.hpp"
#include "Core/Constant/Invalid.hpp"
#include <iterator>

namespace Minty
{
    template <typename T, typename HandleT = T>
    class ResourcePool
    {
#pragma region Type

    public:
        using Handle = Handle<HandleT>;

#pragma endregion

#pragma region Constructors

    public:
        ResourcePool()
            : m_data(), m_generations(), m_uuids(), m_free()
        {
        }

        ResourcePool(ResourcePool const &other) = default;
        ResourcePool(ResourcePool &&other) noexcept = default;
        ~ResourcePool() = default;

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
            Vector<UInt32>::Iterator m_genIter;

        private:
            inline explicit Iterator(Vector<T>::Iterator const &iter, Vector<UInt32>::Iterator const &genIter)
                : m_iter(iter), m_genIter(genIter)
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
                    ++m_genIter;
                } while (m_genIter != m_generations.end() && *m_genIter == INVALID_GENERATION);

                return *this;
            }

            Iterator operator++(int)
            {
                Iterator temp = *this;
                do
                {
                    ++m_iter;
                    ++m_genIter;
                } while (m_genIter != m_generations.end() && *m_genIter == INVALID_GENERATION);
                return temp;
            }

            inline Iterator operator+(Size const value)
            {
                return Iterator(m_iter + value, m_genIter + value);
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
            Vector<UInt32>::ConstIterator m_genIter;

        private:
            inline explicit ConstIterator(Vector<T>::ConstIterator const &iter, Vector<UInt32>::ConstIterator const &genIter)
                : m_iter(iter), m_genIter(genIter)
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
                    ++m_genIter;
                } while (m_genIter != m_generations.end() && *m_genIter == INVALID_GENERATION);
                return *this;
            }

            ConstIterator operator++(int)
            {
                ConstIterator temp = *this;
                do
                {
                    ++m_iter;
                    ++m_genIter;
                } while (m_genIter != m_generations.end() && *m_genIter == INVALID_GENERATION);
                return temp;
            }

            inline ConstIterator operator+(Size const value)
            {
                return ConstIterator(m_iter + value, m_genIter + value);
            }

            inline Bool operator==(ConstIterator const &other) const { return m_iter == other.m_iter; }
            inline Bool operator!=(ConstIterator const &other) const { return m_iter != other.m_iter; }
        };

        Iterator begin() { return Iterator(m_data.begin(), m_generations.begin()); }

        Iterator end() { return Iterator(m_data.end(), m_generations.end()); }

        ConstIterator begin() const { return ConstIterator(m_data.begin(), m_generations.begin()); }

        ConstIterator end() const { return ConstIterator(m_data.end(), m_generations.end()); }

#pragma endregion

#pragma region Operators

    public:
        ResourcePool &operator=(ResourcePool const &other) = default;
        ResourcePool &operator=(ResourcePool &&other) noexcept = default;

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the number of entries currently stored in the list.
         * @return The number of entries in the list.
         */
        inline Size get_size() const { return m_data.get_size() - m_free.get_size(); }

        /**
         * @brief Gets the total capacity of the list.
         * @return The capacity of the list.
         */
        inline Size get_capacity() const { return m_data.get_capacity(); }

        /**
         * @brief Checks if the list is empty (contains no entries).
         * @return True if the list is empty, false otherwise.
         */
        inline Bool is_empty() const { return m_data.get_size() == m_free.get_size(); }

#pragma endregion

#pragma region Methods

        /**
         * @brief Adds a new entry with the given value to the list and returns a handle to it.
         * @param value The value to store in the new entry.
         * @param uuid The UUID to associate with the new entry.
         * @return A handle that can be used to access the new entry.
         */
        Handle add(T const &value, UUID const &uuid)
        {
            Index index;

            // add a new one if no free entries, otherwise use a free entry
            if (m_free.is_empty())
            {
                index = static_cast<Index>(m_data.get_size());
                m_data.add(value);
                m_generations.add(HandlePool<T>::INITIAL_GENERATION);
                m_uuids.add(uuid);
            }
            else
            {
                index = m_free.pop();
                m_data.at(index) = value;
                m_uuids.at(index) = uuid;
                m_generations.at(index)++;
            }

            // return a handle to the new entry
            Handle handle{};
            handle.generation = m_generations.at(index);
            handle.index = index;
            return handle;
        }

        /**
         * @brief Adds a new entry with the given value to the list and returns a handle to it.
         * @param value The value to store in the new entry.
         * @return A handle that can be used to access the new entry.
         */
        Handle add(T &&value, UUID const &uuid)
        {
            Index index;

            // add a new one if no free entries, otherwise use a free entry
            if (m_free.is_empty())
            {
                index = static_cast<Index>(m_data.get_size());
                m_data.add(std::forward<T>(value));
                m_generations.add(HandlePool<T>::INITIAL_GENERATION);
                m_uuids.add(uuid);
            }
            else
            {
                index = m_free.pop();
                m_data.at(index) = std::forward<T>(value);
                m_generations.at(index)++;
                m_uuids.at(index) = uuid;
            }

            // return a handle to the new entry
            Handle handle{};
            handle.generation = m_generations.at(index);
            handle.index = index;
            return handle;
        }

        void insert(Handle const handle, T const &value, UUID const &uuid)
        {
            while (handle.index >= m_data.get_size())
            {
                m_data.add(T());
                m_generations.add(INVALID_GENERATION);
                m_uuids.add(UUID());
            }
            Generation const generation = m_generations.at(handle.index);
            MINTY_ASSERT(generation == handle.generation || generation == INVALID_GENERATION, ErrorCodeEnum::Argument_KeyNotFound);
            m_data.at(handle.index) = value;
            m_generations.at(handle.index) = handle.generation;
            m_uuids.at(handle.index) = uuid;
        }

        void insert(Handle const handle, T &&value, UUID const &uuid)
        {
            while (handle.index >= m_data.get_size())
            {
                m_data.add(T());
                m_generations.add(INVALID_GENERATION);
                m_uuids.add(UUID());
            }
            Generation const generation = m_generations.at(handle.index);
            MINTY_ASSERT(generation == handle.generation || generation == INVALID_GENERATION, ErrorCodeEnum::Argument_KeyNotFound);
            m_data.at(handle.index) = std::forward<T>(value);
            m_generations.at(handle.index) = handle.generation;
            m_uuids.at(handle.index) = uuid;
        }

        /**
         * @brief Removes the entry corresponding to the given handle from the list.
         * @param handle The handle of the entry to remove.
         * @return True if the entry was successfully removed, false if the handle was invalid.
         */
        void remove(Handle const &handle)
        {
            MINTY_ASSERT(handle.index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            Generation const generation = m_generations.at(handle.index);
            MINTY_ASSERT(generation == handle.generation, ErrorCodeEnum::Argument_KeyNotFound);
            m_data.at(handle.index) = T();
            m_generations.at(handle.index) = INVALID_GENERATION;
            m_uuids.at(handle.index) = UUID();
            m_free.push(handle.index);
        }

        /**
         * @brief Checks if the given handle corresponds to a valid entry in the list.
         * @param handle The handle to check.
         * @return True if the handle is valid, false otherwise.
         */
        Bool contains(Handle const &handle) const
        {
            if (handle.index >= m_data.get_size())
            {
                return false;
            }
            Generation const generation = m_generations.at(handle.index);
            return generation == handle.generation;
        }

        /**
         * @brief Gets a reference to the value stored in the entry corresponding to the given handle.
         * @param handle The handle of the entry to access.
         */
        T &at(Handle const &handle)
        {
            MINTY_ASSERT(handle.index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            Generation const generation = m_generations.at(handle.index);
            MINTY_ASSERT(generation == handle.generation, ErrorCodeEnum::Argument_KeyNotFound);
            return m_data.at(handle.index);
        }

        /**
         * @brief Gets a const reference to the value stored in the entry corresponding to the given handle.
         * @param handle The handle of the entry to access.
         */
        T const &at(Handle const &handle) const
        {
            MINTY_ASSERT(handle.index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            Generation const generation = m_generations.at(handle.index);
            MINTY_ASSERT(generation == handle.generation, ErrorCodeEnum::Argument_KeyNotFound);
            return m_data.at(handle.index);
        }

        /**
         * @brief Gets a pointer to the value stored in the entry corresponding to the given handle, or nullptr if the handle is invalid.
         * @param handle The handle of the entry to access.
         * @return A pointer to the value, or nullptr if the handle is invalid.
         */
        T *get(Handle const &handle)
        {
            if (handle.index >= m_data.get_size())
            {
                return nullptr;
            }
            Generation const generation = m_generations.at(handle.index);
            if (generation != handle.generation)
            {
                return nullptr;
            }
            return &m_data.at(handle.index);
        }

        /**
         * @brief Gets a const pointer to the value stored in the entry corresponding to the given handle.
         * @param handle The handle of the entry to access.
         * @return A const pointer to the value, or nullptr if the handle is invalid.
         */
        T const *get(Handle const &handle) const
        {
            if (handle.index >= m_data.get_size())
            {
                return nullptr;
            }
            Generation const generation = m_generations.at(handle.index);
            if (generation != handle.generation)
            {
                return nullptr;
            }
            return &m_data.at(handle.index);
        }

        /**
         * @brief Gets a handle corresponding to the given UUID.
         * @param uuid The UUID to search for.
         * @return A handle corresponding to the given UUID, or an invalid handle if no entry with the UUID exists.
         */
        Handle find_handle(UUID const &uuid) const
        {
            for (Size i = 0; i < m_uuids.get_size(); ++i)
            {
                if (m_uuids.at(i) == uuid)
                {
                    Handle handle{};
                    handle.generation = m_generations.at(i);
                    handle.index = static_cast<Index>(i);
                    return handle;
                }
            }
            return Handle();
        }

        /**
         * @brief Gets the UUID associated with the entry corresponding to the given handle.
         * @param handle The handle of the entry to access.
         * @return The UUID associated with the entry, or an invalid UUID if the handle is invalid.
         */
        UUID const &find_uuid(Handle const &handle) const
        {
            MINTY_ASSERT(handle.index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            Generation const generation = m_generations.at(handle.index);
            MINTY_ASSERT(generation == handle.generation, ErrorCodeEnum::Argument_KeyNotFound);
            return m_uuids.at(handle.index);
        }

        /**
         * @brief Gets a vector of all valid handles currently in the list.
         * @return A vector containing all valid handles.
         */
        Vector<Handle> get_handles() const
        {
            Vector<Handle> handles;
            for (Size i = 0; i < m_data.get_size(); ++i)
            {
                Generation const generation = m_generations.at(i);
                if (generation != INVALID_GENERATION)
                {
                    Handle handle{};
                    handle.index = static_cast<Index>(i);
                    handle.generation = generation;
                    handles.add(handle);
                }
            }
            return handles;
        }

#pragma endregion

#pragma region Variables

    private:
        Vector<T> m_data;
        Vector<UInt32> m_generations;
        Vector<UUID> m_uuids;
        Stack<UInt32> m_free;

#pragma endregion
    };
}