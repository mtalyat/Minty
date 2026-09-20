#include "pch.hpp"
#include "Status.hpp"
#include "Core/Debug/Debug.hpp"

using namespace Minty;

StatusEnum Minty::Status::next(StatusEnum current)
{
    MINTY_ASSERT(current != StatusEnum::Count, ErrorCodeEnum::Status_PromoteFailed);

    return static_cast<StatusEnum>(static_cast<Int>(current) + 1);
}

StatusEnum Minty::Status::previous(StatusEnum current)
{
    MINTY_ASSERT(current != StatusEnum::Undefined, ErrorCodeEnum::Status_DemoteFailed);

    return static_cast<StatusEnum>(static_cast<Int>(current) - 1);
}

Bool Minty::Status::promote()
{
    return promote_to(next(value));
}

Bool Minty::Status::demote()
{
    return demote_to(previous(value));
}

Bool Minty::Status::promote_to(StatusEnum target)
{
    // Ignore if the target is already at or above the target level
    if (value >= target)
    {
        return false;
    }
    
    Bool const canTriggerPromotion = target <= parent; // within bounds of parent
    value = target;
    return canTriggerPromotion;
}

Bool Minty::Status::demote_to(StatusEnum target)
{
    // Ignore if the target is already at or below the target level
    if (value <= target)
    {
        return false;
    }

    Bool const canTriggerDemotion = target < parent; // within bounds of parent
    value = target;
    return canTriggerDemotion;
}

Bool Minty::Status::promote_parent_to(StatusEnum target)
{
    // Ignore if the target is already at or above the parent level
    if (target <= parent)
    {
        return false;
    }

    Bool const canTriggerPromotion = target <= value; // value within bounds of parent
    parent = target;
    return canTriggerPromotion;
}

Bool Minty::Status::demote_parent_to(StatusEnum target)
{
    // Ignore if the target is already at or below the parent level
    if (target >= parent)
    {
        return false;
    }

    Bool const canTriggerDemotion = target < value; // value within bounds of parent
    parent = target;
    return canTriggerDemotion;
}
