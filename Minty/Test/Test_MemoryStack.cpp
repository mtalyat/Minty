#include "Test_MemoryStack.h"
#include "Minty.h"

void test_MemoryStack(Test& _test)
{
	CATEGORY(MemoryStack)
	{
		MemoryStackBuilder builder
		{
			.capacity = 1024
		};

		TEST("Constructor")
		{
			EXPECT_FAILURE(MemoryStack({ 0 }));
			MemoryStack stack(builder);
			EXPECT_TRUE(stack.get_capacity() == 1024);
			EXPECT_TRUE(stack.get_size() == 0);
		}

		TEST("Move Constructor")
		{
			MemoryStack stack(builder);
			stack.allocate(512);
			MemoryStack copy(std::move(stack));
			EXPECT_TRUE(stack.get_capacity() == 0);
			EXPECT_TRUE(stack.get_size() == 0);
			EXPECT_TRUE(copy.get_capacity() == 1024);
			EXPECT_TRUE(copy.get_size() == 512);
		}

		TEST("Move Operator")
		{
			MemoryStack stack(builder);
			stack.allocate(512);
			MemoryStack copy = std::move(stack);
			EXPECT_TRUE(stack.get_capacity() == 0);
			EXPECT_TRUE(stack.get_size() == 0);
			EXPECT_TRUE(copy.get_capacity() == 1024);
			EXPECT_TRUE(copy.get_size() == 512);
		}

		TEST("Get Capacity")
		{
			MemoryStack stack(builder);
			EXPECT_TRUE(stack.get_capacity() == 1024);
		}

		TEST("Get Size")
		{
			MemoryStack stack(builder);
			EXPECT_TRUE(stack.get_size() == 0);
			stack.allocate(512);
			EXPECT_TRUE(stack.get_size() == 512);
			stack.allocate(512);
			EXPECT_TRUE(stack.get_size() == 1024);
		}

		TEST("Get Data")
		{
			MemoryStack stack(builder);
			EXPECT_TRUE(stack.get_data() != nullptr);
			void* ptr = stack.allocate(512);
			EXPECT_TRUE(ptr == stack.get_data());
		}

		TEST("Allocate")
		{
			MemoryStack stack(builder);
			void* ptr = stack.allocate(512);
			EXPECT_FAILURE(stack.allocate(0));
			EXPECT_TRUE(ptr != nullptr);
			EXPECT_TRUE(stack.get_size() == 512);
			ptr = stack.allocate(512);
			EXPECT_TRUE(ptr != nullptr);
			EXPECT_TRUE(stack.get_size() == 1024);
			EXPECT_FAILURE(stack.allocate(1));
		}

		TEST("Deallocate")
		{
			MemoryStack stack(builder);
			EXPECT_FAILURE(stack.deallocate(0));
			EXPECT_FAILURE(stack.deallocate(512));
			void* ptr = stack.allocate(512);
			stack.deallocate(512);
			EXPECT_TRUE(stack.get_size() == 0);
		}

		TEST("Clear")
		{
			MemoryStack stack(builder);
			stack.allocate(512);
			stack.clear();
			EXPECT_TRUE(stack.get_size() == 0);
		}
	}
}