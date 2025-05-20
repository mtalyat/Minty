#include "Test_GamepadAxis.h"

#include "Test_GamepadAxis.h"
#include "Minty.h"

void test_GamepadAxis(Test& _test)
{
    CATEGORY(GamepadAxis)
    {
        std::vector<std::pair<GamepadAxis, String>> VALUES = {
            {GamepadAxis::LeftX, "LeftX"},
            {GamepadAxis::LeftY, "LeftY"},
            {GamepadAxis::RightX, "RightX"},
            {GamepadAxis::RightY, "RightY"},
            {GamepadAxis::LeftTrigger, "LeftTrigger"},
            {GamepadAxis::RightTrigger, "RightTrigger"},
        };

        TEST("To String")
        {
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_EQUAL(to_string(value), name);
            }
        }

        TEST("Parse To")
        {
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_EQUAL(parse_to_gamepad_axis(name), value);
            }

            EXPECT_EQUAL(parse_to_gamepad_axis(""), GamepadAxis());
        }

        TEST("Parse Try")
        {
            GamepadAxis result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_gamepad_axis(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_gamepad_axis("", result));
            EXPECT_EQUAL(result, GamepadAxis());
        }
    }
}