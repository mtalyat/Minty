#include "Test_MemoryManager.h"
#include "Minty.h"

void test_MemoryManager(Test& _test)
{
	CATEGORY(MemoryManager)
	{
		MemoryManagerBuilder builder
		{
			.temporary = { 1024 },
			.task = { 1024 },
			.persistent = {
				{ 8, 10 },
				{ 16, 10 },
				{ 32, 10 },
				{ 64, 10 },
				{ 128, 10 },
				{ 256, 10 },
				{ 512, 10 },
				{ 1024, 10 }
			}
		};

		TEST("Constructor")
		{
			MemoryManager manager(builder);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			EXPECT_TRUE(manager.get_static_size() == 0);
		}

		TEST("Move Constructor")
		{
			MemoryManager manager(builder);
			manager.initialize();
			void* temporary = manager.allocate(24, Allocator::Temporary);
			void* persistent = manager.allocate(24, Allocator::Persistent);
			void* def = manager.allocate(24, Allocator::Default);
			MemoryManager copy(std::move(manager));
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			EXPECT_TRUE(manager.get_static_size() == 0);
			EXPECT_TRUE(copy.get_dynamic_size() == 24);
			EXPECT_TRUE(copy.get_static_size() == 48);
			EXPECT_SUCCESS(copy.deallocate(def, 24, Allocator::Default));

			manager.dispose();
		}

		TEST("Move Operator")
		{
			MemoryManager manager(builder);
			manager.initialize();
			void* temporary = manager.allocate(24, Allocator::Temporary);
			void* persistent = manager.allocate(24, Allocator::Persistent);
			void* def = manager.allocate(24, Allocator::Default);
			MemoryManager copy = std::move(manager);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			EXPECT_TRUE(manager.get_static_size() == 0);
			EXPECT_TRUE(copy.get_dynamic_size() == 24);
			EXPECT_TRUE(copy.get_static_size() == 48);
			EXPECT_SUCCESS(copy.deallocate(def, 24, Allocator::Default));

			manager.dispose();
		}

		TEST("Get Size")
		{
			MemoryManager manager(builder);
			manager.initialize();
			EXPECT_TRUE(manager.get_size() == 0);
			void* temporary = manager.allocate(24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_size() == 24);
			void* persistent = manager.allocate(24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_size() == 48);
			void* def = manager.allocate(24, Allocator::Default);
			EXPECT_TRUE(manager.get_size() == 72);
			manager.deallocate(def, 24, Allocator::Default);
			EXPECT_TRUE(manager.get_size() == 48);
			manager.deallocate(persistent, 24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_size() == 24);
			manager.deallocate(temporary, 24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_size() == 0);

			manager.dispose();
		}

		TEST("Get Static Size")
		{
			MemoryManager manager(builder);
			manager.initialize();
			EXPECT_TRUE(manager.get_static_size() == 0);
			void* temporary = manager.allocate(24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_static_size() == 24);
			void* persistent = manager.allocate(24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_static_size() == 48);
			void* def = manager.allocate(24, Allocator::Default);
			EXPECT_TRUE(manager.get_static_size() == 48);
			manager.deallocate(def, 24, Allocator::Default);
			EXPECT_TRUE(manager.get_static_size() == 48);
			manager.deallocate(persistent, 24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_static_size() == 24);
			manager.deallocate(temporary, 24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_static_size() == 0);

			manager.dispose();
		}

		TEST("Get Dynamic Size")
		{
			MemoryManager manager(builder);
			manager.initialize();
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			void* temporary = manager.allocate(24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			void* persistent = manager.allocate(24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			void* def = manager.allocate(24, Allocator::Default);
			EXPECT_TRUE(manager.get_dynamic_size() == 24);
			manager.deallocate(def, 24, Allocator::Default);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			manager.deallocate(persistent, 24, Allocator::Persistent);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);
			manager.deallocate(temporary, 24, Allocator::Temporary);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);

			manager.dispose();
		}

		TEST("Update")
		{
			MemoryManager manager(builder);
			manager.initialize();
			Time time{};

			for (Size i = 0; i < MemoryManager::TASK_MEMORY_COUNT + 1; i++)
			{
				EXPECT_SUCCESS(manager.allocate(1024, Allocator::Temporary));
				EXPECT_FAILURE(manager.allocate(1024, Allocator::Temporary));

				EXPECT_SUCCESS(manager.allocate(1024, Allocator::Task));
				EXPECT_FAILURE(manager.allocate(1024, Allocator::Task));

				manager.update(time);
			}

			manager.dispose();
		}

		TEST("Allocate")
		{
			void* temporary = nullptr;
			void* task = nullptr;
			void* persistent = nullptr;
			void* def = nullptr;

			MemoryManager manager(builder);
			manager.initialize();
			EXPECT_FAILURE(manager.allocate(0, Allocator::Temporary));
			EXPECT_FAILURE(manager.allocate(0, Allocator::Task));
			EXPECT_FAILURE(manager.allocate(0, Allocator::Persistent));
			EXPECT_FAILURE(manager.allocate(0, Allocator::Default));

			EXPECT_FAILURE(manager.allocate(2048, Allocator::Temporary));
			EXPECT_FAILURE(manager.allocate(2048, Allocator::Task));
			EXPECT_FAILURE(manager.allocate(2048, Allocator::Persistent));
			EXPECT_SUCCESS(def = manager.allocate(2048, Allocator::Default));
			manager.deallocate(def, 2048, Allocator::Default);

			temporary = manager.allocate(1024, Allocator::Temporary);
			EXPECT_TRUE(temporary != nullptr);

			task = manager.allocate(1024, Allocator::Task);
			EXPECT_TRUE(task != nullptr);

			persistent = manager.allocate(1024, Allocator::Persistent);
			EXPECT_TRUE(persistent != nullptr);

			def = manager.allocate(1024, Allocator::Default);
			EXPECT_TRUE(def != nullptr);
			manager.deallocate(def, 1024, Allocator::Default);

			manager.dispose();
		}

		TEST("Deallocate")
		{
			MemoryManager manager(builder);
			manager.initialize();
			EXPECT_FAILURE(manager.deallocate(nullptr, 24, Allocator::Temporary));
			EXPECT_FAILURE(manager.deallocate(nullptr, 24, Allocator::Task));
			EXPECT_FAILURE(manager.deallocate(nullptr, 24, Allocator::Persistent));
			EXPECT_FAILURE(manager.deallocate(nullptr, 24, Allocator::Default));

			void* temporary = manager.allocate(24, Allocator::Temporary);
			EXPECT_FAILURE(manager.deallocate(nullptr, 24, Allocator::Temporary));
			EXPECT_FAILURE(manager.deallocate(temporary, 0, Allocator::Temporary));
			EXPECT_SUCCESS(manager.deallocate(temporary, 24, Allocator::Temporary));

			manager.allocate(24, Allocator::Temporary);
			Time time{};
			manager.update(time);
			EXPECT_FAILURE(manager.deallocate(temporary, 24, Allocator::Temporary));

			void* task = manager.allocate(24, Allocator::Task);
			EXPECT_FAILURE(manager.deallocate(nullptr, 24, Allocator::Task));
			EXPECT_FAILURE(manager.deallocate(task, 0, Allocator::Task));
			EXPECT_FAILURE(manager.deallocate(task, 24, Allocator::Default));
			EXPECT_SUCCESS(manager.deallocate(task, 24, Allocator::Task));

			void* persistent = manager.allocate(24, Allocator::Persistent);
			EXPECT_FAILURE(manager.deallocate(nullptr, 24, Allocator::Persistent));
			EXPECT_FAILURE(manager.deallocate(persistent, 0, Allocator::Persistent));
			EXPECT_FAILURE(manager.deallocate(persistent, 24, Allocator::Default));
			EXPECT_SUCCESS(manager.deallocate(persistent, 24, Allocator::Persistent));

			void* def = manager.allocate(24, Allocator::Default);
			EXPECT_FAILURE(manager.deallocate(nullptr, 24, Allocator::Default));
			EXPECT_FAILURE(manager.deallocate(def, 0, Allocator::Default));
			EXPECT_FAILURE(manager.deallocate(def, 24, Allocator::Temporary));
			EXPECT_SUCCESS(manager.deallocate(def, 24, Allocator::Default));

			EXPECT_TRUE(manager.get_static_size() == 0);
			EXPECT_TRUE(manager.get_dynamic_size() == 0);

			manager.dispose();
		}
	}
}