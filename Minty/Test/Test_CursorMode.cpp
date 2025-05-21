#include "Test_CursorMode.h"
#include "Minty.h"

void test_CursorMode(Test& _test)
{
    CATEGORY(CursorMode)
    {
        std::vector<std::pair<CursorMode, String>> VALUES = {
            {CursorMode::Normal, "Normal"},
            {CursorMode::Hidden, "Hidden"},
            {CursorMode::Disabled, "Disabled"},
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
                EXPECT_EQUAL(parse_to_cursor_mode(name), value);
            }

            EXPECT_EQUAL(parse_to_cursor_mode(""), CursorMode());
        }

        TEST("Parse Try")
        {
            CursorMode result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_cursor_mode(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_cursor_mode("", result));
            EXPECT_EQUAL(result, CursorMode());
        }
    }
}