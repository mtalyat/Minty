#include "Test_MemoryPool.h"
#include "Minty.h"

void test_MemoryPool(Test& _test)
{
	CATEGORY(MemoryPool)
	{
		MemoryPoolBuilder builder
		{
			.blockSize = 1024,
			.blockCountCapacity = 10
		};

		TEST("Constructor")
		{
			EXPECT_FAIL(MemoryPool({ 0, 10 }));
			EXPECT_FAIL(MemoryPool({ 1024, 0 }));
			MemoryPool pool(builder);
			EXPECT_TRUE(pool.get_block_size() == 1024);
			EXPECT_TRUE(pool.get_capacity() == 10);
			EXPECT_TRUE(pool.get_count() == 0);
		}

		TEST("Move Constructor")
		{
			MemoryPool pool(builder);
			pool.allocate();
			MemoryPool copy(std::move(pool));
			EXPECT_TRUE(pool.get_block_size() == 0);
			EXPECT_TRUE(pool.get_capacity() == 0);
			EXPECT_TRUE(pool.get_count() == 0);
			EXPECT_TRUE(copy.get_block_size() == 1024);
			EXPECT_TRUE(copy.get_capacity() == 10);
			EXPECT_TRUE(copy.get_count() == 1);
		}

		TEST("Move Operator")
		{
			MemoryPool pool(builder);
			pool.allocate();
			MemoryPool copy = std::move(pool);
			EXPECT_TRUE(pool.get_block_size() == 0);
			EXPECT_TRUE(pool.get_capacity() == 0);
			EXPECT_TRUE(pool.get_count() == 0);
			EXPECT_TRUE(copy.get_block_size() == 1024);
			EXPECT_TRUE(copy.get_capacity() == 10);
			EXPECT_TRUE(copy.get_count() == 1);
		}

		TEST("Get Block Size")
		{
			MemoryPool pool(builder);
			EXPECT_TRUE(pool.get_block_size() == 1024);
		}

		TEST("Get Capacity")
		{
			MemoryPool pool(builder);
			EXPECT_TRUE(pool.get_capacity() == 10);
		}

		TEST("Get Count")
		{
			MemoryPool pool(builder);
			EXPECT_TRUE(pool.get_count() == 0);
			pool.allocate();
			EXPECT_TRUE(pool.get_count() == 1);
		}

		TEST("Get Data")
		{
			MemoryPool pool(builder);
			EXPECT_TRUE(pool.get_data() != nullptr);
			void* ptr = pool.allocate();
			EXPECT_TRUE(ptr == pool.get_data());
		}

		TEST("Is Full")
		{
			MemoryPool pool({ 1024, 1 });
			EXPECT_TRUE(!pool.is_full());
			pool.allocate();
			EXPECT_TRUE(pool.is_full());
		}

		TEST("Allocate")
		{
			MemoryPool pool(builder);
			void* ptr = pool.allocate();
			EXPECT_TRUE(ptr != nullptr);
			EXPECT_TRUE(pool.get_count() == 1);
			ptr = pool.allocate();
			EXPECT_TRUE(ptr != nullptr);
			EXPECT_TRUE(pool.get_count() == 2);
		}

		TEST("Deallocate")
		{
			MemoryPool pool(builder);
			void* ptr = pool.allocate();
			pool.deallocate(ptr);
			EXPECT_TRUE(pool.get_count() == 0);
		}

		TEST("Clear")
		{
			MemoryPool pool(builder);
			pool.allocate();
			pool.clear();
			EXPECT_TRUE(pool.get_count() == 0);
		}
	}
}