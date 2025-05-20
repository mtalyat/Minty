#include "Test_MouseButton.h"
#include "Minty.h"

void test_MouseButton(Test& _test)
{
    CATEGORY(MouseButton)
    {
        std::vector<std::pair<MouseButton, String>> VALUES = {
            {MouseButton::Button1, "Button1"},
            {MouseButton::Button2, "Button2"},
            {MouseButton::Button3, "Button3"},
            {MouseButton::Button4, "Button4"},
            {MouseButton::Button5, "Button5"},
            {MouseButton::Button6, "Button6"},
            {MouseButton::Button7, "Button7"},
            {MouseButton::Button8, "Button8"},
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
                EXPECT_EQUAL(parse_to_mouse_button(name), value);
            }

            EXPECT_EQUAL(parse_to_mouse_button(""), MouseButton());
        }

        TEST("Parse Try")
        {
            MouseButton result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_mouse_button(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_mouse_button("", result));
            EXPECT_EQUAL(result, MouseButton());
        }
    }
}