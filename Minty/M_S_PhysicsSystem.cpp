#include "pch.h"
#include "M_S_PhysicsSystem.h"

#include "M_Time.h"

#include "M_C_Acceleration.h"
#include "M_C_Velocity.h"
#include "M_C_Transform.h"
#include "M_T_Gravity.h"

namespace minty
{
    void PhysicsSystem::update()
    {
        float deltaTime = Time::deltaTime();

        float gravityDeltaTime = GRAVITY * deltaTime;

        // apply gravity
        for (auto [entity, velocity] : mp_registry->view<Velocity, Gravity const>().each())
        {
            velocity.y += gravityDeltaTime;
        }

        // apply acceleration
        for (auto [entity, velocity, acceleration] : mp_registry->view<Velocity, Acceleration const>().each())
        {
            velocity.x += acceleration.x * deltaTime;
            velocity.y += acceleration.y * deltaTime;
        }

        // apply velocity
        for (auto [entity, transform, velocity] : mp_registry->view<Transform, Velocity const>().each())
        {
            transform.positionX += velocity.x * deltaTime;
            transform.positionY += velocity.y * deltaTime;
        }
    }
}
