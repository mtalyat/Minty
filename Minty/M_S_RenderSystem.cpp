#include "pch.h"
#include "M_S_RenderSystem.h"

#include "M_Sprite.h"
#include "M_Pair.h"
#include "M_PriorityQueue.h"

#include "M_C_Camera.h"
#include "M_C_Center.h"
#include "M_C_Renderer.h"
#include "M_C_Renderable.h"
#include "M_C_Position.h"
#include "M_C_Scale.h"

#include "M_Screen.h"
#include <SDL.h>

namespace minty
{
	void RenderSystem::update()
	{
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

		PriorityQueue<Pair<Rect, Renderer const*>> queue;

		// does not account for scale
		PointF offset;
		for (auto [entity, renderer, renderable] : mp_registry->view<Renderer const, Renderable const>().each())
		{
			if (renderer.isVisible())
			{
				offset = renderer.sprite->offset();
				queue.push(renderer.index, Pair<Rect, Renderer const*>(Rect(math_roundToInt(renderable.x + offset.x), math_roundToInt(renderable.y + offset.y), renderer.sprite->width, renderer.sprite->height), &renderer));
			}
		}

		Pair<Rect, Renderer const*> renderPair;

		// render in order
		while (queue.pop(renderPair))
		{
			SDL_Rect dstrect = renderPair.first.toSDL();
			//SDL_RenderCopy(renderer, renderPair.second->sprite->texture(), NULL, &dstrect);
			SDL_RenderCopyEx(renderer, renderPair.second->sprite->texture(), NULL, &dstrect, 0.0, NULL, renderPair.second->getFlip());
		}

		SDL_RenderPresent(renderer);
	}
}
