#include "Test_StaticContainer.h"
#include "Minty.h"

void test_StaticContainer(Test& _test)
{
	CATEGORY(StaticContainer)
	{
		TEST("Default Constructor")
		{
			StaticContainer test;
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);
		}

		TEST("Capacity Constructor")
		{
			StaticContainer test(5);
			EXPECT_EQUAL(test.get_capacity(), 5);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			StaticContainer test2(0);
			EXPECT_EQUAL(test2.get_capacity(), 0);
			EXPECT_EQUAL(test2.get_size(), 0);
			EXPECT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Data Constructor")
		{
			ID value = UUID::create();
			StaticContainer test(&value, sizeof(ID));
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			StaticContainer test2(nullptr, 10);
			EXPECT_EQUAL(test2.get_capacity(), 0);
			EXPECT_EQUAL(test2.get_size(), 0);
			EXPECT_EQUAL(test2.get_data(), nullptr);

			StaticContainer test3(&value, 0);
			EXPECT_EQUAL(test3.get_capacity(), 0);
			EXPECT_EQUAL(test3.get_size(), 0);
			EXPECT_EQUAL(test3.get_data(), nullptr);
		}

		TEST("Copy Constructor")
		{
			StaticContainer test(5);
			Byte data = 5;
			test.append(&data, sizeof(Byte));
			StaticContainer test2(test);
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), sizeof(Byte));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Move Constructor")
		{
			StaticContainer test(5);
			Byte data = 5;
			test.append(&data, sizeof(Byte));
			StaticContainer test2(std::move(test));
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), sizeof(Byte));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Copy Assignment Operator")
		{
			StaticContainer test(5);
			Byte data = 5;
			test.append(&data, sizeof(Byte));
			StaticContainer test2;
			test2 = test;
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), sizeof(Byte));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Move Assignment Operator")
		{
			StaticContainer test(5);
			Byte data = 5;
			test.append(&data, sizeof(Byte));
			StaticContainer test2;
			test2 = std::move(test);
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), sizeof(Byte));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Get Capacity")
		{
			StaticContainer test(5);
			EXPECT_EQUAL(test.get_capacity(), 5);
		}

		TEST("Get Size")
		{
			StaticContainer test(5);
			EXPECT_EQUAL(test.get_size(), 0);
			test.resize(5);
			EXPECT_EQUAL(test.get_size(), 5);
			test.resize(3);
			EXPECT_EQUAL(test.get_size(), 3);
		}

		TEST("Get Data")
		{
			ID value = UUID::create();
			StaticContainer test(&value, sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			StaticContainer test2;
			EXPECT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Set At")
		{
			ID value = INVALID_ID;
			Int const size = 4;
			StaticContainer test(sizeof(ID) * size);
			test.resize(sizeof(ID) * size);
			for (Size i = 0; i < size; ++i)
			{
				value = UUID::create();
				test.set_at(&value, sizeof(ID), i * sizeof(ID));
				EXPECT_EQUAL(*(static_cast<ID*>(test.get_data()) + i), value);
			}

			EXPECT_FAILURE(test.set_at(nullptr, sizeof(ID), 0));
			EXPECT_FAILURE(test.set_at(&value, 0, 0));
			EXPECT_FAILURE(test.set_at(&value, sizeof(ID), size * sizeof(ID) + 1));
		}

		TEST("Set")
		{
			ID value = UUID::create();
			StaticContainer test(sizeof(ID));
			EXPECT_TRUE(test.set(&value, sizeof(ID)));
			EXPECT_EQUAL(*(static_cast<ID*>(test.get_data())), value);

			EXPECT_FAILURE(test.set(nullptr, sizeof(ID)));
			EXPECT_FAILURE(test.set(&value, 0));
			EXPECT_FALSE(test.set(&value, sizeof(ID) + 1));

			Byte value2 = 1;
			EXPECT_TRUE(test.set(&value2, sizeof(Byte)));
			EXPECT_EQUAL(*(static_cast<Byte*>(test.get_data())), value2);
			EXPECT_EQUAL(test.get_size(), sizeof(Byte));
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));
		}

		TEST("Append")
		{
			StaticContainer test;
			ID value = UUID::create();
			EXPECT_FALSE(test.append(&value, sizeof(ID)));
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);

			StaticContainer test2(sizeof(ID));
			EXPECT_TRUE(test2.append(&value, sizeof(ID)));
			EXPECT_EQUAL(test2.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test2.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Append Object")
		{
			StaticContainer test;
			ID value = UUID::create();
			EXPECT_FALSE(test.append_object(value));
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);

			StaticContainer test2(sizeof(ID));
			EXPECT_TRUE(test2.append_object(value));
			EXPECT_EQUAL(test2.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test2.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Clear")
		{
			ID value = UUID::create();
			StaticContainer test(&value, sizeof(ID));
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);
			EXPECT_EQUAL(*(static_cast<ID*>(test.get_data())), value);
			test.clear();
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);
		}

		TEST("Reserve")
		{
			StaticContainer test;
			EXPECT_TRUE(test.reserve(0));
			EXPECT_FALSE(test.reserve(5));
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);
		}

		TEST("Resize")
		{
			StaticContainer test;
			EXPECT_TRUE(test.resize(0));
			EXPECT_FALSE(test.resize(5));
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);

			StaticContainer test2(5);
			EXPECT_TRUE(test2.resize(0));
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), 0);
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
			EXPECT_TRUE(test2.resize(5));
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), 5);
			EXPECT_FALSE(test2.resize(10));
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), 5);
		}
	}
}
