#include "pch.h"
#include "Text.h"

using namespace Minty;

Owner<Text> Minty::Text::create(TextBuilder const& builder)
{
    return Owner<Text>(builder);
}
