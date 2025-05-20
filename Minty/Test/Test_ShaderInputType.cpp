#include "Test_ShaderInputType.h"
#include "Minty.h"

void test_ShaderInputType(Test& _test)
{
    CATEGORY(ShaderInputType)
    {
        std::vector<std::pair<ShaderInputType, String>> VALUES = {
            {ShaderInputType::Sample, "Sample"},
            {ShaderInputType::CombinedImageSampler, "CombinedImageSampler"},
            {ShaderInputType::SampledImage, "SampledImage"},
            {ShaderInputType::StorageImage, "StorageImage"},
            {ShaderInputType::UniformTexelBuffer, "UniformTexelBuffer"},
            {ShaderInputType::StorageTexelBuffer, "StorageTexelBuffer"},
            {ShaderInputType::UniformBuffer, "UniformBuffer"},
            {ShaderInputType::StorageBuffer, "StorageBuffer"},
            {ShaderInputType::UniformBufferDynamic, "UniformBufferDynamic"},
            {ShaderInputType::StorageBufferDynamic, "StorageBufferDynamic"},
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
                EXPECT_EQUAL(parse_to_shader_input_type(name), value);
            }

            EXPECT_EQUAL(parse_to_shader_input_type(""), ShaderInputType());
        }

        TEST("Parse Try")
        {
            ShaderInputType result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_shader_input_type(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_shader_input_type("", result));
            EXPECT_EQUAL(result, ShaderInputType());
        }
    }
}