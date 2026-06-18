#pragma once

/**
 * @file Registry.h
 * @brief Header file for the Registry class.
 * @author Mitchell Talyat
 */

#include "String.h"
#include "Lookup.h"
#include "Core/Type/Function.h"

namespace Minty
{
    struct Reader;
    struct Writer;

    /**
     * @brief The RegistryData struct holds function pointers for adding, removing, checking existence, serializing, and deserializing data of a specific type.
     * @tparam Inputs The types of the inputs for the functions.
     */
    template<typename... Inputs>
    struct RegistryData
    {
        String name;

        Function<void(Inputs...)> add = nullptr;

        Function<void(Inputs...)> remove = nullptr;

        Function<Bool(Inputs...)> has = nullptr;

        Function<Bool(Reader&, Inputs...)> deserialize = nullptr;

        Function<Bool(Writer&, Inputs...)> serialize = nullptr;
    };

    /**
     * @brief The Registry class is responsible for managing dynamic data that requires some form of lookup -> functionality.
     */
    template<typename... Inputs>
    class Registry
    {
        #pragma region Type

        public:
            using Data = RegistryData<Inputs...>;

        #pragma endregion

        #pragma region Constructor

        public:

        #pragma endregion

        #pragma region Method

        public:
            template<typename T>
            void register_type(Data&& data)
            {
                TypeID const typeId = typeid(T);
                MINTY_ASSERT(!m_data.contains(typeId), ErrorCodeEnum::Object_AlreadyRegistered);
                m_data.add(data.name, typeId, std::move(data));
            }

            template<typename T>
            void unregister_type()
            {
                TypeID const typeId = typeid(T);
                MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
                m_data.remove(typeId);
            }

            template<typename T>
            Bool is_registered() const
            {
                TypeID const typeId = typeid(T);
                return m_data.contains(typeId);
            }

            Bool is_registered(StringView const typeName) const
            {
                return m_data.contains(typeName);
            }

            template<typename T>
            Data const& get_data() const
            {
                TypeID const typeId = typeid(T);
                MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
                return m_data.at(typeId);
            }

            template<typename T>
            void add(Inputs... inputs)
            {
                TypeID const typeId = typeid(T);
                MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
                m_data[typeId].add(std::forward<Inputs>(inputs)...);
            }

            void add(StringView const typeName, Inputs... inputs)
            {
                MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
                m_data[typeName].add(std::forward<Inputs>(inputs)...);
            }

            template<typename T>
            void remove(Inputs... inputs)
            {
                TypeID const typeId = typeid(T);
                MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
                m_data[typeId].remove(std::forward<Inputs>(inputs)...);
            }

            void remove(StringView const typeName, Inputs... inputs)
            {
                MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
                m_data[typeName].remove(std::forward<Inputs>(inputs)...);
            }

            template<typename T>
            Bool has(Inputs... inputs) const
            {
                TypeID const typeId = typeid(T);
                MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
                return m_data[typeId].has(std::forward<Inputs>(inputs)...);
            }

            Bool has(StringView const typeName, Inputs... inputs) const
            {
                MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
                return m_data[typeName].has(std::forward<Inputs>(inputs)...);
            }

            template<typename T>
            Bool deserialize(Reader& reader, Inputs... inputs) const
            {
                TypeID const typeId = typeid(T);
                MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
                return m_data[typeId].deserialize(reader, std::forward<Inputs>(inputs)...);
            }

            Bool deserialize(StringView const typeName, Reader& reader, Inputs... inputs) const
            {
                MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
                return m_data[typeName].deserialize(reader, std::forward<Inputs>(inputs)...);
            }

            template<typename T>
            Bool serialize(Writer& writer, Inputs... inputs) const
            {
                TypeID const typeId = typeid(T);
                MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
                return m_data[typeId].serialize(writer, std::forward<Inputs>(inputs)...);
            }

            Bool serialize(StringView const typeName, Writer& writer, Inputs... inputs) const
            {
                MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
                return m_data[typeName].serialize(writer, std::forward<Inputs>(inputs)...);
            }

        #pragma endregion

        #pragma region Variable

    private:
        Lookup<TypeID, Data> m_data;

        #pragma endregion
    };
}