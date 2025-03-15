#include "Test_ConstantContainer.h"
#include "Minty.h"

void test_ConstantContainer(Test& _test)
{
	CATEGORY(ConstantContainer)
	{
		TEST("Default Constructor")
		{
			ConstantContainer test;
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);
		}

		TEST("Size Constructor")
		{
			ConstantContainer test(5);
			EXPECT_EQUAL(test.get_capacity(), 5);
			EXPECT_EQUAL(test.get_size(), 5);
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			ConstantContainer test2(0);
			EXPECT_EQUAL(test2.get_capacity(), 0);
			EXPECT_EQUAL(test2.get_size(), 0);
			EXPECT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Data Constructor")
		{
			ID value = UUID::create();
			ConstantContainer test(&value, sizeof(ID));
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			ConstantContainer test2(nullptr, 10);
			EXPECT_EQUAL(test2.get_capacity(), 0);
			EXPECT_EQUAL(test2.get_size(), 0);
			EXPECT_EQUAL(test2.get_data(), nullptr);

			ConstantContainer test3(&value, 0);
			EXPECT_EQUAL(test3.get_capacity(), 0);
			EXPECT_EQUAL(test3.get_size(), 0);
			EXPECT_EQUAL(test3.get_data(), nullptr);
		}

		TEST("Copy Constructor")
		{
			ConstantContainer test(5);
			ConstantContainer test2(test);
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), 5);
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Move Constructor")
		{
			ConstantContainer test(5);
			ConstantContainer test2(std::move(test));
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), 5);
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Copy Assignment Operator")
		{
			ConstantContainer test(5);
			ConstantContainer test2;
			test2 = test;
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), 5);
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Move Assignment Operator")
		{
			ConstantContainer test(5);
			ConstantContainer test2;
			test2 = std::move(test);
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), 5);
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Get Capacity")
		{
			ConstantContainer test(5);
			EXPECT_EQUAL(test.get_capacity(), 5);
		}

		TEST("Get Size")
		{
			ConstantContainer test(5);
			EXPECT_EQUAL(test.get_size(), 5);
		}

		TEST("Get Data")
		{
			ID value = UUID::create();
			ConstantContainer test(&value, sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			ConstantContainer test2;
			EXPECT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Set At")
		{
			ID value = INVALID_ID;
			Int const size = 4;
			ConstantContainer test(sizeof(ID) * size);
			for (Size i = 0; i < size; ++i)
			{
				value = UUID::create();
				test.set_at(&value, sizeof(ID), i * sizeof(ID));
				EXPECT_EQUAL(*(static_cast<ID*>(test.get_data()) + i), value);
			}

			EXPECT_FAIL(test.set_at(nullptr, sizeof(ID), 0));
			EXPECT_FAIL(test.set_at(&value, 0, 0));
			EXPECT_FAIL(test.set_at(&value, sizeof(ID), size * sizeof(ID) + 1));
		}

		TEST("Set")
		{
			ID value = UUID::create();
			ConstantContainer test(sizeof(ID));
			test.set(&value, sizeof(ID));
			EXPECT_EQUAL(*(static_cast<ID*>(test.get_data())), value);

			EXPECT_FAIL(test.set(nullptr, sizeof(ID)));
			EXPECT_FAIL(test.set(&value, 0));
			EXPECT_FAIL(test.set(&value, sizeof(ID) + 1));
		}

		TEST("Append")
		{
			ConstantContainer test;
			ID value = UUID::create();
			EXPECT_FALSE(test.append(&value, sizeof(ID)));
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);
		}

		TEST("Append Object")
		{
			ConstantContainer test;
			ID value = UUID::create();
			EXPECT_FALSE(test.append_object(value));
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);
		}

		TEST("Clear")
		{
			ID value = UUID::create();
			ConstantContainer test(&value, sizeof(ID));
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);
			EXPECT_EQUAL(*(static_cast<ID*>(test.get_data())), value);
			test.clear();
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);
			EXPECT_EQUAL(*(static_cast<ID*>(test.get_data())), 0);
		}

		TEST("Reserve")
		{
			ConstantContainer test;
			EXPECT_TRUE(test.reserve(0));
			EXPECT_FALSE(test.reserve(5));
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);
		}

		TEST("Resize")
		{
			ConstantContainer test;
			EXPECT_TRUE(test.resize(0));
			EXPECT_FALSE(test.resize(5));
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);
		}
	}
}
