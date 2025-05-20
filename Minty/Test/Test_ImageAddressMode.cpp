#include "Test_AddressMode.h"
#include "Minty.h"

void test_AddressMode(Test& _test)
{
    CATEGORY(AddressMode)
    {
        std::vector<std::pair<AddressMode, String>> VALUES = {
            {AddressMode::Repeat, "Repeat"},
            {AddressMode::MirroredRepeat, "MirroredRepeat"},
            {AddressMode::ClampToEdge, "ClampToEdge"},
            {AddressMode::ClampToBorder, "ClampToBorder"},
            {AddressMode::MirroredClampToEdge, "MirroredClampToEdge"},
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
                EXPECT_EQUAL(parse_to_address_mode(name), value);
            }

            EXPECT_EQUAL(parse_to_address_mode(""), AddressMode());
        }

        TEST("Parse Try")
        {
            AddressMode result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_address_mode(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_address_mode("", result));
            EXPECT_EQUAL(result, AddressMode());
        }
    }
}