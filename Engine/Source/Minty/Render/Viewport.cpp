#include "pch.h"
#include "Viewport.h"
#include "Minty/Render/ViewportInfo.h"
#include "Minty/Debug/Assert.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Viewport.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::Viewport::Viewport(ViewportInfo const &info)
    : Asset(info.id)
{
    MINTY_ASSERT_F(info.minDepth >= 0.0f && info.minDepth <= 1.0f, ErrorCode::Argument_OutOfBounds, info.minDepth);
    MINTY_ASSERT_F(info.maxDepth >= 0.0f && info.maxDepth <= 1.0f, ErrorCode::Argument_OutOfBounds, info.maxDepth);
    MINTY_ASSERT_F(info.minDepth <= info.maxDepth, ErrorCode::Argument_IncorrectOrder, info.minDepth, info.maxDepth);
}

Shared<Viewport> Minty::Viewport::create(ViewportInfo const &info)
{
#ifdef MINTY_VULKAN
    return Shared<Vulkan_Viewport>::create(info);
#else
    return Shared<Viewport>();
#endif // MINTY_VULKAN
}

Shared<Viewport> Minty::Viewport::create()
{
    ViewportInfo info{};
    return create(info);
}