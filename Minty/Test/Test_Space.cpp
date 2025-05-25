#include "Test_Space.h"
#include "Minty.h"

void test_Space(Test& _test)
{
    CATEGORY(Space)
    {
        std::vector<std::pair<Space, String>> VALUES = {
            {Space::D3, "D3"},
            {Space::D2, "D2"},
            {Space::UI, "UI"},
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
                EXPECT_EQUAL(parse_to_space(name), value);
            }

            EXPECT_EQUAL(parse_to_space(""), Space());
        }

        TEST("Parse Try")
        {
            Space result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_space(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_space("", result));
            EXPECT_EQUAL(result, Space());
        }
    }
}