#pragma once

/**
 * @file Registry.h
 * @brief Header file for the Registry class.
 * @author Mitchell Talyat
 */

#include "String.hpp"
#include "Lookup.hpp"
#include "Core/Type/Function.hpp"

namespace Minty
{
    struct Reader;
    struct Writer;

    /**
     * @brief The RegistryData struct holds function pointers for adding, removing, checking existence, serializing, and deserializing data of a specific type.
     * @tparam Inputs The types of the inputs for the functions.
     */
    template <typename Object, typename... Inputs>
    struct RegistryData
    {
        String name;

        Function<Object(Inputs...)> create = nullptr;

        Function<void(Object const&, Inputs...)> destroy = nullptr;

        Function<void(Object const&, Inputs...)> add = nullptr;

        Function<void(Object const&, Inputs...)> remove = nullptr;

        Function<Bool(Object const&, Inputs...)> has = nullptr;

        Function<Object(Inputs...)> get = nullptr;

        Function<Bool(Reader &, Object const&, Inputs...)> deserialize = nullptr;

        Function<Bool(Writer &, Object const&, Inputs...)> serialize = nullptr;
    };

    /**
     * @brief The Registry class is responsible for managing dynamic data that requires some form of lookup -> functionality.
     */
    template <typename Object, typename... Inputs>
    class Registry
    {
#pragma region Type

    public:
        using Data = RegistryData<Object, Inputs...>;

#pragma endregion

#pragma region Constructor

    public:
#pragma endregion

#pragma region Method

    public:
        template <typename T>
        void register_type(Data &&data)
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(!m_data.contains(typeId), ErrorCodeEnum::Object_AlreadyRegistered);
            m_data.add(data.name, typeId, std::move(data));
        }

        template <typename T>
        void unregister_type()
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
            m_data.remove(typeId);
        }

        template <typename T>
        Bool is_registered() const
        {
            TypeID const typeId = typeid(T);
            return m_data.contains(typeId);
        }

        Bool is_registered(StringView const typeName) const
        {
            return m_data.contains(typeName);
        }

        template <typename T>
        Data const &get_data() const
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
            return m_data.at(typeId);
        }

        template<typename T>
        Object create(Inputs... inputs)
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
            return m_data[typeId].create(std::forward<Inputs>(inputs)...);
        }

        template<typename T>
        void destroy(Object const &object, Inputs... inputs)
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
            m_data[typeId].destroy(object, std::forward<Inputs>(inputs)...);
        }

        template <typename T>
        void add(Object const &object, Inputs... inputs)
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
            m_data[typeId].add(object, std::forward<Inputs>(inputs)...);
        }

        void add(StringView const typeName, Object const &object, Inputs... inputs)
        {
            MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
            m_data[typeName].add(object, std::forward<Inputs>(inputs)...);
        }

        template <typename T>
        void remove(Object const &object, Inputs... inputs)
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
            m_data[typeId].remove(object, std::forward<Inputs>(inputs)...);
        }

        void remove(StringView const typeName, Object const &object, Inputs... inputs)
        {
            MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
            m_data[typeName].remove(object, std::forward<Inputs>(inputs)...);
        }

        template <typename T>
        Bool has(Object const &object, Inputs... inputs) const
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
            return m_data[typeId].has(object, std::forward<Inputs>(inputs)...);
        }

        Bool has(StringView const typeName, Object const &object, Inputs... inputs) const
        {
            MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
            return m_data[typeName].has(object, std::forward<Inputs>(inputs)...);
        }

        template <typename T>
        Object get(Inputs... inputs) const
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
            return m_data[typeId].get(std::forward<Inputs>(inputs)...);
        }

        Object get(StringView const typeName, Inputs... inputs) const
        {
            MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
            return m_data[typeName].get(std::forward<Inputs>(inputs)...);
        }

        template <typename T>
        Bool deserialize(Reader &reader, Object const &object, Inputs... inputs) const
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
            return m_data[typeId].deserialize(reader, object, std::forward<Inputs>(inputs)...);
        }

        Bool deserialize(StringView const typeName, Reader &reader, Object const &object, Inputs... inputs) const
        {
            MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
            return m_data[typeName].deserialize(reader, object, std::forward<Inputs>(inputs)...);
        }

        template <typename T>
        Bool serialize(Writer &writer, Object const &object, Inputs... inputs) const
        {
            TypeID const typeId = typeid(T);
            MINTY_ASSERT(m_data.contains(typeId), ErrorCodeEnum::Object_NotRegistered);
            return m_data[typeId].serialize(writer, object, std::forward<Inputs>(inputs)...);
        }

        Bool serialize(StringView const typeName, Writer &writer, Object const &object, Inputs... inputs) const
        {
            MINTY_ASSERT(m_data.contains(typeName), ErrorCodeEnum::Object_NotRegistered);
            return m_data[typeName].serialize(writer, object, std::forward<Inputs>(inputs)...);
        }

#pragma endregion

#pragma region Variable

    private:
        Lookup<TypeID, Data> m_data;

#pragma endregion
    };
}