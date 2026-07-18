#pragma once

/**
 * @file PointerData.h
 * @brief Header file defining the PointerData struct for managing pointer data in the engine.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty::Internal
{
    /**
     * @struct PointerData
     * @brief Structure to keep track of strong and weak reference counts.
     */
    template <typename Allocator>
    struct PointerData
    {
        /**
         * @brief The number of strong/shared references.
         */
        UInt strongCount;

        /**
         * @brief The number of weak/reference references.
         */
        UInt weakCount;

        /**
         * @brief The allocator used for memory management of the pointer data.
         */
        Allocator allocator;

        /**
         * @brief Constructor for PointerData.
         * @param strong The initial strong reference count.
         * @param weak The initial weak reference count.
         */
        PointerData(UInt const strong, UInt const weak)
            : strongCount(strong), weakCount(weak), allocator()
        {
        }

        static PointerData<Allocator> *create(UInt const strong, UInt const weak)
        {
            Allocator allocator;
            PointerData<Allocator> *data = allocator.template construct<PointerData<Allocator>>(strong, weak);
            data->allocator = std::move(allocator);
            return data;
        }

        static void destroy(PointerData<Allocator> *data)
        {
            Allocator allocator = std::move(data->allocator);
            allocator.destruct(data);
        }
    };
}