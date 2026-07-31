#pragma once

#include "World/Entity/Entity.hpp"
#include "Library/EnTT/EnTT.hpp"
#include <utility>

namespace Minty
{
    template<typename WrappedView>
    class EntityView
    {
    private:
        template<typename WrappedIterator>
        class IteratorBase
        {
#pragma region Variable

        private:
            WrappedIterator m_iterator;

#pragma endregion

#pragma region Constructor

        public:
            explicit IteratorBase(WrappedIterator iterator)
                : m_iterator(iterator)
            {
            }

#pragma endregion

#pragma region Operator

        public:
            inline IteratorBase &operator++()
            {
                ++m_iterator;
                return *this;
            }

            inline Bool operator==(IteratorBase const &other) const { return m_iterator == other.m_iterator; }

            inline Bool operator!=(IteratorBase const &other) const { return m_iterator != other.m_iterator; }

            inline EntityHandle operator*() const { return static_cast<EntityHandle>(*m_iterator); }

#pragma endregion
        };

#pragma region Type

    public:
        using Iterator = IteratorBase<decltype(std::declval<WrappedView &>().begin())>;
        using ConstIterator = IteratorBase<decltype(std::declval<WrappedView const &>().begin())>;

#pragma endregion

#pragma region Variable

    private:
        WrappedView m_view;

#pragma endregion

#pragma region Constructor

    public:
        explicit EntityView(WrappedView view)
            : m_view(std::move(view))
        {
        }

#pragma endregion

#pragma region Accessor

    public:
        inline Iterator begin() { return Iterator(m_view.begin()); }

        inline Iterator end() { return Iterator(m_view.end()); }

        inline ConstIterator begin() const { return ConstIterator(m_view.begin()); }

        inline ConstIterator end() const { return ConstIterator(m_view.end()); }

        inline WrappedView &raw() { return m_view; }

        inline WrappedView const &raw() const { return m_view; }

        inline Size size_hint() const { return m_view.size_hint(); }

        inline Bool contains(EntityHandle const entity) const
        {
            return m_view.contains(minty_to_entt(entity));
        }

#pragma endregion

#pragma region Method

    public:
        inline decltype(auto) each()
        {
            return m_view.each();
        }

        inline decltype(auto) each() const
        {
            return m_view.each();
        }

        template<typename Component>
        inline decltype(auto) get(EntityHandle const entity)
        {
            return m_view.template get<Component>(minty_to_entt(entity));
        }

        template<typename Component>
        inline decltype(auto) get(EntityHandle const entity) const
        {
            return m_view.template get<Component>(minty_to_entt(entity));
        }

#pragma endregion

#pragma region Helper

    private:
        inline static entt::entity minty_to_entt(EntityHandle const entity) { return static_cast<entt::entity>(entity); }

#pragma endregion
    };
}