#include "pch.hpp"
#include "Status.hpp"
#include "Core/Debug/Debug.hpp"

using namespace Minty;

Bool Minty::Status::promote_to(StatusEnum target)
{
    MINTY_ASSERT(value < target, ErrorCodeEnum::Status_PromoteFailed);
    Bool const canTriggerPromotion = target <= parent; // within bounds of parent
    value = target;
    return canTriggerPromotion;
}

Bool Minty::Status::demote_to(StatusEnum target)
{
    MINTY_ASSERT(value > target, ErrorCodeEnum::Status_DemoteFailed);
    Bool const canTriggerDemotion = target < parent; // within bounds of parent
    value = target;
    return canTriggerDemotion;
}

Bool Minty::Status::promote_parent_to(StatusEnum target)
{
    MINTY_ASSERT(target > parent, ErrorCodeEnum::Status_PromoteFailed);
    Bool const canTriggerPromotion = target <= value; // value within bounds of parent
    parent = target;
    return canTriggerPromotion;
}

Bool Minty::Status::demote_parent_to(StatusEnum target)
{
    MINTY_ASSERT(target < parent, ErrorCodeEnum::Status_DemoteFailed);
    Bool const canTriggerDemotion = target < value; // value within bounds of parent
    parent = target;
    return canTriggerDemotion;
}
