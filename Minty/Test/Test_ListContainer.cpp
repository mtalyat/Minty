#include "Test_ListContainer.h"
#include "Minty.h"

void test_ListContainer(Test& _test)
{
	CATEGORY(ListContainer)
	{
		TEST("Constructor Default")
		{
			ListContainer container;
			EXPECT_EQUAL(container.get_size(), 0);
			EXPECT_EQUAL(container.get_capacity(), 0);
			EXPECT_EQUAL(container.get_data(), nullptr);
		}

		TEST("Constructor Capacity")
		{
			ListContainer container(sizeof(int), 10);
			EXPECT_EQUAL(container.get_size(), 0);
			EXPECT_EQUAL(container.get_capacity(), 10 * sizeof(int));
			EXPECT_NOT_EQUAL(container.get_data(), nullptr);
		}

		TEST("Constructor Data")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			EXPECT_EQUAL(container.get_size(), 5 * sizeof(int));
			EXPECT_EQUAL(container.get_capacity(), 5 * sizeof(int));
			EXPECT_NOT_EQUAL(container.get_data(), data);
		}

		TEST("Copy Constructor")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			ListContainer copy(container);
			EXPECT_EQUAL(copy.get_size(), 5 * sizeof(int));
			EXPECT_EQUAL(copy.get_capacity(), 5 * sizeof(int));
			EXPECT_NOT_EQUAL(copy.get_data(), data);
		}

		TEST("Move Constructor")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			ListContainer moved(std::move(container));
			EXPECT_EQUAL(moved.get_size(), 5 * sizeof(int));
			EXPECT_EQUAL(moved.get_capacity(), 5 * sizeof(int));
			EXPECT_NOT_EQUAL(moved.get_data(), data);
		}

		TEST("Copy Assignment")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			ListContainer copy;
			copy = container;
			EXPECT_EQUAL(copy.get_size(), 5 * sizeof(int));
			EXPECT_EQUAL(copy.get_capacity(), 5 * sizeof(int));
			EXPECT_NOT_EQUAL(copy.get_data(), data);
		}

		TEST("Move Assignment")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			ListContainer moved;
			moved = std::move(container);
			EXPECT_EQUAL(moved.get_size(), 5 * sizeof(int));
			EXPECT_EQUAL(moved.get_capacity(), 5 * sizeof(int));
			EXPECT_NOT_EQUAL(moved.get_data(), data);
		}

		TEST("Get Data")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			EXPECT_NOT_EQUAL(container.get_data(), nullptr);
			EXPECT_NOT_EQUAL(container.get_data(), data);
		}

		TEST("Get Size")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			EXPECT_EQUAL(container.get_size(), 5 * sizeof(int));
			ListContainer container2;
			EXPECT_EQUAL(container2.get_size(), 0);
		}

		TEST("Get Capacity")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			EXPECT_EQUAL(container.get_capacity(), 5 * sizeof(int));
			ListContainer container2;
			EXPECT_EQUAL(container2.get_capacity(), 0);
			ListContainer container3(sizeof(int), 100);
			EXPECT_EQUAL(container3.get_capacity(), 100 * sizeof(int));
		}

		TEST("Get Stride")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			EXPECT_EQUAL(container.get_stride(), sizeof(int));
		}

		TEST("Get Count")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			EXPECT_EQUAL(container.get_count(), 5);
		}

		TEST("Get Element")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(0)), 1);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(1)), 2);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(2)), 3);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(3)), 4);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(4)), 5);
			EXPECT_FAILURE(container.get_element(5)); // Out of bounds
		}

		TEST("Is Empty")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			EXPECT_FALSE(container.is_empty());
			container.clear();
			EXPECT_TRUE(container.is_empty());
			ListContainer empty_container;
			EXPECT_TRUE(empty_container.is_empty());
		}

		TEST("Set At")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			int value = 10;
			container.set_at(&value, 1, 0);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(0)), 10);
			value = 1;
			container.set_at(&value, 1, 0);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(0)), 1);
		}

		TEST("Set")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			int value = 10;
			container.set(&value, 1);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(0)), 10);
			EXPECT_EQUAL(container.get_count(), 1);
			container.set(data, 5);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(0)), 1);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(1)), 2);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(2)), 3);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(3)), 4);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(4)), 5);
			EXPECT_EQUAL(container.get_count(), 5);
		}

		TEST("Append")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			int value = 10;
			container.append(&value);
			EXPECT_EQUAL(*static_cast<int*>(container.get_element(5)), 10);
			EXPECT_EQUAL(container.get_count(), 6);
		}

		TEST("Clear")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			container.clear();
			EXPECT_EQUAL(container.get_size(), 0);
			EXPECT_NOT_EQUAL(container.get_data(), nullptr);
			EXPECT_EQUAL(container.get_capacity(), 5 * sizeof(int));
		}

		TEST("Reserve")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			container.reserve(10);
			EXPECT_EQUAL(container.get_size(), 5 * sizeof(int));
			EXPECT_EQUAL(container.get_capacity(), 10 * sizeof(int));
		}

		TEST("Resize")
		{
			int data[5] = { 1, 2, 3, 4, 5 };
			ListContainer container(data, sizeof(int), 5);
			container.resize(10);
			EXPECT_EQUAL(container.get_size(), 10 * sizeof(int));
			EXPECT_EQUAL(container.get_capacity(), 10 * sizeof(int));
		}
	}
}
