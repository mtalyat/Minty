#include "Test_ShaderCullMode.h"
#include "Minty.h"

void test_ShaderCullMode(Test& _test)
{
    CATEGORY(ShaderCullMode)
    {
        std::vector<std::pair<ShaderCullMode, String>> VALUES = {
            {ShaderCullMode::None, "None"},
            {ShaderCullMode::Front, "Front"},
            {ShaderCullMode::Back, "Back"},
            {ShaderCullMode::Both, "Both"},
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
                EXPECT_EQUAL(parse_to_shader_cull_mode(name), value);
            }

            EXPECT_EQUAL(parse_to_shader_cull_mode(""), ShaderCullMode());
        }

        TEST("Parse Try")
        {
            ShaderCullMode result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_shader_cull_mode(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_shader_cull_mode("", result));
            EXPECT_EQUAL(result, ShaderCullMode());
        }
    }
}