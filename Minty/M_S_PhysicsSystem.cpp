#include "pch.h"
#include "M_S_PhysicsSystem.h"

#include "M_Time.h"

#include "M_C_Acceleration.h"
#include "M_C_Velocity.h"
#include "M_C_Position.h"
#include "M_C_Gravity.h"

namespace minty
{
    void PhysicsSystem::update()
    {
        float deltaTime = Time::deltaTime();

        float gravityDeltaTime = GRAVITY * deltaTime;

        // apply gravity
        for (auto [entity, velocity, gravity] : mp_registry->view<Velocity, Gravity const>().each())
        {
            velocity.y += gravityDeltaTime * gravity.scale;
        }

        // apply acceleration
        for (auto [entity, velocity, acceleration] : mp_registry->view<Velocity, Acceleration const>().each())
        {
            velocity.x += acceleration.x * deltaTime;
            velocity.y += acceleration.y * deltaTime;
        }

        // apply velocity
        for (auto [entity, position, velocity] : mp_registry->view<Position, Velocity const>().each())
        {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
        }
    }
}
