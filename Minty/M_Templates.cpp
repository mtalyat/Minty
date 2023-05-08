#include "pch.h"
#include "M_Templates.h"

#include "M_C_Position.h"
#include "M_C_Size.h"
#include "M_C_Camera.h"
#include "M_C_Renderable.h"
#include "M_C_SpriteRenderer.h"
#include "M_C_TextRenderer.h"
#include "M_C_Collider.h"
#include "M_C_UI.h"
#include "M_C_Clickable.h"
#include "M_C_MouseClick.h"
#include "M_C_MouseHover.h"
#include "M_C_MouseEnter.h"
#include "M_C_MouseExit.h"

namespace minty
{
	MINTY_API entt::entity templates_entity_camera(entt::registry* const registry, Screen const* const screen, PointF const& position, PointF const& pivot)
	{
        entt::entity entity = registry->create();

        registry->emplace<Position>(entity, position.x, position.y);
        registry->emplace<Size>(entity, static_cast<float>(screen->width), static_cast<float>(screen->height));
        registry->emplace<Camera>(entity, -pivot.x * screen->width, -pivot.y * screen->height);
        registry->emplace<Renderable>(entity);

        return entity;
    }
    
    MINTY_API entt::entity templates_entity_sprite(entt::registry* const registry, Sprite* const sprite, PointF const& position, int const layer, int const order)
    {
        entt::entity entity = registry->create();

        registry->emplace<Position>(entity, position.x, position.y);
        registry->emplace<SpriteRenderer>(entity, sprite);
        registry->emplace<Renderable>(entity, RendererType::Sprite, layer, order);

        return entity;
    }
    
    MINTY_API entt::entity templates_entity_sprite_collider(entt::registry* const registry, Sprite* const sprite, PointF const& position, int const layer, int const order, bool const isTrigger, bool const isStatic, bool const isDynamic, Rect const* const rect)
    {
        // create entity with sprite
        entt::entity entity = templates_entity_sprite(registry, sprite, position, layer, order);

        // get sprite renderer
        SpriteRenderer const& renderer = registry->get<SpriteRenderer>(entity);

        Rect bounds;

        if (rect)
        {
            bounds = *rect;
        }
        else
        {
            bounds = Rect(0, 0, renderer.sprite->width, renderer.sprite->height);
        }

        // add to collider
        registry->emplace<Collider>(entity, bounds, isTrigger, isStatic, (isDynamic || !renderer.sprite) ? nullptr : renderer.sprite->mask());

        return entity;
    }
    
    MINTY_API entt::entity templates_entity_ui(entt::registry* const registry, Sprite* const sprite, PointF const& position, int const layer, int const order, PointF const& anchor)
    {
        entt::entity entity = registry->create();

        registry->emplace<SpriteRenderer>(entity, sprite);
        registry->emplace<Renderable>(entity, RendererType::Sprite, layer, order);
        registry->emplace<UI>(entity, position.x, position.y, anchor.x, anchor.y);

        return entity;
    }
    
    MINTY_API entt::entity templates_entity_ui_button(entt::registry* const registry, Sprite* const sprite, PointF const& position, mouseclick_t::func const& func, bool const pixelPerfect, int const layer, int const order, PointF const& anchor)
    {
        // create UI
        entt::entity entity = templates_entity_ui(registry, sprite, position, layer, order, anchor);

        // use sprite for bounds
        SpriteRenderer const& sr = registry->get<SpriteRenderer>(entity);

        // add click to it
        registry->emplace<Clickable>(entity, sr.sprite->rect().toRectF(), pixelPerfect);
        MouseClick& click = registry->emplace<MouseClick>(entity, new mouseclick_t());
        click.onClick->emplace(func);

        // all done
        return entity;
    }
    
    MINTY_API entt::entity templates_entity_ui_button_normal(entt::registry* const registry, Sprite* const sprite, PointF const& position, mouseclick_t::func const& func, bool const pixelPerfect, Color const& normalColor, Color const& hoverColor, Color const& downColor, Color const& disabledColor, int const layer, int const order, PointF const& anchor)
    {
        // create UI
        entt::entity entity = templates_entity_ui_button(registry, sprite, position, func, pixelPerfect, layer, order, anchor);

        // add mouse hovering color
        registry->emplace<MouseHover>(entity);
        MouseEnter& enter = registry->emplace<MouseEnter>(entity, new Event<MouseMoveEvent const* const>());
        enter.onEnter->emplace([registry, entity, hoverColor](MouseMoveEvent const* const mme)
            {
                // mouse enter, color
                SpriteRenderer& sr = registry->get<SpriteRenderer>(entity);
        SDL_SetTextureColorMod(sr.sprite->texture(), hoverColor.r(), hoverColor.g(), hoverColor.b());
        SDL_SetTextureAlphaMod(sr.sprite->texture(), hoverColor.a());
            });
        MouseExit& exit = registry->emplace<MouseExit>(entity, new Event<MouseMoveEvent const* const>());
        exit.onExit->emplace([registry, entity, normalColor](MouseMoveEvent const* const mme)
            {
                // mouse exit, back to normal
                SpriteRenderer& sr = registry->get<SpriteRenderer>(entity);
        SDL_SetTextureColorMod(sr.sprite->texture(), normalColor.r(), normalColor.g(), normalColor.b());
        SDL_SetTextureAlphaMod(sr.sprite->texture(), normalColor.a());
            });

        // TODO: mouse click down and up change color

        // TODO: disabled color

        // all done
        return entity;
    }
    
    MINTY_API entt::entity templates_entity_ui_text(entt::registry* const registry, Text* const text, PointF const& position, int const layer, int const order, PointF const& anchor)
    {
        entt::entity entity = registry->create();

        registry->emplace<TextRenderer>(entity, text);
        registry->emplace<Renderable>(entity, RendererType::Text, layer, order);
        registry->emplace<UI>(entity, position.x, position.y, anchor.x, anchor.y);

        return entity;
    }
}
