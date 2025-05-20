#include "Test_ImageAspect.h"
#include "Minty.h"

void test_ImageAspect(Test& _test)
{
    CATEGORY(ImageAspect)
    {
        std::vector<std::pair<ImageAspect, String>> VALUES = {
            {ImageAspect::Color, "Color"},
            {ImageAspect::Depth, "Depth"},
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
                EXPECT_EQUAL(parse_to_image_aspect(name), value);
            }

            EXPECT_EQUAL(parse_to_image_aspect(""), ImageAspect());
        }

        TEST("Parse Try")
        {
            ImageAspect result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_image_aspect(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_image_aspect("", result));
            EXPECT_EQUAL(result, ImageAspect());
        }
    }
}