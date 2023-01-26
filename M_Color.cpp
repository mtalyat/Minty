#include "pch.h"
#include "M_Color.h"
#include "M_Math.h"
#include "M_Random.h"

namespace minty
{
	inline Color minty::Color::darken(float const p) const { return lerp_rgb(*this, Color::black(), math_clamp(p, 0.0f, 1.0f)); }

	inline Color Color::lighten(float const p) const { return lerp_rgb(*this, Color::white(), math_clamp(p, 0.0f, 1.0f)); }

	inline std::string const Color::toString() const { return std::format("Color({0}, {1}, {2}, {3})", r(), g(), b(), a()); }

    inline Color Color::lerp_rgba(Color const left, Color const right, float const t)
    {
        return Color(math_lerp(left.r(), right.r(), t), math_lerp(left.g(), right.g(), t), math_lerp(left.b(), right.b(), t), math_lerp(left.a(), right.a(), t));
    }

    inline Color Color::lerp_rgb(Color const left, Color const right, float const t)
    {
        return Color(math_lerp(left.r(), right.r(), t), math_lerp(left.g(), right.g(), t), math_lerp(left.b(), right.b(), t), left.a());
    }

    inline Color Color::random() { return Color(random_range(256), random_range(256), random_range(256), 255); }
}
