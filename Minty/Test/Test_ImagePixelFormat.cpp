#include "Test_ImagePixelFormat.h"
#include "Minty.h"

void test_ImagePixelFormat(Test& _test)
{
    CATEGORY(ImagePixelFormat)
    {
        std::vector<std::pair<ImagePixelFormat, String>> VALUES = {
            {ImagePixelFormat::Gray, "Gray"},
            {ImagePixelFormat::GrayAlpha, "GrayAlpha"},
            {ImagePixelFormat::RedGreenBlue, "RedGreenBlue"},
            {ImagePixelFormat::RedGreenBlueAlpha, "RedGreenBlueAlpha"},
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
                EXPECT_EQUAL(parse_to_image_pixel_format(name), value);
            }

            EXPECT_EQUAL(parse_to_image_pixel_format(""), ImagePixelFormat());
        }

        TEST("Parse Try")
        {
            ImagePixelFormat result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_image_pixel_format(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_image_pixel_format("", result));
            EXPECT_EQUAL(result, ImagePixelFormat());
        }
    }
}