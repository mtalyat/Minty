#pragma once

#include "M_Main.h"
#include "M_Point.h"
#include "M_PointF.h"
#include "M_Sprite.h"
#include "entt.hpp"
#include <SDL.h>

namespace minty
{
	enum class MINTY_API RendererType : unsigned char
	{
		/// <summary>
		/// This renderer has no type.
		/// </summary>
		None = 0,

		/// <summary>
		/// This renderer will render a Sprite.
		/// </summary>
		Sprite = 1,

		/// <summary>
		/// This renderer will render some text.
		/// </summary>
		Text = 2
	};

	/// <summary>
	/// Holds data regarding rendering to the screen.
	/// </summary>
	struct MINTY_API Renderable
	{
		/// <summary>
		/// The type of renderer that this is.
		/// </summary>
		RendererType rendererType;

		/// <summary>
		/// The layer index of this Renderable.
		/// </summary>
		int layer;

		/// <summary>
		/// The order index of this Renderable within its layer.
		/// </summary>
		int order;

		/// <summary>
		/// Is this Sprite invisible?
		/// </summary>
		bool invisible;

		/// <summary>
		/// Is the Renderer flipped?
		/// </summary>
		int flip;

		/// <summary>
		/// Rendering position.
		/// </summary>
		float x, y;

		/// <summary>
		/// Gets the renderer flip mode for this entity.
		/// </summary>
		/// <returns></returns>
		inline SDL_RendererFlip getFlip() const { return static_cast<SDL_RendererFlip>(flip); }

		/// <summary>
		/// Gets the rendering position as a Point.
		/// </summary>
		/// <returns>The rendering position.</returns>
		inline Point toPoint() const { return Point(x, y); }
		/// <summary>
		/// Gets the rendering position as a PointF.
		/// </summary>
		/// <returns>The rendering position.</returns>
		inline PointF toPointF() const { return PointF(x, y); }

		/// <summary>
		/// Gets the Sprite belonging to this Renderable.
		/// </summary>
		/// <param name="entity">The enitity this Renderable belongs to.</param>
		/// <param name="registry">The registry that the entity belongs to.</param>
		/// <returns>The Sprite, or null if not exists.</returns>
		static Sprite* getSprite(entt::entity const entity, entt::registry* const registry);
	};
}