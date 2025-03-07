#include "Test_Base.h"
#include "Minty.h"

void test_Base(Test& _test)
{
	CATEGORY(Base)
	{
		Application app({});

		TEST("Allocate/Deallocate")
		{
			void* ptr = allocate(16, Allocator::Default);
			EXPECT_TRUE(ptr != nullptr);
			deallocate(ptr, 16, Allocator::Default);
		}

		TEST("Construct/Destruct")
		{
			int* ptr = construct<int>(Allocator::Default, 5);
			EXPECT_TRUE(ptr != nullptr);
			EXPECT_TRUE(*ptr == 5);
			destruct<int>(ptr, Allocator::Default);
		}
		
		TEST("Construct/Destruct Array")
		{
			Size const count = 3;
			int* ptr = construct_array<int>(count, Allocator::Default, 5);
			EXPECT_TRUE(ptr != nullptr);
			for (int i = 0; i < count; ++i)
			{
				EXPECT_TRUE(ptr[i] == 5);
			}
			destruct_array<int>(ptr, count, Allocator::Default);
		}
	}
}
