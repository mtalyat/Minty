#include "Test_ImageUsage.h"
#include "Minty.h"

void test_ImageUsage(Test& _test)
{
    CATEGORY(ImageUsage)
    {
        std::vector<std::pair<ImageUsage, String>> VALUES = {
            {ImageUsage::Sampled, "Sampled"},
            {ImageUsage::Storage, "Storage"},
            {ImageUsage::Color, "Color"},
            {ImageUsage::DepthStencil, "DepthStencil"},
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
                EXPECT_EQUAL(parse_to_image_usage(name), value);
            }

            EXPECT_EQUAL(parse_to_image_usage(""), ImageUsage());
        }

        TEST("Parse Try")
        {
            ImageUsage result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_image_usage(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_image_usage("", result));
            EXPECT_EQUAL(result, ImageUsage());
        }
    }
}