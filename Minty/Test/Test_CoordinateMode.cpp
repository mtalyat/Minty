#include "Test_CoordinateMode.h"

#include "Test_CoordinateMode.h"
#include "Minty.h"

void test_CoordinateMode(Test& _test)
{
    CATEGORY(CoordinateMode)
    {
        std::vector<std::pair<CoordinateMode, String>> VALUES = {
            {CoordinateMode::Normalized, "Normalized"},
            {CoordinateMode::Pixel, "Pixel"},
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
                EXPECT_EQUAL(parse_to_coordinate_mode(name), value);
            }

            EXPECT_EQUAL(parse_to_coordinate_mode(""), CoordinateMode());
        }

        TEST("Parse Try")
        {
            CoordinateMode result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_coordinate_mode(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_coordinate_mode("", result));
            EXPECT_EQUAL(result, CoordinateMode());
        }
    }
}