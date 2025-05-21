#include "Test_KeyModifiers.h"
#include "Minty.h"

void test_KeyModifiers(Test& _test)
{
    CATEGORY(KeyModifiers)
    {
        std::vector<std::pair<KeyModifiers, String>> VALUES = {
            {KeyModifiers::Shift, "Shift"},
            {KeyModifiers::Control, "Control"},
            {KeyModifiers::Alt, "Alt"},
            {KeyModifiers::Super, "Super"},
            {KeyModifiers::CapsLock, "CapsLock"},
            {KeyModifiers::NumLock, "NumLock"},
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
                EXPECT_EQUAL(parse_to_key_modifiers(name), value);
            }

            EXPECT_EQUAL(parse_to_key_modifiers(""), KeyModifiers());
        }

        TEST("Parse Try")
        {
            KeyModifiers result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_key_modifiers(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_key_modifiers("", result));
            EXPECT_EQUAL(result, KeyModifiers());
        }
    }
}