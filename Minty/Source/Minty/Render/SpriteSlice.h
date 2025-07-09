#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Render/CoordinateMode.h"

namespace Minty
{
	/// <summary>
	/// Represents a slice of a Texture that can be used to create a Sprite.
	/// </summary>
	struct SpriteSlice
	{
		/// <summary>
		/// How the coordinates are interpreted.
		/// </summary>
		CoordinateMode coordinateMode = CoordinateMode::Normalized;

		/// <summary>
		/// The offset of this Sprite within the Texture.
		/// </summary>
		Float2 offset = { 0.0f, 0.0f };

		/// <summary>
		/// The size of this Sprite within the Texture.
		/// </summary>
		Float2 size = { 1.0f, 1.0f };

		/// <summary>
		/// The pivot of this Sprite within world space.
		/// </summary>
		Float2 pivot = { 0.5f, 0.5f };

		/// <summary>
		/// The number of pixels that fit within 1 unit of world space.
		/// </summary>
		Float pixelsPerUnit = 16.0f;
	};
}