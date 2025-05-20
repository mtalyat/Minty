#include "Test_ShaderStage.h"
#include "Minty.h"

void test_ShaderStage(Test& _test)
{
    CATEGORY(ShaderStage)
    {
        std::vector<std::pair<ShaderStage, String>> VALUES = {
            {ShaderStage::Vertex, "Vertex"},
            {ShaderStage::Fragment, "Fragment"},
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
                EXPECT_EQUAL(parse_to_shader_stage(name), value);
            }

            EXPECT_EQUAL(parse_to_shader_stage(""), ShaderStage());
        }

        TEST("Parse Try")
        {
            ShaderStage result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_shader_stage(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_shader_stage("", result));
            EXPECT_EQUAL(result, ShaderStage());
        }
    }
}