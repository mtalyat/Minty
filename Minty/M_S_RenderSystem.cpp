#include "pch.h"
#include "M_S_RenderSystem.h"

#include "M_Sprite.h"
#include "M_Pair.h"
#include "M_PriorityQueue.h"

#include "M_C_Camera.h"
#include "M_C_Center.h"
#include "M_C_Renderable.h"
#include "M_C_Position.h"
#include "M_C_Scale.h"
#include "M_C_SpriteRenderer.h"
#include "M_C_TextRenderer.h"
#include "M_C_UI.h"

#include "M_C_Name.h"

#include "M_Screen.h"
#include <SDL.h>

namespace minty
{
	void RenderSystem::update()
	{
		// get the renderer for use
		SDL_Renderer* const renderer = mp_screen->renderer();

		// clear the screen so there is no smearing
		if (mp_screen->backgroundTexture())
		{
			// background
			SDL_RenderCopy(renderer, mp_screen->backgroundTexture(), NULL, NULL);
		}
		else
		{
			// set background color
			Color bgColor = mp_screen->backgroundColor();
			SDL_SetRenderDrawColor(renderer, bgColor.r(), bgColor.g(), bgColor.b(), bgColor.a());

			// color background
			SDL_RenderClear(renderer);
		}

		// update cameras
		for (auto [entity, camera, position, renderable] : mp_registry->view<Camera const, Position const, Renderable>().each())
		{
			renderable.x = position.x + camera.offsetX;
			renderable.y = position.y + camera.offsetY;
		}

		// get camera pos
		Renderable* const cameraPos = mp_registry->try_get<Renderable>(*mp_mainCameraEntity);

		// update renderable positions
		// normal objects
		if (cameraPos)
		{
			// if has a position, change renderable position to reflect camera position
			for (auto [entity, position, renderable] : mp_registry->view<Position const, Renderable>().each())
			{
				renderable.x = position.x - cameraPos->x;
				renderable.y = position.y - cameraPos->y;
			}
		}
		else
		{
			// no camera position
			for (auto [entity, position, renderable] : mp_registry->view<Position const, Renderable>().each())
			{
				renderable.x = position.x;
				renderable.y = position.y;
			}
		}

		// ui objects
		for (auto [entity, ui, renderable] : mp_registry->view<UI const, Renderable>().each())
		{
			renderable.x = ui.x + mp_screen->width * ui.anchorX;
			renderable.y = ui.y + mp_screen->height * ui.anchorY;
		}

		// TODO: only sort when new renderable added to registry
		// should be a way to do that with EnTT

		// sort it
		mp_registry->sort<Renderable>([](Renderable const& left, Renderable const& right)
			{
				if (left.layer != right.layer)
				{
					// unequal layers
					return left.layer < right.layer;
				}
				else
				{
					// equal layers
					return left.order < right.order;
				}
			});

		Sprite* sprite;

		// since entities are sorted, just render them in iteration order
		for (auto [entity, renderable] : mp_registry->view<Renderable>().each())
		{
			// skip if invisible
			if (renderable.invisible)
			{
				continue;
			}

			// render based on type
			switch (renderable.rendererType)
			{
			case RendererType::Sprite:
			{
				SpriteRenderer* sr = mp_registry->try_get<SpriteRenderer>(entity);

				if (!sr)
				{
					break;
				}

				sprite = sr->sprite;

				// if renderer exists, and sprite exists
				if (sprite)
				{
					PointF offset = sprite->offset();

					SDL_Rect dstrect = SDL_Rect{
						math_roundToInt(renderable.x + offset.x),
						math_roundToInt(renderable.y + offset.y),
						sprite->width,
						sprite->height
					};

					SDL_RenderCopyEx(renderer, sprite->texture(), NULL, &dstrect, 0.0, NULL, renderable.getFlip());
				}

				break;
			}
			case RendererType::Text:
			{
				TextRenderer* tr = mp_registry->try_get<TextRenderer>(entity);
				
				if (!tr || !tr->text)
				{
					break;
				}

				// if text has been edited, apply first
				if (tr->text->isDirty())
				{
					tr->text->apply(renderer);
				}

				// get sprite to render
				sprite = tr->text->getSprite();

				// if renderer exists, and text exists, and font exists
				if (sprite)
				{
					PointF offset = sprite->offset();

					SDL_Rect dstrect = SDL_Rect{
						math_roundToInt(renderable.x + offset.x),
						math_roundToInt(renderable.y + offset.y),
						sprite->width,
						sprite->height
					};

					SDL_RenderCopyEx(renderer, sprite->texture(), NULL, &dstrect, 0.0, NULL, renderable.getFlip());
				}

				break;
			}
			}
		}

		SDL_RenderPresent(renderer);
	}
	
	PointF RenderSystem::screenToWorldPosition(Point const& screenPosition, entt::entity const cameraEntity)
	{
		Position const& cameraPos = mp_registry->get<Position>(cameraEntity);
		Camera const& camera = mp_registry->get<Camera>(cameraEntity);

		return PointF(cameraPos.x + camera.offsetX + screenPosition.x, cameraPos.y + camera.offsetY + screenPosition.y);
	}
	
	Point RenderSystem::worldToScreenPosition(PointF const& worldPosition, entt::entity const cameraEntity)
	{
		Debug::logNotImplemented("", "GameScene::worldToScreenPoint()", "GameScene.cpp");
		return Point();
	}
}
