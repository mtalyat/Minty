#include "Test_UUID.h"
#include "Minty.h"

void test_UUID(Test& _test)
{
	CATEGORY(UUID)
	{
		TEST("Default Constructor")
		{
			UUID uuid;
			EXPECT_EQUAL(uuid.get_data(), 0);
		}

		TEST("ID Constructor")
		{
			UUID uuid(0);
			EXPECT_EQUAL(uuid.get_data(), 0);

			uuid = UUID(1);
			EXPECT_EQUAL(uuid.get_data(), 1);

			uuid = UUID(0xFFFFFFFFFFFFFFFF);
			EXPECT_EQUAL(uuid.get_data(), 0xFFFFFFFFFFFFFFFF);
		}

		TEST("ID Operator")
		{
			UUID uuid;
			ID id = uuid;
			EXPECT_EQUAL(id, 0);
			uuid = UUID(1);
			id = uuid;
			EXPECT_EQUAL(id, 1);
			uuid = UUID(0xFFFFFFFFFFFFFFFF);
			id = uuid;
			EXPECT_EQUAL(id, 0xFFFFFFFFFFFFFFFF);
		}

		TEST("Equal Operator")
		{
			UUID uuid1(0);
			UUID uuid2(0);
			EXPECT_TRUE(uuid1 == uuid2);
			uuid1 = UUID(1);
			EXPECT_TRUE(!(uuid1 == uuid2));
			uuid2 = UUID(1);
			EXPECT_TRUE(uuid1 == uuid2);
			uuid1 = UUID(0xFFFFFFFFFFFFFFFF);
			uuid2 = UUID(0xFFFFFFFFFFFFFFFF);
			EXPECT_TRUE(uuid1 == uuid2);
		}

		TEST("Not Equal Operator")
		{
			UUID uuid1(0);
			UUID uuid2(0);
			EXPECT_TRUE(!(uuid1 != uuid2));
			uuid1 = UUID(1);
			EXPECT_TRUE(uuid1 != uuid2);
			uuid2 = UUID(1);
			EXPECT_TRUE(!(uuid1 != uuid2));
			uuid1 = UUID(0xFFFFFFFFFFFFFFFF);
			uuid2 = UUID(0xFFFFFFFFFFFFFFFF);
			EXPECT_TRUE(!(uuid1 != uuid2));
		}

		TEST("ID Equal Operator")
		{
			UUID uuid(0);
			ID id = 0;
			EXPECT_TRUE(uuid == id);
			uuid = UUID(1);
			EXPECT_TRUE(!(uuid == id));
			id = 1;
			EXPECT_TRUE(uuid == id);
			uuid = UUID(0xFFFFFFFFFFFFFFFF);
			EXPECT_TRUE(!(uuid == id));
			EXPECT_TRUE(uuid == 0xFFFFFFFFFFFFFFFF);
		}

		TEST("ID Not Equal Operator")
		{
			UUID uuid(0);
			ID id = 0;
			EXPECT_TRUE(!(uuid != id));
			uuid = UUID(1);
			EXPECT_TRUE(uuid != id);
			id = 1;
			EXPECT_TRUE(!(uuid != id));
			uuid = UUID(0xFFFFFFFFFFFFFFFF);
			EXPECT_TRUE(uuid != id);
			EXPECT_TRUE(!(uuid != 0xFFFFFFFFFFFFFFFF));
		}

		TEST("Get Data")
		{
			ID id = 0;
			UUID uuid(id);
			EXPECT_EQUAL(uuid.get_data(), id);
			id = 1;
			uuid = UUID(id);
			EXPECT_EQUAL(uuid.get_data(), id);
			id = 0xFFFFFFFFFFFFFFFF;
			uuid = UUID(id);
			EXPECT_EQUAL(uuid.get_data(), id);
		}

		TEST("Is Valid")
		{
			UUID uuid;
			EXPECT_TRUE(!uuid.is_valid());
			uuid = UUID(1);
			EXPECT_TRUE(uuid.is_valid());
			uuid = UUID(0xFFFFFFFFFFFFFFFF);
			EXPECT_TRUE(uuid.is_valid());
			uuid = UUID(INVALID_ID);
			EXPECT_TRUE(!uuid.is_valid());
		}

		TEST("Create")
		{
			for (Size i = 0; i < 10; ++i)
			{
				UUID uuid = UUID::create();
				EXPECT_TRUE(uuid.is_valid());
				EXPECT_TRUE(uuid != INVALID_ID);
			}
		}
	}
}
