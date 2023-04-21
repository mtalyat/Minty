#pragma once

#include "M_Object.h"
#include "M_Color.h"
#include "M_Sprite.h"
#include "M_Brush.h"
#include "M_Renderer.h"
#include <SDL.h>
#include <vector>

namespace minty
{
	/// <summary>
	/// An easily modifyable Sprite, which allows for drawing, filling, among other options.
	/// </summary>
	class MINTY_API Canvas
		: public Object
	{
	public:
		// the width of the Canvas sprite
		int const width;
		// the height of the Canvas sprite
		int const height;

	private:
		// the pixel data from the Sprite
		color_t* mp_pixels;
		// the Sprite itself
		Sprite* const mp_sprite;
		// has the Sprite been modified since last time it was drawn?
		bool m_dirty;

	public:
		/// <summary>
		/// Creates a new Canvas using the given width and height in pixels.
		/// </summary>
		/// <param name="width">The width of the Canvas in pixels.</param>
		/// <param name="height">The height of the Canvas in pixels.</param>
		/// <param name="renderer">The Engine Renderer.</param>
		Canvas(int const width, int const height, Renderer* const renderer);

		~Canvas();

		/// <summary>
		/// Locks the Sprite so it can be edited, but no longer be rendered.
		/// </summary>
		void lock();

		/// <summary>
		/// Unlocks the Sprite so it can no longer be edited, but it can be rendererd.
		/// </summary>
		void unlock();

		/// <summary>
		/// Checks if the Canvas is locked.
		/// </summary>
		/// <returns>True if locked, otherwise false.</returns>
		constexpr bool isLocked() const { return mp_pixels != nullptr; }

		/// <summary>
		/// Sets the pixel at the given X and Y position to the given color.
		/// </summary>
		/// <param name="x">The column of the pixel.</param>
		/// <param name="y">The row of the pixel.</param>
		/// <param name="color">The color to set the pixel to.</param>
		inline void set(int const x, int const y, color_t const color);

		/// <summary>
		/// Does a bound check, and sets the pixel at the given X and Y position to the given color, if it is within bounds.
		/// </summary>
		/// <param name="x">The column of the pixel.</param>
		/// <param name="y">The row of the pixel.</param>
		/// <param name="color">The color to set the pixel to.</param>
		void set_s(int const x, int const y, color_t const color);

		/// <summary>
		/// Gets the color of the pixel at the given X and Y position.
		/// </summary>
		/// <param name="x">The column of the pixel.</param>
		/// <param name="y">The row of the pixel.</param>
		/// <returns>The color of the pixel.</returns>
		constexpr color_t get(int const x, int const y) const;

		/// <summary>
		/// Does a bound check, and gets the color of the pixel at the given X and Y position, if it is within bounds.
		/// </summary>
		/// <param name="x">The column of the pixel.</param>
		/// <param name="y">The row of the pixel.</param>
		/// <returns>The color of the pixel, or 0 if out of bounds.</returns>
		constexpr color_t get_s(int const x, int const y) const;

		/// <summary>
		/// Checks if the given X and Y positon is within the bounds of the Canvas.
		/// </summary>
		/// <param name="x">The column of the pixel.</param>
		/// <param name="y">The row of the pixel.</param>
		/// <returns>True if within bounds, otherwise false.</returns>
		constexpr bool contains(int const x, int const y) const;

#pragma region Drawing

		/// <summary>
		/// Draws a pixel at the given X and Y position using the given Brush.
		/// </summary>
		/// <param name="x">The column of the pixel.</param>
		/// <param name="y">The row of the pixel.</param>
		/// <param name="brush">The Brush to paint with.</param>
		void draw(int const x, int const y, Brush const& brush);

		/// <summary>
		/// Draws a line from (x1, y1) to (x2, y2), using the given Brush and brush width.
		/// </summary>
		/// <param name="x1">The starting column of the line.</param>
		/// <param name="y1">The starting row of the line.</param>
		/// <param name="x2">The ending column of the line.</param>
		/// <param name="y2">The ending row of the line.</param>
		/// <param name="brush">The Brush to paint with.</param>
		void drawLine(int const x1, int const y1, int const x2, int const y2, Brush const& brush);

		/// <summary>
		/// Draws a rectangle at the given X and Y position, using the given size and given Brush.
		/// </summary>
		/// <param name="x">The top left column of the rectangle.</param>
		/// <param name="y">The top right row of the rectangle.</param>
		/// <param name="width">The width of the rectangle.</param>
		/// <param name="height">The height of the rectangle.</param>
		/// <param name="brush">The Brush to paint with.</param>
		void drawRect(int const x, int const y, int const width, int const height, Brush const& brush);

		/// <summary>
		/// Draws a circle at the given X and Y position, using the given radius and given Brush.
		/// </summary>
		/// <param name="xm">The center column of the circle.</param>
		/// <param name="ym">The center row of the circle.</param>
		/// <param name="radius">The radius of the circle.</param>
		/// <param name="brush">The Brush to paint with.</param>
		void drawCircle(int const xm, int const ym, int const radius, Brush const& brush);

		/// <summary>
		/// Draws the given Sprite at the given X and Y position.
		/// </summary>
		/// <param name="x">The top left column of the Sprite.</param>
		/// <param name="y">The top right row of the Sprite.</param>
		/// <param name="sprite">The Sprite to draw.</param>
		void drawSprite(int const x, int const y, Sprite const* const sprite);

#pragma endregion

#pragma region Filling

		/// <summary>
		/// Fills a rectangle at the given X and Y position, using the given size and given Brush.
		/// </summary>
		/// <param name="x">The top left column of the rectangle.</param>
		/// <param name="y">The top right row of the rectangle.</param>
		/// <param name="width">The width of the rectangle.</param>
		/// <param name="height">The height of the rectangle.</param>
		/// <param name="brush">The Brush to paint with.</param>
		void fillRect(int const x, int const y, int const width, int const height, Brush const& brush);

		/// <summary>
		/// Fills a circle at the given X and Y position, using the given radius and given Brush.
		/// </summary>
		/// <param name="xm">The center column of the circle.</param>
		/// <param name="ym">The center row of the circle.</param>
		/// <param name="radius">The radius of the circle.</param>
		/// <param name="brush">The Brush to paint with.</param>
		void fillCircle(int const xm, int const ym, int const radius, Brush const& brush);

		/// <summary>
		/// Draws several slices of a circle at the given X and Y position, using the given radius and given Sprites to draw as the background of each Sprite.
		/// </summary>
		/// <param name="xm">The center column of the circle.</param>
		/// <param name="ym">The center row of the circle.</param>
		/// <param name="radius">The radius of the circle.</param>
		/// <param name="sprites">The sprites to draw the background of each slice with.</param>
		/// <param name="offset">The offset rotation of the circle, where the first slice will start, in radians.</param>
		void fillSlices(int const xm, int const ym, int const radius, std::vector<Sprite*> const& sprites, float offset = 0.0f);

		/// <summary>
		/// Draws several slices of a circle at the given X and Y position, using the given radius and given Sprites to draw as the background of each Sprite.
		/// </summary>
		/// <param name="xm">The center column of the circle.</param>
		/// <param name="ym">The center row of the circle.</param>
		/// <param name="radius">The radius of the circle.</param>
		/// <param name="brushes">The Brushes to draw the background of each slice with.</param>
		/// <param name="offset">The offset rotation of the circle, where the first slice will start, in radians.</param>
		void fillSlices(int const xm, int const ym, int const radius, std::vector<Brush*> const& brushes, float offset = 0.0f);

#pragma endregion

#pragma region Clearing

		/// <summary>
		/// Sets every pixel to same pixel color.
		/// </summary>
		/// <param name="color">The color to set every pixel to.</param>
		void clear(color_t const color = 0);

#pragma endregion

		/// <summary>
		/// Gets the Sprite that this Canvas is modifying.
		/// </summary>
		/// <returns>The Sprite that this Canvas modifies.</returns>
		Sprite* sprite() const { return mp_sprite; }
	};
}