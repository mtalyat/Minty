#include "Test_ShaderPolygonMode.h"
#include "Minty.h"

void test_ShaderPolygonMode(Test& _test)
{
    CATEGORY(ShaderPolygonMode)
    {
        std::vector<std::pair<ShaderPolygonMode, String>> VALUES = {
            {ShaderPolygonMode::Fill, "Fill"},
            {ShaderPolygonMode::Line, "Line"},
            {ShaderPolygonMode::Point, "Point"},
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
                EXPECT_EQUAL(parse_to_shader_polygon_mode(name), value);
            }

            EXPECT_EQUAL(parse_to_shader_polygon_mode(""), ShaderPolygonMode());
        }

        TEST("Parse Try")
        {
            ShaderPolygonMode result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_shader_polygon_mode(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_shader_polygon_mode("", result));
            EXPECT_EQUAL(result, ShaderPolygonMode());
        }
    }
}