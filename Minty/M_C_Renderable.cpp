#include "pch.h"
#include "M_C_Renderable.h"
#include "M_C_SpriteRenderer.h"
#include "M_C_TextRenderer.h"

namespace minty
{
	Sprite* Renderable::getSprite(entt::entity const entity, entt::registry* const registry)
	{
		Renderable const& renderable = registry->get<Renderable>(entity);

		switch (renderable.rendererType)
		{
		case RendererType::Sprite:
			return registry->get<SpriteRenderer>(entity).sprite;
		case RendererType::Text:
			return registry->get<TextRenderer>(entity).text->sprite();
		default:
			return nullptr;
		}
	}
}
