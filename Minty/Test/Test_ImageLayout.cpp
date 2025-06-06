#include "Test_ImageLayout.h"
#include "Minty.h"

void test_ImageLayout(Test& _test)
{
    CATEGORY(ImageLayout)
    {
        std::vector<std::pair<ImageLayout, String>> VALUES = {
            {ImageLayout::General, "General"},
            {ImageLayout::ColorAttachment, "ColorAttachment"},
            {ImageLayout::DepthStencilAttachment, "DepthStencilAttachment"},
            {ImageLayout::DepthStencilReadOnly, "DepthStencilReadOnly"},
            {ImageLayout::ShaderReadOnly, "ShaderReadOnly"},
            {ImageLayout::TransferSource, "TransferSource"},
            {ImageLayout::TransferDestination, "TransferDestination"},
            {ImageLayout::Preinitialized, "Preinitialized"},
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
                EXPECT_EQUAL(parse_to_image_layout(name), value);
            }

            EXPECT_EQUAL(parse_to_image_layout(""), ImageLayout());
        }

        TEST("Parse Try")
        {
            ImageLayout result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_image_layout(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_image_layout("", result));
            EXPECT_EQUAL(result, ImageLayout());
        }
    }
}