#include "Test_ShaderInputRate.h"
#include "Minty.h"

void test_ShaderInputRate(Test& _test)
{
    CATEGORY(ShaderInputRate)
    {
        std::vector<std::pair<ShaderInputRate, String>> VALUES = {
            {ShaderInputRate::Vertex, "Vertex"},
            {ShaderInputRate::Instance, "Instance"},
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
                EXPECT_EQUAL(parse_to_shader_input_rate(name), value);
            }

            EXPECT_EQUAL(parse_to_shader_input_rate(""), ShaderInputRate());
        }

        TEST("Parse Try")
        {
            ShaderInputRate result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_shader_input_rate(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_shader_input_rate("", result));
            EXPECT_EQUAL(result, ShaderInputRate());
        }
    }
}