#include "Test_ShaderFrontFace.h"
#include "Minty.h"

void test_ShaderFrontFace(Test& _test)
{
    CATEGORY(ShaderFrontFace)
    {
        std::vector<std::pair<ShaderFrontFace, String>> VALUES = {
            {ShaderFrontFace::CounterClockwise, "CounterClockwise"},
            {ShaderFrontFace::Clockwise, "Clockwise"},
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
                EXPECT_EQUAL(parse_to_shader_front_face(name), value);
            }

            EXPECT_EQUAL(parse_to_shader_front_face(""), ShaderFrontFace());
        }

        TEST("Parse Try")
        {
            ShaderFrontFace result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_shader_front_face(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_shader_front_face("", result));
            EXPECT_EQUAL(result, ShaderFrontFace());
        }
    }
}