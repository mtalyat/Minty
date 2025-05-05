#include "Test_Object.h"
#include "Minty.h"

void test_Object(Test& _test)
{
	CATEGORY(Object)
	{
		TEST("Default Constructor")
		{
			Object object;
			EXPECT_TRUE(object.is_empty());
		}

		TEST("Capacity Constructor")
		{
			Object object(10);
			EXPECT_TRUE(object.is_empty());
		}

		TEST("Initializer List Constructor")
		{
			Object object({
				{"key1", Variable(10)},
				{"key2", Variable(20.0f) }
				});
			EXPECT_FALSE(object.is_empty());
			EXPECT_EQUAL(object.get_size(), 2);
			EXPECT_EQUAL(object.at("key1").get<Int>(), 10);
			EXPECT_EQUAL(object.at("key2").get<Float>(), 20.0f);
		}

		TEST("Vector Constructor")
		{
			Vector<Pair<String, Variable>> variables;
			Object object(variables);
			EXPECT_TRUE(object.is_empty());
			variables.add(Pair<String, Variable>("key", Variable(10)));
			object = Object(variables);
			EXPECT_FALSE(object.is_empty());
		}

		TEST("Copy Constructor")
		{
			Object object(10);
			Object copy(object);
			EXPECT_TRUE(copy.is_empty());
			object.add("key", Variable(10));
			copy = Object(object);
			EXPECT_FALSE(copy.is_empty());
		}

		TEST("Move Constructor")
		{
			Object object(10);
			Object move(std::move(object));
			EXPECT_TRUE(move.is_empty());
			object.add("key", Variable(10));
			move = Object(std::move(object));
			EXPECT_FALSE(move.is_empty());
		}

		TEST("Copy Assignment")
		{
			Object object(10);
			Object copy;
			EXPECT_TRUE(copy.is_empty());
			object.add("key", Variable(10));
			copy = object;
			EXPECT_FALSE(copy.is_empty());
		}

		TEST("Move Assignment")
		{
			Object object(10);
			Object move;
			EXPECT_TRUE(move.is_empty());
			object.add("key", Variable(10));
			move = std::move(object);
			EXPECT_FALSE(move.is_empty());
		}

		TEST("Get Variables")
		{
			Object object(10);
			object.add("key", Variable(10));
			Vector<Pair<String, Variable>> variables = object.get_variables();
			EXPECT_EQUAL(variables.get_size(), 1);
			EXPECT_EQUAL(variables[0].first, "key");
			EXPECT_EQUAL(variables[0].second.get<Int>(), 10);
		}

		TEST("Get Size")
		{
			Object object(10);
			EXPECT_EQUAL(object.get_size(), 0);
			object.add("key", Variable(10));
			EXPECT_EQUAL(object.get_size(), 1);
		}

		TEST("Is Empty")
		{
			Object object(10);
			EXPECT_TRUE(object.is_empty());
			object.add("key", Variable(10));
			EXPECT_FALSE(object.is_empty());
		}

		TEST("Contains")
		{
			Object object(10);
			object.add("key", Variable(10));
			EXPECT_TRUE(object.contains("key"));
			EXPECT_FALSE(object.contains("nonexistent"));
		}

		TEST("At")
		{
			Object object(10);
			object.add("key", Variable(10));
			EXPECT_EQUAL(object.at("key").get<Int>(), 10);
			EXPECT_FAILURE(object.at("nonexistent"));
		}

		TEST("At Const")
		{
			Object obj(10);
			obj.add("key", Variable(10));
			Object const& object = obj;
			EXPECT_EQUAL(object.at("key").get<Int>(), 10);
			EXPECT_FAILURE(object.at("nonexistent"));
		}

		TEST("Add")
		{
			Object object(10);
			EXPECT_EQUAL(object.get_size(), 0);
			object.add("key", Variable(10));
			EXPECT_EQUAL(object.get_size(), 1);
			EXPECT_EQUAL(object.at("key").get<Int>(), 10);
		}

		TEST("Set")
		{
			Object object(10);
			EXPECT_FALSE(object.contains("key"));
			object.set("key", Variable(10));
			EXPECT_EQUAL(object.at("key").get<Int>(), 10);
			object.set("key", Variable(20));
			EXPECT_EQUAL(object.at("key").get<Int>(), 20);
		}

		TEST("Remove")
		{
			Object object(10);
			object.add("key", Variable(10));
			EXPECT_EQUAL(object.get_size(), 1);
			object.remove("key");
			EXPECT_EQUAL(object.get_size(), 0);
			EXPECT_FALSE(object.contains("key"));
		}

		TEST("Pack")
		{
			// setup
			Int value0 = 10;
			Size value0Size = sizeof(Int);
			Float value1 = 20.0f;
			Size value1Size = sizeof(Float);
			Byte value2 = 30;
			Size value2Size = sizeof(Byte);
			Object object(3);

			// just value0
			object.add("key0", Variable(value0));
			ConstantContainer container = object.pack();
			EXPECT_EQUAL(container.get_size(), value0Size);
			EXPECT_EQUAL(*static_cast<Int*>(container.get_data()), 10);
			
			// value0 and value1
			object.add("key1", Variable(value1));
			container = object.pack();
			EXPECT_EQUAL(container.get_size(), value0Size + value1Size);
			EXPECT_EQUAL(*static_cast<Int*>(container.get_data()), 10);
			EXPECT_EQUAL(*static_cast<Float*>(static_cast<void*>(static_cast<Byte*>(container.get_data()) + value0Size)), 20.0f);

			// value0, value1 and value2
			object.add("key2", Variable(value2));
			container = object.pack();
			EXPECT_EQUAL(container.get_size(), value0Size + value1Size + value2Size);
			EXPECT_EQUAL(*static_cast<Int*>(container.get_data()), 10);
			EXPECT_EQUAL(*static_cast<Float*>(static_cast<void*>(static_cast<Byte*>(container.get_data()) + value0Size)), 20.0f);
			EXPECT_EQUAL(*static_cast<Byte*>(static_cast<void*>(static_cast<Byte*>(container.get_data()) + value0Size + value1Size)), 30);
		}
	}
}
