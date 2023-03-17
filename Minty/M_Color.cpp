#include "pch.h"
#include "M_Color.h"
#include "M_Math.h"
#include "M_Random.h"

namespace minty
{
	inline Color minty::Color::darken(float const p) const { return lerp_rgb(*this, Color::black(), math_clamp(p, 0.0f, 1.0f)); }

	inline Color Color::lighten(float const p) const { return lerp_rgb(*this, Color::white(), math_clamp(p, 0.0f, 1.0f)); }

    inline SDL_Color Color::toSDL() const
    {
        return SDL_Color{ r(), g(), b(), a() };
    }

	inline std::string const Color::toString() const { return std::format("Color({0}, {1}, {2}, {3})", r(), g(), b(), a()); }

    inline Color Color::lerp_rgba(color_t const left, color_t const right, float const t)
    {
        return Color(math_lerp(getR(left), getR(right), t), math_lerp(getG(left), getG(right), t), math_lerp(getB(left), getB(right), t), math_lerp(getA(left), getA(right), t));
    }

    inline Color Color::lerp_rgb(color_t const left, color_t const right, float const t)
    {
        return Color(math_lerp(getR(left), getR(right), t), math_lerp(getG(left), getG(right), t), math_lerp(getB(left), getB(right), t), getA(left));
    }

    inline Color Color::random() { return Color(random_range(256), random_range(256), random_range(256), 255); }
}
