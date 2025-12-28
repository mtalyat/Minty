#include "pch.h"
#include "MeshType.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size MESHTYPE_COUNT = 4;
static constexpr Char const* MESHTYPE_STRINGS[MESHTYPE_COUNT] =
{
	"Empty",
	"Custom",
	"Quad",
	"Cube"
};

Bool Minty::Parser<MeshType>::parse(StringView const str, MeshType &value)
{
    return Tool::try_parse_enum(str, MESHTYPE_STRINGS, MESHTYPE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<MeshType>::to_string(MeshType const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), MESHTYPE_STRINGS, MESHTYPE_COUNT);
}