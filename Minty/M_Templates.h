#pragma once

#include "M_Main.h"
#include "entt.hpp"
#include "M_PointF.h"
#include "M_Screen.h"
#include "M_Sprite.h"
#include "M_Text.h"
#include "M_Color.h"
#include "M_C_MouseClick.h"

namespace minty
{
	MINTY_API entt::entity templates_entity_camera(entt::registry* const registry, Screen const* const screen, PointF const& position = PointF(), PointF const& pivot = PointF());

	MINTY_API entt::entity templates_entity_sprite(entt::registry* const registry, Sprite* const sprite, PointF const& position, int const layer = 0, int const order = 0);

	MINTY_API entt::entity templates_entity_sprite_collider(entt::registry* const registry, Sprite* const sprite, PointF const& position, int const layer = 0, int const order = 0, bool const isTrigger = false, bool const isStatic = false, bool const isDynamic = false, Rect const* const rect = nullptr);

	MINTY_API entt::entity templates_entity_ui(entt::registry* const registry, Sprite* const sprite, PointF const& position, int const layer = 0, int const order = 0, PointF const& anchor = PointF());

	MINTY_API entt::entity templates_entity_ui_button(entt::registry* const registry, Sprite* const sprite, PointF const& position, mouseclick_t::func const& func, bool const pixelPerfect, int const layer = 0, int const order = 0, PointF const& anchor = PointF());

	MINTY_API entt::entity templates_entity_ui_button_normal(entt::registry* const registry, Sprite* const sprite, PointF const& position, mouseclick_t::func const& func, bool const pixelPerfect, Color const& normalColor, Color const& hoverColor, Color const& downColor, Color const& disabledColor, int const layer = 0, int const order = 0, PointF const& anchor = PointF());

	MINTY_API entt::entity templates_entity_ui_text(entt::registry* const registry, Text* const text, PointF const& position, int const layer = 0, int const order = 0, PointF const& anchor = PointF());
}