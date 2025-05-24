#include "Test_GamepadButton.h"
#include "Minty.h"

void test_GamepadButton(Test& _test)
{
    CATEGORY(GamepadButton)
    {
        std::vector<std::pair<GamepadButton, String>> VALUES = {
            {GamepadButton::ButtonSouth, "ButtonSouth"},
            {GamepadButton::ButtonEast, "ButtonEast"},
            {GamepadButton::ButtonWest, "ButtonWest"},
            {GamepadButton::ButtonNorth, "ButtonNorth"},
            {GamepadButton::LeftBumper, "LeftBumper"},
            {GamepadButton::RightBumper, "RightBumper"},
            {GamepadButton::Back, "Back"},
            {GamepadButton::Start, "Start"},
            {GamepadButton::Home, "Home"},
            {GamepadButton::LeftThumb, "LeftThumb"},
            {GamepadButton::RightThumb, "RightThumb"},
            {GamepadButton::DpadUp, "DpadUp"},
            {GamepadButton::DpadRight, "DpadRight"},
            {GamepadButton::DpadDown, "DpadDown"},
            {GamepadButton::DpadLeft, "DpadLeft"},
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
                EXPECT_EQUAL(parse_to_gamepad_button(name), value);
            }

            EXPECT_EQUAL(parse_to_gamepad_button(""), GamepadButton());
        }

        TEST("Parse Try")
        {
            GamepadButton result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_gamepad_button(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_gamepad_button("", result));
            EXPECT_EQUAL(result, GamepadButton());
        }
    }
}