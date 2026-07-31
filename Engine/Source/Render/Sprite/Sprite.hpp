#pragma once

#include "Core/Type/CoordinateMode.hpp"
#include "Core/Type/Int2.hpp"
#include "Render/Type/Handle.hpp"

namespace Minty
{
    struct SpriteInfo;

    class Sprite
    {
#pragma region Constructor

    public:
        Sprite();

        Sprite(SpriteInfo const &info);

#pragma endregion

#pragma region Accessor

    public:
        inline TextureHandle get_texture_handle() const { return m_textureHandle; }
        inline Int2 get_offset() const { return m_offset; }
        inline Int2 get_size() const { return m_size; }
        inline Int2 get_pivot() const { return m_pivot; }
        inline Float get_pixels_per_unit() const { return m_pixelsPerUnit; }

#pragma endregion

#pragma region Variables

    private:
        TextureHandle m_textureHandle;
        Int2 m_offset;
        Int2 m_size;
        Int2 m_pivot;
        Float m_pixelsPerUnit;

#pragma endregion
    };
}