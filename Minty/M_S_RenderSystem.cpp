#include "pch.h"
#include "M_S_RenderSystem.h"

#include "M_Sprite.h"
#include "M_Pair.h"
#include "M_PriorityQueue.h"

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

		PriorityQueue<Pair<Rect, Sprite const*>> queue;

		// get camera pos
		Position* const cameraPos = mp_registry->try_get<Position>(*mp_mainCameraEntity);

		if (cameraPos)
		{
			// if has a position, change renderable position to reflect camera position
			for (auto [entity, position, renderable] : mp_registry->view<Position const, Renderable>().each())
			{
				renderable.x = math_floorToInt(position.x - cameraPos->x);
				renderable.y = math_floorToInt(position.y - cameraPos->y);
			}
		}
		else
		{
			// no camera position
			for (auto [entity, position, renderable] : mp_registry->view<Position const, Renderable>().each())
			{
				renderable.x = math_floorToInt(position.x);
				renderable.y = math_floorToInt(position.y);
			}
		}

		// required: renderer, position
		// optional: scale

		//auto groupNoScale = mp_registry->group<Renderer, Renderable>({}, entt::exclude<Scale>);
		//auto groupScale = mp_registry->group<Renderer, Renderable, Scale>();

		//for (auto [entity, renderer, renderable] : groupNoScale.each())
		//{
		//	if (renderer.isVisible())
		//	{
		//		queue.push(renderer.index, Pair<Rect, Sprite const*>(Rect(renderable.x, renderable.y, renderer.sprite->width, renderer.sprite->height), renderer.sprite));
		//	}
		//}

		//for (auto [entity, renderer, renderable, scale] : groupScale.each())
		//{
		//	if (renderer.isVisible())
		//	{
		//		queue.push(renderer.index, Pair<Rect, Sprite const*>(Rect(renderable.x, renderable.y, math_floorToInt(renderer.sprite->width * scale.x), math_floorToInt(renderer.sprite->height * scale.y)), renderer.sprite));
		//	}
		//}

		// does not account for scale
		for (auto [entity, renderer, renderable] : mp_registry->view<Renderer const, Renderable const>().each())
		{
			if (renderer.isVisible())
			{
				//queue.push(renderer.index, Pair<Rect, Sprite const*>(Rect(renderable.x, renderable.y, math_floorToInt(renderer.sprite->width * scale.x), math_floorToInt(renderer.sprite->height * scale.y)), renderer.sprite));
				queue.push(renderer.index, Pair<Rect, Sprite const*>(Rect(renderable.x, renderable.y, renderer.sprite->width, renderer.sprite->height), renderer.sprite));
			}
		}

		Pair<Rect, Sprite const*> renderPair;

		// render in order
		while (queue.pop(renderPair))
		{
			SDL_Rect dstrect = renderPair.first.toSDL();
			SDL_RenderCopy(renderer, renderPair.second->texture(), NULL, &dstrect);
		}

		SDL_RenderPresent(renderer);
	}
}