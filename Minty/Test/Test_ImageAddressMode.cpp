#include "Test_ImageAddressMode.h"
#include "Minty.h"

void test_ImageAddressMode(Test& _test)
{
    CATEGORY(ImageAddressMode)
    {
        std::vector<std::pair<ImageAddressMode, String>> VALUES = {
            {ImageAddressMode::Repeat, "Repeat"},
            {ImageAddressMode::MirroredRepeat, "MirroredRepeat"},
            {ImageAddressMode::ClampToEdge, "ClampToEdge"},
            {ImageAddressMode::ClampToBorder, "ClampToBorder"},
            {ImageAddressMode::MirroredClampToEdge, "MirroredClampToEdge"},
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
                EXPECT_EQUAL(parse_to_image_address_mode(name), value);
            }

            EXPECT_EQUAL(parse_to_image_address_mode(""), ImageAddressMode());
        }

        TEST("Parse Try")
        {
            ImageAddressMode result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_image_address_mode(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_image_address_mode("", result));
            EXPECT_EQUAL(result, ImageAddressMode());
        }
    }
}