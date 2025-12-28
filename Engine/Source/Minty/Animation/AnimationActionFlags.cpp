#include "pch.h"
#include "AnimationActionFlags.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size ANIMATIONACTIONFLAGS_COUNT = 3;
static constexpr Char const* ANIMATIONACTIONFLAGS_STRINGS[ANIMATIONACTIONFLAGS_COUNT] = {
	"Smooth",
	"Add",
	"Remove"
};

Bool Minty::Parser<AnimationActionFlags>::parse(StringView const str, AnimationActionFlags &value)
{
    return Tool::try_parse_enum_flags(str, ANIMATIONACTIONFLAGS_STRINGS, ANIMATIONACTIONFLAGS_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<AnimationActionFlags>::to_string(AnimationActionFlags const &value)
{
    return Tool::to_string_enum_flags(reinterpret_cast<Size const&>(value), ANIMATIONACTIONFLAGS_STRINGS, ANIMATIONACTIONFLAGS_COUNT);
}