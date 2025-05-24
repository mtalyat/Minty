#include "Test_JobManager.h"
#include "Minty.h"

void test_JobManager(Test& _test)
{
	CATEGORY(JobManager)
	{
		TEST("Constructor")
		{
			// default thread count
			JobManagerBuilder builder{};
			EXPECT_SUCCESS(JobManager manager(builder));
			
			builder.threadCount = 0;
			EXPECT_FAILURE(JobManager manager(builder));
		}

		TEST("Schedule Job")
		{
			JobManagerBuilder builder{};
			JobManager manager(builder);
			manager.initialize();
			CLEAR_OUTPUT();
			
			Handle handle = manager.schedule([]() { std::cout << "Hello World!" << std::flush; });

			manager.wait(handle);
			EXPECT_TRUE(manager.is_complete(handle));
			EXPECT_OUTPUT("Hello World!");
			manager.dispose();
		}

		TEST("Schedule Job with Dependency")
		{
			JobManagerBuilder builder{};
			JobManager manager(builder);
			manager.initialize();
			CLEAR_OUTPUT();

			Int value = 0;
			Handle handle0 = manager.schedule([&value]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				value = 1;
				});
			Handle handle1 = manager.schedule([&value]() {
				std::cout << value << std::flush;
				}, handle0);

			manager.wait(handle1);
			EXPECT_TRUE(manager.is_complete(handle0) && manager.is_complete(handle1));
			EXPECT_OUTPUT("1");
			manager.dispose();
		}

		TEST("Schedule Job with Dependencies")
		{
			JobManagerBuilder builder{};
			JobManager manager(builder);
			manager.initialize();
			CLEAR_OUTPUT();

			Int value0 = 0;
			Int value1 = 0;
			Handle handle0 = manager.schedule([&value0]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				value0 = 1;
				});
			Handle handle1 = manager.schedule([&value1]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				value1 = 2;
				});
			Handle handle2 = manager.schedule([&value0, &value1]() {
				std::cout << value0 + value1 << std::flush;
				}, { handle0, handle1 });

			manager.wait(handle2);
			EXPECT_TRUE(manager.is_complete(handle0) && manager.is_complete(handle1) && manager.is_complete(handle2));
			EXPECT_OUTPUT("3");
			manager.dispose();
		}

		TEST("Schedule Parallel Job")
		{
			JobManagerBuilder builder{};
			JobManager manager(builder);
			manager.initialize();

			Size const count = 100;
			Int values[count] = { 0 };
			Handle handle = manager.schedule_parallel([&values](Size index) {
				values[index] = static_cast<Int>(index);
				}, count);

			manager.wait(handle);
			EXPECT_TRUE(manager.is_complete(handle));
			for (Size i = 0; i < count; ++i)
			{
				EXPECT_EQUAL(values[i], i);
			}
			manager.dispose();
		}

		TEST("Schedule Parallel Job with Dependency")
		{
			JobManagerBuilder builder{};
			JobManager manager(builder);
			manager.initialize();

			Size const count = 100;
			Int values[count] = { 0 };
			Handle handle0 = manager.schedule_parallel([&values](Size index) {
				values[index] = static_cast<Int>(index);
				}, count);
			Handle handle1 = manager.schedule_parallel([&values](Size index) {
				values[index] += 1;
				}, count, handle0);

			manager.wait(handle1);
			EXPECT_TRUE(manager.is_complete(handle0) && manager.is_complete(handle1));
			for (Size i = 0; i < count; ++i)
			{
				EXPECT_EQUAL(values[i], i + 1);
			}
			manager.dispose();
		}

		TEST("Schedule Parallel Job with Dependencies")
		{
			JobManagerBuilder builder{};
			JobManager manager(builder);
			manager.initialize();

			Size const count = 100;
			Int values[count] = { 0 };
			Int values2[count] = { 0 };
			Int results[count] = { 0 };
			Handle handle0 = manager.schedule([&values, count]() {
				for (Size i = 0; i < count; ++i)
				{
					values[i] = static_cast<Int>(i);
				}
				});
			Handle handle1 = manager.schedule([&values2, count]() {
				for (Size i = 0; i < count; ++i)
				{
					values2[i] = static_cast<Int>(i);
				}
				});
			Handle handle2 = manager.schedule_parallel([&values, &values2, &results](Size index) {
				results[index] = values[index] * values2[index];
				}, count, { handle0, handle1 });

			manager.wait(handle2);
			EXPECT_TRUE(manager.is_complete(handle0) && manager.is_complete(handle1) && manager.is_complete(handle2));
			for (Size i = 0; i < count; ++i)
			{
				EXPECT_EQUAL(results[i], i * i);
			}
			manager.dispose();
		}

		TEST("Is Complete")
		{
			JobManagerBuilder builder{};
			JobManager manager(builder);
			manager.initialize();
			Handle handle = manager.schedule([]() { std::this_thread::sleep_for(std::chrono::milliseconds(10)); });
			EXPECT_FALSE(manager.is_complete(handle));
			manager.wait(handle);
			EXPECT_TRUE(manager.is_complete(handle));
			manager.dispose();
		}

		TEST("Wait")
		{
			JobManagerBuilder builder{};
			JobManager manager(builder);
			manager.initialize();
			Handle handle = manager.schedule([]() { std::this_thread::sleep_for(std::chrono::milliseconds(10)); });
			manager.wait(handle);
			EXPECT_TRUE(manager.is_complete(handle));
			manager.dispose();
		}

		TEST("Wait Multiple")
		{
			JobManagerBuilder builder{};
			JobManager manager(builder);
			manager.initialize();
			Handle handle0 = manager.schedule([]() { std::this_thread::sleep_for(std::chrono::milliseconds(10)); });
			Handle handle1 = manager.schedule([]() { std::this_thread::sleep_for(std::chrono::milliseconds(10)); });
			manager.wait({ handle0, handle1 });
			EXPECT_TRUE(manager.is_complete(handle0) && manager.is_complete(handle1));
			manager.dispose();
		}
	}
}
