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
		template<typename Func>
		void each(Func&& func)
		{
			m_view.each(func);
		}

    private:
		entt::view<entt::get_t<Get...>> m_view;
    };
}