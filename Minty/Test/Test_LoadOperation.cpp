#include "Test_LoadOperation.h"
#include "Minty.h"

void test_LoadOperation(Test& _test)
{
    CATEGORY(LoadOperation)
    {
        std::vector<std::pair<LoadOperation, String>> VALUES = {
            {LoadOperation::DontCare, "DontCare"},
            {LoadOperation::Load, "Load"},
            {LoadOperation::Clear, "Clear"},
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
                EXPECT_EQUAL(parse_to_load_operation(name), value);
            }

            EXPECT_EQUAL(parse_to_load_operation(""), LoadOperation());
        }

        TEST("Parse Try")
        {
            LoadOperation result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_load_operation(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_load_operation("", result));
            EXPECT_EQUAL(result, LoadOperation());
        }
    }
}
