#include "Test_ShaderPrimitiveTopology.h"
#include "Minty.h"

void test_ShaderPrimitiveTopology(Test& _test)
{
    CATEGORY(ShaderPrimitiveTopology)
    {
        std::vector<std::pair<ShaderPrimitiveTopology, String>> VALUES = {
            {ShaderPrimitiveTopology::PointList, "PointList"},
            {ShaderPrimitiveTopology::LineList, "LineList"},
            {ShaderPrimitiveTopology::LineStrip, "LineStrip"},
            {ShaderPrimitiveTopology::TriangleList, "TriangleList"},
            {ShaderPrimitiveTopology::TriangleStrip, "TriangleStrip"},
            {ShaderPrimitiveTopology::TriangleFan, "TriangleFan"},
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
                EXPECT_EQUAL(parse_to_shader_primitive_topology(name), value);
            }

            EXPECT_EQUAL(parse_to_shader_primitive_topology(""), ShaderPrimitiveTopology());
        }

        TEST("Parse Try")
        {
            ShaderPrimitiveTopology result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_shader_primitive_topology(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_shader_primitive_topology("", result));
            EXPECT_EQUAL(result, ShaderPrimitiveTopology());
        }
    }
}