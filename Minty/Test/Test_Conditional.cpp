#include "Test_Conditional.h"
#include "Minty.h"

void test_Conditional(Test& _test)
{
    CATEGORY(Conditional)
    {
        std::vector<std::pair<Conditional, String>> VALUES = {
            {Conditional::Equal, "Equal"},
            {Conditional::NotEqual, "NotEqual"},
            {Conditional::GreaterThan, "GreaterThan"},
            {Conditional::GreaterThanOrEqualTo, "GreaterThanOrEqualTo"},
            {Conditional::LessThan, "LessThan"},
            {Conditional::LessThanOrEqualTo, "LessThanOrEqualTo"},
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
                EXPECT_EQUAL(parse_to_conditional(name), value);
            }

            EXPECT_EQUAL(parse_to_conditional(""), Conditional());
        }

        TEST("Parse Try")
        {
            Conditional result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_conditional(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_conditional("", result));
            EXPECT_EQUAL(result, Conditional());
        }
    }
}
