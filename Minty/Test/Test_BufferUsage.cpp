#include "Test_BufferUsage.h"
#include "Minty.h"

void test_BufferUsage(Test& _test)
{
	CATEGORY(BufferUsage)
	{
        std::vector<std::pair<BufferUsage, String>> VALUES = {
            {BufferUsage::Transfer, "Transfer"},
            {BufferUsage::Vertex, "Vertex"},
            {BufferUsage::Index, "Index"},
            {BufferUsage::Uniform, "Uniform"},
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
                EXPECT_EQUAL(parse_to_buffer_usage(name), value);
            }

            EXPECT_EQUAL(parse_to_buffer_usage(""), BufferUsage());
        }

        TEST("Parse Try")
        {
            BufferUsage result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_buffer_usage(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_buffer_usage("", result));
            EXPECT_EQUAL(result, BufferUsage());
        }
	}
}
