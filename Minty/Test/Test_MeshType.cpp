#include "Test_MeshType.h"
#include "Minty.h"

void test_MeshType(Test& _test)
{
    CATEGORY(MeshType)
    {
        std::vector<std::pair<MeshType, String>> VALUES = {
            {MeshType::Empty, "Empty"},
            {MeshType::Custom, "Custom"},
            {MeshType::Quad, "Quad"},
            {MeshType::Cube, "Cube"},
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
                EXPECT_EQUAL(parse_to_mesh_type(name), value);
            }

            EXPECT_EQUAL(parse_to_mesh_type(""), MeshType());
        }

        TEST("Parse Try")
        {
            MeshType result;
            for (auto const& [value, name] : VALUES)
            {
                EXPECT_TRUE(parse_try_mesh_type(name, result));
                EXPECT_EQUAL(result, value);
            }

            EXPECT_FALSE(parse_try_mesh_type("", result));
            EXPECT_EQUAL(result, MeshType());
        }
    }
}