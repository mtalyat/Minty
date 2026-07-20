#pragma once

#include "Core/Data/Vector.hpp"
#include <functional>

namespace Minty
{
    template <typename Func>
    class Signal;

    template <typename Return, typename... Args>
    class Signal<Return(Args...)>
    {
#pragma region Type

    public:
        using Function = std::function<Return(Args...)>;

#pragma endregion

#pragma region Constructor

    public:
        Signal()
            : m_listeners()
        {
        }

#pragma endregion

#pragma region Operator

    public:
        Signal &operator+=(Function const &listener)
        {
            connect(listener);
            return *this;
        }

        Signal &operator-=(Function const &listener)
        {
            disconnect(listener);
            return *this;
        }

        Signal const&operator()(Args... args) const
        {
            emit(args...);
            return *this;
        }

#pragma endregion

#pragma region Methods

    public:
        void connect(Function const &listener)
        {
            m_listeners.add(listener);
        }

        void disconnect(Function const &listener)
        {
            for (Size i = 0; i < m_listeners.get_size(); ++i)
            {
                if (m_listeners[i].target_type() == listener.target_type())
                {
                    m_listeners.remove(i);
                    return;
                }
            }
        }

        void emit(Args... args) const
        {
            for (Function const &listener : m_listeners)
            {
                listener(args...);
            }
        }

#pragma endregion

#pragma region Variable

    private:
        Vector<Function> m_listeners;

#pragma endregion
    };
}