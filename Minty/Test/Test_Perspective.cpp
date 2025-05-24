#include "Test_Perspective.h"
#include "Minty.h"

void test_Perspective(Test& _test)
{
    CATEGORY(Perspective)
    {
        std::vector<std::pair<Perspective, String>> VALUES = {
            {Perspective::Perspective, "Perspective"},
            {Perspective::Orthographic, "Orthographic"},
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
                EXPECT_EQUAL(parse_to_perspective(name), value);
            }

            EXPECT_EQUAL(parse_to_perspective(""), Perspective());
        }

        TEST("Parse Try")
        {
            Perspective result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_perspective(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_perspective("", result));
            EXPECT_EQUAL(result, Perspective());
        }
    }
}