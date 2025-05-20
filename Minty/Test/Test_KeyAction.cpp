#include "Test_KeyAction.h"
#include "Minty.h"

void test_KeyAction(Test& _test)
{
    CATEGORY(KeyAction)
    {
        std::vector<std::pair<KeyAction, String>> VALUES = {
            {KeyAction::Up, "Up"},
            {KeyAction::Down, "Down"},
            {KeyAction::Hold, "Hold"},
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
                EXPECT_EQUAL(parse_to_key_action(name), value);
            }

            EXPECT_EQUAL(parse_to_key_action(""), KeyAction());
        }

        TEST("Parse Try")
        {
            KeyAction result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_key_action(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_key_action("", result));
            EXPECT_EQUAL(result, KeyAction());
        }
    }
}