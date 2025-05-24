#include "Test_ImageTiling.h"
#include "Minty.h"

void test_ImageTiling(Test& _test)
{
    CATEGORY(ImageTiling)
    {
        std::vector<std::pair<ImageTiling, String>> VALUES = {
            {ImageTiling::Optimal, "Optimal"},
            {ImageTiling::Linear, "Linear"},
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
                EXPECT_EQUAL(parse_to_image_tiling(name), value);
            }

            EXPECT_EQUAL(parse_to_image_tiling(""), ImageTiling());
        }

        TEST("Parse Try")
        {
            ImageTiling result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_image_tiling(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_image_tiling("", result));
            EXPECT_EQUAL(result, ImageTiling());
        }
    }
}