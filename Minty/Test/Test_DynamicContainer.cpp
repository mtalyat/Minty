#include "Test_DynamicContainer.h"
#include "Minty.h"

void test_DynamicContainer(Test& _test)
{
	CATEGORY(DynamicContainer)
	{
		TEST("Default Constructor")
		{
			DynamicContainer test;
			EXPECT_EQUAL(test.get_capacity(), 0);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_EQUAL(test.get_data(), nullptr);
		}

		TEST("Capacity Constructor")
		{
			DynamicContainer test(5);
			EXPECT_EQUAL(test.get_capacity(), 5);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			DynamicContainer test2(0);
			EXPECT_EQUAL(test2.get_capacity(), 0);
			EXPECT_EQUAL(test2.get_size(), 0);
			EXPECT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Data Constructor")
		{
			ID value = UUID::create();
			DynamicContainer test(&value, sizeof(ID));
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			DynamicContainer test2(nullptr, 10);
			EXPECT_EQUAL(test2.get_capacity(), 0);
			EXPECT_EQUAL(test2.get_size(), 0);
			EXPECT_EQUAL(test2.get_data(), nullptr);

			DynamicContainer test3(&value, 0);
			EXPECT_EQUAL(test3.get_capacity(), 0);
			EXPECT_EQUAL(test3.get_size(), 0);
			EXPECT_EQUAL(test3.get_data(), nullptr);
		}

		TEST("Copy Constructor")
		{
			DynamicContainer test(5);
			Byte data = 5;
			test.append(&data, sizeof(Byte));
			DynamicContainer test2(test);
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), sizeof(Byte));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Move Constructor")
		{
			DynamicContainer test(5);
			Byte data = 5;
			test.append(&data, sizeof(Byte));
			DynamicContainer test2(std::move(test));
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), sizeof(Byte));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Copy Assignment Operator")
		{
			DynamicContainer test(5);
			Byte data = 5;
			test.append(&data, sizeof(Byte));
			DynamicContainer test2;
			test2 = test;
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), sizeof(Byte));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Move Assignment Operator")
		{
			DynamicContainer test(5);
			Byte data = 5;
			test.append(&data, sizeof(Byte));
			DynamicContainer test2;
			test2 = std::move(test);
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), sizeof(Byte));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Get Capacity")
		{
			DynamicContainer test(5);
			EXPECT_EQUAL(test.get_capacity(), 5);
			test.reserve(10);
			EXPECT_EQUAL(test.get_capacity(), 10);
		}

		TEST("Get Size")
		{
			DynamicContainer test(5);
			EXPECT_EQUAL(test.get_size(), 0);
			test.resize(5);
			EXPECT_EQUAL(test.get_size(), 5);
			test.resize(10);
			EXPECT_EQUAL(test.get_size(), 10);
		}

		TEST("Get Data")
		{
			ID value = UUID::create();
			DynamicContainer test(&value, sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			DynamicContainer test2;
			EXPECT_EQUAL(test2.get_data(), nullptr);
			test2.reserve(5);
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Set At")
		{
			ID value = INVALID_ID;
			Int const size = 4;
			DynamicContainer test(sizeof(ID) * size);
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
			DynamicContainer test(sizeof(ID));
			EXPECT_TRUE(test.set(&value, sizeof(ID)));
			EXPECT_EQUAL(*(static_cast<ID*>(test.get_data())), value);

			EXPECT_FAILURE(test.set(nullptr, sizeof(ID)));
			EXPECT_FAILURE(test.set(&value, 0));
			EXPECT_TRUE(test.set(&value, sizeof(ID) + 1));

			test = DynamicContainer(sizeof(ID));

			Byte value2 = 1;
			EXPECT_TRUE(test.set(&value2, sizeof(Byte)));
			EXPECT_EQUAL(*(static_cast<Byte*>(test.get_data())), value2);
			EXPECT_EQUAL(test.get_size(), sizeof(Byte));
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));

			ID values[2] = { UUID::create(), UUID::create() };
			EXPECT_TRUE(test.set(values, sizeof(ID) * 2));
			EXPECT_EQUAL(*(static_cast<ID*>(test.get_data())), values[0]);
			EXPECT_EQUAL(*(static_cast<ID*>(test.get_data()) + 1), values[1]);
			EXPECT_EQUAL(test.get_size(), sizeof(ID) * 2);
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID) * 2);
		}

		TEST("Append")
		{
			DynamicContainer test;
			ID value = UUID::create();
			EXPECT_TRUE(test.append(&value, sizeof(ID)));
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			DynamicContainer test2(sizeof(ID));
			EXPECT_TRUE(test2.append(&value, sizeof(ID)));
			EXPECT_EQUAL(test2.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test2.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);

			test2.clear();
			for (Size i = 0; i < 5; ++i)
			{
				value = UUID::create();
				EXPECT_TRUE(test2.append(&value, sizeof(ID)));
				EXPECT(test2.get_capacity(), >=, sizeof(ID) * (i + 1));
				EXPECT_EQUAL(test2.get_size(), sizeof(ID) * (i + 1));
				EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
			}
		}

		TEST("Append Object")
		{
			DynamicContainer test;
			ID value = UUID::create();
			EXPECT_TRUE(test.append_object(value));
			EXPECT_EQUAL(test.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			DynamicContainer test2(sizeof(ID));
			EXPECT_TRUE(test2.append_object(value));
			EXPECT_EQUAL(test2.get_capacity(), sizeof(ID));
			EXPECT_EQUAL(test2.get_size(), sizeof(ID));
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
		}

		TEST("Clear")
		{
			ID value = UUID::create();
			DynamicContainer test(&value, sizeof(ID));
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
			DynamicContainer test;
			EXPECT_TRUE(test.reserve(0));
			EXPECT_TRUE(test.reserve(5));
			EXPECT_EQUAL(test.get_capacity(), 5);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);
			test.reserve(10);
			EXPECT_EQUAL(test.get_capacity(), 10);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);
			test.reserve(5);
			EXPECT_EQUAL(test.get_capacity(), 10);
			EXPECT_EQUAL(test.get_size(), 0);
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);
		}

		TEST("Resize")
		{
			DynamicContainer test;
			EXPECT_TRUE(test.resize(0));
			EXPECT_TRUE(test.resize(5));
			EXPECT_EQUAL(test.get_capacity(), 5);
			EXPECT_EQUAL(test.get_size(), 5);
			EXPECT_NOT_EQUAL(test.get_data(), nullptr);

			DynamicContainer test2(5);
			EXPECT_TRUE(test2.resize(0));
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), 0);
			EXPECT_NOT_EQUAL(test2.get_data(), nullptr);
			EXPECT_TRUE(test2.resize(5));
			EXPECT_EQUAL(test2.get_capacity(), 5);
			EXPECT_EQUAL(test2.get_size(), 5);
			EXPECT_TRUE(test2.resize(10));
			EXPECT_EQUAL(test2.get_capacity(), 10);
			EXPECT_EQUAL(test2.get_size(), 10);
			EXPECT_TRUE(test2.resize(5));
			EXPECT_EQUAL(test2.get_capacity(), 10);
			EXPECT_EQUAL(test2.get_size(), 5);
		}
	}
}
