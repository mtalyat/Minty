#include "pch.h"
#include "Collider.h"
#ifdef MINTY_BULLET
#include "Platform/Bullet/Bullet_Collider.h"
#endif

using namespace Minty;

Owner<Collider> Minty::Collider::create(ColliderBuilder const& builder)
{
#if defined(MINTY_BULLET)
	return Owner<Bullet_Collider>(builder);
#else
    return Owner<Collider>();
#endif
}
