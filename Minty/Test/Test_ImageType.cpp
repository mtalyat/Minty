#include "Test_ImageType.h"
#include "Minty.h"

void test_ImageType(Test& _test)
{
    CATEGORY(ImageType)
    {
        std::vector<std::pair<ImageType, String>> VALUES = {
            {ImageType::D1, "D1"},
            {ImageType::D2, "D2"},
            {ImageType::D3, "D3"},
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
                EXPECT_EQUAL(parse_to_image_type(name), value);
            }

            EXPECT_EQUAL(parse_to_image_type(""), ImageType());
        }

        TEST("Parse Try")
        {
            ImageType result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_image_type(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_image_type("", result));
            EXPECT_EQUAL(result, ImageType());
        }
    }
}