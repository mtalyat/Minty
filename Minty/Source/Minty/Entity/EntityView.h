#pragma once  
#include "Minty/Entity/Entity.h"
#include "Minty/Library/EnTT.h"

namespace Minty  
{
    template<typename... Get>
    class EntityView
    {
	public:
		EntityView(entt::registry& registry)
			: m_view(registry.view<Get...>())
		{
		}

		EntityView(entt::registry const& registry)
			: m_view(registry.view<Get...>())
		{
		}

		template<typename Func>
		void each(Func&& func)
		{
			m_view.each(func);
		}

		auto each()
		{
			return m_view.each();
		}

		auto each() const
		{
			return m_view.each();
		}

    private:
		entt::view<entt::get_t<Get...>> m_view;
    };
}