#pragma once

#include "Platform/Type/Primitive.hpp"
#include <array>

namespace Minty
{
    template <typename... Types>
    class TypeArray
    {
#pragma region Constructor

    public:
        TypeArray()
            : m_types{TypeID(typeid(Types))...},
              m_memorySize((static_cast<Size>(sizeof(Types)) + ... + 0))
        {
        }

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the TypeID at the given index.
         * @param index The index of the TypeID.
         * @return The TypeID.
         */
        constexpr TypeID const &at(Size const index) const
        {
            return m_types[index];
        }

        /**
         * @brief Gets the size of this TypeArray.
         * @return The size.
         */
        constexpr Size get_size() const
        {
            return m_types.size();
        }

        /**
         * @brief Gets the memory size of all types within this TypeArray.
         * @return The size of memory.
         */
        constexpr Size get_memory_size() const
        {
            return m_memorySize;
        }

#pragma endregion

#pragma region Variables

    private:
        std::array<TypeID, sizeof...(Types)> m_types;
        Size m_memorySize;

#pragma endregion
    };
}