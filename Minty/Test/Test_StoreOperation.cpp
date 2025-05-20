#include "Test_StoreOperation.h"
#include "Minty.h"

void test_StoreOperation(Test& _test)
{
    CATEGORY(StoreOperation)
    {
        std::vector<std::pair<StoreOperation, String>> VALUES = {
            {StoreOperation::DontCare, "DontCare"},
            {StoreOperation::Store, "Store"},
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
                EXPECT_EQUAL(parse_to_store_operation(name), value);
            }

            EXPECT_EQUAL(parse_to_store_operation(""), StoreOperation());
        }

        TEST("Parse Try")
        {
            StoreOperation result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_store_operation(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_store_operation("", result));
            EXPECT_EQUAL(result, StoreOperation());
        }
    }
}