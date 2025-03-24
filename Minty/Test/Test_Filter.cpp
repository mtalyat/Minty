#include "Test_Filter.h"
#include "Minty.h"

void test_Filter(Test& _test)
{
    CATEGORY(Filter)
    {
        std::vector<std::pair<Filter, String>> VALUES = {
            {Filter::Nearest, "Nearest"},
            {Filter::Linear, "Linear"},
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
                EXPECT_EQUAL(parse_to_filter(name), value);
            }

            EXPECT_EQUAL(parse_to_filter(""), Filter());
        }

        TEST("Parse Try")
        {
            Filter result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_filter(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_filter("", result));
            EXPECT_EQUAL(result, Filter());
        }
    }
}