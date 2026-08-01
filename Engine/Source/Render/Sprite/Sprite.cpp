#include "pch.hpp"
#include "Sprite.hpp"
#include "Render/Sprite/SpriteInfo.hpp"

using namespace Minty;

Minty::Sprite::Sprite()
    : Sprite(SpriteInfo{})
{
}

Minty::Sprite::Sprite(SpriteInfo const &info)
    : m_textureHandle(info.textureHandle),
      m_offset(info.offset),
      m_size(info.size),
      m_pivot(info.pivot),
      m_pixelsPerUnit(info.pixelsPerUnit),
      m_scale(1.0f / info.pixelsPerUnit)
{
}
